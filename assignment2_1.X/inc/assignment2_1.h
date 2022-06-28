/* 
 * File:   assignment2_1.h
 * Author: Fer
 *
 * Created on 27 juni 2022, 16:57
 */

#ifndef ASSIGNMENT2_1_H
#define	ASSIGNMENT2_1_H

#include <xc.h>
#include "config.h"

#ifdef	__cplusplus
extern "C" {
#endif
    //public functions
    void speed_Sensor_Init();
    uint8_t get_Speed();
    int32_t pid_controller(float kp, float ki, float kd, int16_t error);
    
    //private functions
    static uint8_t calc_Speed();
    static void readEncoder(int edge);

#ifdef	__cplusplus
}
#endif

#endif	/* ASSIGNMENT2_1_H */

