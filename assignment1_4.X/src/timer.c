#include <proc/p32mx370f512l.h>

#include "config.h"
#include "timer.h"

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
void Timer1_Init() {
    //Set period register to wrap every Timer1_Period seconds at 1:256 prescaler
    PR1 = (int)(((float)(Timer1_Period * PB_FRQ) / 256) - 1);
    //Clear the timer register
    TMR1CLR = 0xFFFF;
    //Set prescaler to 1:256
    T1CONSET = 0b11 << 4;
    //Set timer to use internal clock
    T1CONCLR = 1 << 1;
    //Disable Gated time accumulation
    T1CONCLR = 1 << 7;
    //Enable the timer
    T1CONSET = 1 << 15;
    //Set interrupt priority to 7 and subpriority to 3
    IPC1SET = 7 << 2;
    IPC1SET = 3 << 0;
    //Clear interrupt flag
    IFS0CLR = 1 << 4;
}

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
void Timer2_Init() {
    //Set period register to wrap every Timer2_Period seconds at 1:256 prescaler
    PR2 = (int)(((float)(Timer2_Period * PB_FRQ) / 256) - 1);
    //Clear the timer register
    TMR2CLR = 0xFFFF;
    //Set prescaler to 1:256
    T2CONSET = 0b111 << 4;
    //Set timer to use internal clock
    T2CONCLR = 1 << 1;
    //Disable 32-bit timer mode
    T2CONCLR = 1 << 3;
    //Disable Gated time accumulation
    T2CONCLR = 1 << 7;
    //Enable the timer
    T2CONSET = 1 << 15;
    //Set interrupt priority to 7 and subpriority to 2
    IPC2SET = 7 << 2;
    IPC2SET = 2 << 0;
    //Clear interrupt flag
    IFS0CLR = 1 << 9;
}