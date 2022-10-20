#ifndef _PWM_H
#define _PWM_H

/**
 * Platform: Basys MX3
 * Authors: Robert Konarskis, Michal Mikolajczyk
 * 
 * This library provides basic PWM functionality using timer and oc libraries.
 * Allows initializing a PWM channel by using a timer and an OC, and generates interrupts for those.
 */

/**
 * External functions
 */

/**
 * Initialize a PWM signal for a specified timer and OC unit.
 * Interrupts for the selected timer and OC unit are enabled with a priority of 7.
 * 
 * @param freq - integer
 *        Peripheral bus clock frequency.
 * 
 * @param timerChannel - integer
 *        Timer selection (2, 3).
 * 
 * @param ocChannel - integer
 *        OC selection (1-5).
 * 
 * @param period - integer
 *        PWM period value in ms.
 */
void pwm_init(int freq, int timerChannel, int ocChannel, int period);

/**
 * Set width of PWM signal in us.
 * 
 * @param timerChannel - integer
 *        Timer selection (2, 3).
 * 
 * @param ocChannel - integer
 *        OC selection (1-5).
 * 
 * @param widthUs - integer
 *        PWM signal width in us.
 */
void pwm_setWidth(int timerChannel, int ocChannel, int widthUs);

/**
 * Internal functions
 */
int getTimerTime(int channel);

#endif /* _PWM_H */