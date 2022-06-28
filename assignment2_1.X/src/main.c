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

#define Kp 1
#define Ki 2
#define Kd 0.1
#define Bits_To_Int 200/1023

int main() {    
    uint16_t POT_Value;
    uint8_t Set_Speed;
    uint8_t rpm;
    int16_t error;
    int32_t PID_Error;
    char LCD_String[2][40];
    
    AIC_Init();
    LCD_Init();
    MOT_Init(1);
    speed_Sensor_Init();
    macro_enable_interrupts();
    
    while(1) {
        //Set speed
        POT_Value = AIC_Val();
        Set_Speed = POT_Value * Bits_To_Int;
        
        //Measured speed
        rpm = get_Speed();
        
        //Correction signal
        error = Set_Speed - rpm;
        PID_Error = pid_controller(Kp, Ki, Kd, error);
        if (PID_Error > 255) {
            PID_Error = 255;
        } else if (PID_Error < 0) {
            PID_Error = 0;
        }
        //Output signal
        MOT_SetPhEnMotor1(0, PID_Error);
        
        sprintf(LCD_String[0], "Set %u CMD %d  ", Set_Speed, PID_Error);
        sprintf(LCD_String[1], "Speed %u   ", rpm);
        LCD_WriteStringAtPos(LCD_String[0], 0, 0);
        LCD_WriteStringAtPos(LCD_String[1], 1, 0);
    }
    return (0);
}