
/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

 #include "mbed.h"//#include "arm_book_lib.h"
 #include "alarm_state.h"
 #include "gas_temp_sensors.h"
 #include "display.h"
 #include "matrix_keypad.h"
 #include <string>
 #include <chrono>
 using namespace std;
     int alarm = 0;
 void alarmcheck(){
     if(mq2Reading>0.60f && lm35TempC>32.00f){
          displayCharPositionWrite(0, 2);
             displayStringWrite("                    ");
          displayCharPositionWrite(0 , 2);
             displayStringWrite("Alarm State: Active");
             displayclear();
             alarm = 1;
         while (alarm == 1){
             displayCharPositionWrite(0 , 0);
             displayStringWrite("Alarm State: Active");
             displayCharPositionWrite(0 , 1);
             displayStringWrite("Enter PIN to Disable");
             pin();
         }
     }else if(mq2Reading>0.60f && lm35TempC<32.00f){
          displayCharPositionWrite(0, 2);
             displayStringWrite("                    ");
         displayCharPositionWrite(0 , 2);
             displayStringWrite("Alarm State: Gas");
     }else if(mq2Reading<0.60f && lm35TempC>32.00f){
          displayCharPositionWrite(0, 2);
             displayStringWrite("                    ");
         displayCharPositionWrite(0 , 2);
             displayStringWrite("Alarm State: Temp");
     }else{
          displayCharPositionWrite(0, 2);
             displayStringWrite("                    ");
         displayCharPositionWrite(0 , 2);
             displayStringWrite("Alarm State: Offline");
     }
 }
 
 
 