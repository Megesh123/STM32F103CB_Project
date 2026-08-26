#include "stm32f1xx_hal.h"

#ifdef HAL_TIM_MODULE_ENABLED

__weak void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  UNUSED(htim);
}

__weak void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
  UNUSED(htim);
}

__weak void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  UNUSED(htim);
}

HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)
{
  if (htim == NULL || htim->Instance == NULL)
  {
    return HAL_ERROR;
  }

  if (htim->State == HAL_TIM_STATE_RESET)
  {
    htim->Lock = HAL_UNLOCKED;
    HAL_TIM_Base_MspInit(htim);
  }

  htim->State = HAL_TIM_STATE_BUSY;

  htim->Instance->CR1 = 0U;
  htim->Instance->PSC = (uint16_t)htim->Init.Prescaler;
  htim->Instance->ARR = (uint16_t)htim->Init.Period;
  htim->Instance->CNT = 0U;
  htim->Instance->EGR = TIM_EGR_UG;
  htim->Instance->SR = 0U;

  htim->State = HAL_TIM_STATE_READY;
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim)
{
  if (htim == NULL || htim->Instance == NULL)
  {
    return HAL_ERROR;
  }

  htim->Instance->CR1 &= ~TIM_CR1_CEN;
  htim->Instance->DIER &= ~TIM_DIER_UIE;
  HAL_TIM_Base_MspDeInit(htim);
  htim->State = HAL_TIM_STATE_RESET;
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim,
                                             TIM_ClockConfigTypeDef *sClockSourceConfig)
{
  if (htim == NULL || sClockSourceConfig == NULL)
  {
    return HAL_ERROR;
  }

  /* TIM2 uses its normal internal APB1 timer clock. */
  (void)sClockSourceConfig;
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim)
{
  if (htim == NULL || htim->Instance == NULL)
  {
    return HAL_ERROR;
  }

  htim->Instance->CR1 |= TIM_CR1_CEN;
  htim->State = HAL_TIM_STATE_READY;
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim)
{
  if (htim == NULL || htim->Instance == NULL)
  {
    return HAL_ERROR;
  }

  htim->Instance->CR1 &= ~TIM_CR1_CEN;
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim)
{
  if (htim == NULL || htim->Instance == NULL)
  {
    return HAL_ERROR;
  }

  htim->Instance->SR &= ~TIM_SR_UIF;
  htim->Instance->DIER |= TIM_DIER_UIE;
  htim->Instance->CR1 |= TIM_CR1_CEN;
  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim)
{
  if (htim == NULL || htim->Instance == NULL)
  {
    return HAL_ERROR;
  }

  htim->Instance->DIER &= ~TIM_DIER_UIE;
  htim->Instance->CR1 &= ~TIM_CR1_CEN;
  return HAL_OK;
}

void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)
{
  if (htim == NULL || htim->Instance == NULL)
  {
    return;
  }

  if (((htim->Instance->SR & TIM_SR_UIF) != 0U) &&
      ((htim->Instance->DIER & TIM_DIER_UIE) != 0U))
  {
    htim->Instance->SR &= ~TIM_SR_UIF;
    HAL_TIM_PeriodElapsedCallback(htim);
  }
}

#endif /* HAL_TIM_MODULE_ENABLED */
