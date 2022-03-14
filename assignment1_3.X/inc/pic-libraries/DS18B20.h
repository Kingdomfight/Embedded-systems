#ifndef DS18B20_h
#define DS18B20_h

#include <stdio.h>
#include <stdlib.h>
#include "onewire.h"

void broadcastConvert();
float getTemperature(unsigned char* address);
int getTemperatureInt(unsigned char* address);
void getAddress(char* address);

#endif