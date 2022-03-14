/* 
 * File:   main.c
 * Author: Roy Meijer
 *
 * Created on 16 February 2022, 15:03
 */

/* Generic C libraries */
#include <stdio.h>
#include <stdlib.h>

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>

/* Your own libraries */
#include "string4digits.h"
#include "timer1.h"

#include "led.h"
#include "lcd.h"

#include "voltageReading.h"
#include "temperatureReading.h"

// Device Config Bits in DEVCFG1:	
#pragma config FNOSC =      FRCPLL
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	XT
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_2

// Device Config Bits in  DEVCFG2:	
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

#pragma config JTAGEN =     OFF     
#pragma config FWDTEN =     OFF  

//assignment defines
#define LCD_ROWS 2
#define LCD_COLS 16
#define ALARM_TEMPERATURE 25.0
#define TIMER_FREQUENCY 2

int main() {
    //string which is printed to LCD
    char lcdString[LCD_ROWS][LCD_COLS];
    
    //measures values
    int16_t batteryMilliVolts = 0;
    int16_t circuitMilliAmperes = 0;
    float temperatureDegreesCelcius = 0.0;
    
    //measures values in string
    char batteryMilliVoltsString[5];
    char circuitMilliAmperesString[5];
    char temperatureDegreesCelciusString[5];
    
    //initialisation functions
    LED_Init();
    LCD_Init();
    
    timer1_Init(TIMER_FREQUENCY);
    
    voltageReading_Init();
    temperatureReading_Init();
    
    while(1) {
        //check if timer 1 has interrupted
        if (timer1_interrupted()) {
            //read milli volts, cap between 4 digits
            batteryMilliVolts = voltageReading_getBatteryMilliVolts();
            itoa4digits(batteryMilliVolts, batteryMilliVoltsString);
            
            //read milli amps, cap between 4 digits
            circuitMilliAmperes = voltageReading_getCircuitMilliAmperes();
            itoa4digits(circuitMilliAmperes, circuitMilliAmperesString);
            
            //makes sure there is 1 digit after the decimal sign
            temperatureDegreesCelcius = temperatureReading_getDegreesCelcius();
            ftoa4digits(temperatureDegreesCelcius, temperatureDegreesCelciusString);
            
            //store voltage and current on line 0 of lcd stringcircuitMilliAmperesString);
            sprintf(lcdString[0], "%s mV  %s mA", batteryMilliVoltsString, circuitMilliAmperesString);
            sprintf(lcdString[1], "%s deg C", temperatureDegreesCelciusString);
            
            //write voltage, current and temperature on LCD screen
            LCD_WriteStringAtPos(lcdString[0], 0, 0);
            LCD_WriteStringAtPos(lcdString[1], 1, 0);
            
            //blink LD1 when the temperature becomes above 25 degrees Celcius
            if (temperatureReading_checkAlarm(ALARM_TEMPERATURE)) {
                LED_ToggleValue(0);
            } else { //turn off LD1 when the temperature becomes below 25 degrees Celcius
                LED_SetValue(0, 0);
            }
        }
    }
    return (0);
}