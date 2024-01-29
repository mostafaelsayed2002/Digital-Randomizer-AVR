/******************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: eeprom.h
 *
 * Description: Header file for the AVR EEPROM driver
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef _EEPROM_H_
#define _EEPROM_H_

 #include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
    ERASE_WRITE,
    ERASE_ONLY,
    WRITE_ONLY    
}EEPROM_Mode;

typedef struct 
{
    EEPROM_Mode mode;
}EEPROM;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize The EEPROM 
 * set the mode (erase and write | erase only | write only)
 */
void EEPOROM_init(EEPROM* eeprom);
/*
 * Description :
 * write to a specific address in EEPROM
 * wait untill the previous writing is finished
 */
void EEPROM_write(uint16 address, uint8 data); 
/*
 * Description :
 * read from a specific address in EEPROM
 * wait untill the previous writing is finished
 */
uint8  EEPROM_read(uint16 address);



#endif  