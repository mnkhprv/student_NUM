// Гүйцэтгэгч ESP32: серверээс төлөв татаж LED, servo, buzzer, relay удирдана
// Library: "ESP32Servo"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

// ---- Өөрчлөх хэсэг ----
const char* WIFI_SSID = "Samsung s27 ultira plas";
const char* WIFI_PASS = "WIFI_NUUTS_UG";
const char* SERVER_URL = "http://10.177.250.225:3000/api/actuators";  // компьютерийн IP

// ---- Pin ----
#define LED_PIN 25
#define SERVO_PIN 26
#define BUZZER_PIN 33
#define RELAY_PIN 32

const int DOOR_OPEN_ANGLE = 90;
const int DOOR_CLOSED_ANGLE = 0;

Servo door;

void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 30) {
    delay(500);
    tries++;
  }
}

// "led=1\nservo=0\n..." гэсэн текстээс нэг утга авна
int getValue(String text, String key) {
  int i = text.indexOf(key + "=");
  if (i < 0) return 0;
  return text.charAt(i + key.length() + 1) == '1' ? 1 : 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  door.attach(SERVO_PIN);
  door.write(DOOR_CLOSED_ANGLE);
  connectWifi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWifi();
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(SERVER_URL);
    int code = http.GET();
    if (code == 200) {
      String text = http.getString();
      digitalWrite(LED_PIN, getValue(text, "led"));
      digitalWrite(BUZZER_PIN, getValue(text, "buzzer"));
      digitalWrite(RELAY_PIN, getValue(text, "relay"));  // relay модуль LOW-ээр асдаг бол эсрэгээр нь болго
      door.write(getValue(text, "servo") ? DOOR_OPEN_ANGLE : DOOR_CLOSED_ANGLE);
    } else {
      Serial.println("Серверээс хариу ирсэнгүй: " + String(code));
    }
    http.end();
  }
  delay(500);
}
