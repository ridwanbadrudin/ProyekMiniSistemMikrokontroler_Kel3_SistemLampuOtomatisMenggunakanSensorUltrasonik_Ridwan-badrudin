/*
Menampilkan jarak cm dan in ke dalam lcd
LED akan menyala jika jarak kurang dari 100cm
*/

#include <LiquidCrystal_I2C.h>
#define ECHO_PIN 2
#define TRIG_PIN 3
#define LED_BUILTIN 13

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd.begin(20, 4);     // Ukuran layar LCD
  lcd.init();           // Inisialisasi LCD
  lcd.backlight();
  lcd.print("--> Distance <--");
  delay(3000);
  lcd.clear();
}

float jarak_cm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

float jarak_in() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return (duration * 0.034 / 2) / 2.54;
}

void loop() {
  float cm = jarak_cm();
  float IN = jarak_in();
  bool isNearby = cm < 100;
  digitalWrite(LED_BUILTIN, isNearby);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("inches");
  lcd.setCursor(12, 0);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print(IN, 1);
  lcd.setCursor(11, 1);
  lcd.print(cm, 1);

  delay(1000);
}
