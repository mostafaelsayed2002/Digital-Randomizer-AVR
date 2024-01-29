/******************************************************************************
 *
 * Module: SEVEN_SEGMENT
 *
 * File Name: seven_segment.h
 *
 * Description: Header file for the AVR SEVEN_SEGMENT driver
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef struct 
{
   uint8 PORT_ID;
   uint8 PIN_ID;
}SEVEN_SEGMENT_Led;

typedef struct 
{
    SEVEN_SEGMENT_Led a;
    SEVEN_SEGMENT_Led b;
    SEVEN_SEGMENT_Led c;
    SEVEN_SEGMENT_Led d;
    SEVEN_SEGMENT_Led e;
    SEVEN_SEGMENT_Led f;
    SEVEN_SEGMENT_Led g;
    SEVEN_SEGMENT_Led DP;
}SEVEN_SEGMENT;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initializes the bins that connected to 7-segment 
 */
void SEVEN_SEGMENT_init(SEVEN_SEGMENT * sevenSegment);
/*
 * Description :
 * Display the val on the segment
 * If the number more that 15 or less than 0 ,The function will not handle the request. 
 */
void SEVEN_SEGMENT_write(SEVEN_SEGMENT *sevenSegment,uint8 val, uint8 valDp);

#endif
