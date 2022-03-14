/* 
 * File:   string4digits.h
 * Author: Roy Meijer
 *
 * Created on 17 February 2022, 12:33
 */

#ifndef _STRING4DIGITS_H
#define _STRING4DIGITS_H

#include <stdint.h>

//places interger in string buffer. caps at 4 digits
void itoa4digits (int inputInt, char* outputString);

//places floating point variable in string buffer. caps at 4 digits
void ftoa4digits (float inputFloat, char* outputString);

#endif /* _STRING4DIGITS_H */
