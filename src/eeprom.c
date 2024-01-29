#include "eeprom.h"
#include "common_macros.h"
#include "reg.h"


void EEPOROM_init(EEPROM* eeprom){
    switch (eeprom->mode)
    {
    case ERASE_WRITE:
       CLEAR_BIT(EECR,EEPM0);
       CLEAR_BIT(EECR,EEPM1);
        break;
    case ERASE_ONLY:
       SET_BIT(EECR,EEPM0);
       CLEAR_BIT(EECR,EEPM1);
        break;
    case WRITE_ONLY:
       CLEAR_BIT(EECR,EEPM0);
       SET_BIT(EECR,EEPM1);
        break;
    }
}

void EEPROM_write(uint16 address, uint8 data)
{
while(READ_BIT(EECR,EEPE));

EEARL = (uint8) address;
EEARH = (uint8) (address>>8);
EEDR = data;

SET_BIT(EECR,EEMPE);
SET_BIT(EECR,EEPE);
}

uint8  EEPROM_read(uint16 address)
{
while(READ_BIT(EECR,EEPE));

EEARL = (uint8) address;
EEARH = (uint8) (address>>8);

SET_BIT(EECR,EERE);
return EEDR;
}

