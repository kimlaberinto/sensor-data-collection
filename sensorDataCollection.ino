#include <ADCTouch.h> //Single Pin Capacitance Sensor Library


//Constants
int ANALOG = 0;
int CAPACITANCE = 1;

//Sensors
const int numberPins = 2; //Number of Pins
int sensorPinArray[numberPins] = {A0, A1}; //Insert which pins to read from
int sensorTypeArray[numberPins] = {CAPACITANCE, CAPACITANCE}; //Sensor types in order
int sensorReferenceArray[numberPins]; //reference values to remove offset, normalization

//ledPin
const int ledPin = 8;

//runningSum Array
int runningSumArray[2];

//Settings
//num of readings per averaging



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

  for (int n=0; n<20; n++) {

    if(n%2 == 0) { //ledPin blinks while taking readings
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

    delay(100);

    if (n==19) { //Last test
      Serial.print("Reading: ");
      for (int i=0; i<numberPins; i++) {
        float average = runningSumArray[i]/20.0;
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
