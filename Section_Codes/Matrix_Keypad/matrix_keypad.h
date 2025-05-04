#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

#include "mbed.h"
#include <cstring>
#include <chrono>
#include <cctype> // to fix isdigit


//=====[Defines]===============================================================
#define TIME_INCREMENT_MS        10
#define DEBOUNCE_KEY_TIME_MS     40
#define KEYPAD_ROWS              4
#define KEYPAD_COLS              4
#define MAX_ALARM_LOGS           5

//=====[Keypad Pin Configuration]===============================================
extern DigitalOut keypadRowPins[KEYPAD_ROWS];
extern DigitalInOut keypadColPins[KEYPAD_COLS];

//=====[Keypad State Machine]==================================================
typedef enum {
    KEYPAD_SCANNING,
    KEYPAD_DEBOUNCE,
    KEYPAD_HOLD_PRESSED
} keypadState_t;

extern keypadState_t keypadState;
extern char keypadLastKeyPressed;
extern int debounceTimer;

extern char inputBuffer[5];
extern int inputIndex;
extern const char correctPin[5];

extern char keyMap[];
extern time_t alarmLog[MAX_ALARM_LOGS];
extern int alarmLogIndex;

//=====[Public Function Declarations]===========================================
void keypadInit();
char keypadScan();
char keypadUpdate();
void pin();


#endif // MATRIX_KEYPAD_H
