const stateText = {
  on: 'Асаалттай', off: 'Унтраалттай', open: 'Нээлттэй', closed: 'Хаалттай',
};

let chart = null;

async function getJson(url) {
  const res = await fetch(url);
  return res.json();
}

// хамгийн сүүлийн сенсорын утга
async function loadLatest() {
  const r = await getJson('/api/readings/latest');
  if (!r) return;
  document.getElementById('temp').textContent = r.temperature !== null ? r.temperature + ' °C' : '--';
  document.getElementById('hum').textContent = r.humidity !== null ? r.humidity + ' %' : '--';
  document.getElementById('light').textContent = r.light !== null ? r.light + ' %' : '--';
  document.getElementById('motion').textContent = r.motion ? 'Илэрсэн' : 'Байхгүй';
  document.getElementById('dist').textContent =
    r.distance_cm !== null && r.distance_cm > 0 ? r.distance_cm + ' см' : '--';
  document.getElementById('alert').hidden = !(r.temperature >= 30);
}

// төхөөрөмжүүдийн төлөв, горим
async function loadState() {
  const s = await getJson('/api/state');
  ['led', 'servo', 'relay', 'buzzer'].forEach((name) => {
    const el = document.getElementById('st-' + name);
    el.textContent = stateText[s[name]];
    el.className = (s[name] === 'on' || s[name] === 'open') ? 'on' : 'off';
  });

  const auto = s.mode === 'auto';
  document.getElementById('mode-auto').className = auto ? 'active' : '';
  document.getElementById('mode-manual').className = auto ? '' : 'active';
  document.querySelectorAll('.ctl').forEach((b) => { b.disabled = auto; });
  document.getElementById('hint').hidden = !auto;
}

async function loadDevices() {
  const list = await getJson('/api/devices');
  document.getElementById('devices').innerHTML = list.map((d) =>
    '<span class="dev"><i class="' + (d.online ? 'up' : 'down') + '"></i>' + d.name + '</span>'
  ).join('');
}

async function loadEvents() {
  const list = await getJson('/api/events');
  document.getElementById('events').innerHTML = list.map((e) =>
    '<li class="' + (e.type === 'alert' ? 'alert-event' : '') + '">' + e.created_at + ' - ' + e.message + '</li>'
  ).join('');
}

async function loadSummary() {
  const s = await getJson('/api/summary');
  document.getElementById('summary').textContent = s.count
    ? 'Өнөөдөр: доод ' + s.temp_min + '°C, дээд ' + s.temp_max + '°C, дундаж ' + s.temp_avg +
      '°C, чийгшил дундаж ' + s.humidity_avg + '%'
    : '';
}

async function loadChart() {
  const rows = await getJson('/api/readings?hours=1');
  const labels = rows.map((r) => r.time.slice(11));
  const temps = rows.map((r) => r.temperature);
  const hums = rows.map((r) => r.humidity);

  if (!chart) {
    chart = new Chart(document.getElementById('chart'), {
      type: 'line',
      data: {
        labels: labels,
        datasets: [
          { label: 'Температур (°C)', data: temps, borderColor: '#d93025', tension: 0.2 },
          { label: 'Чийгшил (%)', data: hums, borderColor: '#1a73e8', tension: 0.2 },
        ],
      },
    });
  } else {
    chart.data.labels = labels;
    chart.data.datasets[0].data = temps;
    chart.data.datasets[1].data = hums;
    chart.update();
  }
}

// товч дарахад команд илгээнэ
async function send(target, value) {
  const res = await fetch('/api/commands', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ target: target, value: value }),
  });
  if (!res.ok) {
    const err = await res.json();
    alert(err.error);
  }
  loadState();
  loadEvents();
}

function refresh() {
  loadLatest().catch(console.error);
  loadState().catch(console.error);
  loadDevices().catch(console.error);
  loadEvents().catch(console.error);
}

refresh();
loadChart();
loadSummary();
setInterval(refresh, 3000);
setInterval(() => { loadChart(); loadSummary(); }, 30000);
