#include <WiFi.h>
#include <WiFiUdp.h>

//WiFi config

const char* ssid = "ESP32_Control";
const int localPort = 5005;

//Motor driver pin definitions

const int enA = 14;
const int in1 = 27;
const int in2 = 26;

WiFiUDP udp;
char packetBuffer[255];

void setup()
{
  //Serial Monitor Serial
  Serial.begin(115200);

  delay(500);

  //Configure wifi access point
  WiFi.mode(WIFI_AP);
  bool success = WiFi.softAP(ssid, NULL, 1);

  if (success) {
    Serial.println("Access point successfully started");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP()); // the chip's actual AP address
  } else {
    Serial.println("failed to start access point.");
  }

  //start listening for UDP packets from MATLAB
  udp.begin(localPort);
  Serial.printf("Listening on UDP port %d\n", localPort);

  //Initialize Motor Driver Pins

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //start with motor off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, 0);

  //Instructions to the user
  Serial.println("ESP 32 trials");
  Serial.println("send '1' to turn motor on");
  Serial.println("send '0' to turn motor off");
}

void loop() {

  int packetSize = udp.parsePacket();

  // Only act when a fresh UDP packet actually arrives
  if (packetSize)
  {
    int len = udp.read(packetBuffer, 255);
    if (len > 0)
    {
      packetBuffer[len] = 0;   // null-terminate the received data
    }

    //Motor logic
    String command = String(packetBuffer);
    command.trim();

    if (command == "1")
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 200);
      Serial.println("Motor is running");
    }
    else if (command == "0")
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enA, 0);
      Serial.println("Motor stopped");
    }
    else
    {
      Serial.print("Unknown command: ");
      Serial.println(command);
    }
  }
}
