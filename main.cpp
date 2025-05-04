/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

 #include "mbed.h"
 #include "display.h"
 #include "gas_temp_sensors.h"
 #include "matrix_keypad.h"
 #include "alarm_state.h"
 
 #include <cctype> // to fix isdigit
 #include <string> // Added to resolve std::string error
 #include <chrono> // to try fix time issue
 
 // Blinking rate in milliseconds
 #define SHOW_STATE_TIMER 5s
 #define UPDATE_TIMER 500ms
 void serialWriteChar(char chr) {
     uartUsb.write(&chr, 1);
 }
 
 int main() {
     keypadInit();
     displayInit(DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER);
     displayclear();
     displayCharPositionWrite(0, 0);
     displayStringWrite("Activating");
     ThisThread::sleep_for(SHOW_STATE_TIMER);
     displayclear();
 
 
     while (true) {
         SensorTask2();
         /*displayCharPositionWrite(0 , 0);
         displayStringWrite("Waiting For Input");
         if (key == '2') {
             displayclear();
             pcSerialComStringWrite("\r\nEntered --> ");
             serialWriteChar(key);
             pcSerialComStringWrite("\r\n");
 
             Gas_State(); // Do your gas function
 
             auto start = Kernel::Clock::now();
             while (Kernel::Clock::now() - start < SHOW_STATE_TIMER) {
                 // you could refresh data if you want
                 ThisThread::sleep_for(500ms);
             }
 
             displayclear(); // Clear after showing
         }
             else if (key == '3') {
             displayclear();
             pcSerialComStringWrite("\r\nEntered --> ");
             serialWriteChar(key);
             pcSerialComStringWrite("\r\n");
 
             over_temp(); // Do your temp function
 
             auto start = Kernel::Clock::now();
             while (Kernel::Clock::now() - start < SHOW_STATE_TIMER) {
                 // refresh or show temp data if needed
                 ThisThread::sleep_for(500ms);
             }
 
             displayclear(); // Clear after showing
         }*/
                     auto start = Kernel::Clock::now();
             while (Kernel::Clock::now() - start < UPDATE_TIMER) {
                 // you could refresh data if you want
                 ThisThread::sleep_for(10ms);
             }
            // ThisThread::sleep_for(SHOW_STATE_TIMER);
     }  
 }
 