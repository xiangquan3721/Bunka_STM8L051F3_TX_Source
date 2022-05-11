/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
//PC14-LOGIN
#define OPEN_Pin GPIO_PIN_14
#define OPEN_GPIO_Port GPIOC
//PC15-CLOSE
#define CLOSE_Pin GPIO_PIN_15
#define CLOSE_GPIO_Port GPIOC
//PA0-STOP
#define STOP_Pin  GPIO_PIN_0
#define STOP_GPIO_Port GPIOA
//PA3-OPEN
#define LOGIN_Pin  GPIO_PIN_3
#define LOGIN_GPIO_Port GPIOA
//PA2-VENT
#define VENT_Pin  GPIO_PIN_2
#define VENT_GPIO_Port GPIOA



//PA2-TX
#define TX_AND_KEY2_Pin GPIO_PIN_2
#define TX_AND_KEY2_GPIO_Port GPIOA
//PA3-RX
#define RX_AND_KEY1_Pin GPIO_PIN_3
#define RX_AND_KEY1_GPIO_Port GPIOA

//POWER-PA4
#define POWER_Pin GPIO_PIN_4
#define POWER_GPIO_Port GPIOA
//LE-PA5
#define ADF7021_LE_Pin GPIO_PIN_5
#define ADF7021_LE_GPIO_Port GPIOA
//DATA-PA6
#define ADF7021_DATA_Pin GPIO_PIN_6
#define ADF7021_DATA_GPIO_Port GPIOA
//CLK-PA7
#define ADF7021_CLK_Pin GPIO_PIN_7
#define ADF7021_CLK_GPIO_Port GPIOA
//TXDATA-PA10
#define TXDATA_Pin GPIO_PIN_10
#define TXDATA_GPIO_Port GPIOA
//CE-PA9
#define ADF7021_CE_Pin GPIO_PIN_9
#define ADF7021_CE_GPIO_Port GPIOA

//PA1-BEEP
#define BEEP_Pin GPIO_PIN_1
#define BEEP_GPIO_Port GPIOA

//PB1-TXCLK
#define EXTI_TXCLK_Pin GPIO_PIN_1
#define EXTI_TXCLK_GPIO_Port GPIOB
#define EXTI_TXCLK_EXTI_IRQn EXTI0_1_IRQn

#ifndef MODEL_TEST
//A13-TEST IN
#define TEST_MODE_Pin GPIO_PIN_13
#define TEST_MODE_GPIO_Port GPIOA
//PA14-LED
#define LED_Pin GPIO_PIN_14
#define LED_GPIO_Port GPIOA
#endif
/* USER CODE BEGIN Private defines */
void MX_TIM2_Init(void);
void exit_init(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
