#include <xc.h>
#include "assignment2_1.h"
#include "timer.h"
#include "gpioInterrupt.h"

#define RPM_DIVIDER 30*PB_FRQ/256
#define Timer2_PR 0.1*PB_FRQ/256
#define dt 0.1

static volatile uint8_t rpm = 0;

void speed_Sensor_Init() {
    gpioInterrupt_initCNRG9(readEncoder);
    timer1_Init(0xFFFF);
    timer2_Init(Timer2_PR);
}

static uint8_t calc_Speed() {
    T1CONCLR = 1 << 15; //Disable timer 1
    uint16_t Time = TMR1;
    TMR1CLR = 0xFFFF;   //Reset timer 1
    T1CONSET = 1 << 15; //Enable timer 1
    rpm = RPM_DIVIDER/Time;
}

uint8_t get_Speed() {
    if(timer2_interrupted()) {  //If rpm drops below 30, return 0
        return 0;
    } else {
        return rpm;
    }
}

static void readEncoder(int edge) {
    static uint8_t localCount = 0;
    if(edge == 1) {
        TMR2CLR = 0xFFFF;
        if(localCount >= 9) {
            calc_Speed();
            localCount = 0;
        } else {
            localCount++;
        }
    }
}

int32_t pid_controller(float kp, float ki, float kd, int16_t error) {
    int32_t output;
    static int16_t prevError = 0;
    static int16_t intError = 0;
    int16_t diffError = error - prevError;
    intError += error;
    output = (int32_t)(error*kp + intError*ki*dt + diffError*kd/dt);
    prevError = error;
    return output;
}