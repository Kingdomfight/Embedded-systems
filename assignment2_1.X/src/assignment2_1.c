#include <xc.h>
#include "assignment2_1.h"

volatile uint8_t localCount = 0;

uint8_t getSpeed() {
    T1CONCLR = 1 << 15; //Disable timer 1
    uint16_t Time = TMR1;
    TMR1CLR = 0xFFFF;   //Reset timer 1
    T1CONSET = 1 << 15; //Enable timer 1
    localCount = 0;
    uint16_t RPM = RPM_DIVIDER/Time;
    return RPM;
}

void readEncoder(int edge) {
    //put your change notice (rotary encoder) interrupt code here
    if (edge == 1) {
        localCount++;
    }
}