#include "external_interrupts.h"
#include "reg.h"
#include "common_macros.h"

void EXTERNAL_INTERRUPTS_init(EXTERNAL_INTERRUPTS_Types interruptType)
{
    CLEAR_BIT(SREG, 7);
    switch (interruptType)
    {
    case INT_INT0:
        SET_BIT(EICRA, ISC00);
        SET_BIT(EICRA, ISC01);
        SET_BIT(EIMSK, INT0);
        break;
    case INT_INT1:
        SET_BIT(EICRA, ISC10);
        SET_BIT(EICRA, ISC11);
        SET_BIT(EIMSK, INT1);
        break;
    case INT_PCINT0:
        SET_BIT(PCICR, PCIE0);
        SET_BIT(PCMSK0, PCINT0);
        break;
    case INT_PCINT1:
        SET_BIT(PCICR, PCIE0);
        SET_BIT(PCMSK0, PCINT1);
        break;
    case INT_PCINT2:
        SET_BIT(PCICR, PCIE0);
        SET_BIT(PCMSK0, PCINT2);
        break;
    case INT_PCINT3:
        SET_BIT(PCICR, PCIE0);
        SET_BIT(PCMSK0, PCINT3);
        break;
    case INT_PCINT4:
        SET_BIT(PCICR, PCIE0);
        SET_BIT(PCMSK0, PCINT4);
        break;
    case INT_PCINT5:
        SET_BIT(PCICR, PCIE0);
        SET_BIT(PCMSK0, PCINT5);
        break;
    case INT_PCINT6:
        SET_BIT(PCICR, PCIE0);
        SET_BIT(PCMSK0, PCINT6);
        break;
    case INT_PCINT7:
        SET_BIT(PCICR, PCIE0);
        SET_BIT(PCMSK0, PCINT7);
        break;
    case INT_PCINT8:
        SET_BIT(PCICR, PCIE1);
        SET_BIT(PCMSK1, PCINT8);
        break;
    case INT_PCINT9:
        SET_BIT(PCICR, PCIE1);
        SET_BIT(PCMSK1, PCINT9);
        break;
    case INT_PCINT10:
        SET_BIT(PCICR, PCIE1);
        SET_BIT(PCMSK1, PCINT10);
        break;
    case INT_PCINT11:
        SET_BIT(PCICR, PCIE1);
        SET_BIT(PCMSK1, PCINT11);
        break;
    case INT_PCINT12:
        SET_BIT(PCICR, PCIE1);
        SET_BIT(PCMSK1, PCINT12);
        break;
    case INT_PCINT13:
        SET_BIT(PCICR, PCIE1);
        SET_BIT(PCMSK1, PCINT13);
        break;
    case INT_PCINT14:
        SET_BIT(PCICR, PCIE1);
        SET_BIT(PCMSK1, PCINT14);
        break;
    case INT_PCINT16:
        SET_BIT(PCICR, PCIE2);
        SET_BIT(PCMSK2, PCINT16);
        break;
    case INT_PCINT17:
        SET_BIT(PCICR, PCIE2);
        SET_BIT(PCMSK2, PCINT17);
        break;
    case INT_PCINT18:
        SET_BIT(PCICR, PCIE2);
        SET_BIT(PCMSK2, PCINT18);
        break;
    case INT_PCINT19:
        SET_BIT(PCICR, PCIE2);
        SET_BIT(PCMSK2, PCINT19);
        break;
    case INT_PCINT20:
        SET_BIT(PCICR, PCIE2);
        SET_BIT(PCMSK2, PCINT20);
        break;
    case INT_PCINT21:
        SET_BIT(PCICR, PCIE2);
        SET_BIT(PCMSK2, PCINT21);
        break;
    case INT_PCINT22:
        SET_BIT(PCICR, PCIE2);
        SET_BIT(PCMSK2, PCINT22);
        break;
    case INT_PCINT23:
        SET_BIT(PCICR, PCIE2);
        SET_BIT(PCMSK2, PCINT23);
        break;
    }
    SET_BIT(SREG, 7);
}

void EXTERNAL_INTERRUPTS_diable(EXTERNAL_INTERRUPTS_Types interruptType)
{
    switch (interruptType)
    {
    case INT_INT0:
        CLEAR_BIT(EIMSK, INT0);
        break;
    case INT_INT1:
        CLEAR_BIT(EIMSK, INT1);
        break;
    case INT_PCINT0:
        CLEAR_BIT(PCMSK0, PCINT0);
        break;
    case INT_PCINT1:
        CLEAR_BIT(PCMSK0, PCINT1);
        break;
    case INT_PCINT2:
        CLEAR_BIT(PCMSK0, PCINT2);
        break;
    case INT_PCINT3:
        CLEAR_BIT(PCMSK0, PCINT3);
        break;
    case INT_PCINT4:
        CLEAR_BIT(PCMSK0, PCINT4);
        break;
    case INT_PCINT5:
        CLEAR_BIT(PCMSK0, PCINT5);
        break;
    case INT_PCINT6:
        CLEAR_BIT(PCMSK0, PCINT6);
        break;
    case INT_PCINT7:
        CLEAR_BIT(PCMSK0, PCINT7);
        break;
    case INT_PCINT8:
        CLEAR_BIT(PCMSK1, PCINT8);
        break;
    case INT_PCINT9:
        CLEAR_BIT(PCMSK1, PCINT9);
        break;
    case INT_PCINT10:
        CLEAR_BIT(PCMSK1, PCINT10);
        break;
    case INT_PCINT11:
        CLEAR_BIT(PCMSK1, PCINT11);
        break;
    case INT_PCINT12:
        CLEAR_BIT(PCMSK1, PCINT12);
        break;
    case INT_PCINT13:
        CLEAR_BIT(PCMSK1, PCINT13);
        break;
    case INT_PCINT14:
        CLEAR_BIT(PCMSK1, PCINT14);
        break;
    case INT_PCINT16:
        CLEAR_BIT(PCMSK2, PCINT16);
        break;
    case INT_PCINT17:
        CLEAR_BIT(PCMSK2, PCINT17);
        break;
    case INT_PCINT18:
        CLEAR_BIT(PCMSK2, PCINT18);
        break;
    case INT_PCINT19:
        CLEAR_BIT(PCMSK2, PCINT19);
        break;
    case INT_PCINT20:
        CLEAR_BIT(PCMSK2, PCINT20);
        break;
    case INT_PCINT21:
        CLEAR_BIT(PCMSK2, PCINT21);
        break;
    case INT_PCINT22:
        CLEAR_BIT(PCMSK2, PCINT22);
        break;
    case INT_PCINT23:
        CLEAR_BIT(PCMSK2, PCINT23);
        break;
    }
}