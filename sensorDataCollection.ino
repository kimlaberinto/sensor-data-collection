#include <ADCTouch.h> //Single Pin Capacitance Sensor Library


//Constants
const int ANALOG = 0;
const int CAPACITANCE = 1;

//Sensors
const int numberPins = 2; //Number of Pins
int sensorPinArray[numberPins] = {A0, A1}; //Insert which pins to read from
int sensorTypeArray[numberPins] = {CAPACITANCE, CAPACITANCE}; //Sensor types in order


//ledPin
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
    
  //Wait 5000 milliseconds before reading;
  for (int i = 0; i<10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
  }

  //create reference values to account for the capacitance of the pad itself
  for (int i=0; i<numberPins; i++) {
    sensorReferenceArray[i] = ADCTouch.read(sensorPinArray[i], 500);
  }

  Serial.println("sensorDataCollection initialized.");
} 

//wait until button pressed before continuing
void waitForPress() {
  while(digitalRead(2)==LOW) { 
      
      if (digitalRead(2)==HIGH) {
        return;
      }
    }
}

void collectAndPrintReadings() {
  for (int i=0; i<numberPins; i++) {
    runningSumArray[i] = 0;
  }

  for (int n=0; n<numberTests; n++) {

    if(n%2 == 0) { //ledPin flashes while taking readings
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

void loop() {

  digitalWrite(ledPin, HIGH);
  waitForPress();
  collectAndPrintReadings();
  t++;
}


int readPin(int pin, int sensorType) { //returns sensorValue
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
