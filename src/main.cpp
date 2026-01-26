#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define LED_PIN 2
#define MIN_CM 10
#define MAX_CM 70

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(LED_PIN, OUTPUT);

  Serial.println("VL53L0X Baslatiliyor...");

  if (!lox.begin()) {
    Serial.println("Sensor bulunamadi!");
    while (1);
  }

  Serial.println("Sensor hazir.");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 3) {

    int mesafe_cm = measure.RangeMilliMeter / 10;

    Serial.print("Mesafe: ");
    Serial.print(mesafe_cm);
    Serial.println(" cm");

    if (mesafe_cm > MIN_CM && mesafe_cm < MAX_CM) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }

  } else {
    Serial.println("Olcum disi");
    digitalWrite(LED_PIN, LOW);
  }

  delay(500);

}