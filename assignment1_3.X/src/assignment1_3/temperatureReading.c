/* 
 * File:   temperatureReading.c
 * Author: ...
 *
 * Created on ...
 */

#include "temperatureReading.h"

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>

#include "DS18B20.h"

char tempAddress [9];
float temp;

void temperatureReading_Init() {
    getAddress(tempAddress);
}

float temperatureReading_getDegreesCelcius() {
    broadcastConvert();
    temp = getTemperature(tempAddress);
    
    return temp;
}

uint8_t temperatureReading_checkAlarm(float alarmTemperature) {
    
    if(temp >= alarmTemperature){
        return 1;
    }
    else{
        return 0;
    }
}