#include <ADCTouch.h> //Single Pin Capacitance Sensor Library

int refA, refB;       //reference values to remove offset

//Sensor Pins

//ledPin

//Indicator Pin

//runningSum Array

//Settings
//num of readings per averaging


//Constants
int ANALOG = 0;
int CAPACITANCE = 1;



void setup() {


    Serial.begin(9600);
    
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(8, OUTPUT);
    
    for (int i = 0; i<10; i++) {
      digitalWrite(8, HIGH);
      delay(250);
      digitalWrite(8, LOW);
      delay(250);
    }

    //create reference values to account for the capacitance of the pad itself
    refA = ADCTouch.read(A1, 500);
    refB = ADCTouch.read(A0, 500);

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
  float runningSumA = 0;
  float runningSumB = 0;
  for (int n=0; n<20; n++) {

    if(n%2 == 0) {
      digitalWrite(8, LOW);
    } else {
      digitalWrite(8, HIGH);
    }

    int valueA = ADCTouch.read(A1);
    int valueB = ADCTouch.read(A0);

    valueA -= refA;
    valueB -= refB;

    runningSumA += valueA;
    runningSumB += valueB;

    delay(100);

    if (n==19) { //last test
      float averageA = runningSumA/20.0;
      float averageB = runningSumB/20.0;
      Serial.print("Reading: A avg: ");
      Serial.print(averageA);
      Serial.print(", B avg: ");
      Serial.println(averageB);
      }
    }
  }
}

void loop() {

  digitalWrite(8, HIGH);
  waitForPress();
  collectAndPrintReadings();

}



//TO IMPLEMENT ONCE SENSOR PIN ARRAY IS DONE
int readPin(int pin, int sensorType) { //returns sensorValue
  // if sensorType == ANALOG, if it's a normal analog type of sensor, use readAnalog(pin).
  // if sensorType == CAPACITANCE, if a capacitance sensor, ADCTouch.read(pin) or use some library to read it
  // Feel free to add other sensor types and other ways to read the pin.

  int sensorValue;

  if(sensorType == ANALOG) {
    sensorValue = analogRead(pin);
  } else if (sensorype == CAPACITANCE) {
    sensorValue = ADCTouch.read(pin);
    sensorValue -= refA;
  }

  if (sensorValue == null) {
    Serial.print("ERROR: sensorValue null. pin:")
    Serial.print(pin);
    Serial.print(", sensorType:");
    Serial.print(sensorType);
  }

  return sensorValue;
}