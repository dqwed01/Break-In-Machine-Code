#include "functions.h"
#include "globals.h"

int buttonPress(void){ //Return HIGH if a new Button state is registered as HIGH, return LOW else
  static int oldState = LOW;
  static int returnCounter = LOW;
  int currentState = digitalRead(BUTTONPIN);
  if(currentState != oldState) {
    oldState = currentState;
    returnCounter++;
  }
  if(2 == returnCounter){
    returnCounter = LOW;
    return HIGH;
    }
  else return LOW;
}

void initLCD(void){
    lcdDisplay.init();
    lcdDisplay.clear();
    lcdDisplay.backlight();
}

int readButtonClicks(int maxNumClicks, int msTime){
  static unsigned long timeSpan = millis();
  static int numButtonClicks = 0;
  static int buttonSave = 0;
  if(buttonPress() && numButtonClicks < maxNumClicks) {
    numButtonClicks++;
    timeSpan = millis(); //Ensures that the time gap between double click is always 500ms
  }
  if (millis() - timeSpan >= msTime){
    timeSpan = millis();
    buttonSave = numButtonClicks;
    numButtonClicks = 0;
    return buttonSave;
  }
}

int readButtonHold(int msTime){
  static unsigned long timeSpan = LOW;
  static int counter = LOW;
  int currentState = digitalRead(BUTTONPIN);
  if(currentState && LOW == counter){
    timeSpan = millis();
    counter = HIGH;
  }
  else if(!(currentState) && HIGH == counter) counter = LOW;

  if(millis() - timeSpan >= msTime && HIGH == counter) return HIGH;
  else return LOW;
  
}

int readPotentioVolt(void){
  return analogRead(POTENTIOPIN) >> 4;
}


