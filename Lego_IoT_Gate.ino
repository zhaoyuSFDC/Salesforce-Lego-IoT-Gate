// Constants
const int leftLEDPin = D3;
const int leftLightPin = D4;
const int middleLEDPin = D1;
const int middleLightPin = D2;
const int rightLEDPin = D5;
const int rightLightPin = D6;

// Enums
enum state {IN, OUT};

// Global vars
int timeStamp = 0;
int outCount = 0;
int inCount = 0;
enum state middleGateState = IN;

void setup() {
  // set the digital pin as output:
  pinMode(leftLEDPin, OUTPUT);
  pinMode(middleLEDPin, OUTPUT);
  pinMode(rightLEDPin, OUTPUT);

  // Start serial mode
  Serial.begin(9600);
}

void loop() {
  timeStamp = millis();
  
  // Read input from light sensors
  int leftLightInput = analogRead(leftLightPin);
  int middleLightInput = analogRead(middleLightPin);
  int rightLightInput = analogRead(rightLightPin);

  pprint("Left Sensor", leftLightInput);

  // DEBUG
  analogWrite(leftLEDPin, leftLightInput);
  analogWrite(middleLEDPin, middleLightInput);
  analogWrite(rightLEDPin, rightLightInput);

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

