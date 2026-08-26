#include "buzzer.h"
#include "main.h"

void Buzzer_Init(void)
{
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
}

void Buzzer_Set(bool on)
{
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,
                      on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Buzzer_Update(bool proximity_detected, bool limit_switch_pressed)
{
    Buzzer_Set(proximity_detected && limit_switch_pressed);
}
