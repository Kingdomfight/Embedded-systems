#include <xc.h>
#include <sys/attribs.h>
#include <proc/p32mx370f512l.h>

#include "assignment1_4.h"
#include "led.h"

void __ISR(_TIMER_1_VECTOR, ipl7auto) Timer1ISR(void) { 
    LED_ToggleValue(0);
    
    IFS0CLR = 1 << 4; //Clear interrupt flag
}

void __ISR(_TIMER_2_VECTOR, ipl7auto) Timer2ISR(void) {
    LED_ToggleValue(1);
    
    IFS0CLR = 1 << 9; //Clear interrupt flag
}