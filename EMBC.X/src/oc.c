#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "oc.h"

#define ERROR -1

int clk;

int oc_init(int freq, int channel, int timerChannel, int period, int interruptEnabled, int interruptPriority) {
    clk = freq;
    
    setupOc(channel, getTimerCode(timerChannel), period);
    
    if (interruptEnabled) {
        oc_attachInterrupt(channel, interruptPriority);
    }
    
    return 1;
}

void oc_attachInterrupt(int channel, int priority) {
    switch(channel) {
        case 1:
            IPC1bits.OC1IP = priority;
            IPC1bits.OC1IS = 3;
            IFS0bits.OC1IF = 0;
            IEC0bits.OC1IE = 1;
            break;
            
        case 2:
            IPC2bits.OC2IP = priority;
            IPC2bits.OC2IS = 3;
            IFS0bits.OC2IF = 0;
            IEC0bits.OC2IE = 1;
            break;
            
        case 3:
            IPC3bits.OC3IP = priority;
            IPC3bits.OC3IS = 3;
            IFS0bits.OC3IF = 0;
            IEC0bits.OC3IE = 1;
            break;
            
        case 4:
            IPC4bits.OC4IP = priority;
            IPC4bits.OC4IS = 3;
            IFS0bits.OC4IF = 0;
            IEC0bits.OC4IE = 1;
            break;
            
        case 5:
            IPC5bits.OC5IP = priority;
            IPC5bits.OC5IS = 3;
            IFS0bits.OC5IF = 0;
            IEC0bits.OC5IE = 1;
            break;
            
        default: 
            break;
    }
}

void oc_detachInterrupt(int channel) {
    switch(channel) {
        case 1:
            IEC0bits.OC1IE = 0;
            break;
            
        case 2:
            IEC0bits.OC2IE = 0;
            break;
            
        case 3:
            IEC0bits.OC3IE = 0;
            break;
            
        case 4:
            IEC0bits.OC4IE = 0;
            break;
            
        case 5:
            IEC0bits.OC5IE = 0;
            break;
            
        default: 
            break;
    }
}

void oc_stop(int channel) {
    switch(channel) {
        case 1:
            OC1CONbits.ON = 0;
            break;
            
        case 2:
            OC2CONbits.ON = 0;
            break;
            
        case 3:
            OC3CONbits.ON = 0;
            break;
            
        case 4:
            OC4CONbits.ON = 0;
            break;
            
        case 5:
            OC5CONbits.ON = 0;
            break;
            
        default: 
            break;
    }
}

void setupOc(int channel, int timerChannel, int period) {
    switch(channel) {
        case 1:
            OC1RS = period;
            OC1R = period;
            OC1CONbits.ON = 0;
            OC1CONbits.OCM = 3;
            OC1CONbits.OCTSEL = timerChannel;
            OC1CONbits.ON = 1;
            break;
            
        case 2:
            OC2RS = period;
            OC2R = period;
            OC2CONbits.ON = 0;
            OC2CONbits.OCM = 3;
            OC2CONbits.OCTSEL = timerChannel;
            OC2CONbits.ON = 1;
            break;
            
        case 3:
            OC3RS = period;
            OC3R = period;
            OC3CONbits.ON = 0;
            OC3CONbits.OCM = 3;
            OC3CONbits.OCTSEL = timerChannel;
            OC3CONbits.ON = 1;
            break;
            
        case 4:
            OC4RS = period;
            OC4R = period;
            OC4CONbits.ON = 0;
            OC4CONbits.OCM = 3;
            OC4CONbits.OCTSEL = timerChannel;
            OC4CONbits.ON = 1;
            break;
            
        case 5:
            OC5RS = period;
            OC5R = period;
            OC5CONbits.ON = 0;
            OC5CONbits.OCM = 3;
            OC5CONbits.OCTSEL = timerChannel;
            OC5CONbits.ON = 1;
            break;
            
        default: 
            break;
    }
}

int getTimerCode(int timerChannel) {
    return timerChannel == 2 ? 0 : 1;
}