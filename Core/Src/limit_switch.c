#include "limit_switch.h"
#include "main.h"

bool LimitSwitch1_IsPressed(void)
{
    return (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET);
}

bool LimitSwitch2_IsPressed(void)
{
    return (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET);
}

bool LimitSwitch3_IsPressed(void)
{
    return (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_SET);
}

bool LimitSwitch_AnyPressed(void)
{
    return LimitSwitch1_IsPressed() ||
           LimitSwitch2_IsPressed() ||
           LimitSwitch3_IsPressed();
}
