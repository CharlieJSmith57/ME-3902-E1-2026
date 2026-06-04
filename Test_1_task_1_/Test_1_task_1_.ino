const int LED1_Pin=2; //LED Pin number on Arduino

const int button1_Pin=3; //Button Pin number on Arduino

int button1_state=0;

void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
	pinMode(2, OUTPUT); // Set the LED anode pin as an output

  pinMode(button1_Pin,INPUT); //Set the button as an input
}


void loop() {

  //Read Button State
  button1_state = digitalRead(button1_Pin);

if (button1_state==HIGH)
{
  Serial.println("Button is Pressed"); //Print a message to the output terminal
    digitalWrite(LED1_Pin, HIGH); // Turn the LED on
  
}
else
{
  Serial.println("Button is no longer Pressed"); //Print a message to the output terminal
    digitalWrite(LED1_Pin, LOW); // Turn the LED off
}
 delay(100); // optional: Small delay to avoid spamming serial monitor
}