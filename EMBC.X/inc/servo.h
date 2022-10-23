/* 
 * File:   servo.h
 * Author: Fer
 *
 * Created on 22 oktober 2022, 17:41
 */

#ifndef SERVO_H
#define	SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ========================================================================== */
/* function: servo_init( fpb, channel, angle );                               */
/*                                                                            */
/* description: initialises a servo channel.                                  */
/*                                                                            */
/* pre:     fpb - peripheral bus clock frequency in Hz                        */
/*          channel - number of the servo channel to initialise               */
/*                    (range 1...5)                                           */
/*          angle - servo opening angle in degrees (range -45...45)           */
/*                                                                            */
/* post: return value - 0 if initialisation failed, 1 if succeeded            */
/* ========================================================================== */
uint8_t servo_init
(
    int fpb,
    uint8_t channel,
    int8_t angle
);
/* ========================================================================== */
/* function: servo_setpos( fpb, channel, angle );                             */
/*                                                                            */
/* description: changes the opening angle for a servo channel.                */
/*                                                                            */
/* pre:     channel - number of the servo channel to set the position for     */
/*                    (range 1...5)                                           */
/*          angle - servo opening angle in degrees (range -45...45)           */
/*                                                                            */
/* post: none                                                                 */
/* ========================================================================== */
void servo_setpos
(
    uint8_t channel,
    int8_t angle
);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

