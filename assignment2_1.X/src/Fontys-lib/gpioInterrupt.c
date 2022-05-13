#include <xc.h>
#include <sys/attribs.h>
#include "led.h"

#include "gpioInterrupt.h"

volatile uint8_t CNRG9CallbackFlag = 0;
void (*CNRG9CallbackFunctionPointer)();

void gpioInterrupt_initCNRG9(void (*callbackFunction)()) {
    //disable change notice interrupt
    IEC1bits.CNGIE = 0;
    
    //register callback function
    CNRG9CallbackFunctionPointer = callbackFunction;
    CNRG9CallbackFlag = 1;
    
    LED_Init();
    
    //PMOD Pin JA10 is connected to bit 9 of port G (RG9)
    TRISGbits.TRISG3 = 1;
    ANSELGbits.ANSG9 = 0;
    
    CNPUGbits.CNPUG9 = 0;
    CNPDGbits.CNPDG9 = 0;
    CNENGbits.CNIEG9 = 1;
    CNCONGbits.ON = 1;
    
    IPC8bits.CNIP = 1;
    IPC8bits.CNIS = 0;
    IFS1bits.CNGIF = 0;
    
    //enable change notice interrupt
    IEC1bits.CNGIE = 1;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL1SOFT) CNHandler(void) {
    uint8_t tempCNRG9 = CNSTATGbits.CNSTATG9;
    if (IFS1bits.CNGIF == 1 && tempCNRG9 != 0) {
        uint8_t pinRG9 = PORTGbits.RG9;
        //check if callback function has been registered
        if (CNRG9CallbackFlag == 1) {
            if (pinRG9 == 1) {
                CNRG9CallbackFunctionPointer(1);
                //turn on led 0
                LED_SetValue(0, 1);
                //turn off led 1
                LED_SetValue(1, 0);
            } else { //if pinRG9 == 0
                CNRG9CallbackFunctionPointer(-1);
                //turn off led 0
                LED_SetValue(0, 0);
                //turn on led 1
                LED_SetValue(1, 1);
            }
        }
        tempCNRG9 = 0;
    }
    IFS1bits.CNGIF = 0;
}
