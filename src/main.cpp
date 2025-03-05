#include <Arduino.h>

// Definisikan pin untuk tombol dan LED
const int button1Pin = 22; // Tombol 1
const int button2Pin = 21; // Tombol 2
const int button3Pin = 19; // Tombol 3

const int led1Pin = 12;    // LED merah
const int led2Pin = 14;    // LED kuning
const int led3Pin = 13;    // LED hijau

// Variabel debounce
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
const unsigned long debounceDelay = 50;

// Variabel status tombol sebelumnya
int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;

// Fungsi untuk membuat LED berkedip non-blocking
void blinkLED(int pin, int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
  }
}

void setup() {
  // Inisialisasi pin tombol sebagai input dengan pull-up
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  // Inisialisasi pin LED sebagai output
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  // Matikan semua LED pada awal
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
}

void loop() {
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);

  unsigned long currentMillis = millis();

  // Cek Tombol 1
  if (button1State == LOW && lastButton1State == HIGH && (currentMillis - lastDebounceTime1 > debounceDelay)) {
    lastDebounceTime1 = currentMillis;
    blinkLED(led1Pin, 5, 500);
  }
  lastButton1State = button1State;

  // Cek Tombol 2
  if (button2State == LOW && lastButton2State == HIGH && (currentMillis - lastDebounceTime2 > debounceDelay)) {
    lastDebounceTime2 = currentMillis;
    for (int i = 0; i < 5; i++) {
      digitalWrite(led1Pin, HIGH); 
      digitalWrite(led3Pin, LOW);
      delay(500);
      digitalWrite(led1Pin, LOW);
      digitalWrite(led3Pin, HIGH);
      delay(500);
    }
    digitalWrite(led1Pin, LOW);
    digitalWrite(led3Pin, LOW);
  }
  lastButton2State = button2State;

  // Cek Tombol 3
  if (button3State == LOW && lastButton3State == HIGH && (currentMillis - lastDebounceTime3 > debounceDelay)) {
    lastDebounceTime3 = currentMillis;
    for (int i = 0; i < 5; i++) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);
      digitalWrite(led3Pin, LOW);
      delay(500);

      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, HIGH);
      delay(500);

      digitalWrite(led2Pin, LOW);
      digitalWrite(led3Pin, HIGH);
      delay(500);

      digitalWrite(led3Pin, LOW);
    }
  }
  lastButton3State = button3State;
}
