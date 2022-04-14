#ifndef _ASSIGNMENT_4_H
#define _ASSIGNMENT_4_H

#include "stdbool.h"

#define Timer1_Period 0.350 //350ms
#define Timer2_Period 0.175 //175ms

typedef enum{
    S0, S1, S2, S3, S4
}state;

typedef enum{
    RRR, DDR, DRD, INV
}T_Sequence;

/* ------------------------------------------------------------ */
/***	Timer1_Init
**
**	Parameters:
**		
**
**	Return Value:
**		
**
**	Description:
**		This function initializes timer 1 with a period of Timer1_Period seconds using the internal clock.
**      Timer1 interrupt is setup with a priority of 7 and subpriority of 3.
**      The interrupt enable bit has to be set manually using "IEC0SET = 1 << 4;".
**          
*/
void Timer1_Init();

/* ------------------------------------------------------------ */
/***	Timer1_SetPeriod
**
**	Parameters:
**		bool PeriodSelect       True: Set period to Timer1_Period
 *                              False: Set period to Timer2_Period
**
**	Return Value:
**		
**
**	Description:
**		This function sets timer 1 period register to either Timer1_Period or
 *      Timer2_Period depending on the parameter
**          
*/
void Timer1_SetPeriod(bool PeriodSelect);

void shift(char *Sequence, char input);

state SequenceDetector(state CurrentState);

void StateOutput(state CurrentState);

#endif