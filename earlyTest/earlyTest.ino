#include "functions.h"
#include "globals.h"

   //Init Global Variables;
  int servoInAction = LOW;
  int potentioVolt = 0;
  int currentMode = WELCOME;
  int speedIndicatorLevel;
  int actuationTimeHrs;
  float speedVoltage;
  LiquidCrystal_I2C lcdDisplay( 0x27, 16, 2);
  

void setup() {
  initLCD();
  //lcdDisplay.print("Hello World!"); //Prints at col 1, row 1 
  pinMode(SERVOPIN, OUTPUT); //PWM Output
  pinMode(BUTTONPIN, INPUT);
  pinMode(POTENTIOPIN, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  displayLCD(currentMode);
  inputHandling(currentMode);
  movementControl(currentMode);
}


void displayLCD(int currentMode){
  if (BREAKIN != currentMode) configLCD();
  else breakInLCD();
}

void inputHandling(int currentMode){
  if (BREAKIN != currentMode) configInputs();
  else breakInInputs();
}

void movementControl(int currentMode){
  if(BREAKIN != currentMode) configMovements();
  else breakInMovements();
}
