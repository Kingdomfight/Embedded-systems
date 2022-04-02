#ifndef _TIMER_H
#define _TIMER_H

#define Timer1_Period 0.175 //175ms
#define Timer2_Period 0.350 //350ms

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
/***	Timer2_Init
**
**	Parameters:
**		
**
**	Return Value:
**		
**
**	Description:
**		This function initializes timer 2 with a period of Timer2_Period seconds using the internal clock.
**      Timer2 interrupt is setup with a priority of 7 and subpriority of 2.
**      The interrupt enable bit has to be set manually using "IEC0SET = 1 << 9;".
**          
*/
void Timer2_Init();

#endif