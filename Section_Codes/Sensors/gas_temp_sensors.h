#ifndef GAS_TEMP_SENSORS_H
#define GAS_TEMP_SENSORS_H

#include "mbed.h"
#include <string>

//=====[Defines]===============================================================

#define delay 2000ms

//=====[Declaration of Public Variables]=======================================
extern UnbufferedSerial uartUsb;
void pcSerialComStringWrite(const char* str);

extern AnalogIn potentiometer;
extern AnalogIn lm35;
extern AnalogIn mq2;
extern DigitalInOut sirenPin;

extern bool quit;
extern char receivedChar;

extern float mq2Reading;
extern float lm35Reading;
extern float lm35TempC;
extern float lm35TempF;
extern float potentiometerReading;
extern float potentiometerScaledToC;
extern float potentiometerScaledToF;

//=====[Declaration of Public Functions]=======================================
void over_temp();
void Gas_State();
void UpdatedTemp();
void UpdatedGas();
void updateTemperature();
void Gasdetection();
void Tempvalue();
void SensorTask2();
float analogReadingScaledWithTheLM35Formula(float analogReading);
void uartTask();
char pcSerialComCharRead();
float potentiometerScaledToCelsius(float analogValue);
#endif
