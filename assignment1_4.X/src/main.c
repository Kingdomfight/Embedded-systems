/* 
 * File:   main.c
 * Author: Roy Meijer
 *
 * Created on 6 March 2022, 21:02
 */

/* Generic C libraries */
#include <stdio.h>
#include <stdlib.h>

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>

/* Your own libraries */
#include "config.h"
#include "timer.h"
#include "led.h"
#include "btn.h"
#include "basysmx3Debounce.h"
#include "utils.h"
#include "assignment1_4.h"
#include <proc/p32mx370f512l.h>

/* Device Config Bits in DEVCFG1:  */
#pragma config FNOSC =      FRC
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	XT
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_1

/* Device Config Bits in  DEVCFG2: */
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

#pragma config JTAGEN =     OFF     
#pragma config FWDTEN =     OFF  

int main() {
    //all intialization functions
    LED_Init();
    Timer1_Init();
    Timer2_Init();
    macro_enable_interrupts();
    IEC0SET = 1 << 4;
    IEC0SET = 1 << 9;
    while(1) {
        //infinite loop
    }
    return (0);
}