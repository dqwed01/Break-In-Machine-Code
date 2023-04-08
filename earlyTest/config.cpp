#include "config.h"
#include "globals.h"
#include "utilities.h"

int actuationPrintBool = LOW;
int configPrintBool = LOW;
int speedPrintBool = LOW;

void configLCD(void){
  if(WELCOME == currentMode) printWelcome();
  else if(CONFIG == currentMode) printConfig();
  else if(ACTUATION == currentMode) printActuation();
  else if(SPEED == currentMode) printSpeed();
  
}


void configInputs(void){  
  if(CONFIG == currentMode || WELCOME == currentMode) inputConfig();
  else if(ACTUATION == currentMode) inputActuation();
  else if(SPEED == currentMode) inputSpeed();
}

void configMovements(void){
  digitalWrite(SERVOPIN, LOW);
}

//LCD Functions
void printWelcome(void){
  static int timeStamp = millis();
  static int printStatus = LOW;
  if(HIGH != printStatus) {
    lcdDisplay.print("Break-In Machine");
    printStatus = HIGH;
  }
  if(millis() - timeStamp >= HUNDRED_MS * 50){
    currentMode = CONFIG;  
  }
}

void printConfig(void){
  if(HIGH != configPrintBool){
    lcdDisplay.clear();
    lcdDisplay.home();
    lcdDisplay.print("*:Actua. Start:-");
    lcdDisplay.setCursor(0, 1);
    lcdDisplay.print("**:Speed");
    configPrintBool = HIGH;
  }
  Serial.print("Hours: ");
  Serial.println(actuationTimeHrs);
  Serial.print("Voltage: ");
  Serial.println(speedVoltage);
}

void printActuation(void){
  static int oldActuationTime = LOW;

  if(LOW == actuationPrintBool){
    lcdDisplay.clear();
    lcdDisplay.home();
    lcdDisplay.print("Actua.: ");
    lcdDisplay.setCursor(10, 0);
    lcdDisplay.print("Hrs");
    lcdDisplay.setCursor(0, 1);
    lcdDisplay.print("*: Confrim");
    actuationPrintBool = HIGH;    
  }
  if(oldActuationTime != actuationTimeHrs){
    oldActuationTime = actuationTimeHrs;
    lcdDisplay.setCursor(8, 0);
    lcdDisplay.print(oldActuationTime);
    if(oldActuationTime < 10){ //Erase decimals of 2 digit numbers when print 1 digit numbers
      lcdDisplay.setCursor(9,0);
      lcdDisplay.print(" ");
    }
  }
}

void printSpeed(void){
  static float oldSpeedVolt = LOW;

  if(LOW == speedPrintBool){
    lcdDisplay.clear();
    lcdDisplay.home();
    lcdDisplay.print("Speed: ");
    lcdDisplay.setCursor(10, 0);
    lcdDisplay.setCursor(0, 1);
    lcdDisplay.print("*: Confrim");
    speedPrintBool = HIGH;    
  }

  if(oldSpeedVolt != speedVoltage){
    oldSpeedVolt = speedVoltage;
    lcdDisplay.setCursor(7, 0);
    lcdDisplay.print(oldSpeedVolt, 1);
    lcdDisplay.print("V ");
  }
}



//Input Functions
void inputConfig(void){
  /*
    1. Single Press brings to Actuation menu
    2. Double Press brings to Speed menu
    3. Hold starts break-in machine
  */
  static int numButtonPress = LOW;
  static int maxClick = 2;
  numButtonPress = readButtonClicks(maxClick, HUNDRED_MS * 5);
  delay(1); //Adding a 1ms delay seems to prevent the program from jumping immediately into a new mode, even when no input has been registered
  if(1 == numButtonPress) currentMode = ACTUATION;
  else if (2 == numButtonPress) currentMode = SPEED;
  
  if (readButtonHold(HUNDRED_MS * 5)) currentMode = BREAKIN;

  if(currentMode != CONFIG) configPrintBool = LOW;
}

void inputActuation(void){
  //Read Potentiometer, adjust actuation time for switch. Button returns to config
  int potentioVolt = readPotentioVolt();
  static int maxClick = 1;
  actuationTimeHrs = 5 + ((potentioVolt + 1) * 0.3); //Range is from 5hrs to 24hrs.

  if(1 == readButtonClicks(maxClick, HUNDRED_MS * 5)){
    actuationPrintBool = LOW;
    currentMode = CONFIG;
  }

}

void inputSpeed(void){
  int potentioVolt = readPotentioVolt() >> 2;
  static int maxClick = 1;
  speedVoltage = 5 + 0.5 * potentioVolt;
  speedVoltage = (speedVoltage >= 12) ? 12 : speedVoltage;

  if(1 == readButtonClicks(maxClick, HUNDRED_MS * 5)){
    speedPrintBool = LOW;
    currentMode = CONFIG;
  }
}
