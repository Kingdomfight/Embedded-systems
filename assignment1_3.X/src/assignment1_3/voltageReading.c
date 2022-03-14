/* 
 * File:   voltageReading.c
 * Author: ...
 *
 * Created on ...
 */

#include "voltageReading.h"

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>

#include "adc.h"

#define V_PRECISION 3.3/1024;

void voltageReading_Init() {
    ADC_Init();
}

int16_t voltageReading_getBatteryMilliVolts() {
    unsigned int ADC = ADC_AnalogRead(18);
    float V = ADC * V_PRECISION;
    return V * 1000;
}

int16_t voltageReading_getCircuitMilliAmperes() {
    unsigned int ADC = ADC_AnalogRead(19);
    float V = ADC * V_PRECISION;
    float I = V / 82;
    return I * 1000;
}