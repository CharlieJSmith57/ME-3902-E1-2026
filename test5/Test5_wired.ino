//Motor driver pin definitions

const int enA = 14;
const int in1 = 27;
const int in2 = 26;

void setup()
{
  //Serial Monitor / command channel
  Serial.begin(115200);

  delay(500);

  //Initialize Motor Driver Pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //start with motor off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, 0);

  //Instructions to the user
  Serial.println("ESP 32 trials (wired serial)");
  Serial.println("send '1' to turn motor on");
  Serial.println("send '0' to turn motor off");
}

void loop() {

  // Only act when a byte actually arrives over serial
  if (Serial.available() > 0)
  {
    char command = Serial.read();   // read a single character

    if (command == '1')
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 200);
      Serial.println("Motor is running");
    }
    else if (command == '0')
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enA, 0);
      Serial.println("Motor stopped");
    }
    // any other character (e.g. stray newline) is ignored
  }
}
