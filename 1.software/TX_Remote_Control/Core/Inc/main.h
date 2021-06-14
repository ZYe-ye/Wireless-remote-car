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

#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "usart.h"
#include "spi.h"
#include "adc.h"

#include "bsp_nrf24l01.h"
#include "serial.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern uint8_t status;         //用于判断接收/发送状态
extern uint8_t txbuf[32];     //发送缓冲
extern uint8_t rxbuf[32];     //接收缓冲
extern uint8_t tf;

extern uint16_t adcBuf[4];//保存adc转后的值

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
//#define Serial_Deal

#ifdef Serial_Deal
#define DEBUG       printf
#else
#define DEBUG
#endif
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
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define ADC1_Pin GPIO_PIN_3
#define ADC1_GPIO_Port GPIOA
#define ADC2_Pin GPIO_PIN_4
#define ADC2_GPIO_Port GPIOA
#define ADC3_Pin GPIO_PIN_0
#define ADC3_GPIO_Port GPIOB
#define ADC4_Pin GPIO_PIN_1
#define ADC4_GPIO_Port GPIOB
#define KEY7_Pin GPIO_PIN_10
#define KEY7_GPIO_Port GPIOB
#define KEY8_Pin GPIO_PIN_11
#define KEY8_GPIO_Port GPIOB
#define KEY9_Pin GPIO_PIN_12
#define KEY9_GPIO_Port GPIOB
#define KEY10_Pin GPIO_PIN_13
#define KEY10_GPIO_Port GPIOB
#define KEY11_Pin GPIO_PIN_14
#define KEY11_GPIO_Port GPIOB
#define KEY12_Pin GPIO_PIN_15
#define KEY12_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_5
#define KEY2_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_6
#define KEY3_GPIO_Port GPIOB
#define KEY4_Pin GPIO_PIN_7
#define KEY4_GPIO_Port GPIOB
#define KEY5_Pin GPIO_PIN_8
#define KEY5_GPIO_Port GPIOB
#define KEY6_Pin GPIO_PIN_9
#define KEY6_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
