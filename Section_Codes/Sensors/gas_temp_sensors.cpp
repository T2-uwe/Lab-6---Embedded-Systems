#include "gas_temp_sensors.h"
#include <cstdio>
#include "display.h"
#include "alarm_state.h"

//=====[Definition of Public Variables]=======================================
AnalogIn potentiometer(A0);
AnalogIn lm35(A5);
AnalogIn mq2(A2);
DigitalInOut sirenPin(PE_10);

bool quit = false;
char receivedChar = '\0';

float mq2Reading = 0.0;
float lm35Reading = 0.0;
float lm35TempC = 0.0;
float lm35TempF = 0.0;

float potentiometerReading = 0.0;
float potentiometerScaledToC = 0.0;
float potentiometerScaledToF = 0.0;

//=====[Definition of Public Functions]=======================================
UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
void pcSerialComStringWrite(const char* str)
{
    uartUsb.write(str, strlen(str));
}

char pcSerialComCharRead()
{
    char receivedChar = '\0';
    if (uartUsb.readable()) {
        uartUsb.read(&receivedChar, 1);
    }
    return receivedChar;
}
float potentiometerScaledToCelsius(float analogValue)
{
    return 148.0f * analogValue + 2.0f;
}

float analogReadingScaledWithTheLM35Formula(float analogReading)
{
    return analogReading * 330.0f;
}

void over_temp(){
    UpdatedTemp();
        if (lm35TempC > 32.00f) {
            displayCharPositionWrite(0, 1); 
            displayStringWrite("                    "); 

            displayCharPositionWrite(0 , 1);
            displayStringWrite("Temp State: Not Safe");
        }else{
            displayCharPositionWrite(0, 1); 
            displayStringWrite("                    "); 
            displayCharPositionWrite(0 , 1);
            displayStringWrite("Temp State: Safe");
        }
}
void Gas_State(){
     if (mq2Reading > 0.60f) {
            displayCharPositionWrite(0, 0);
            displayStringWrite("                    ");
            displayCharPositionWrite(0 , 0);
            displayStringWrite("Gas State: Not Safe");
        }else{
            displayCharPositionWrite(0, 0);
            displayStringWrite("                    "); 
            displayCharPositionWrite(0 , 0);
            displayStringWrite("Gas State: Safe");
        }

}
void Tempvalue(){
    int lm35Temp;
    lm35Temp = lm35TempC;
    char tempStr[20];
    int whole = (int)lm35Temp;
    int frac = (int)(lm35Temp * 100) % 100;  // 2 decimal places
 sprintf(tempStr, "Temperature: %d.%02d", whole, frac);
    displayCharPositionWrite(0, 1);
    displayStringWrite(tempStr); 
}

void Gasdetection(){
        UpdatedGas();
if (mq2Reading > 0.60f) {
            displayCharPositionWrite(0, 0); 
            displayStringWrite("                    ");
            displayCharPositionWrite(0 , 0);
            displayStringWrite("Gas: Detected");
        }else{
            displayCharPositionWrite(0, 0); 
            displayStringWrite("                    ");
            displayCharPositionWrite(0 , 0);
            displayStringWrite("Gas: Not Detected");
        }
}

void UpdatedTemp(){
    float lm35Reading = lm35.read();
    lm35TempC = analogReadingScaledWithTheLM35Formula(lm35Reading);
}
void UpdatedGas(){
    mq2Reading = mq2.read();
}

void uartTask()
{
    sirenPin.mode(OpenDrain);
    sirenPin.input();

    while (true) {
        char str[1000] = "";

        potentiometerReading = potentiometer.read();

        potentiometerScaledToC = potentiometerScaledToCelsius(potentiometerReading);
        lm35TempC = analogReadingScaledWithTheLM35Formula(lm35Reading);

         UpdatedTemp();  // <-- Add this
        UpdatedGas();   // <-- Add this

sprintf(str,"LM35: %d.%02d , Potentiometer scaled to: %d.%02d, Gas Level: %d.%02d V\r\n",
    (int)lm35TempC, (int)(lm35TempC * 100) % 100,
    (int)potentiometerScaledToC, (int)(potentiometerScaledToC * 100) % 100,
    (int)mq2Reading, (int)(mq2Reading * 100) % 100);
        pcSerialComStringWrite(str);

        ThisThread::sleep_for(delay);

        receivedChar = pcSerialComCharRead();

       
    }
}
void SensorTask2(){
    while (true) {
    UpdatedTemp();
    UpdatedGas();
    Gasdetection();
    Tempvalue();
    alarmcheck();
}

}
