#ifndef REG_H_
#define REG_H_

#include "std_types.h"

/*******************************************************************************
 *                                   GPIO                                      *
 *******************************************************************************/
#define PORTB (*(volatile uint8*)0x25)
#define PORTC (*(volatile uint8*)0x28)
#define PORTD (*(volatile uint8*)0x2B)
#define DDRB (*(volatile uint8*)0x24)
#define DDRC (*(volatile uint8*)0x27)
#define DDRD (*(volatile uint8*)0x2A)
#define PINB (*(volatile uint8*)0x23)
#define PINC (*(volatile uint8*)0x26)
#define PIND (*(volatile uint8*)0x29)
#define SREG (*(volatile uint8*)0x5F) 

/*******************************************************************************
 *                                    ADC                                       *
 *******************************************************************************/
#define ADMUX (*(volatile uint8*)0x7C)
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX3 3
#define MUX2 2
#define MUX1 1
#define MUX0 0
#define ADCSRA (*(volatile uint8*)0x7A)
#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0
#define ADCH (*(volatile uint8*)0x79)
#define ADCL (*(volatile uint8*)0x78)
#define ADCSRB (*(volatile uint8*)0x7B)
#define ACME 6
#define ADTS2 2
#define ADTS1 1
#define ADTS0 0
#define DIDR0 (*(volatile uint8*)0x7E)
#define ADC5D 5
#define ADC4D 4
#define ADC3D 3
#define ADC2D 2
#define ADC1D 1
#define ADC0D 0

/*******************************************************************************
 *                                    UART                                     *
 *******************************************************************************/
#define UDR0 (*(volatile uint8*)0xC6)
#define UCSR0A (*(volatile uint8*)0xC0)
#define RXC0 7
#define TXC0 6
#define UDRE0 5
#define FE0 4
#define DOR0 3
#define UPE0 2
#define U2X0 1
#define MPCM0 0
#define UCSR0B (*(volatile uint8*)0xC1)
#define RXCIE0 7
#define TXCIE0 6
#define UDRIE0 5
#define RXEN0 4
#define TXEN0 3
#define UCSZ02 2
#define RXB80 1
#define TXB80 0
#define UCSR0C (*(volatile uint8*)0xC2)
#define UMSEL01 7
#define UMSEL00 6
#define UPM01 5
#define UPM00 4
#define USBS0 3
#define UCSZ01 2
#define UCSZ00 1
#define UCPOL0 0
#define UBRR0L (*(volatile uint8*)0xC4)
#define UBRR0H (*(volatile uint8*)0xC5)


/*******************************************************************************
 *                                    TIMER0                                   *
 *******************************************************************************/
#define TCCR0A (*(volatile uint8*)0x44)
#define TCCR0B (*(volatile uint8*)0x45)
#define TCNT0 (*(volatile uint8*)0x46)
#define OCR0A (*(volatile uint8*)0x47)
#define OCR0B (*(volatile uint8*)0x48)
#define TIMSK0 (*(volatile uint8*)0x6E)
#define TIFR0 (*(volatile uint8*)0x35)
#define WGM00 0
#define WGM01 1
#define WGM02 3
#define TOIE0 0
#define OCIE0A 1
#define OCIE0B 2
#define COM0A1 7
#define COM0A0 6
#define COM0B1 5
#define COM0B0 4
#define CS00 0
#define CS01 1
#define CS02 2

/*******************************************************************************
 *                                    TIMER1                                   *
 *******************************************************************************/
#define TCCR1A (*(volatile uint8*)0x80)
#define TCCR1B (*(volatile uint8*)0x81)
#define TCNT1 (*(volatile uint16*)0x84)
#define OCR1A (*(volatile uint16*)0x88)

#define OCR1B (*(volatile uint16*)0x8A)

#define TIMSK1 (*(volatile uint8*)0x6F)
#define TIFR1 (*(volatile uint8*)0x36)
#define ICR1 (*(volatile uint8*)0x86)

#define ICR1L (*(volatile uint8*)0x86)
#define ICR1H (*(volatile uint8*)0x87)

#define OCR1AL (*(volatile uint8*)0x88)
#define OCR1AH (*(volatile uint8*)0x89)

#define OCR1BL (*(volatile uint8*)0x8A)
#define OCR1BH (*(volatile uint8*)0x8B)



#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4
#define TOIE1 0
#define OCIE1A 1
#define OCIE1B 2
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define CS10 0
#define CS11 1
#define CS12 2

/*******************************************************************************
 *                                    TIMER2                                   *
 *******************************************************************************/
#define TCCR2A (*(volatile uint8*)0xB0)
#define TCCR2B (*(volatile uint8*)0xB1)
#define TCNT2 (*(volatile uint8*)0xB2)
#define OCR2A (*(volatile uint8*)0xB3)
#define OCR2B (*(volatile uint8*)0xB4)
#define TIMSK2 (*(volatile uint8*)0x70)
#define TIFR2 (*(volatile uint8*)0x37)
#define WGM20 0
#define WGM21 1
#define WGM22 3
#define TOIE2 0
#define OCIE2A 1
#define OCIE2B 2
#define COM2A1 7
#define COM2A0 6
#define COM2B1 5
#define COM2B0 4
#define CS20 0
#define CS21 1
#define CS22 2

/*******************************************************************************
 *                                    INTERRUPTS                               *
 *******************************************************************************/

// INT0 INT1 
#define EICRA (*(volatile uint8*)0x69)
#define ISC11 3
#define ISC10 2
#define ISC01 1
#define ISC00 0
#define EIMSK (*(volatile uint8*)0x3D)
#define INT1 1
#define INT0 0
#define EIFR (*(volatile uint8*)0x3C)
#define INTF1 1
#define INTF0 0

// PCINT0 ----> PCINT23

#define PCICR (*(volatile uint8*)0x68)
#define PCIE2 2
#define PCIE1 1
#define PCIE0 0
#define PCIFR (*(volatile uint8*)0x3B)
#define PCIF2 2
#define PCIF1 1
#define PCIF0 0
#define PCMSK0 (*(volatile uint8*)0x6B)
#define PCINT7 7
#define PCINT6 6
#define PCINT5 5
#define PCINT4 4
#define PCINT3 3
#define PCINT2 2
#define PCINT1 1
#define PCINT0 0
#define PCMSK1 (*(volatile uint8*)0x6C)
#define PCINT14 6
#define PCINT13 5
#define PCINT12 4
#define PCINT11 3
#define PCINT10 2
#define PCINT9 1
#define PCINT8 0
#define PCMSK2 (*(volatile uint8*)0x6D)
#define PCINT23 7
#define PCINT22 6
#define PCINT21 5
#define PCINT20 4
#define PCINT19 3
#define PCINT18 2
#define PCINT17 1
#define PCINT16 0

/*******************************************************************************
 *                                    EEPROM                                   *
 *******************************************************************************/


#define EEARL (*(volatile uint8*)0x41)
#define EEAR7 7
#define EEAR6 6
#define EEAR5 5
#define EEAR4 4
#define EEAR3 3
#define EEAR2 2
#define EEAR1 1
#define EEAR0 0
#define EEARH (*(volatile uint8*)0x42)
#define EEAR8 0
#define EEDR (*(volatile uint8*)0x40)
#define EECR (*(volatile uint8*)0x3F)
#define EEPM1 5
#define EEPM0 4
#define EERIE 3
#define EEMPE 2
#define EEPE 1
#define EERE 0







#endif

