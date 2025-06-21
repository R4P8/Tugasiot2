#define BLYNK_TEMPLATE_ID "TMPL6p0FDTVJl"
#define BLYNK_TEMPLATE_NAME "ESP32WATER"
#define BLYNK_AUTH_TOKEN "sWa5g-ivAel25JPdFa_iJQhA5sHuEAYx"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin setup
const int LED1 = 26; // Hijau
const int LED2 = 27; // Merah
const int pot1Pin = 33;
const int pot2Pin = 32;
const int pot3Pin = 35;

// WiFi credentials
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Sensor values
int val1 = 0;
int val2 = 0;
int val3 = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup started");

  // LED setup
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal, lanjut tanpa OLED");
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("ESP32 Ready!");
    display.display();
  }

  delay(1000);

  // WiFi connection
  WiFi.begin(ssid, pass);
  Serial.print("Menghubungkan WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung");

  // Connect to Blynk (non-blocking)
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect(5000);  // timeout 5 detik

  // Display success
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi & Blynk Terhubung!");
  display.display();
  delay(1000);

  Serial.println("WiFi & Blynk Terhubung...");
  Serial.println("==============================");
}

void loop() {
  Blynk.run();

  // Baca nilai potensiometer
  val1 = analogRead(pot1Pin);
  val2 = analogRead(pot2Pin);
  val3 = analogRead(pot3Pin);

  // Kirim data ke Blynk
  Blynk.virtualWrite(V0, val1);
  Blynk.virtualWrite(V1, val2);
  Blynk.virtualWrite(V2, val3);

  // Tampilkan di OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Pot1: "); display.println(val1);
  display.print("Pot2: "); display.println(val2);
  display.print("Pot3: "); display.println(val3);

  // Cek status aman / tidak aman
  if (val1 < 2000 && val2 < 2000 && val3 < 2000) {
    digitalWrite(LED1, HIGH);  // Hijau ON
    digitalWrite(LED2, LOW);   // Merah OFF
    display.println("Status: AMAN");

    Serial.println("[STATUS] Semua sensor di bawah ambang batas.");
    Serial.println("LED Hijau: ON | LED Merah: OFF | Status: AMAN");
  } else {
    digitalWrite(LED1, LOW);   // Hijau OFF
    digitalWrite(LED2, HIGH);  // Merah ON
    display.println("Status: TIDAK AMAN");

    Serial.println("[STATUS] Sensor melebihi ambang batas!");
    Serial.println("LED Hijau: OFF | LED Merah: ON | Status: TIDAK AMAN");
  }

  display.display(); // Update OLED

  Serial.println("------------------------------");
delay(500);
}