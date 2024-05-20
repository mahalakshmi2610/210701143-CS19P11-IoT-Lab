// Final Code for led and fan automation: 
int pirPin = 2;         // PIR sensor output connected to digital pin 2
int relayPin = 3;       // Relay module control pin connected to digital pin 3
int ldrPin = A0;        // LDR sensor output connected to analog pin A0
int pirState = LOW;     // Variable to store PIR sensor state
int fanState = LOW;     // Fan state (OFF by default)
bool fanOn = false;     // Flag to track if the fan is on
int ldrThreshold = 500; // LDR threshold value for LED control

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  digitalWrite(relayPin, fanState); // Set initial fan state
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read the PIR sensor state
  pirState = digitalRead(pirPin);

  // If motion is detected and fan is off, turn on the fan
  if (pirState == HIGH && fanState == LOW) {
    fanState = HIGH;
    digitalWrite(relayPin, fanState); // Turn on the fan
    fanOn = true; // Set the flag
    Serial.println("Motion detected! Fan turned on."); // Print message
    delay(1000); // Delay to avoid multiple detections
  }
  // If no motion is detected and fan is on, turn off the fan
  else if (pirState == LOW && fanState == HIGH && fanOn) {
    fanState = LOW;
    digitalWrite(relayPin, fanState); // Turn off the fan
    fanOn = false; // Reset the flag
    Serial.println("No motion detected. Fan turned off."); // Print message
    delay(1000); // Delay to avoid multiple detections
  }

  // Read the LDR sensor and control the LED
  int ldrValue = analogRead(ldrPin);
  if (ldrValue > ldrThreshold) {
    digitalWrite(4, HIGH); // Turn on the LED
  } else {
    digitalWrite(4, LOW);  // Turn off the LED
  }
  delay(100); // Delay for stability
}
