/******************************************************************************
 *
 * Module: EXTERNAL INTERRRUPT
 *
 * File Name: interrupts.h
 *
 * Description: Header file for the AVR EXTERNAL INTERRRUPT
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef _EXTERNAL_INTERRUPTS_H
#define _EXTERNAL_INTERRUPTS_H


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
    INT_INT0,
    INT_INT1,
    INT_PCINT0,
    INT_PCINT1,
    INT_PCINT2,
    INT_PCINT3,
    INT_PCINT4,
    INT_PCINT5,
    INT_PCINT6,
    INT_PCINT7,
    INT_PCINT8,
    INT_PCINT9,
    INT_PCINT10,
    INT_PCINT11,
    INT_PCINT12,
    INT_PCINT13,
    INT_PCINT14,
    INT_PCINT16,
    INT_PCINT17,
    INT_PCINT18,
    INT_PCINT19,
    INT_PCINT20,
    INT_PCINT21,
    INT_PCINT22,
    INT_PCINT23
}EXTERNAL_INTERRUPTS_Types;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * Enable the passed external interrupt 
 * support external interrupr from INT0 to PCINT23
 */
void EXTERNAL_INTERRUPTS_init(EXTERNAL_INTERRUPTS_Types interruptType);
/*
 * Description :
 * Disable the passed external interrupt
 * support external interrupr from INT0 to PCINT23
 */
void EXTERNAL_INTERRUPTS_diable(EXTERNAL_INTERRUPTS_Types interruptType);

#endif