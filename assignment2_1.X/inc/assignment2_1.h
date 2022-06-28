/* 
 * File:   assignment2_1.h
 * Author: Fer
 *
 * Created on 27 juni 2022, 16:57
 */

#ifndef ASSIGNMENT2_1_H
#define	ASSIGNMENT2_1_H

#include <xc.h>
#include "config.h"

#define RPM_DIVIDER 30*PB_FRQ/256
#define Bits_To_Int 200/1023
#define Timer1_PR 1

#ifdef	__cplusplus
extern "C" {
#endif

    uint8_t getSpeed();
    void readEncoder(int edge);
    
    extern volatile uint8_t localCount;


#ifdef	__cplusplus
}
#endif

#endif	/* ASSIGNMENT2_1_H */

