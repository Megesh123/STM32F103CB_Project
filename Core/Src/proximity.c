#include "proximity.h"
#include "main.h"

bool Proximity_IsDetected(void)
{
    return (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_SET);
}
