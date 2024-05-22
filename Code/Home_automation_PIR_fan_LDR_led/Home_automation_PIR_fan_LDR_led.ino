// Final Code for led and fan automation: 
const int pirPin = 2; // PIR sensor input pin
const int relayPin = 3; // Relay module output pin      // Relay module control pin connected to digital pin 3
int ldrPin = A0;        // LDR sensor output connected to analog pin A0

int pirState = LOW;     // Variable to store PIR sensor state
int fanState = LOW;     // Fan state (OFF by default)

// Define a state variable for the fan
bool isFanOn = false;

int ldrThreshold = 500; // LDR threshold value for LED control

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  digitalWrite(relayPin, LOW); // Set initial fan state
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read the PIR sensor value
  int pirValue = digitalRead(pirPin);

  // Check if motion is detected
  if (pirValue == HIGH) {
    // Toggle the fan state
    isFanOn = !isFanOn;
    // Update the relay state based on the fan state
    digitalWrite(relayPin, isFanOn ? HIGH : LOW);

    // Debug output
    Serial.print("Motion detected. Fan is now ");
    Serial.println(isFanOn ? "ON" : "OFF");

    // Wait for a moment to debounce the PIR sensor
    delay(5000); // 5 seconds delay
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
