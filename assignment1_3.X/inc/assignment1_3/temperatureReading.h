/* 
 * File:   temperatureReading.h
 * Author: Roy Meijer
 *
 * Created on 16 February 2022, 15:03
 */

#ifndef _TEMPERATUREREADING_H
#define _TEMPERATUREREADING_H

#include <stdint.h>

//used for initialisation of the DS18B20 temperature sensor
void temperatureReading_Init();

//used for reading the DS18B20 temperature sensor
//should return the temperature in degrees Celcius, type float
float temperatureReading_getDegreesCelcius();

//used for checking if the measured temperature has exceeded the alarm temperature
//the input is the alarm temperature, type float
//if the measured temperature has exceeded the alarm temperature, the function should return 1 (type uint8_t). otherwise it should return 0 (type uint8_t).
uint8_t temperatureReading_checkAlarm(float alarmTemperature);

#endif /* _TEMPERATUREREADING_H */
