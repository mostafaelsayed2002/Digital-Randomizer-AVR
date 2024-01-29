#define MCU HMI
#define PROCESSING 0
#define HMI 1

#if (MCU == PROCESSING) // Processing microcontroller

#include "../include/adc.h"
#include "../include/uart.h"
#include "../include/randomizer.h"
#include "../include/gpio.h"
#include "../include/timers.h"

/******************************************************************************
 *                                processing MCU                              *
 *******************************************************************************/
int main(void)
{

  // Init UART
  UART uart;
  uart.baudRate = BPS_9600;
  uart.characterSize = EIGHT_BITS;
  uart.parityMode = EVEN;
  uart.stopBit = ONE_BIT;
  uart.RxInterrupt = RXINT_DISABLE;
  uart.txInterrupt = TXINT_DISABLE;
  UART_init(&uart);

  // Init ADC
  ADC adc;
  adc.autoTriggerSource = TRIGGER_SOURCE_DISABLE;
  adc.inputChannel = ADC0;
  adc.interrupt = ADC_INTERRUPT_DIABLE;
  adc.preScaler = ADC_F_128;
  adc.voltageReference = AVCC;
  ADC_init(&adc);

  GPIO_setupPortDirection(PORTD_ID, 0x1C); // make pin 2 ,3 ,4 output  
  
  while (1)
  {
    uint8 req;
    do
    {
      req = UART_receive();
    } while (req != 'a');   // wait for request
    GPIO_writePin(PORTD_ID, PIN2_ID, HIGH); // turn on the led  after get the request
    TIMER0_delay_ms(1000); // delay one second

    uint16 randNumber = rand(); // get the random number 
    GPIO_writePin(PORTD_ID, PIN3_ID, HIGH); // turn on the second led after generate the random number
    TIMER0_delay_ms(1000); // delay one second


    UART_transmit(randNumber); 
    UART_transmit(randNumber >> 8); //transmit the random number
    GPIO_writePin(PORTD_ID, PIN4_ID, HIGH);  // turn on the thrid led after generate the random number
    TIMER0_delay_ms(1000);  // delay one second

    GPIO_writePin(PORTD_ID, PIN2_ID, LOW);   
    GPIO_writePin(PORTD_ID, PIN3_ID, LOW);
    GPIO_writePin(PORTD_ID, PIN4_ID, LOW);  // turn off all leds 
  }

  return 0;
}


#endif

#if (MCU == HMI) // Human interface microcontroller

#include "../include/uart.h"
#include "../include/seven_segment.h"
#include "../include/gpio.h"
#include "../include/external_interrupts.h"
#include "../include/timers.h"
#include "../include/reg.h"
#include "../include/common_macros.h"
#include "../include/std_types.h"
#include "../include/timer1_pwm.h"
#include "../include/eeprom.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define RANDOM_NUMBER_L 0x190
#define RANDOM_NUMBER_H 0x191
#define CURRENT_DIGIT 0x192
#define IS_FIXED 0x193
#define IS_DONE 0x194

/*******************************************************************************
 *                             Global Variables                                *
 *******************************************************************************/

uint16 randomNumber = 0;        // The gnereated random number
uint8 currentDigit = 0;         // The current displayed digit
volatile uint8 isGenerated = 0; // 0 if the number is not generated | 1 if generated
volatile uint8 isFixed = 0;     // if want fixed number (Next/Previous)
uint8 isDone = 0;               // A Flag indicating that the five seconds have passed

uint32 scalers[] = {1, 10, 100, 1000, 10000}; // scalers used to get each digit in the random number

/*******************************************************************************
 *                             Configuration Structures                        *
 *******************************************************************************/

SEVEN_SEGMENT sevenSegment; // seven segment configuration structure
UART uart;                  // uart configuration structure
TIMER1_PWM pwm;             // Timer1 pwm mode configuration structure
EEPROM eeprom;              // EEPROM configuration structure

/*******************************************************************************
 *                             Functions                                       *
 *******************************************************************************/

void processCurrentState()
{
  CLEAR_BIT(SREG, 7);                // Disable the global interrupt (make this code atomic)
  if (currentDigit != 5 && !isFixed) // move to the next digit
    currentDigit++;                  // only if the last number has not been reached or user want specific number (Next/Previous)

  // turn off all leds
  GPIO_writePort(PORTC_ID, 0);
  // turn on the led for the current digit
  GPIO_writePin(PORTC_ID, currentDigit, HIGH);
  // get the digit
  uint8 digit = (randomNumber % (10 * scalers[currentDigit - 1])) / scalers[currentDigit - 1];
  // display the digit
  SEVEN_SEGMENT_write(&sevenSegment, digit, 0);
  // move the servo
  TIMER1_PWM_DutyCycle_OC1A_Servo(((randomNumber % 180) / 5) * currentDigit, &pwm, 1, 2);
  // Turn on the buzzer
  if (!isDone)
    TIMER1_PWM_DutyCycle_OC1B(digit / 10.0, &pwm);
  else
    TIMER1_PWM_DutyCycle_OC1B(randomNumber / 65535.0, &pwm);

  if (!isFixed)
  {
    TIMER0_delay_ms(1000);
    if (currentDigit == 5)
    {
      isFixed = 1;
      isDone = 1;
    }
  }
  SET_BIT(SREG, 7); // enable the global interrupt
}

