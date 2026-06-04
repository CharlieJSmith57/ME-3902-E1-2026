// --- Existing LED and Button 1 ---
const int LED1_Pin = 2;       // LED 1 Pin number on Arduino
const int button1_Pin = 3;    // Button 1 Pin number on Arduino
int button1_state = 0;

// --- Task B: New LED and Button 2 Variables ---
const int LED2_Pin = 4;       // LED 2 Pin number on Arduino
const int button2_Pin = 5;    // Button 2 Pin number on Arduino
int button2_state = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Configure Pins for Pair 1
  pinMode(LED1_Pin, OUTPUT);    // Set LED1 pin as an output
  pinMode(button1_Pin, INPUT);  // Set Button1 pin as an input

  // Configure Pins for Pair 2
  pinMode(LED2_Pin, OUTPUT);    // Set LED2 pin as an output
  pinMode(button2_Pin, INPUT);  // Set Button2 pin as an input
}

void loop() {
  // -------------------------------------------------------------
  // CONTROLLING LED 1 WITH BUTTON 1
  // -------------------------------------------------------------
  button1_state = digitalRead(button1_Pin); // Read Button 1 State

  if (button1_state == HIGH) {
    Serial.println("Button 1 is Pressed");
    digitalWrite(LED1_Pin, HIGH);           // Turn LED 1 ON
  } else {
    Serial.println("Button 1 is no longer Pressed");
    digitalWrite(LED1_Pin, LOW);            // Turn LED 1 OFF
  }

  // -------------------------------------------------------------
  // Task B: CONTROLLING LED 2 WITH BUTTON 2
  // -------------------------------------------------------------
  button2_state = digitalRead(button2_Pin); // Read Button 2 State

  if (button2_state == HIGH) {
    Serial.println("Button 2 is Pressed");
    digitalWrite(LED2_Pin, HIGH);           // Turn LED 2 ON
  } else {
    Serial.println("Button 2 is no longer Pressed");
    digitalWrite(LED2_Pin, LOW);            // Turn LED 2 OFF
  }

  delay(100); // Small delay to avoid spamming the serial monitor
}