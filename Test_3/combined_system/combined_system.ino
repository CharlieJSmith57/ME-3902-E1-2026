/*  Test 3 - Combined system
    Ultrasonic (HC-SR04) + VL53L0X Time-of-Flight + IR detector + SSD1306 OLED
    Target board: Arduino Nano

    I2C devices (OLED + ToF) share pins A4 (SDA) and A5 (SCL).
    Ultrasonic uses D3/D4, IR uses D2.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Adafruit_VL53L0X.h"

// ---- OLED ----
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_ADDR     0x3C
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---- Time-of-Flight ----
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// ---- Ultrasonic (HC-SR04) ----
const int trigPin = 3;          // set these to match how you wired it
const int echoPin = 4;

// ---- IR detector ----
const int irPin = 2;            // digital OUT from the IR module

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT);

 if (!display.begin(OLED_ADDR, true)) {
    Serial.println(F("OLED not found"));
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  if (!lox.begin()) {
    Serial.println(F("VL53L0X not found"));
  }

  // CSV header - printed ONCE so CoolTerm captures clean columns
  Serial.println("Time_ms,Ultrasonic_cm,ToF_cm,IR_detected");
}

float readUltrasonicCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // 30 ms timeout (~5 m) so a missing echo doesn't freeze the whole loop
  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;          // -1 = no echo / out of range
  return duration * 0.0343 / 2.0;        // cm
}

float readToFCm() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  if (measure.RangeStatus != 4) return measure.RangeMilliMeter / 10.0;
  return -1;                             // -1 = out of range
}

void loop() {
  float us  = readUltrasonicCm();
  float tof = readToFCm();
  bool  obj = (digitalRead(irPin) == LOW);   // LOW = obstacle on this module

  // ---- OLED ----
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print(F("US : "));
  if (us < 0) display.println(F("--"));
  else { display.print(us, 1); display.println(F(" cm")); }

  display.print(F("ToF: "));
  if (tof < 0) display.println(F("--"));
  else { display.print(tof, 1); display.println(F(" cm")); }

  display.print(F("IR : "));
  display.println(obj ? F("OBJECT") : F("clear"));

  display.display();

  // ---- Serial CSV (for CoolTerm) ----
  Serial.print(millis());  Serial.print(',');
  Serial.print(us, 1);     Serial.print(',');
  Serial.print(tof, 1);    Serial.print(',');
  Serial.println(obj ? 1 : 0);

  delay(100);
}
