/* 
 * File:   string4digits.c
 * Author: Roy Meijer
 *
 * Created on 17 February 2022, 12:33
 */

#include "string4digits.h"

/* XC32 libraries */
#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>

void itoa4digits (int inputInt, char* outputString) {
    if (inputInt >= 0) {
        if (inputInt < 10) {
            sprintf(outputString, "   %d", inputInt);
        } else if (inputInt < 100) {
            sprintf(outputString, "  %d", inputInt);
        } else if (inputInt < 1000) {
            sprintf(outputString, " %d", inputInt);
        } else if (inputInt < 9999) {
            sprintf(outputString, "%d", inputInt);
        } else {
            sprintf(outputString, "%s", "9999");
        }
    } else {
        if (-inputInt < 10) {
            sprintf(outputString, "  -%d", -inputInt);
        } else if (-inputInt < 100) {
            sprintf(outputString, " -%d", -inputInt);
        } else if (-inputInt < 1000) {
            sprintf(outputString, "-%d", -inputInt);
        } else {
            sprintf(outputString, "%s", "-999");
        }
    }
}

void ftoa4digits (float inputFloat, char* outputString) {
    int tempFloat = (int)(inputFloat * 10);
    
    if (tempFloat >= 0) {
        if (tempFloat < 10) {
            sprintf(outputString, " 0.%d", tempFloat);
        } else if (tempFloat < 100) {
            sprintf(outputString, " %d.%d", tempFloat/10, tempFloat%10);
        } else if (tempFloat < 1000) {
            sprintf(outputString, "%d.%d", tempFloat/10, tempFloat%10);
        } else {
            sprintf(outputString, "%s", "99.9");
        }
    } else {
        if (-tempFloat < 10) {
            sprintf(outputString, "-0.%d", -tempFloat);
        } else if (-tempFloat < 100) {
            sprintf(outputString, "-%d.%d", (-tempFloat)/10, (-tempFloat)%10);
        } else {
            sprintf(outputString, "%s", "-9.9");
        }
    }
}