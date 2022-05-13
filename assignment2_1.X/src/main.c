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

#define Bits_To_Int 200/1023;

void readEncoder(int edge);
int32_t pid_controller(float kp, float ki, float kd, float error);

int main() {    
    __builtin_disable_interrupts();
    //put initialisation functions which are sensitive for interrupts here
    macro_enable_interrupts();
    //put other initialisation functions here
    AIC_Init();
    LCD_Init();
    MOT_Init(1);
    
    unsigned int POT_Value;
    unsigned int Set_Speed;
    char LCD_String[2][40];
    
    while(1) {
        //put your infinite loop here
        POT_Value = AIC_Val();
        Set_Speed = POT_Value * Bits_To_Int;
        
        sprintf(LCD_String[0], "Set %u   ", Set_Speed);
        LCD_WriteStringAtPos(LCD_String[0], 0, 0);
        
        MOT_SetPhEnMotor1(0, Set_Speed);
    }
    return (0);
}

void readEncoder(int edge) {
    //put your change notice (rotary encoder) interrupt code here
}

int32_t pid_controller(float kp, float ki, float kd, float error) {
    int32_t output;
    //put pid controller code here
    return output;
}