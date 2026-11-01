const express = require('express');
const { DatabaseSync } = require('node:sqlite');
const fs = require('fs');
const path = require('path');

const PORT = 3000;

// автомат дүрмийн хязгаарууд
const TEMP_HIGH = 30;          // °C, buzzer + relay асна
const TEMP_LOW = 29;           // °C, энээс доош болвол унтарна
const DARK_LIGHT = 30;         // гэрэл 0-100%, энээс бага бол харанхуй
const DOOR_DISTANCE = 5;       // см
const DOOR_CLOSE_DELAY = 3000; // мс, объект алга болоод хаалга хаагдах хугацаа
const LED_OFF_DELAY = 5 * 60 * 1000; // мс, хөдөлгөөнгүй 5 минутын дараа LED унтарна

const VALID_VALUES = {
  led: ['on', 'off'],
  servo: ['open', 'closed'],
  buzzer: ['on', 'off'],
  relay: ['on', 'off'],
  mode: ['auto', 'manual'],
};

// database нээж, хүснэгтүүдийг үүсгэнэ
const db = new DatabaseSync(path.join(__dirname, 'smarthome.db'));
db.exec(fs.readFileSync(path.join(__dirname, 'schema.sql'), 'utf8'));

const app = express();
app.use(express.json());
app.use(express.static(path.join(__dirname, '..', 'frontend')));
app.use('/vendor', express.static(path.join(__dirname, 'node_modules', 'chart.js', 'dist')));

// ---------- туслах функцууд ----------

function logEvent(type, message) {
  db.prepare('INSERT INTO events (type, message) VALUES (?, ?)').run(type, message);
}

function getState(name) {
  const row = db.prepare('SELECT state FROM device_states WHERE name = ?').get(name);
  return row ? row.state : null;
}

// төлөв өөрчлөх. Өөрчлөгдсөн бол команд болон event хадгална
function setState(name, state, reason) {
  if (getState(name) === state) return false;
  db.prepare("UPDATE device_states SET state = ?, updated_at = datetime('now', 'localtime') WHERE name = ?")
    .run(state, name);
  if (name !== 'mode') {
    db.prepare('INSERT INTO commands (target, value) VALUES (?, ?)').run(name, state);
  }
  logEvent('action', name + ' -> ' + state + ' (' + reason + ')');
  return true;
}

function touchDevice(name) {
  db.prepare("UPDATE devices SET last_seen = datetime('now', 'localtime') WHERE name = ?").run(name);
}

// ---------- автомат дүрмүүд ----------

let lastMotion = 0;
let lastNear = 0;
let tempAlertOn = false;

function applyRules(r) {
  const now = Date.now();

  if (r.motion === 1) lastMotion = now;

  // температурын анхааруулга (mode-оос үл хамааран лог хийнэ)
  if (r.temperature != null && r.temperature >= TEMP_HIGH && !tempAlertOn) {
    tempAlertOn = true;
    logEvent('alert', 'Температур ' + r.temperature + '°C хүрлээ');
  } else if (r.temperature != null && r.temperature <= TEMP_LOW) {
    tempAlertOn = false;
  }

  if (getState('mode') !== 'auto') return;

  // 1.2 Харанхуй + хөдөлгөөн -> LED асна, 5 минут хөдөлгөөнгүй бол унтарна
  const dark = r.light != null && r.light < DARK_LIGHT;
  if (r.motion === 1 && dark) {
    setState('led', 'on', 'харанхуй + хөдөлгөөн');
  } else if (r.motion !== 1 && now - lastMotion > LED_OFF_DELAY) {
    setState('led', 'off', '5 минут хөдөлгөөнгүй');
  }

  // 1.3 5 см-ээс ойр объект -> хаалга нээгдэнэ
  if (r.distance_cm != null && r.distance_cm > 0 && r.distance_cm < DOOR_DISTANCE) {
    lastNear = now;
    setState('servo', 'open', 'объект ' + r.distance_cm + ' см');
  } else if (getState('servo') === 'open' && now - lastNear > DOOR_CLOSE_DELAY) {
    setState('servo', 'closed', 'объект алга болсон');
  }

  // 1.4 Температур 30°C-ээс дээш -> buzzer + relay (сэнс)
  if (r.temperature != null) {
    if (r.temperature >= TEMP_HIGH) {
      setState('buzzer', 'on', 'температур ' + r.temperature + '°C');
      setState('relay', 'on', 'температур ' + r.temperature + '°C');
    } else if (r.temperature <= TEMP_LOW) {
      setState('buzzer', 'off', 'температур буурсан');
      setState('relay', 'off', 'температур буурсан');
    }
  }
}

// ---------- сенсорын ESP32 ----------

