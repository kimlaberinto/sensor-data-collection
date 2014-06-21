#include <ADCTouch.h>

int refA, refB;       //reference values to remove offset

//sensor Pins

//button Pin

//indicator Pin

//settings
//num of readings per averaging

//poss details to add such as min/max per reading
//maybe even just raw data it out

//Move on to gitHub
//running count of data

void setup() {
    // No pins to setup, pins can still be used regularly, although it will affect readings

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
    
    refA = ADCTouch.read(A1, 500);    //create reference values to 
    refB = ADCTouch.read(A0, 500);      //account for the capacitance of the pad
  
    collectAndPrintReadings();

} 

void waitForPress() {
  while(digitalRead(2)==LOW) { //wait until button pressed
      
      if (digitalRead(2)==HIGH) {
        return;
      }
    }
}

void collectAndPrintReadings() {
    while(true) {
      digitalWrite(8, HIGH);
      
      waitForPress();
      
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
    
    return;
}

void loop() 
{

}

