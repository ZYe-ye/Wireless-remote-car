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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx.h"
#include "retarget.h"
#include "sys.h"
#include "delay.h"


#include "gpio.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"

#include "bsp_nrf24l01.h"
#include "motor.h"
#include "robot_arm.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

#define Serial_Deal

#ifdef Serial_Deal
#define DEBUG       printf
#else
#define DEBUG
#endif

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define EN1_Pin GPIO_PIN_14
#define EN1_GPIO_Port GPIOC
#define EN2_Pin GPIO_PIN_15
#define EN2_GPIO_Port GPIOC
#define Servo1_Pin GPIO_PIN_0
#define Servo1_GPIO_Port GPIOA
#define EN6_Pin GPIO_PIN_3
#define EN6_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_4
#define EN3_GPIO_Port GPIOA
#define ENC_Pin GPIO_PIN_0
#define ENC_GPIO_Port GPIOB
#define END_Pin GPIO_PIN_1
#define END_GPIO_Port GPIOB
#define Servo2_Pin GPIO_PIN_10
#define Servo2_GPIO_Port GPIOB
#define Servo3_Pin GPIO_PIN_11
#define Servo3_GPIO_Port GPIOB
#define EN4_Pin GPIO_PIN_12
#define EN4_GPIO_Port GPIOB
#define EN8_Pin GPIO_PIN_15
#define EN8_GPIO_Port GPIOB
#define EN7_Pin GPIO_PIN_11
#define EN7_GPIO_Port GPIOA
#define EN5_Pin GPIO_PIN_3
#define EN5_GPIO_Port GPIOB
#define ENA_Pin GPIO_PIN_4
#define ENA_GPIO_Port GPIOB
#define ENB_Pin GPIO_PIN_5
#define ENB_GPIO_Port GPIOB
#define Chassis_Pin GPIO_PIN_6
#define Chassis_GPIO_Port GPIOB
#define Forearm_Pin GPIO_PIN_7
#define Forearm_GPIO_Port GPIOB
#define Postbrachium_Pin GPIO_PIN_8
#define Postbrachium_GPIO_Port GPIOB
#define Claw_Pin GPIO_PIN_9
#define Claw_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
