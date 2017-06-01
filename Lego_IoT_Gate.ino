// constants won't change. Used here to set a pin number :
const int ledPin =  D1;// the number of the LED pin
const int lightPin = D2;

// Enums
enum state {IN, OUT};

// Global vars
int timeStamp = 0;
int outCount = 0;
int inCount = 0;
enum state middleGateState = IN;

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
  pprint("Light", lightInput);

  // DEBUG
  analogWrite(ledPin, lightInput);

  // Delay
  delay(100);
}

void changeState() {
  enum state tempMiddleGateState = middleGateState;

  if (inCount >= outCount * 2) {
    // Too many INs
    tempMiddleGateState = IN;
    Serial.println("Changing state to IN");
  } else if (outCount >= inCount * 2) {
    // Too many OUTs
    tempMiddleGateState = OUT;
    Serial.println("Changing state to OUT");
  } else {
    // Else gate will stay the same
    Serial.println("Keeping state the same: " + tempMiddleGateState);
  }
  
  // TODO locks for middle gate change
  middleGateState = tempMiddleGateState;

  // TODO locks for reseting counts
  inCount = 0;
  outCount = 0;
}

void pprint(String label, int val) {
  String toPrint = label + ": ";
  toPrint += val;
  Serial.println(toPrint);
}

