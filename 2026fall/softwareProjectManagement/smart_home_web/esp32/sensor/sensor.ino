// Сенсорын ESP32: PIR, LDR, DHT22, HC-SR04 уншаад серверт илгээнэ, OLED дээр харуулна
// Library: "DHT sensor library" (Adafruit), "Adafruit SSD1306", "Adafruit GFX"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ---- Өөрчлөх хэсэг ----
const char* WIFI_SSID = "Samsung s27 ultira plas";
const char* WIFI_PASS = "00111111";
const char* SERVER_URL = "http://10.177.250.225:3000/api/readings";  // компьютерийн IP

// ---- Pin ----
#define DHT_PIN 4
#define PIR_PIN 27
#define LDR_PIN 34    // analog (зөвхөн input pin)
#define TRIG_PIN 5
#define ECHO_PIN 18   // HC-SR04 ECHO нь 5V өгдөг тул резисторын хуваагчаар оруулах
// OLED: SDA = 21, SCL = 22

DHT dht(DHT_PIN, DHT22);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long t = pulseIn(ECHO_PIN, HIGH, 30000);  // 30 мс хүртэл хүлээнэ
  if (t == 0) return -1;                     // echo ирээгүй
  return t * 0.0343 / 2;
}

// 0-100% (өндөр = гэрэлтэй). Модулийн төрлөөс шалтгаалж эсрэгээр байвал 100 - x болго
int readLight() {
  int raw = analogRead(LDR_PIN);             // 0..4095
  return 100 - raw * 100 / 4095;
}

void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 30) {
    delay(500);
    tries++;
  }
}

void showOled(float t, float h, int light, int motion, bool wifiOk) {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.print("T: "); oled.print(t, 1); oled.println(" C");
  oled.print("H: "); oled.print(h, 0); oled.println(" %");
  oled.print("Light: "); oled.print(light); oled.println(" %");
  oled.print("Motion: "); oled.println(motion ? "YES" : "no");
  oled.print("WiFi: "); oled.println(wifiOk ? "OK" : "ERROR");
  oled.display();
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  dht.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  connectWifi();
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int light = readLight();
  int motion = digitalRead(PIR_PIN);
  float dist = readDistance();

  // DHT22 уншиж чадаагүй бол өмнөх утгыг ашиглахгүй, илгээхгүй
  bool dhtOk = !(isnan(t) || isnan(h));

  if (WiFi.status() != WL_CONNECTED) {
    connectWifi();
  }
  bool wifiOk = (WiFi.status() == WL_CONNECTED);

  if (wifiOk) {
    String json = "{\"light\":" + String(light) +
                  ",\"motion\":" + String(motion) +
                  ",\"distance_cm\":" + String(dist, 1);
    if (dhtOk) {
      json += ",\"temperature\":" + String(t, 1) + ",\"humidity\":" + String(h, 1);
    }
    json += "}";

    HTTPClient http;
    http.begin(SERVER_URL);
    http.addHeader("Content-Type", "application/json");
    int code = http.POST(json);
    Serial.println(json + " -> " + String(code));
    http.end();
  }

  showOled(dhtOk ? t : 0, dhtOk ? h : 0, light, motion, wifiOk);
  delay(1000);
}
