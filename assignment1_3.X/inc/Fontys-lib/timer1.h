/* 
 * File:   timer1.h
 * Author: Roy Meijer
 *
 * Created on 17 February 2022, 12:33
 */

#ifndef _TIMER1_H
#define _TIMER1_H

#include <stdint.h>
#include <stdbool.h>

//initialisation of timer 1 for an interrupt rate of 2 Hz
void timer1_Init(uint16_t frequency);

//checks if timer 1 has interrupted
bool timer1_interrupted();

#endif /* _TIMER1_H */
