#ifndef _OC_H
#define _OC_H

/**
 * Platform: Basys MX3
 * Authors: Robert Konarskis, Michal Mikolajczyk
 * 
 * This library provides basic output compare units functionality for OCs 1-5.
 * Allows initializing an OC and an interrupt for that OC (optional).
 */

/**
 * External functions
 */

/**
 * Initialize an OC for a specific timer
 * 
 * @param freq - integer
 *        Peripheral bus clock frequency.
 * 
 * @param channel - integer
 *        OC selection (1-5).
 * 
 * @param timerChannel - integer
 *        Timer selection (2, 3).
 * 
 * @param period - integer
 *        OC trigger value (OCxR and OCxRS)
 * 
 * @param interruptEnabled - boolean
 *        Initialize an interrupt for this OC.
 *        
 * @param interruptPriority - integer
 *        Interrupt priority (1-7).
 * 
 * @return success
 */
int oc_init(int freq, int channel, int timerChannel, int period, int interruptEnabled, int interruptPriority);

/**
 * Attach an interrupt to an OC
 * 
 * @param channel - integer
 *        OC selection (1-5).
 * 
 * @param priority - integer
 *        Interrupt priority (1-7).
 */
void oc_attachInterrupt(int channel, int priority);

/**
 * Detach an interrupt from an OC
 * 
 * @param channel - integer
 *        OC selection (1-5).
 */
void oc_detachInterrupt(int channel);

/**
 * Disable an OC
 * 
 * @param channel - integer
 *        OC selection (1-5).
 */ 
void oc_stop(int channel);

/**
 * Internal functions
 */
int getTimerCode(int timerChannel);
void setupOc(int channel, int timerChannel, int period);

/**
 * OC __ISR examples

void __ISR(_OUTPUT_COMPARE_1_VECTOR, ipl7auto) Oc1ISR() {
    IFS0bits.OC1IF = 0;
}

void __ISR(_OUTPUT_COMPARE_2_VECTOR, ipl7auto) Oc2ISR() {
    IFS0bits.OC2IF = 0;
}

void __ISR(_OUTPUT_COMPARE_3_VECTOR, ipl7auto) Oc3ISR() {
    IFS0bits.OC3IF = 0;
}

void __ISR(_OUTPUT_COMPARE_4_VECTOR, ipl7auto) Oc4ISR() {
    IFS0bits.OC4IF = 0;
}

void __ISR(_OUTPUT_COMPARE_5_VECTOR, ipl7auto) Oc5ISR() {
    IFS0bits.OC5IF = 0;
}
*/

#endif /* _OC_H */