// POST /api/readings  {temperature, humidity, light, motion, distance_cm}
app.post('/api/readings', (req, res) => {
  const b = req.body || {};
  const num = (v) => (v === undefined || v === null || isNaN(Number(v)) ? null : Number(v));

  const r = {
    temperature: num(b.temperature),
    humidity: num(b.humidity),
    light: num(b.light),
    motion: num(b.motion) === 1 ? 1 : 0,
    distance_cm: num(b.distance_cm),
  };
  if (r.temperature === null && r.humidity === null && r.light === null && r.distance_cm === null) {
    return res.status(400).json({ error: 'Сенсорын утга алга' });
  }

  const device = db.prepare('SELECT id FROM devices WHERE name = ?').get('esp32_sensor');
  db.prepare(`INSERT INTO sensor_readings (device_id, temperature, humidity, light, motion, distance_cm)
              VALUES (?, ?, ?, ?, ?, ?)`)
    .run(device.id, r.temperature, r.humidity, r.light, r.motion, r.distance_cm);
  touchDevice('esp32_sensor');

  applyRules(r);
  res.json({ ok: true });
});

// ---------- гүйцэтгэгч ESP32 ----------

// GET /api/actuators  -> энгийн текст (ESP32 дээр parse хийхэд амар)
// led=1 servo=1 buzzer=0 relay=0
app.get('/api/actuators', (req, res) => {
  const get = (n) => getState(n);
  const text =
    'led=' + (get('led') === 'on' ? 1 : 0) + '\n' +
    'servo=' + (get('servo') === 'open' ? 1 : 0) + '\n' +
    'buzzer=' + (get('buzzer') === 'on' ? 1 : 0) + '\n' +
    'relay=' + (get('relay') === 'on' ? 1 : 0) + '\n';
  touchDevice('esp32_actuator');
  db.prepare('UPDATE commands SET done = 1 WHERE done = 0').run();
  res.type('text/plain').send(text);
});

// ---------- вэб хуудас ----------

app.get('/api/readings/latest', (req, res) => {
  const row = db.prepare('SELECT * FROM sensor_readings ORDER BY id DESC LIMIT 1').get();
  res.json(row || null);
});

// минут тутамд дундажлан, графикт зориулна
app.get('/api/readings', (req, res) => {
  let hours = Number(req.query.hours) || 1;
  if (hours < 1) hours = 1;
  if (hours > 24) hours = 24;
  const rows = db.prepare(`
    SELECT strftime('%Y-%m-%d %H:%M', created_at) AS time,
           ROUND(AVG(temperature), 1) AS temperature,
           ROUND(AVG(humidity), 1) AS humidity,
           ROUND(AVG(light), 0) AS light
    FROM sensor_readings
    WHERE created_at >= datetime('now', 'localtime', ?)
    GROUP BY time ORDER BY time`).all('-' + hours + ' hours');
  res.json(rows);
});

app.get('/api/state', (req, res) => {
  const obj = {};
  db.prepare('SELECT name, state FROM device_states').all().forEach((r) => { obj[r.name] = r.state; });
  res.json(obj);
});

// POST /api/commands  {target:'led', value:'on'}
app.post('/api/commands', (req, res) => {
  const { target, value } = req.body || {};
  if (!VALID_VALUES[target] || !VALID_VALUES[target].includes(value)) {
    return res.status(400).json({ error: 'Буруу команд' });
  }
  if (target !== 'mode' && getState('mode') === 'auto') {
    return res.status(409).json({ error: 'Автомат горимд гараар удирдах боломжгүй' });
  }
  setState(target, value, 'гараар');
  res.json({ ok: true });
});

app.get('/api/events', (req, res) => {
  const rows = db.prepare('SELECT type, message, created_at FROM events ORDER BY id DESC LIMIT 20').all();
  res.json(rows);
});

app.get('/api/devices', (req, res) => {
  const rows = db.prepare(`
    SELECT name, type, last_seen,
           (strftime('%s', 'now', 'localtime') - strftime('%s', last_seen)) < 15 AS online
    FROM devices`).all();
  res.json(rows);
});

// өнөөдрийн дүн
app.get('/api/summary', (req, res) => {
  const row = db.prepare(`
    SELECT COUNT(*) AS count,
           ROUND(MIN(temperature), 1) AS temp_min,
           ROUND(MAX(temperature), 1) AS temp_max,
           ROUND(AVG(temperature), 1) AS temp_avg,
           ROUND(AVG(humidity), 1) AS humidity_avg
    FROM sensor_readings WHERE date(created_at) = date('now', 'localtime')`).get();
  res.json(row);
});

app.get('/api/health', (req, res) => {
  res.json({ status: 'ok' });
});

// 7 хоногоос хуучин өгөгдлийг устгана
function cleanOld() {
  db.prepare("DELETE FROM sensor_readings WHERE created_at < datetime('now', 'localtime', '-7 days')").run();
}
cleanOld();
setInterval(cleanOld, 60 * 60 * 1000);

app.listen(PORT, '0.0.0.0', () => {
  console.log('Server ажиллаж байна: http://localhost:' + PORT);
});
