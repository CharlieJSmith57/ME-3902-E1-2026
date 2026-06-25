#include <Stepper.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu3;

// 1.8 degree step angle = 200 steps per revolution

const int StepsPerRevolution = 200;

// Initializing Stepper Library
// (steps,AIN1,AIN2, BIN1, BIN2)
Stepper nema17Stepper(StepsPerRevolution, 5, 4, 6, 7);

//Number of rotations - 15rpm for 3 minutes - 45 rotations

//define the time in milliseconds

const long duration = 3*60*1000; //18000 milliseconds


int sensor2 = 2; // sensor pin
int val2; // 1: Magnetic field detected, 0: No magnetic field detected


void setup() {
  // put your setup code here, to run once:

  //Set the motor speed in rpm
  nema17Stepper.setSpeed(15); //15 rpm

  Serial.begin(9600);

  Serial.println("NEMA 17 is initialized with TB6612");

   pinMode(sensor2, INPUT); // Hall Effect Sensor set sensor pin as input
 
  // Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize MPU at I2C address 3 (change this to your MPU's actual address)!
  if (!mpu3.begin()) {   // defaults to 0x68
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("3 minute cycle starting");

  long startTime=millis();


  Serial.println("Time, Hall Effect, RotX, RotY, RotZ");
  // delay(1000);
 
  
  while (millis()-startTime < duration)
  {
   Serial.print(millis());
   nema17Stepper.step(1);

   Serial.print(",");
   

    val2 = digitalRead(sensor2); // Read the sensor

    Serial.print(val2);
    Serial.print(",");

      /* Get new sensor events with the readings */
  sensors_event_t a3, g3, temp3;
 mpu3.getEvent(&a3, &g3, &temp3);
    Serial.print(",");
   Serial.print(g3.gyro.x);
    Serial.print(",");
   Serial.print(g3.gyro.y);
    Serial.print(",");
   Serial.println(g3.gyro.z);
  }
}
