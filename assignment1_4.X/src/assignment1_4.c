#include <xc.h>
#include <sys/attribs.h>
#include "assignment1_4.h"
#include "config.h"
#include "stdbool.h"
#include <proc/p32mx370f512l.h>
#include "basysmx3Debounce.h"
#include "led.h"
#include "lcd.h"

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
    
    macro_enable_interrupts();
}

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
void Timer1_SetPeriod(bool PeriodSelect) {
    if (PeriodSelect) {
        PR1 = (int)(((float)(Timer1_Period * PB_FRQ) / 256) - 1);
    } else {
        PR1 = (int)(((float)(Timer2_Period * PB_FRQ) / 256) - 1);
    }
}

void __ISR(_TIMER_1_VECTOR, ipl7auto) Timer1ISR(void) { 
    static int count = -3;
    LED_SetGroupValue(0x00);
    LED_ToggleValue(abs(count));
    if (count < 3) {
        count++;
    } else {
        count = -2;
    }
    
    IFS0CLR = 1 << 4; //Clear interrupt flag
}

void shift(char *Sequence, char input) {
    Sequence[2] = Sequence[1];
    Sequence[1] = Sequence[0];
    Sequence[0] = input;
}

state SequenceDetector(state CurrentState) {
    static char Sequence[3] = {'-','-','-'};
    T_Sequence CompleteSequence;
    int btnrDebounce = basysmx3Debounce_debounceButton(BTNR_IDX);
    int btndDebounce = basysmx3Debounce_debounceButton(BTND_IDX);
    int btncDebounce = basysmx3Debounce_debounceButton(BTNC_IDX);
    int btnlDebounce = basysmx3Debounce_debounceButton(BTNL_IDX);
    int btnuDebounce = basysmx3Debounce_debounceButton(BTNU_IDX);
    
    if (btnrDebounce == RISING) {
        shift(Sequence, 'R');
    }
    else if (btndDebounce == RISING) {
        shift(Sequence, 'D');
    }
    else if (btncDebounce == RISING || btnlDebounce == RISING 
            || btnuDebounce == RISING) {
        shift(Sequence, '-');
    }

    if (Sequence[0] == 'R' && Sequence[1] == 'R' && Sequence[2] == 'R') {
        CompleteSequence = RRR;
    }
    else if (Sequence[0] == 'R' && Sequence[1] == 'D' && Sequence[2] == 'D') {
        CompleteSequence = DDR;
    }
    else if (Sequence[0] == 'D' && Sequence[1] == 'R' && Sequence[2] == 'D') {
        CompleteSequence = DRD;
    }
    else {
        CompleteSequence = INV;
    }
    switch(CurrentState) {
        case S0: 
            if (CompleteSequence == RRR) {
                Sequence[0] = '-';
                CurrentState = S1;
            }
            break;
        case S1:
        case S2:
        case S3:
            if (CompleteSequence == RRR) {
                Sequence[0] = '-';
                CurrentState = S4;
            }
            else if (CompleteSequence == DDR) {
                Sequence[0] = '-';
                CurrentState = S3;
            }
            else if (CompleteSequence == DRD) {
                Sequence[0] = '-';
                CurrentState = S2;
            }
            break;
        case S4: 
            if (CompleteSequence == RRR) {
                Sequence[0] = '-';
                CurrentState = S1;
            }
            break;
    }
    return CurrentState;
}

void StateOutput(state CurrentState) {
    static state PreviousState = S1;
    if (CurrentState != PreviousState) {
            PreviousState = CurrentState;
            switch (CurrentState) {
                case S0:
                    LCD_DisplayClear();
                    LCD_WriteStringAtPos("KITT activated", 0, 0);
                    LED_SetGroupValue(0x0);
                    IEC0CLR = 1 << 4;
                    break;
                case S1:
                    LCD_DisplayClear();
                    LCD_WriteStringAtPos("Yes Michael", 0, 0);
                    LED_SetGroupValue(0xF);
                    IEC0CLR = 1 << 4;
                    break;
                case S2:
                    LCD_DisplayClear();
                    LCD_WriteStringAtPos("SWOOSH SWOOSH", 0, 0);
                    IEC0CLR = 1 << 4;
                    Timer1_SetPeriod(true);
                    IEC0SET = 1 << 4;
                    break;
                case S3:
                    LCD_DisplayClear();
                    LCD_WriteStringAtPos("TURBO BOOST", 0, 0);
                    IEC0CLR = 1 << 4;
                    Timer1_SetPeriod(false);
                    IEC0SET = 1 << 4;
                    break;
                case S4:
                    LCD_DisplayClear();
                    LCD_WriteStringAtPos("Bye Michael", 0, 0);
                    LED_SetGroupValue(0x00);
                    IEC0CLR = 1 << 4;
                    break;
            }
        }
}