/* 
 * File:   gpioInterrupt.h
 * Author: Roy Meijer
 *
 * Created on 24 April 2022, 12:29
 */

#ifndef _GPIOINTERRUPT_H
#define _GPIOINTERRUPT_H

#include <stdint.h>

void gpioInterrupt_initCNRG9(void (*callbackFunction)());

#endif /* _GPIOINTERRUPT_H */
