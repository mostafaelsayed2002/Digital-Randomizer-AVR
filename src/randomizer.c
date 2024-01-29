#include "randomizer.h"
#include "adc.h"
#include "uart.h"
#include "timers.h"
#include "reg.h"


static uint16 prev = 33508;
static uint8 seedExists = 0;

static uint16 calcNumber()
{
    //I tried Linear congruential algorithm but number get saturated after very short period

    // using xorshift algorithm
    uint16 res; 
    res = prev;
    res = res ^(res<<13);
    res = res ^(res>>9);
    res = res^(res<<5);
    res  = res % 65536;

    prev = res;    
    return res;
}

static void setSeed(uint16 val)
{
    prev = val;
    seedExists = 1; 
}

static uint16 TRNG_get_seed()
{
    uint16 res = 0;
    for (int i = 0; i < 6; i++)
    {
        TIMER0_delay_ms(2);
        ADC_changeChannel(i);
        ADC_start();
        res += ADC_read();
    }
    res += TCNT0;
    return res;
}

uint16 rand()
{
#if (TYPE == TRNG)
    if(seedExists == 0)
        setSeed(TRNG_get_seed());
#endif
    return calcNumber();
}