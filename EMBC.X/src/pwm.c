#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "pwm.h"
#include "timer.h"
#include "oc.h"

int frq, periodUs;
int timer2Pr;
int timer3Pr;

void pwm_init(int freq, int timerChannel, int ocChannel, int period) {
    timer_init(freq, timerChannel, period, 1, 7);
    oc_init(freq, ocChannel, timerChannel, 0, 1, 7);
    
    if (timerChannel == 2) {
        timer2Pr = period * 1000;
    } else if (timerChannel == 3) {
        timer3Pr = period * 1000;
    }
}

void pwm_setWidth(int timerChannel, int ocChannel, int widthUs) {
    float fVal = ((float) (timer_getPeriod(timerChannel) + 1) * (float) widthUs) / getTimerTime(timerChannel);
    unsigned short value = (unsigned short) fVal; 
    
    switch(ocChannel) {
        case 1:
            OC1RS = value;
            OC1R = value;
            break;
            
        case 2:
            OC2RS = value;
            OC2R = value;
            break;
            
        case 3:
            OC3RS = value;
            OC3R = value;
            break;
            
        case 4:
            OC4RS = value;
            OC4R = value;
            break;
            
        case 5:
            OC5RS = value;
            OC5R = value;
            break;
            
        default:
            break;    
    }
}

int getTimerTime(int channel) {
    return channel == 2 ? timer2Pr : timer3Pr;
}
