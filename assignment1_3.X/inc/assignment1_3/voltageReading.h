/* 
 * File:   voltageReading.h
 * Author: Roy Meijer
 *
 * Created on 16 February 2022, 15:03
 */

#ifndef _VOLTAGEREADING_H
#define _VOLTAGEREADING_H

#include <stdint.h>

//used for initialisation of the ADCs
void voltageReading_Init();

//used to read the battery voltage in milli volts
//should return the battery voltage in milli volts (type int16_t)
int16_t voltageReading_getBatteryMilliVolts();

//used to read the circuit current in milli amperes
//should return the circuit current in milli amperes (type int16_t)
int16_t voltageReading_getCircuitMilliAmperes();

#endif /* _VOLTAGEREADING_H */
