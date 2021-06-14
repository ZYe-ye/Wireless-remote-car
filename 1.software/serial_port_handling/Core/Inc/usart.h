/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

#define UART_RX_BUFFER_SIZE 256
extern unsigned char UART_RxBuffer[UART_RX_BUFFER_SIZE];
//串口接收数组指针
extern unsigned char UART_RxPtr;
/* 命令接收完成 */
extern uint8_t receive_cmd;

extern uint32_t debug_message;

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */

void uart_FlushRxBuffer(void);//串口1(调试)，清空接收缓冲
void Usart_SendByte(uint8_t str);
void Usart_SendString(uint8_t *str);

void deal_USART1_data(void);//处理串口1接收到的数据,用于调试
void Serial_debugging();//串口调试

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
