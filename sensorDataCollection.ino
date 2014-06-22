#include <ADCTouch.h> //Single Pin Capacitance Sensor Library


//Constants
const int ANALOG = 0;
const int CAPACITANCE = 1;

//Sensors
const int numberPins = 2; //Number of Pins
int sensorPinArray[numberPins] = {A0, A1}; //Insert which pins to read from
int sensorTypeArray[numberPins] = {CAPACITANCE, CAPACITANCE}; //Sensor types in order

//ledPin //If no ledPin available, feel free to also use LEDBUILT_IN
const int ledPin = 8;

//Variables
int runningSumArray[2];
int sensorReferenceArray[numberPins]; //reference values to remove offset, normalization

int t = 0; //running count, names each reading as a specific number

//Settings
//These numbers multiplied togeher give the duration of the reading (in ms ofcourse)
const int numberTests = 20; //number of tests in a reading
const int testDelay = 100; //milliseconds between tests during the reading

void setup() {
  Serial.begin(9600);
  Serial.println("sensorDataCollection initializing... ");
  
  pinMode(ledPin, OUTPUT);
    
  //Wait 5000 milliseconds before reading. Gives time for you until the tests to create the reference values. 
  //Feel free to disable if you wish. Somewhat only comestic
  for (int i = 0; i<10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
  }

  //create reference values to account for the capacitance of the pad itself
  //Note: manually reads the pins instead of the readPin(pin, type) function
  for (int i=0; i<numberPins; i++) {
    if (sensorTypeArray[i] == ANALOG) {
      sensorReferenceArray[i] = analogRead(sensorPinArray[i]);
    } else if (sensorTypeArray[i] == CAPACITANCE) {
      sensorReferenceArray[i] = ADCTouch.read(sensorPinArray[i], 500);
    } else {
      Serial.print("ERROR: sensor type not found. Cannot reference, autoset to 0. ");
      Serial.print(sensorPinArray[i]);
      Serial.print(" pin, type: ");
      Serial.print(sensorTypeArray[i]);

      sensorReferenceArray[i] = 0;
    }
  }

  Serial.println("sensorDataCollection initialized.");
}

void loop() {
  digitalWrite(ledPin, HIGH); //lights up ledPin to indicate that it's ready to do another reading
  waitForPress();
  collectAndPrintReading();
  t++;
}

//Called when waiting until button pressed before continuing
void waitForPress() {
  while(digitalRead(2)==LOW) { 
      if (digitalRead(2)==HIGH) {
        return;
      }
    }
}

//When called, it does a reading. It collects the test data and prints the reading.
//By printing out each test, or by printing out the average at the end (or both)
void collectAndPrintReading() {
  for (int i=0; i<numberPins; i++) {
    runningSumArray[i] = 0;
  }

  //Repeat the test a number of times to create one reading
  for (int n=0; n<numberTests; n++) {
    //ledPin blinks/flashes while taking the reading. Comestic, not necessary
    if(n%2 == 0) {
      digitalWrite(ledPin, LOW);
    } else {
      digitalWrite(ledPin, HIGH);
    }

    Serial.print("values: ");
    for (int i=0; i<numberPins; i++) {
      int sensorValue = readPin(sensorPinArray[i], sensorTypeArray[i]);
      sensorValue -= sensorReferenceArray[i];

      Serial.print(sensorValue);
      Serial.print("\t");
      runningSumArray[i] += sensorValue;
    }
    Serial.println("");

    delay(testDelay);

    if (n==(numberTests-1)) { //Last test
      Serial.print("reading ");
      Serial.print(t);
      Serial.print(" : ");
      for (int i=0; i<numberPins; i++) {
        float average = runningSumArray[i]/float(numberTests); //convert int to float to allow for decimals in the averaging
        Serial.print(sensorPinArray[i]);
        Serial.print(" pin avg : ");
        Serial.print(average);
        Serial.print("  ");
      }
      Serial.println(""); //print newline
    }
  }
}

//When called returns sensorValue of a given pin based on it's sensorType
int readPin(int pin, int sensorType) { 
  // if sensorType == ANALOG, if it's a normal analog type of sensor, use readAnalog(pin).
  // if sensorType == CAPACITANCE, if a capacitance sensor, ADCTouch.read(pin) or use some library to read it
  // Feel free to add other sensor types and other ways to read the pin.

  int sensorValue;

  if(sensorType == ANALOG) {
    sensorValue = analogRead(pin);
  } else if (sensorType == CAPACITANCE) {
    sensorValue = ADCTouch.read(pin);
  } else {
    Serial.print("ERROR, sensorType not found: sensorValue: ");
    Serial.print(sensorValue);
    Serial.print(", pin:");
    Serial.print(pin);
    Serial.print(", sensorType:");
    Serial.println(sensorType);
  }

  return sensorValue;
}
