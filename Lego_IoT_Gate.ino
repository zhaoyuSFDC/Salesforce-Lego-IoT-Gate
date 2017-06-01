// constants won't change. Used here to set a pin number :
const int ledPin =  D1;// the number of the LED pin
const int lightPin = D2;

// Global vars
int timeStamp = 0;
int outCount = 0;
int inCount = 0;

// Variables will change :
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
  timeStamp = millis();
  
  // Read input from light sensor
  int lightInput = analogRead(lightPin);
  Serial.println("Light" + lightInput);

  // DEBUG
  analogWrite(ledPin , lightInput);

  // Delay
  delay(100);
}
