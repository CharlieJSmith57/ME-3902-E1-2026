#include <Stepper.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


Adafruit_MPU6050 mpu3;

//1.8 degree step angle = 200 steps per revolution

//const int StepsPerRevolution = 200;

//Initializing Stepper Library
//(steps,AIN1,AIN2, BIN1, BIN2)
//Stepper nema17Stepper(StepsPerRevolution, 5, 4, 6, 7);

//int sensor2 = 2; // sensor pin
//int val2; // 1: Magnetic field detected, 0: No magnetic field detected


void setup() {
  // put your setup code here, to run once:

  //Set the motor speed in rpm
  // nema17Stepper.setSpeed(10);

  // Serial.begin(9600);

  // Serial.println("NEMA 17 is initialized with TB6612");

  //  pinMode(sensor2, INPUT); // set sensor pin as input
  Serial.begin(9600);
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

  // Serial.println("Moving Clockwise");
  // nema17Stepper.step(StepsPerRevolution);
  // delay(1000); //Pause for one second

  // Serial.println("Moving CCW");
  // nema17Stepper.step(-StepsPerRevolution);
  // delay(1000);

  // val2 = digitalRead(sensor2); // Read the sensor

  // if(val2==1)
  // {
  // Serial.println("Magnet Not Detected");
  // }

  // else
  // {
  //     Serial.println("Magnet Detected");
    
  // }

  // delay(50);
 /* Get new sensor events with the readings */
  sensors_event_t a3, g3, temp3;
  mpu3.getEvent(&a3, &g3, &temp3);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a3.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a3.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a3.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g3.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g3.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g3.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp3.temperature);
  Serial.println(" degC");
  delay(500);
}