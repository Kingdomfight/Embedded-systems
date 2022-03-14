/* 
 * File:   timer1.c
 * Author: Roy Meijer
 *
 * Created on 17 February 2022, 12:33
 */

#include "timer1.h"

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>

void timer1_Init(uint16_t frequency) {
    TMR1 = 0; //initial value of timer register = 0
    T1CON = 0x8030; //set prescaler to 1:256 (approx 31250 Hz)
    if (frequency < 15625) {
        PR1 = (31250 / frequency) - 1; //set period register to make timer overflow at "frequency"
    } else {
        PR1 = 0; //frequecy = 31250
    }
}

bool timer1_interrupted() {
    if (IFS0bits.T1IF) { //check if the timer has generated an interrupt by overflowing PR1
        IFS0bits.T1IF = 0; //clear interrupt bit
        return true; //return true
    }
    return false; //return false
}
