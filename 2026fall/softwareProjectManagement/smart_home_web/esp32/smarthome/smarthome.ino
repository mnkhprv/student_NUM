// Ухаалаг гэр: нэг ESP32 дээр бүх зүйл (сенсор, автомат дүрэм, удирдлага, OLED, вэб сервер)
// Library: "DHT sensor library", "Adafruit SSD1306", "Adafruit GFX Library", "ESP32Servo"
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <ESP32Servo.h>

// ---- Өөрчлөх хэсэг ----
const char* WIFI_SSID = "Samsung s27 ultira plas";
const char* WIFI_PASS = "00111111";

// ---- Pin ----
#define DHT_PIN 4
#define PIR_PIN 27
#define LDR_PIN 34     // analog (зөвхөн input pin)
#define TRIG_PIN 5
#define ECHO_PIN 17    // HC-SR04 ECHO нь 5V өгдөг тул резисторын хуваагчаар оруулах
#define SONAR_VCC_PIN 19  // HC-SR04 VCC-г GPIO-оос тэжээж байгаа (HIGH)
#define SONAR_GND_PIN 18  // HC-SR04 GND-г GPIO-оор холбосон (LOW)
#define LED_PIN 25
#define SERVO_PIN 26
#define BUZZER_PIN 33
#define RELAY_PIN 32
// OLED: SDA = 21, SCL = 22

// ---- Автомат дүрмийн хязгаарууд ----
const float TEMP_HIGH = 30;                  // °C, buzzer + relay асна
const float TEMP_LOW = 29;                   // °C, энээс доош болвол унтарна
const int DARK_LIGHT = 30;                   // гэрэл 0-100%, энээс бага бол харанхуй
const float DOOR_DISTANCE = 5;               // см
const unsigned long DOOR_CLOSE_DELAY = 3000; // мс
const unsigned long LED_OFF_DELAY = 300000;  // мс (5 минут)
const int DOOR_OPEN_ANGLE = 90;
const int DOOR_CLOSED_ANGLE = 0;

WebServer server(80);
DHT dht(DHT_PIN, DHT22);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
Servo door;

// сенсорын утгууд
float temperature = NAN, humidity = NAN, distanceCm = -1;
int light = 0, motion = 0;

// төхөөрөмжүүдийн төлөв
bool ledOn = false, doorOpen = false, buzzerOn = false, relayOn = false;
bool autoMode = true;

unsigned long lastMotion = 0, lastNear = 0;
bool tempAlert = false;
String ipText = "";

// температур, чийгшлийн түүх (RAM дотор, 10 секунд тутамд)
const int HIST = 90;
float histT[HIST], histH[HIST];
int histCount = 0, histPos = 0;

