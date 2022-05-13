/* 
 * File:   timer1.h
 * Author: Roy Meijer
 *
 * Created on 17 February 2022, 12:33
 */

#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>
#include <stdbool.h>

//initialisation of timer 1
void timer1_Init(uint16_t periodRegister);

//initialisation of timer 2
void timer2_Init(uint16_t periodRegister);

//checks if timer 1 has generated an interrupt by overflowing value of PR1
bool timer1_interrupted();

//checks if timer 1 has generated an interrupt by overflowing value of PR2
bool timer2_interrupted();

#endif /* _TIMER1_H */
