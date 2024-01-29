#include "timer1_pwm.h"
#include "reg.h"
#include "common_macros.h"

static void setComA(TIMER1_PWM_ComMode com)
{
    switch (com)
    {
    case TIMER1_NORMAL_PWM:
        CLEAR_BIT(TCCR1A, COM1A0);
        CLEAR_BIT(TCCR1A, COM1A1);
        break;
    case TIMER1_NON_INVERTING_PWM:
        SET_BIT(DDRB, 1);
        CLEAR_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1A1);
        break;
    case TIMER1_INVERTING_PWM:
        SET_BIT(DDRB, 1);
        SET_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1A1);
        break;
    }
}

static void setComB(TIMER1_PWM_ComMode com)
{
    switch (com)
    {
    case TIMER1_NORMAL_PWM:
        CLEAR_BIT(TCCR1A, COM1B0);
        CLEAR_BIT(TCCR1A, COM1B1);
        break;
    case TIMER1_NON_INVERTING_PWM:
        SET_BIT(DDRB, 2);
        CLEAR_BIT(TCCR1A, COM1B0);
        SET_BIT(TCCR1A, COM1B1);
        break;
    case TIMER1_INVERTING_PWM:
        SET_BIT(DDRB, 2);
        SET_BIT(TCCR1A, COM1B0);
        SET_BIT(TCCR1A, COM1B1);
        break;
    }
}

static void setMode(TIMER1_PWM_ModeOfOperation mode, uint16 ICR1_PWM, uint16 OCR1A_PWM)
{
    switch (mode)
    {
    case TIMER1_FAST_PWM_8_BIT:
        SET_BIT(TCCR1A, WGM10);
        CLEAR_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        CLEAR_BIT(TCCR1B, WGM13);
        break;
    case TIMER1_FAST_PWM_9_BIT:
        CLEAR_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        CLEAR_BIT(TCCR1B, WGM13);
        break;
    case TIMER1_FAST_PWM_10_BIT:
        SET_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        CLEAR_BIT(TCCR1B, WGM13);
        break;
    case TIMER1_FAST_PWM_ICR1:
        CLEAR_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1B, WGM13);
        ICR1H |= (uint8)(ICR1_PWM >> 8);
        ICR1L |= (uint8)ICR1_PWM;
        break;
    case TIMER1_FAST_PWM_OCR1A:
        SET_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1B, WGM13);
        OCR1AH |= (uint8)(OCR1A_PWM >> 8);
        OCR1AL |= (uint8)OCR1A_PWM;
        break;
    }
}

static void setClock(TIMER1_PWM_Clock clk)
{

    switch (clk)
    {
    case TIMER1_PWM_1_CLOCK:
        SET_BIT(TCCR1B, CS10);
        CLEAR_BIT(TCCR1B, CS11);
        CLEAR_BIT(TCCR1B, CS12);
        break;
    case TIMER1_PWM_8_CLOCK:
        CLEAR_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        CLEAR_BIT(TCCR1B, CS12);
        break;

    case TIMER1_PWM_64_CLOCK:
        SET_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        CLEAR_BIT(TCCR1B, CS12);
        break;
    case TIMER1_PWM_256_CLOCK:
        CLEAR_BIT(TCCR1B, CS10);
        CLEAR_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
        break;
    case TIMER1_PWM_1024_CLOCK:
        SET_BIT(TCCR1B, CS10);
        CLEAR_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
        break;
    }
}

void TIMER1_PWM_init(TIMER1_PWM *pwm)
{
    setComA(pwm->comA);
    setComB(pwm->comB);
    setMode(pwm->mode, pwm->ICR1_PWM, pwm->OCR1A_PWM);
    setClock(pwm->clock);
}

void TIMER1_PWM_DutyCycle_OC1A(float32 Precent, TIMER1_PWM *pwm)
{
    uint16 ocra;
    switch (pwm->mode)
    {
    case TIMER1_FAST_PWM_8_BIT:
        ocra = 256 - (256 * Precent);
        OCR1AH = (uint8)(ocra >> 8);
        OCR1AL = (uint8)ocra;
        break;
    case TIMER1_FAST_PWM_10_BIT:
        ocra = 1024 - (1024 * Precent);
        OCR1AH = (uint8)(ocra >> 8);
        OCR1AL = (uint8)ocra;
        break;
    case TIMER1_FAST_PWM_ICR1:
        ocra = pwm->ICR1_PWM - (pwm->ICR1_PWM * Precent);
        OCR1AH = (uint8)(ocra >> 8);
        OCR1AL = (uint8)ocra;
        break;
    case TIMER1_FAST_PWM_OCR1A:
        break;
    }
}

void TIMER1_PWM_DutyCycle_OC1B(float32 Precent, TIMER1_PWM *pwm)
{
    uint16 ocrb;
    switch (pwm->mode)
    {
    case TIMER1_FAST_PWM_8_BIT:
        ocrb = 256 - (256 * Precent);
        OCR1BH = (uint8)(ocrb >> 8);
        OCR1BL = (uint8)ocrb;
        break;
    case TIMER1_FAST_PWM_10_BIT:
        ocrb = 1024 - (1024 * Precent);
        OCR1BH = (uint8)(ocrb >> 8);
        OCR1BL = (uint8)ocrb;
        break;
    case TIMER1_FAST_PWM_ICR1:
        ocrb = pwm->ICR1_PWM - (pwm->ICR1_PWM * Precent);
        OCR1BH = (uint8)(ocrb >> 8);
        OCR1BL = (uint8)ocrb;
        break;
    case TIMER1_FAST_PWM_OCR1A:
        ocrb = pwm->OCR1A_PWM - (pwm->OCR1A_PWM * Precent);
        OCR1BH = (uint8)(ocrb >> 8);
        OCR1BL = (uint8)ocrb;
        break;
    }
}

void TIMER1_PWM_DutyCycle_OC1A_Servo(uint16 Angle, TIMER1_PWM *pwm, uint8 minus90, uint8 pluse90)
{
    if (Angle > 180 || Angle < 0)
        return;
    uint32 F;
    float32 T;
    switch (pwm->clock)
    {
    case TIMER1_PWM_1_CLOCK:
        F = 16000000 / 1;
        T = 1.0 / F;
        break;
    case TIMER1_PWM_8_CLOCK:
        F = 16000000 / 8;
        T = 1.0 / F;
        break;
    case TIMER1_PWM_64_CLOCK:
        F = 16000000 / 64;
        T = 1.0 / F;
        break;
    case TIMER1_PWM_256_CLOCK:
        F = 16000000 / 256;
        T = 1.0 / F;
        break;
    case TIMER1_PWM_1024_CLOCK:
        F = 16000000 / 1024;
        T = 1.0 / F;
        break;
    }
    uint16 start = (minus90 * 1e-3) / T;
    uint32 end = (pluse90 * 1e-3) / T;
    uint16 ocra = (Angle / 180.0) * start + (end - start);
    if(pwm->mode != TIMER1_FAST_PWM_OCR1A)
        OCR1AH = (uint8)(ocra >> 8);
        OCR1AL = (uint8)ocra;
}