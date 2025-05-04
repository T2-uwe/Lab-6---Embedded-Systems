#include "display.h"
#include "gas_temp_sensors.h"
#include "matrix_keypad.h"
#include "alarm_state.h"

#include <cctype> // to fix isdigit
#include <string> // Added to resolve std::string error
#include <chrono> // to try fix time issue

//=====[Keypad Pin Configuration]===============================================
DigitalOut keypadRowPins[KEYPAD_ROWS] = {PB_3, PB_5, PC_7, PA_15};
DigitalInOut keypadColPins[KEYPAD_COLS] = {PB_12, PB_13, PB_15, PC_6};

//=====[Keypad State Machine]==================================================
keypadState_t keypadState;
char keypadLastKeyPressed = '\0';
int debounceTimer = 0;
char inputBuffer[5];
int inputIndex = 0;
const char correctPin[] = "1805";
char key;

char keyMap[] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'
};

time_t alarmLog[MAX_ALARM_LOGS];
int alarmLogIndex = 0;

//=====[Functions]=============================================================

void keypadInit() {
    keypadState = KEYPAD_SCANNING;
    for (int i = 0; i < KEYPAD_COLS; i++) {
        keypadColPins[i].input();
        keypadColPins[i].mode(PullUp);
    }
}

char keypadScan() {
    for (int r = 0; r < KEYPAD_ROWS; r++) {
        for (int i = 0; i < KEYPAD_ROWS; i++) {
            keypadRowPins[i] = 1;
        }
        keypadRowPins[r] = 0; // Drive the current row low

        for (int c = 0; c < KEYPAD_COLS; c++) {
            if (keypadColPins[c].read() == 0) { // If the column goes low
                return keyMap[r * KEYPAD_COLS + c];
            }
        }
    }
    return '\0'; // No key pressed
}

char keypadUpdate() {
    char keyDetected = '\0';
    char keyReleased = '\0';

    switch (keypadState) {
        case KEYPAD_SCANNING:
            keyDetected = keypadScan();
            if (keyDetected != '\0') {
                keypadLastKeyPressed = keyDetected;
                debounceTimer = 0;
                keypadState = KEYPAD_DEBOUNCE;
            }
            break;

        case KEYPAD_DEBOUNCE:
            if (debounceTimer >= DEBOUNCE_KEY_TIME_MS) {
                keyDetected = keypadScan();
                if (keyDetected == keypadLastKeyPressed) {
                    keypadState = KEYPAD_HOLD_PRESSED;
                } else {
                    keypadState = KEYPAD_SCANNING;
                }
            }
            debounceTimer += TIME_INCREMENT_MS;
            break;

        case KEYPAD_HOLD_PRESSED:
            keyDetected = keypadScan();
            if (keyDetected != keypadLastKeyPressed) {
                if (keyDetected == '\0') {
                    keyReleased = keypadLastKeyPressed;
                }
                keypadState = KEYPAD_SCANNING;
            }
            break;

        default:
            keypadInit();
            break;
    }

    return keyReleased;
}
void pin(){ 
        displayCharPositionWrite(0 , 2);
        displayStringWrite("--> ");
        pcSerialComStringWrite("Enter pin\r\n");

    while (1){
            key = keypadUpdate();
        if (key != '\0'){
            if (key == '#'){
            inputBuffer[inputIndex] = '\0';
            displayStringWrite(inputBuffer);

            if (strcmp(inputBuffer, correctPin) == 0) {
                    displayCharPositionWrite(4 , 2);
                    displayStringWrite("Correct Pin"); 
                    pcSerialComStringWrite("Correct\r\n");
                    ThisThread::sleep_for(2s);
                    displayCharPositionWrite(4, 2); 
                    displayStringWrite("                    "); 
                    alarm = 0;
                    break;          
                    } else {
                        displayCharPositionWrite(4 , 2);
                        displayStringWrite("Incorrect Pin");
                        pcSerialComStringWrite("Incoreect\r\n");
                        ThisThread::sleep_for(2s);
                        displayCharPositionWrite(4, 2); 
                        displayStringWrite("                    ");
                        inputIndex = 0;
                    }
                }
                    else if (inputIndex < sizeof(inputBuffer)-1 && isdigit(key)){
                        inputBuffer[inputIndex++] = key;
                        inputBuffer[inputIndex] = '\0';
                        displayCharPositionWrite(4, 2);           // Set cursor to start of row 3
                        displayStringWrite("                    ");  // Clear the line
                        displayCharPositionWrite(4, 2);           // Reset cursor again
                        displayStringWrite(inputBuffer);  
                        pcSerialComStringWrite(inputBuffer);
                        }
                
                }
        }
    ThisThread::sleep_for(100ms);
}