/* 
 * File:   timer1.c
 * Author: Roy Meijer
 *
 * Created on 17 February 2022, 12:33
 */

#include "timer.h"

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>

void timer1_Init(uint16_t periodRegister) {
    T1CONbits.ON = 0; //disable timer
    TMR1 = 0; //initial value of counter register = 0
    T1CONbits.TCKPS = 0b11; //set prescaler to 1:256 (8 MHz / 256 = 31250 Hz)
    T1CONbits.TGATE = 0;
    T1CONbits.TCS = 0;
    PR1 = periodRegister; //set period register
    T1CONbits.ON = 1;  //enable timer
}

void timer2_Init(uint16_t periodRegister) {
    T2CONbits.ON = 0; //disable timer
    TMR2 = 0; //initial value of counter register = 0
    T2CONbits.TCKPS = 0b111; //set prescaler to 1:256 (8 MHz / 256 = 31250 Hz)
    T2CONbits.TGATE = 0;
    T2CONbits.TCS = 0;
    PR2 = periodRegister; //set period register
    T2CONbits.ON = 1; //enable timer
}

bool timer1_interrupted() {
    if (IFS0bits.T1IF) { //check if the timer has generated an interrupt by overflowing PR1
        IFS0bits.T1IF = 0; //clear interrupt bit
        return true; //return true
    }
    return false; //return false
}

bool timer2_interrupted() {
    if (IFS0bits.T2IF) { //check if the timer has generated an interrupt by overflowing PR2
        IFS0bits.T2IF = 0; //clear interrupt bit
        return true; //return true
    }
    return false; //return false
}

