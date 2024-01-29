/******************************************************************************
 *
 * Module: TIMER1 PWM
 *
 * File Name: external_interrupt.h
 *
 * Description: Header file for the AVR TIMER1 PWM driver
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef _TIMER1_PWM_
#define _TIMER1_PWM_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
    TIMER1_NORMAL_PWM,
    TIMER1_NON_INVERTING_PWM,
    TIMER1_INVERTING_PWM
}TIMER1_PWM_ComMode;

typedef enum{
    TIMER1_FAST_PWM_8_BIT,
    TIMER1_FAST_PWM_9_BIT,
    TIMER1_FAST_PWM_10_BIT,
    TIMER1_FAST_PWM_ICR1,
    TIMER1_FAST_PWM_OCR1A
}TIMER1_PWM_ModeOfOperation;


typedef enum{
    TIMER1_PWM_1_CLOCK,
    TIMER1_PWM_8_CLOCK,
    TIMER1_PWM_64_CLOCK,
    TIMER1_PWM_256_CLOCK,
    TIMER1_PWM_1024_CLOCK
}TIMER1_PWM_Clock;


typedef struct 
{
    TIMER1_PWM_Clock clock;
    TIMER1_PWM_ComMode comA;
    TIMER1_PWM_ComMode comB;
    TIMER1_PWM_ModeOfOperation mode;
    uint16 ICR1_PWM;
    uint16 OCR1A_PWM;
}TIMER1_PWM;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initializes PWM in Timer1 
 */
void TIMER1_PWM_init(TIMER1_PWM * pwm);
/*
 * Description :
 * Change the duty cycle of oc1a
 */
void TIMER1_PWM_DutyCycle_OC1A(float32 Precent,TIMER1_PWM *pwm);
/*
 * Description :
 * Change the duty cycle of oc1b
 */
void TIMER1_PWM_DutyCycle_OC1B(float32 Precent,TIMER1_PWM *pwm);
/*
 * Description :
 * move a sevro motor connected to ocra with specific angle
 * minus90 and pluse90 in ms
 */
void TIMER1_PWM_DutyCycle_OC1A_Servo(uint16 Angle ,TIMER1_PWM *pwm ,uint8 minus90 ,uint8 pluse90);

#endif  


