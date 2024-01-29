/******************************************************************************
 *
 * Module: RANDOMIZER
 *
 * File Name: gpio.h
 *
 * Description: Header file for the digital RANDOMIZER
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef _RANDOMIZER_H_
#define _RANDOMIZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TYPE PRNG
#define PRNG 0
#define TRNG 1

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * get random number
 */
uint16 rand();

#endif