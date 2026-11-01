-- ESP32 төхөөрөмжүүд
CREATE TABLE IF NOT EXISTS devices (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL UNIQUE,
  type TEXT NOT NULL,              -- 'sensor' эсвэл 'actuator'
  last_seen TEXT
);

-- Сенсорын түүх
CREATE TABLE IF NOT EXISTS sensor_readings (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  device_id INTEGER,
  temperature REAL,
  humidity REAL,
  light INTEGER,
  motion INTEGER,                  -- 0 / 1
  distance_cm REAL,
  created_at TEXT DEFAULT (datetime('now', 'localtime')),
  FOREIGN KEY (device_id) REFERENCES devices(id)
);

-- Одоогийн төлөв (led, servo, buzzer, relay)
CREATE TABLE IF NOT EXISTS device_states (
  name TEXT PRIMARY KEY,
  state TEXT NOT NULL,
  updated_at TEXT DEFAULT (datetime('now', 'localtime'))
);

-- Вэбээс өгсөн команд
CREATE TABLE IF NOT EXISTS commands (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  target TEXT NOT NULL,            -- led, servo, relay
  value TEXT NOT NULL,             -- on / off / open / close
  done INTEGER DEFAULT 0,
  created_at TEXT DEFAULT (datetime('now', 'localtime'))
);

-- Үйл явдлын лог
CREATE TABLE IF NOT EXISTS events (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  type TEXT NOT NULL,
  message TEXT NOT NULL,
  created_at TEXT DEFAULT (datetime('now', 'localtime'))
);

-- Эхний төлөвүүд
INSERT OR IGNORE INTO device_states (name, state) VALUES
  ('led', 'off'),
  ('servo', 'closed'),
  ('buzzer', 'off'),
  ('relay', 'off'),
  ('mode', 'auto');

INSERT OR IGNORE INTO devices (name, type) VALUES
  ('esp32_sensor', 'sensor'),
  ('esp32_actuator', 'actuator');
