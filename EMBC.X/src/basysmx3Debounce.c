/* 
 * File:   basysmx3Debounce.c
 * Author: Roy Meijer
 *
 * Created on 9 February 2022, 22:41
 */

#include "basysmx3Debounce.h"

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>

PIN_CHANGE basysmx3Debounce_debounceGeneric(PIN_LEVEL currentLevel, PIN_LEVEL *previousLevel, uint16_t *pressCount, uint16_t *releaseCount) {
    PIN_CHANGE returnValue = NO_CHANGE;
    
    if (currentLevel == HIGH) {
        (*pressCount) ++;
        *releaseCount = 0;
        if (*pressCount > BOUNCE_COUNT) {
            if (*previousLevel == LOW) {
                *previousLevel = HIGH;
                returnValue = RISING;
            }
            *pressCount = 0;
        }
    } else {
        (*releaseCount) ++;
        *pressCount = 0;
        if (*releaseCount > BOUNCE_COUNT) {
            if (*previousLevel == HIGH) {
                *previousLevel = LOW;
                returnValue = FALLING;
            }
            *releaseCount = 0;
        }
    }
    
    return returnValue;
}

PIN_CHANGE basysmx3Debounce_debounceButton(BTN_IDX buttonIndex) {
    static PIN_LEVEL previousLevel[NR_OF_BTN] = {LOW};
    static uint16_t pressCount[NR_OF_BTN] = {0};
    static uint16_t releaseCount[NR_OF_BTN] = {0};
    
    PIN_CHANGE returnValue = NO_CHANGE;
    
    switch (buttonIndex) {
        case BTNU_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTBbits.RB1), &(previousLevel[buttonIndex]), &(pressCount[buttonIndex]), &(releaseCount[buttonIndex]));
            break;
            
        case BTNL_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTBbits.RB0), &(previousLevel[buttonIndex]), &(pressCount[buttonIndex]), &(releaseCount[buttonIndex]));
            break;
            
        case BTNC_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTFbits.RF0), &(previousLevel[buttonIndex]), &(pressCount[buttonIndex]), &(releaseCount[buttonIndex]));
            break;
            
        case BTNR_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTBbits.RB8), &(previousLevel[buttonIndex]), &(pressCount[buttonIndex]), &(releaseCount[buttonIndex]));
            break;
            
        case BTND_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTAbits.RA15), &(previousLevel[buttonIndex]), &(pressCount[buttonIndex]), &(releaseCount[buttonIndex]));
            break;
    }
    return returnValue;
}

PIN_CHANGE basysmx3Debounce_debounceSwitch(SW_IDX switchIndex) {
    static PIN_LEVEL previousLevel[NR_OF_SW] = {LOW};
    static uint16_t pressCount[NR_OF_SW] = {0};
    static uint16_t releaseCount[NR_OF_SW] = {0};
    
    PIN_CHANGE returnValue = NO_CHANGE;
    
    switch (switchIndex) {
        case SW0_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTFbits.RF3), &(previousLevel[switchIndex]), &(pressCount[switchIndex]), &(releaseCount[switchIndex]));
            break;
            
        case SW1_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTFbits.RF5), &(previousLevel[switchIndex]), &(pressCount[switchIndex]), &(releaseCount[switchIndex]));
            break;
            
        case SW2_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTFbits.RF4), &(previousLevel[switchIndex]), &(pressCount[switchIndex]), &(releaseCount[switchIndex]));
            break;
            
        case SW3_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTDbits.RD15), &(previousLevel[switchIndex]), &(pressCount[switchIndex]), &(releaseCount[switchIndex]));
            break;
            
        case SW4_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTDbits.RD14), &(previousLevel[switchIndex]), &(pressCount[switchIndex]), &(releaseCount[switchIndex]));
            break;

        case SW5_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTBbits.RB11), &(previousLevel[switchIndex]), &(pressCount[switchIndex]), &(releaseCount[switchIndex]));
            break;
            
        case SW6_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTBbits.RB10), &(previousLevel[switchIndex]), &(pressCount[switchIndex]), &(releaseCount[switchIndex]));
            break;

        case SW7_IDX:
            returnValue = basysmx3Debounce_debounceGeneric((PIN_LEVEL)(PORTBbits.RB9), &(previousLevel[switchIndex]), &(pressCount[switchIndex]), &(releaseCount[switchIndex]));
            break;
    }
    return returnValue;
}