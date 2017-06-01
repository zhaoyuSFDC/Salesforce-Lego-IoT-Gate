#include "Timer.h"

Timer t;

// Constants
const int leftLEDPin = D2;
const int leftLightPin = D1;
const int middleLEDPin = D4;
const int middleLightPin = D3;
const int rightLEDPin = D6;
const int rightLightPin = D5;

// Enums
enum state {IN, OUT};

// Global vars
int timeStamp = 0;
int outCount = 1;
int inCount = 1;
enum state middleGateState = IN;

// Previous sensor values
int prevRight = 0;
int prevMiddle = 0;
int prevLeft = 0;

void setup() {
  // set the digital pin as output:
  pinMode(leftLEDPin, OUTPUT);
  pinMode(middleLEDPin, OUTPUT);
  pinMode(rightLEDPin, OUTPUT);
  pinMode(leftLightPin, INPUT_PULLUP);
  pinMode(middleLightPin, INPUT_PULLUP);
  pinMode(rightLightPin, INPUT_PULLUP);

  digitalWrite(leftLEDPin, HIGH);
  digitalWrite(middleLEDPin, LOW);
  digitalWrite(rightLEDPin, LOW);

  // Start serial mode
  Serial.begin(9600);

  t.every(5000, changeState);
}

void loop() {
  timeStamp = millis();
  t.update();
  
  // Read input from light sensors
  int leftLightInput = digitalRead(leftLightPin);
  leftLightInput ^= 1;
  int middleLightInput = digitalRead(middleLightPin);
  int rightLightInput = digitalRead(rightLightPin);

  // Check for spikes in values
  if (leftLightInput == 0 && prevLeft == 1) {
    inCount += 1;
    Serial.println("Left gate triggered");
  }
  if (rightLightInput == 0 && prevRight == 1) {
    outCount += 1;
    Serial.println("Right gate triggered");
  }
  if (middleLightInput == 0 && prevMiddle == 1) {
    Serial.println("Middle gate triggered");
    if (middleGateState == IN) {
      inCount += 1;
    } else {
      outCount += 1;
    }
  }

  // Update temp values
  prevLeft = leftLightInput;
  prevMiddle = middleLightInput;
  prevRight = rightLightInput;
}

void changeState() {
  enum state tempMiddleGateState = middleGateState;

  if (inCount >= outCount * 2) {
    // Too many INs
    tempMiddleGateState = IN;
    digitalWrite(middleLEDPin, HIGH);
    Serial.println("Changing state to IN");
  } else if (outCount >= inCount * 2) {
    // Too many OUTs
    tempMiddleGateState = OUT;
    digitalWrite(middleLEDPin, LOW);
    Serial.println("Changing state to OUT");
  } else {
    // Else gate will stay the same
    pprint("Keeping state the same", tempMiddleGateState);
  }
  
  // Change gate status
  middleGateState = tempMiddleGateState;

  // Reseting counts
  inCount = 1;
  outCount = 1;
}

void pprint(String label, int val) {
  String toPrint = label + ": ";
  toPrint += val;
  Serial.println(toPrint);
}


