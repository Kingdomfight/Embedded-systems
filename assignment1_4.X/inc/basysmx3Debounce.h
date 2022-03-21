/* 
 * File:   basysmx3Debounce.h
 * Author: Roy Meijer
 *
 * Created on 9 February 2022, 22:41
 */

#ifndef _BASYSMX3DEBOUNCE_H
#define _BASYSMX3DEBOUNCE_H

/* required for uint16_t type*/
#include <stdint.h>

/* debouce counter value, may be tweaked to change debounce speed or accuracy */
#define BOUNCE_COUNT 200

/* number of pushbuttons on Basys MX3 board */
#define NR_OF_BTN 5

/* number of switches on Basys MX3 board */
#define NR_OF_SW 8

/* typedef enum for the level of a GPIO pin */
typedef enum {
    LOW = 0,
    HIGH = 1
} PIN_LEVEL;

/* typedef enum for the change in the level of a GPIO pin */
typedef enum {
    FALLING = -1,
    NO_CHANGE = 0,
    RISING = 1
} PIN_CHANGE;

/* typedef enum for the indexes of the Basys MX3 board pushbuttons */
typedef enum {
    BTNU_IDX = 0,
    BTNL_IDX = 1,
    BTNC_IDX = 2,
    BTNR_IDX = 3,
    BTND_IDX = 4
} BTN_IDX;

/* typedef enum for the indexes of the Basys MX3 board toggle switches */
typedef enum {
    SW0_IDX = 0,
    SW1_IDX = 1,
    SW2_IDX = 2,
    SW3_IDX = 3,
    SW4_IDX = 4,
    SW5_IDX = 5,
    SW6_IDX = 6,
    SW7_IDX = 7,           
} SW_IDX;

/* ========================================================================== */
/* function: basysmx3Debounce_debounceGeneric( currentLevel,                  */
/*                                             &previousLevel,                */
/*                                             &pressCount,                   */
/*                                             &releaseCount );               */
/*                                                                            */
/* description: Debounces a GPIO pin based on the current level of the pin,   */
/* previous level of the pin, press counterand release counter.               */
/*                                                                            */
/* Returns FALLING (-1) when the pin is debounced from high to low,           */
/* Returns NO_CHANGE (0) if the pin has not been debounced                    */
/* Returns RISING (1) if the pin is debounced from low to HIGH                */
/* ========================================================================== */
PIN_CHANGE basysmx3Debounce_debounceGeneric(PIN_LEVEL currentLevel, PIN_LEVEL *previousLevel, uint16_t *pressCount, uint16_t *releaseCount);

/* ========================================================================== */
/* function: basysmx3Debounce_debounceButton( buttonIndex )                  */
/*                                                                            */
/* description: Debounces a pushbutton based on the index number of the button*/
/* (see typedef enum BTN_IDX)                                                 */
/*                                                                            */
/* Returns FALLING (-1) when the button is debounced from high to low,        */
/* Returns NO_CHANGE (0) if the button has not been debounced                 */
/* Returns RISING (1) if the button debounced from low to HIGH                */
/* ========================================================================== */
PIN_CHANGE basysmx3Debounce_debounceButton(BTN_IDX buttonIndex);

/* ========================================================================== */
/* function: basysmx3Debounce_debounceSwitch( buttonIndex )                   */
/*                                                                            */
/* description: Debounces a toggle switch based on the index number of        */
/* the switch. (see typedef enum SW_IDX)                                      */
/*                                                                            */
/* Returns FALLING (-1) when the switch is debounced from high to low,        */
/* Returns NO_CHANGE (0) if the switch has not been debounced                 */
/* Returns RISING (1) if the switch debounced from low to HIGH                */
/* ========================================================================== */
PIN_CHANGE basysmx3Debounce_debounceSwitch(SW_IDX switchIndex);

#endif /* _BASYSMX3DEBOUNCE_H */
