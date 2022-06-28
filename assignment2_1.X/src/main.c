/* 
 * File:   main.c
 * Author: Roy Meijer
 *
 * Created on 16 March 2022, 10:09
 */

/* Generic C libraries */
#include <stdio.h>
#include <stdlib.h>

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>

/* Your own libraries */
#include "timer.h"
#include "gpioInterrupt.h"

#include "aic.h"
#include "config.h"
#include "lcd.h"
#include "mot.h"

#include "assignment2_1.h"

// Device Config Bits in DEVCFG1:	
#pragma config FNOSC =      FRC
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	XT
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_1

// Device Config Bits in  DEVCFG2:	
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1
#pragma config JTAGEN =     OFF     
#pragma config FWDTEN =     OFF  

//const float Kp = 200;
//const float Ki = 100;
//const float Kd = 0;
//
//int32_t pid_controller(float kp, float ki, float kd, float error);

int main() {    
    __builtin_disable_interrupts();
    //put initialisation functions which are sensitive for interrupts here
    macro_enable_interrupts();
    //put other initialisation functions here
    
    AIC_Init();
    LCD_Init();
    MOT_Init(1);
    gpioInterrupt_initCNRG9(readEncoder);
    timer1_Init(Timer1_PR * PB_FRQ / 256);
    
    uint16_t POT_Value;
    uint8_t Set_Speed;
    uint16_t rpm = 0;
    char LCD_String[2][40];
//    float error;
//    int32_t PID_Error;
//    uint8_t motorCmd;
    
    while(1) {
        //put your infinite loop here
        POT_Value = AIC_Val();
        Set_Speed = POT_Value * Bits_To_Int;
        MOT_SetPhEnMotor1(0, Set_Speed);
        
        if (localCount >= 10) {
            rpm = getSpeed();
        }
        else if(timer1_interrupted()) {
            rpm = 0;
            localCount = 0;
        }
//        error = Set_Speed - rpm;
//        PID_Error = pid_controller(Kp, Ki, Kd, error);
//        if (PID_Error > 255) {
//            PID_Error = 255;
//        } else if (PID_Error < 0) {
//            PID_Error = 0;
//        }
//        sprintf(LCD_String[0], "Set %u CMD %u      ", Set_Speed, motorCmd);
        sprintf(LCD_String[0], "Set %u   ", Set_Speed);
        sprintf(LCD_String[1], "Speed %u   ", rpm);
        LCD_WriteStringAtPos(LCD_String[0], 0, 0);
        LCD_WriteStringAtPos(LCD_String[1], 1, 0);        
    }
    return (0);
}

//int32_t pid_controller(float kp, float ki, float kd, float error) {
////    int32_t output;
////    const float dt = 0.1;
////    static float prevError = 0;
////    static float intError = 0;
////    //put pid controller code here
////    float diffError = error - prevError;
////    intError = intError + error;
////    output = (int32_t)(error*kp + intError*ki*dt + diffError*kd/dt);
////    prevError = error;
////    return output;
//}