// үйл явдлын лог
const int EV = 12;
String evText[EV];
unsigned long evTime[EV];
int evCount = 0, evPos = 0;

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="mn"><head><meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Ухаалаг гэр</title>
<style>
body{font-family:Arial,sans-serif;background:#f2f4f7;margin:0;padding:16px;color:#222}
h1{margin:0 0 12px} h2{margin-top:0;font-size:18px}
.cards{display:flex;gap:12px;flex-wrap:wrap;margin-bottom:12px}
.card{background:#fff;border-radius:8px;padding:12px 16px;min-width:110px;flex:1;box-shadow:0 1px 3px #0002}
.card span{display:block;color:#666;font-size:13px} .card b{font-size:24px}
.box{background:#fff;border-radius:8px;padding:16px;margin-bottom:12px;box-shadow:0 1px 3px #0002}
.alert{background:#d93025;color:#fff;padding:10px 16px;border-radius:8px;margin-bottom:12px;font-weight:bold}
.hint{color:#666;font-size:13px}
table{border-collapse:collapse;width:100%} td{padding:8px;border-bottom:1px solid #eee}
button{padding:6px 12px;border:1px solid #888;border-radius:4px;background:#fff;cursor:pointer}
button:disabled{opacity:.4;cursor:not-allowed}
button.active{background:#1a73e8;color:#fff;border-color:#1a73e8}
.on{color:#188038;font-weight:bold} .off{color:#888}
#events{padding-left:18px;margin:0;font-size:14px} .ev-alert{color:#d93025;font-weight:bold}
canvas{width:100%;height:160px}
</style></head><body>
<h1>Ухаалаг гэр <small id="conn" style="font-size:13px;color:#888"></small></h1>
<div class="cards">
<div class="card"><span>Температур</span><b id="temp">--</b></div>
<div class="card"><span>Чийгшил</span><b id="hum">--</b></div>
<div class="card"><span>Гэрэл</span><b id="light">--</b></div>
<div class="card"><span>Хөдөлгөөн</span><b id="motion">--</b></div>
<div class="card"><span>Зай</span><b id="dist">--</b></div>
</div>
<div id="alert" class="alert" hidden>Анхааруулга: температур 30°C-ээс өндөр байна!</div>
<div class="box"><h2>Удирдлага</h2>
<p>Горим: <button id="m-auto" onclick="send('mode','auto')">Автомат</button>
<button id="m-manual" onclick="send('mode','manual')">Гараар</button></p>
<p id="hint" class="hint">Автомат горимд товчнууд идэвхгүй. Гараар удирдахын тулд "Гараар" горимыг сонго.</p>
<table>
<tr><td>LED</td><td id="s-led"></td><td><button class="ctl" onclick="send('led','on')">Асаах</button> <button class="ctl" onclick="send('led','off')">Унтраах</button></td></tr>
<tr><td>Хаалга (servo)</td><td id="s-door"></td><td><button class="ctl" onclick="send('door','open')">Нээх</button> <button class="ctl" onclick="send('door','closed')">Хаах</button></td></tr>
<tr><td>Сэнс (relay)</td><td id="s-relay"></td><td><button class="ctl" onclick="send('relay','on')">Асаах</button> <button class="ctl" onclick="send('relay','off')">Унтраах</button></td></tr>
<tr><td>Buzzer</td><td id="s-buzzer"></td><td><button class="ctl" onclick="send('buzzer','on')">Асаах</button> <button class="ctl" onclick="send('buzzer','off')">Унтраах</button></td></tr>
</table></div>
<div class="box"><h2>Температур (улаан), чийгшил (цэнхэр)</h2>
<canvas id="chart"></canvas><p id="range" class="hint"></p></div>
<div class="box"><h2>Үйл явдлууд</h2><ul id="events"></ul></div>
<script>
const txt={on:'Асаалттай',off:'Унтраалттай',open:'Нээлттэй',closed:'Хаалттай'};
const $=i=>document.getElementById(i);
function ago(s){return s<60?s+' сек':s<3600?Math.floor(s/60)+' мин':Math.floor(s/3600)+' цаг'}
function line(c,a,col,min,max){
  if(a.length<2)return; c.strokeStyle=col; c.lineWidth=2; c.beginPath();
  a.forEach((v,i)=>{const x=i*(c.canvas.width-1)/(a.length-1);
    const y=c.canvas.height-4-(v-min)/(max-min||1)*(c.canvas.height-8);
    i?c.lineTo(x,y):c.moveTo(x,y)}); c.stroke();
}
function draw(t,h){
  const cv=$('chart'); cv.width=cv.clientWidth; cv.height=cv.clientHeight;
  const c=cv.getContext('2d'); c.clearRect(0,0,cv.width,cv.height);
  if(t.length<2){$('range').textContent='Түүх цуглаж байна...';return}
  const mn=Math.min(...t)-1, mx=Math.max(...t)+1;
  line(c,t,'#d93025',mn,mx); line(c,h,'#1a73e8',0,100);
  $('range').textContent='Температур: '+Math.min(...t)+'-'+Math.max(...t)+'°C, сүүлийн '+Math.round(t.length*10/60)+' минут';
}
function render(d){
  $('conn').textContent='';
  $('temp').textContent=d.temp===null?'--':d.temp+' °C';
  $('hum').textContent=d.hum===null?'--':d.hum+' %';
  $('light').textContent=d.light+' %';
  $('motion').textContent=d.motion?'Илэрсэн':'Байхгүй';
  $('dist').textContent=d.dist>0?d.dist+' см':'--';
  $('alert').hidden=!(d.temp>=30);
  ['led','door','relay','buzzer'].forEach(n=>{const e=$('s-'+n);e.textContent=txt[d[n]];
    e.className=(d[n]=='on'||d[n]=='open')?'on':'off'});
  const a=d.mode=='auto';
  $('m-auto').className=a?'active':''; $('m-manual').className=a?'':'active';
  document.querySelectorAll('.ctl').forEach(b=>b.disabled=a); $('hint').hidden=!a;
  $('events').innerHTML=d.events.map(e=>'<li class="'+(e.alert?'ev-alert':'')+'">'+ago(e.ago)+' өмнө - '+e.msg+'</li>').join('');
  draw(d.histT,d.histH);
}
async function load(){
  try{render(await (await fetch('/api/data')).json())}
  catch(e){$('conn').textContent='(холболт алдаатай)'}
}
async function send(t,v){
  const r=await fetch('/api/cmd?target='+t+'&value='+v,{method:'POST'});
  if(!r.ok)alert(await r.text()); load();
}
load(); setInterval(load,2000);
</script></body></html>
)rawliteral";

// ---------- лог, төлөв өөрчлөх ----------

void addEvent(String msg, bool isAlert = false) {
  evText[evPos] = (isAlert ? "!" : "") + msg;
  evTime[evPos] = millis();
  evPos = (evPos + 1) % EV;
  if (evCount < EV) evCount++;
  Serial.println(msg);
}

void setLed(bool on, String why) {
  if (ledOn == on) return;
  ledOn = on;
  digitalWrite(LED_PIN, on);
  addEvent(String("LED ") + (on ? "асав" : "унтарлаа") + " (" + why + ")");
}

void setDoor(bool open, String why) {
  if (doorOpen == open) return;
  doorOpen = open;
  door.write(open ? DOOR_OPEN_ANGLE : DOOR_CLOSED_ANGLE);
  addEvent(String("Хаалга ") + (open ? "нээгдлээ" : "хаагдлаа") + " (" + why + ")");
}

void setBuzzer(bool on, String why) {
  if (buzzerOn == on) return;
  buzzerOn = on;
  digitalWrite(BUZZER_PIN, on);
  addEvent(String("Buzzer ") + (on ? "асав" : "унтарлаа") + " (" + why + ")");
}

void setRelay(bool on, String why) {
  if (relayOn == on) return;
  relayOn = on;
  digitalWrite(RELAY_PIN, on);  // relay модуль LOW-ээр асдаг бол эсрэгээр нь болго
  addEvent(String("Сэнс ") + (on ? "асав" : "унтарлаа") + " (" + why + ")");
}

// ---------- сенсор ----------

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long t = pulseIn(ECHO_PIN, HIGH, 30000);
  if (t == 0) return -1;
  return t * 0.0343 / 2;
}

// 0-100% (өндөр = гэрэлтэй). Модулийн төрлөөс шалтгаалж эсрэгээр байвал 100 - x болго
int readLight() {
  return 100 - analogRead(LDR_PIN) * 100 / 4095;
}

// ---------- автомат дүрмүүд ----------

void applyRules() {
  unsigned long now = millis();
  if (motion == 1) lastMotion = now;

  bool tempValid = !isnan(temperature);
  if (tempValid && temperature >= TEMP_HIGH && !tempAlert) {
    tempAlert = true;
    addEvent("Температур " + String(temperature, 1) + "°C хүрлээ", true);
  } else if (tempValid && temperature <= TEMP_LOW) {
    tempAlert = false;
  }

  if (!autoMode) return;

  // Харанхуй + хөдөлгөөн -> LED, 5 минут хөдөлгөөнгүй бол унтарна
  if (motion == 1 && light < DARK_LIGHT) {
    setLed(true, "харанхуй + хөдөлгөөн");
  } else if (motion == 0 && now - lastMotion > LED_OFF_DELAY) {
    setLed(false, "5 минут хөдөлгөөнгүй");
  }

  // 5 см-ээс ойр объект -> хаалга нээгдэнэ
  if (distanceCm > 0 && distanceCm < DOOR_DISTANCE) {
    lastNear = now;
    setDoor(true, "объект " + String(distanceCm, 1) + " см");
  } else if (doorOpen && now - lastNear > DOOR_CLOSE_DELAY) {
    setDoor(false, "объект алга болсон");
  }

  // Температур 30°C-ээс дээш -> buzzer + relay
  if (tempValid) {
    if (temperature >= TEMP_HIGH) {
      setBuzzer(true, "температур өндөр");
      setRelay(true, "температур өндөр");
    } else if (temperature <= TEMP_LOW) {
      setBuzzer(false, "температур буурсан");
      setRelay(false, "температур буурсан");
    }
  }
}

// ---------- вэб сервер ----------

void handleRoot() {
  server.send_P(200, "text/html; charset=utf-8", PAGE);
}

void handleData() {
  String j = "{";
  j += "\"temp\":" + (isnan(temperature) ? String("null") : String(temperature, 1));
  j += ",\"hum\":" + (isnan(humidity) ? String("null") : String(humidity, 1));
  j += ",\"light\":" + String(light);
  j += ",\"motion\":" + String(motion);
  j += ",\"dist\":" + String(distanceCm, 1);
  j += ",\"led\":\"" + String(ledOn ? "on" : "off") + "\"";
  j += ",\"door\":\"" + String(doorOpen ? "open" : "closed") + "\"";
  j += ",\"buzzer\":\"" + String(buzzerOn ? "on" : "off") + "\"";
  j += ",\"relay\":\"" + String(relayOn ? "on" : "off") + "\"";
  j += ",\"mode\":\"" + String(autoMode ? "auto" : "manual") + "\"";

  // түүх (хуучнаас шинэ рүү)
  String t = "[", h = "[";
  for (int i = 0; i < histCount; i++) {
    int k = (histPos - histCount + i + HIST) % HIST;
    if (i > 0) { t += ","; h += ","; }
    t += String(histT[k], 1);
    h += String(histH[k], 1);
  }
  j += ",\"histT\":" + t + "],\"histH\":" + h + "]";

  // үйл явдлууд (шинэ нь эхэнд)
  j += ",\"events\":[";
  for (int i = 0; i < evCount; i++) {
    int k = (evPos - 1 - i + EV) % EV;
    String m = evText[k];
    bool isAlert = m.startsWith("!");
    if (isAlert) m = m.substring(1);
    if (i > 0) j += ",";
    j += "{\"ago\":" + String((millis() - evTime[k]) / 1000) + ",\"alert\":" + (isAlert ? "true" : "false") +
         ",\"msg\":\"" + m + "\"}";
  }
  j += "]}";
  server.send(200, "application/json", j);
}

void handleCmd() {
  String target = server.arg("target");
  String value = server.arg("value");

  if (target == "mode" && (value == "auto" || value == "manual")) {
    autoMode = (value == "auto");
    addEvent(String("Горим: ") + (autoMode ? "автомат" : "гараар"));
    server.send(200, "text/plain", "ok");
    return;
  }
  if (autoMode) {
    server.send(409, "text/plain", "Автомат горимд гараар удирдах боломжгүй");
    return;
  }

  bool on = (value == "on");
  if (target == "led" && (value == "on" || value == "off")) setLed(on, "гараар");
  else if (target == "buzzer" && (value == "on" || value == "off")) setBuzzer(on, "гараар");
  else if (target == "relay" && (value == "on" || value == "off")) setRelay(on, "гараар");
  else if (target == "door" && (value == "open" || value == "closed")) setDoor(value == "open", "гараар");
  else {
    server.send(400, "text/plain", "Буруу команд");
    return;
  }
  server.send(200, "text/plain", "ok");
}

// ---------- WiFi, OLED ----------

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 40) {
    delay(500);
    tries++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    ipText = WiFi.localIP().toString();
  } else {
    // hotspot олдсонгүй бол өөрөө WiFi үүсгэнэ
    WiFi.mode(WIFI_AP);
    WiFi.softAP("SmartHome");
    ipText = WiFi.softAPIP().toString();
  }
  Serial.println("Хаяг: http://" + ipText);
}

void showOled() {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.print("T: ");
  if (isnan(temperature)) oled.print("--"); else oled.print(temperature, 1);
  oled.print(" H: ");
  if (isnan(humidity)) oled.println("--"); else oled.println(humidity, 0);
  oled.print("Light:"); oled.print(light); oled.print("% Mot:"); oled.println(motion ? "Y" : "n");
  oled.print("LED:"); oled.print(ledOn ? "on" : "off");
  oled.print(" Door:"); oled.println(doorOpen ? "open" : "shut");
  oled.print("Fan:"); oled.print(relayOn ? "on" : "off");
  oled.print(" Buz:"); oled.println(buzzerOn ? "on" : "off");
  oled.print("Mode:"); oled.println(autoMode ? "auto" : "manual");
  oled.println(ipText);
  oled.display();
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(SONAR_VCC_PIN, OUTPUT);
  pinMode(SONAR_GND_PIN, OUTPUT);
  digitalWrite(SONAR_VCC_PIN, HIGH);
  digitalWrite(SONAR_GND_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  door.attach(SERVO_PIN);
  door.write(DOOR_CLOSED_ANGLE);
  dht.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  connectWifi();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/data", HTTP_GET, handleData);
  server.on("/api/cmd", HTTP_POST, handleCmd);
  server.begin();
  addEvent("Систем эхэллээ");
}

unsigned long lastSensor = 0, lastDht = 0, lastHist = 0, lastOled = 0;

void loop() {
  server.handleClient();
  unsigned long now = millis();

  // DHT22-г 2 секунд тутамд уншина
  if (now - lastDht >= 2000) {
    lastDht = now;
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t) && !isnan(h)) {
      temperature = t;
      humidity = h;
    }
  }

  // бусад сенсор, дүрэм 0.25 секунд тутам (хаалга хурдан хариу өгөхөөр)
  if (now - lastSensor >= 250) {
    lastSensor = now;
    light = readLight();
    motion = digitalRead(PIR_PIN);
    distanceCm = readDistance();
    applyRules();
  }

  if (now - lastOled >= 1000) {
    lastOled = now;
    showOled();
  }

  // түүхэнд 10 секунд тутам хадгална
  if (now - lastHist >= 10000 && !isnan(temperature)) {
    lastHist = now;
    histT[histPos] = temperature;
    histH[histPos] = humidity;
    histPos = (histPos + 1) % HIST;
    if (histCount < HIST) histCount++;
  }
}
