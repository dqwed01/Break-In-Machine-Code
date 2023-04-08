#pragma once

#define SERVOPIN 7
#define BUTTONPIN 2
#define HUNDRED_MS 100  
#define POTENTIOPIN 3

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


enum modes {WELCOME, CONFIG, ACTUATION, SPEED, BREAKIN};

extern int servoInAction;
extern int potentioVolt;
extern int currentMode;

extern int actuationTimeHrs;
extern float speedVoltage;



extern LiquidCrystal_I2C lcdDisplay;
