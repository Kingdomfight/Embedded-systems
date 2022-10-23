/* 
 * File:   testservo.c
 * Author: fercl
 *
 * Created on 20 oktober 2022, 2:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

#include "pragma.h"
#include "servo.h"
#include "basysmx3Debounce.h"

#define SERVO_CHANNEL 2
#define SERVO_START_ANGLE 0

int main(int argc, char** argv) {
    ansel_BTN_BTNR = 0;
    tris_BTN_BTNR = 1;
    tris_BTN_BTNC = 1;
    
    macro_enable_interrupts();
    if(servo_init(PB_FRQ, SERVO_CHANNEL, SERVO_START_ANGLE) == 0) {
        return 0;
    }
    
    int8_t servoAngle = SERVO_START_ANGLE;
    PIN_CHANGE BTNR_Status;
    PIN_CHANGE BTNC_Status;
    
    while(true) {
        BTNR_Status = basysmx3Debounce_debounceButton(BTNR_IDX);
        BTNC_Status = basysmx3Debounce_debounceButton(BTNC_IDX);
        if(BTNR_Status == RISING) {
            servoAngle += 5;
            servoAngle = (servoAngle > 45) ? 45 : servoAngle;
            servo_setpos(SERVO_CHANNEL, servoAngle);
        }
        if(BTNC_Status == RISING) {
            servoAngle -= 5;
            servoAngle = (servoAngle < -45) ? -45 : servoAngle;
            servo_setpos(SERVO_CHANNEL, servoAngle);
        }
    }
    return (1);
}

