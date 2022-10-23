#ifndef _TIMER_H
#define _TIMER_H

/**
 * Platform: Basys MX3
 * Authors: Robert Konarskis, Michal Mikolajczyk
 * 
 * This library provides basic timer functionality for Timers 1-5.
 * Allows initializing a timer and an interrupt for that timer (optional).
 */

/**
 * External functions
 */

/**
 * Initialize a timer providing period in ms
 * 
 * @param freq - integer
 *        Peripheral bus clock frequency.
 * 
 * @param channel - integer
 *        Timer selection (1-5).
 * 
 * @param periodMs - integer
 *        Timer period in ms. 
 *        Keep in mind that the upper limit depends on clock frequency.
 * 
 * @param interruptEnabled - boolean
 *        Initialize an interrupt for this timer.
 *        
 * @param interruptPriority - integer
 *        Interrupt priority (1-7).
 * 
 * @return success
 */
int timer_init(int freq, int channel, int periodMs, int interruptEnabled, int interruptPriority);

/**
 * Initialize a timer providing PRx and prescaler values
 * 
 * @param freq - integer
 *        Peripheral bus clock frequency.
 * 
 * @param channel - integer
 *        Timer selection (1-5).
 * 
 * @param period - integer
 *        Timer PR register value
 * 
 * @param prescaler - integer
 *        Timer prescaler value
 * 
 * @param interruptEnabled - boolean
 *        Initialize an interrupt for this timer.
 *        
 * @param interruptPriority - integer
 *        Interrupt priority (1-7).
 * 
 * @return success
 */
int timer_initRaw(int freq, int channel, int period, int prescaler, int interruptEnabled, int interruptPriority);

/**
 * Attach an interrupt to a timer
 * 
 * @param channel - integer
 *        Timer selection (1-5).
 * 
 * @param priority - integer
 *        Interrupt priority (1-7).
 */
void timer_attachInterrupt(int channel, int priority);

/**
 * Detach an interrupt from a timer
 * 
 * @param channel - integer
 *        Timer selection (1-5).
 */
void timer_detachInterrupt(int channel);

/**
 * Disable a timer
 * 
 * @param channel - integer
 *        Timer selection (1-5).
 * 
 * @return success
 */
int timer_stop(int channel);

/**
 * Reset timer counter
 * 
 * @param channel - integer
 *        Timer selection (1-5).
 */
void timer_reset(int channel);

/**
 * Get PRx value of defined timer channel
 * 
 * @param channel - integer
 *        Timer selection (1-5).
 * 
 * @return PR value
 */
int timer_getPeriod(int channel);

/**
 * Internal functions
 */
int getPrescaler(int channel, int periodMs);
int getPrescalerCode(int channel, int prescaler);
int getPeriod(int channel, int periodMs, int prescaler);
void setupTimer(int channel, int period, int prescalerCode);
void savePeriod(int channel, int period);

/**
 * Timer __ISR examples

void __ISR(_TIMER_1_VECTOR, ipl7auto) Timer1ISR() {
    IFS0bits.T1IF = 0;
}

void __ISR(_TIMER_2_VECTOR, ipl7auto) Timer2ISR() {
    IFS0bits.T2IF = 0;
}

void __ISR(_TIMER_3_VECTOR, ipl7auto) Timer3ISR() {
    IFS0bits.T3IF = 0;
}

void __ISR(_TIMER_4_VECTOR, ipl7auto) Timer4ISR() {
    IFS0bits.T4IF = 0;
}

void __ISR(_TIMER_5_VECTOR, ipl7auto) Timer5ISR() {
    IFS0bits.T5IF = 0;
}
*/

#endif /* _TIMER_H */