void uartConfiguration()
{
  uart.baudRate = BPS_9600;
  uart.characterSize = EIGHT_BITS;
  uart.parityMode = EVEN;
  uart.stopBit = ONE_BIT;
  uart.RxInterrupt = RXINT_DISABLE;
  uart.txInterrupt = TXINT_DISABLE;
  UART_init(&uart);
}

void sevenSegmentConfiguration()
{
  sevenSegment.a.PIN_ID = PIN4_ID;
  sevenSegment.a.PORT_ID = PORTD_ID;
  sevenSegment.b.PIN_ID = PIN5_ID;
  sevenSegment.b.PORT_ID = PORTD_ID;
  sevenSegment.c.PIN_ID = PIN6_ID;
  sevenSegment.c.PORT_ID = PORTD_ID;
  sevenSegment.d.PIN_ID = PIN7_ID;
  sevenSegment.d.PORT_ID = PORTD_ID;
  sevenSegment.e.PIN_ID = PIN3_ID;
  sevenSegment.e.PORT_ID = PORTB_ID;
  sevenSegment.f.PIN_ID = PIN4_ID;
  sevenSegment.f.PORT_ID = PORTB_ID;
  sevenSegment.g.PIN_ID = PIN5_ID;
  sevenSegment.g.PORT_ID = PORTB_ID;
  SEVEN_SEGMENT_init(&sevenSegment);
}

void externalInterruptConfiguration()
{
  EXTERNAL_INTERRUPTS_init(INT_INT0);
  EXTERNAL_INTERRUPTS_init(INT_INT1);
  EXTERNAL_INTERRUPTS_init(INT_PCINT0);
}

void pwmConfiguration()
{
  pwm.clock = TIMER1_PWM_8_CLOCK;
  pwm.ICR1_PWM = 40000 - 1;
  pwm.mode = TIMER1_FAST_PWM_ICR1;
  pwm.comA = TIMER1_NON_INVERTING_PWM;
  pwm.comB = TIMER1_NON_INVERTING_PWM;
  TIMER1_PWM_init(&pwm);
}

void eepromConfiguration()
{
  eeprom.mode = ERASE_WRITE;
  EEPOROM_init(&eeprom);
}

void load()
{
  uint16 readVal = EEPROM_read(RANDOM_NUMBER_L);
  if (readVal != 0xFF)
  {
    randomNumber = readVal;
    readVal = EEPROM_read(RANDOM_NUMBER_H);
    randomNumber |= (readVal << 8);
    currentDigit = EEPROM_read(CURRENT_DIGIT);
    isFixed = EEPROM_read(IS_FIXED);
    isDone = EEPROM_read(IS_DONE);
    isGenerated = 1;
  }
}

void save()
{
  uint8 readVal = EEPROM_read(RANDOM_NUMBER_L);
  uint8 randomNumberL = randomNumber;
  if (readVal != randomNumberL)
  {
    EEPROM_write(RANDOM_NUMBER_L, randomNumberL);
  }

  readVal = EEPROM_read(RANDOM_NUMBER_H);
  uint8 randomNumberH = randomNumber >> 8;
  if (readVal != randomNumberH)
  {
    EEPROM_write(RANDOM_NUMBER_H, randomNumberH);
  }

  readVal = EEPROM_read(CURRENT_DIGIT);
  if (readVal != currentDigit)
  {
    EEPROM_write(CURRENT_DIGIT, currentDigit);
  }

  readVal = EEPROM_read(IS_FIXED);
  if (readVal != isFixed)
  {
    EEPROM_write(IS_FIXED, isFixed);
  }

  readVal = EEPROM_read(IS_DONE);
  if (readVal != isDone)
  {
    EEPROM_write(IS_DONE, isDone);
  }
}

/*******************************************************************************
 *                             Main                                            *
 *******************************************************************************/
int main(void)
{
  // Init UART
  uartConfiguration();
  // Init  SEVEN SEGMENT
  sevenSegmentConfiguration();
  // Interrupts
  externalInterruptConfiguration();
  // Five-Leds
  GPIO_setupPortDirection(PORTC_ID, 0x3E);
  // Servo and buzzer
  pwmConfiguration();
  // EEPORM
  eepromConfiguration();
  // load data
  load();
  while (1)
  {
    save(); // save current state
    if (isGenerated)
      processCurrentState();
  }
  return 0;
}

/*******************************************************************************
 *                             ISRS                                            *
 *******************************************************************************/
// Generate push botton
ISR(INT0_vect)
{
  UART_transmit('a');
  uint16 lower = UART_receive();
  uint16 upper = UART_receive();
  randomNumber = lower;
  randomNumber |= (upper << 8);
  currentDigit = 0;
  isFixed = 0;
  isDone = 0;
  isGenerated = 1;
}

// Next push botton
ISR(INT1_vect)
{
  isFixed = 1;
  isDone = 0;
  if (currentDigit != 5)
    currentDigit++;
}

// Previous push botton
ISR(PCINT0_vect)
{
  if (GPIO_readPin(PORTB_ID, PIN0_ID)) // because PCINT0 is a PIN CHANGE interruprt
  {
    isFixed = 1;
    isDone = 0;
    if (currentDigit != 1)
      currentDigit--;
  }
}

#endif
