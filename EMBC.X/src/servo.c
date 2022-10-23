#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "servo.h"
#include "pwm.h"
#include "timer.h"
#include "oc.h"

#define PWM_TIMER 2
#define PWM_PERIOD 50

#define CHANNEL_1_MASK  0b00000001
#define CHANNEL_2_MASK  0b00000010

static uint8_t SetupPin( uint8_t channel );
static uint16_t AngleToUs( int8_t angle );
static void servo_T2callback( void );
static void servo_OC1callback( void );
static void servo_OC2callback( void );

static uint8_t Active_Channels = 0;

uint8_t servo_init( int fpb, uint8_t channel, int8_t angle ) {
    if(!SetupPin(channel)) {
        return 0;
    }
    timer_register_T2callback(servo_T2callback);
    pwm_init(fpb, PWM_TIMER, channel, PWM_PERIOD);
    uint16_t PWM_Time = AngleToUs(angle);
    pwm_setWidth(PWM_TIMER, channel, PWM_Time);
    return 1;
}

void servo_setpos( uint8_t channel, int8_t angle ) {
    uint16_t PWM_Time = AngleToUs(angle);
    pwm_setWidth(PWM_TIMER, channel, PWM_Time);
}

static uint8_t SetupPin( uint8_t channel ) {
    switch(channel) {
        case 1:
            ansel_SRV_S0PWM = 0;
            tris_SRV_S0PWM = 0;
            Active_Channels |= CHANNEL_1_MASK;
            break;
        case 2:
            tris_SRV_S1PWM = 0;
            Active_Channels |= CHANNEL_2_MASK;
            break;
        default:
            return 0;
            break;
    }
    return 1;
}

static uint16_t AngleToUs( int8_t angle ) {
    angle = (angle > 45) ? 45 : ((angle < -45) ? -45 : angle);
    uint16_t Time = (600/45)*angle + 1500;
    return Time;
}

static void servo_T2callback( void ) {
    if(Active_Channels & CHANNEL_1_MASK) {
        lat_SRV_S0PWM = 1;
    }
    if(Active_Channels & CHANNEL_2_MASK) {
        lat_SRV_S1PWM = 1;
    }
}

static void servo_OC1callback( void ) {
    lat_SRV_S0PWM = 0;
}

static void servo_OC2callback( void ) {
    lat_SRV_S1PWM = 0;
}