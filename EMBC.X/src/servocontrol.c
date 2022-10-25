/* 
 * File:   servocontrol.c
 * Author: Fer
 *
 * Created on 24 oktober 2022, 1:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

#include "pragma.h"
#include "servo.h"
#include "timer.h"
#include "spiflash.h"


#define SERVO_CHANNEL 2
#define SERVO_DEFAULT_ANGLE 0
#define BTN_TMR 1
#define BTN_TMR_PRD 0xFFFF
#define BTN_TMR_PRE 64
#define SPIFLASH_ANGLE_ADDR 0x00F000

int main(int argc, char** argv) {
    ansel_BTN_BTNR = 0;
    tris_BTN_BTNR = 1;
    tris_BTN_BTNC = 1;
    int prescalerCode = getPrescalerCode(BTN_TMR, BTN_TMR_PRE);
    if(timer_initRaw(PB_FRQ, BTN_TMR, BTN_TMR_PRD, prescalerCode, 0, 0) == -1) {
        return 0;
    }
    timer_stop(BTN_TMR);
    timer_reset(BTN_TMR);
    
    SPIFLASH_Init();
    int8_t servoAngle;
    uint8_t servoAngleChange = 0;
    SPIFLASH_Read(SPIFLASH_ANGLE_ADDR, &servoAngle, 1);
    servoAngle = (servoAngle > 45 || servoAngle < -45) ? SERVO_DEFAULT_ANGLE : servoAngle;
    
    if(servo_init(PB_FRQ, SERVO_CHANNEL, servoAngle) == 0) {
        return 0;
    }
    macro_enable_interrupts();
    
    while(true) {
        if(prt_BTN_BTNR != prt_BTN_BTNC) {
            timer_start(BTN_TMR);
            if(TMR1 >= PB_FRQ/BTN_TMR_PRE*0.1) {
                timer_reset(BTN_TMR);
                if(prt_BTN_BTNR) {
                    servoAngle = (servoAngle >= 45) ? 45 : ++servoAngle;
                } else {
                    servoAngle = (servoAngle <= -45) ? -45 : --servoAngle;
                }
                servo_setpos(SERVO_CHANNEL, servoAngle);
                servoAngleChange = 1;
            }
        } else {
            timer_stop(BTN_TMR);
            if(servoAngleChange) {
                SPIFLASH_Erase4k(SPIFLASH_ANGLE_ADDR);
                SPIFLASH_ProgramPage(SPIFLASH_ANGLE_ADDR, &servoAngle, 1);
                servoAngleChange = 0;
            }
        }
    }
    return 1;
}

