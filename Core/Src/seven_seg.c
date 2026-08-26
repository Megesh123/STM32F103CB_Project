#include "seven_seg.h"
#include "main.h"

#define SEG_ON    GPIO_PIN_SET
#define SEG_OFF   GPIO_PIN_RESET
#define DIGIT_ON  GPIO_PIN_SET
#define DIGIT_OFF GPIO_PIN_RESET

static volatile uint16_t display_value = 0U;
static uint8_t current_digit = 0U;
static uint16_t second_counter_ms = 0U;

static const uint8_t digit_segments[10] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F  /* 9 */
};

static void SevenSeg_AllDigitsOff(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  DIGIT_OFF); /* SEG1 */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, DIGIT_OFF); /* SEG2 */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, DIGIT_OFF); /* SEG3 */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, DIGIT_OFF); /* SEG4 */
}

static void SevenSeg_WriteSegments(uint8_t pattern)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (pattern & 0x01U) ? SEG_ON : SEG_OFF); /* A */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2,  (pattern & 0x02U) ? SEG_ON : SEG_OFF); /* B */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5,  (pattern & 0x04U) ? SEG_ON : SEG_OFF); /* C */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (pattern & 0x08U) ? SEG_ON : SEG_OFF); /* D */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (pattern & 0x10U) ? SEG_ON : SEG_OFF); /* E */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,  (pattern & 0x20U) ? SEG_ON : SEG_OFF); /* F */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,  (pattern & 0x40U) ? SEG_ON : SEG_OFF); /* G */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SEG_OFF);                               /* DP */
}

static void SevenSeg_EnableDigit(uint8_t digit)
{
    switch (digit)
    {
        case 0U: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  DIGIT_ON); break;  /* SEG1 */
        case 1U: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, DIGIT_ON); break;  /* SEG2 */
        case 2U: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, DIGIT_ON); break;  /* SEG3 */
        case 3U: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, DIGIT_ON); break;  /* SEG4 */
        default: break;
    }
}

void SevenSeg_Init(void)
{
    SevenSeg_AllDigitsOff();
    SevenSeg_WriteSegments(0U);
    display_value = 0U;
    current_digit = 0U;
    second_counter_ms = 0U;
}

void SevenSeg_SetNumber(uint16_t value)
{
    if (value > 9999U)
    {
        value = 9999U;
    }

    display_value = value;
}

void SevenSeg_Tick(void)
{
    uint16_t value = display_value;
    uint8_t digit_value;

    /* 1 ms tick: multiplex one digit. */
    SevenSeg_AllDigitsOff();

    switch (current_digit)
    {
        case 0U: digit_value = (uint8_t)((value / 1000U) % 10U); break;
        case 1U: digit_value = (uint8_t)((value / 100U) % 10U);  break;
        case 2U: digit_value = (uint8_t)((value / 10U) % 10U);   break;
        default: digit_value = (uint8_t)(value % 10U);           break;
    }

    SevenSeg_WriteSegments(digit_segments[digit_value]);
    SevenSeg_EnableDigit(current_digit);

    current_digit++;
    if (current_digit >= 4U)
    {
        current_digit = 0U;
    }

    /* Display elapsed seconds from 0000 to 9999, then roll over. */
    second_counter_ms++;
    if (second_counter_ms >= 1000U)
    {
        second_counter_ms = 0U;

        if (display_value >= 9999U)
        {
            display_value = 0U;
        }
        else
        {
            display_value++;
        }
    }
}
