/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/*-----------����1��Ϊ����ʹ��-----------------*/
//���ڽ�������
unsigned char UART_RxBuffer[UART_RX_BUFFER_SIZE];
//���ڽ�������ָ��
unsigned char UART_RxPtr;
/* ���������� */
uint8_t receive_cmd = 0;
/*------------------------------------------*/


uint32_t debug_message = 0;//�ô��ڵ���ʱʹ��

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

//�ض���c�⺯��printf������DEBUG_USART���ض�����ʹ��printf����
int fputc(int ch, FILE *f) {
    /* ����һ���ֽ����ݵ�����DEBUG_USART */
    HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 1000);

    return (ch);
}

//�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f) {

    int ch;
    HAL_UART_Receive(&huart1, (uint8_t *) &ch, 1, 1000);
    return (ch);
}

/*---------------------����1����ʹ��----------------------------*/
/*****************  ����1��ս��ջ��� **********************/
void uart_FlushRxBuffer(void) {
    UART_RxPtr = 0;
    UART_RxBuffer[UART_RxPtr] = 0;
}

/*****************  ����1�����ַ� **********************/
void Usart_SendByte(uint8_t str) {
    HAL_UART_Transmit(&huart1, &str, 1, 1000);
}

/*****************  ����1�����ַ��� **********************/
void Usart_SendString(uint8_t *str) {
    unsigned int k = 0;
    do {
        HAL_UART_Transmit(&huart1, (uint8_t *) (str + k), 1, 1000);
        k++;
    } while (*(str + k) != '\0');
}
/*------------------------------------------------------------*/

/**
  * @brief  ��������1���յ������ݣ����ڵ���
  * @param  ��
  * @retval ��
  */
void deal_USART1_data(void) {
    //���յ���ȷ��ָ���Ϊ1
    char okCmd_1 = 0;
    //����Ƿ���յ�ָ��
    if (receive_cmd == 1) {
        if (!strcmp(UART_RxBuffer, "x1!")) {
            okCmd_1 = 1;
            debug_message = 1;
        } else if (!strcmp(UART_RxBuffer, "x2!")) {
            okCmd_1 = 1;
            debug_message = 2;
        } else if (!strcmp(UART_RxBuffer, "x3!")) {
            okCmd_1 = 1;
            debug_message = 3;
        } else if (!strcmp(UART_RxBuffer, "x4!")) {
            okCmd_1 = 1;
            debug_message = 4;
        } else if (!strcmp(UART_RxBuffer, "x5!")) {
            okCmd_1 = 1;
            debug_message = 5;
        }

        if (okCmd_1 != 1) {
//            printf("\n\r ������������������...\n\r");
        }

        //��մ��ڽ��ջ�������
        receive_cmd = 0;
        uart_FlushRxBuffer();
    }
}

//����1����
void Serial_debugging() {

    deal_USART1_data();//��������1����

    //�Խ��յ�����1�����ݽ��д���
    switch (debug_message) {
        case 1:
            debug_message = 0;
            printf("x1!\n");
            break;
        case 2:
            debug_message = 0;
            printf("x1!\n");
            break;
        case 3:
            debug_message = 0;
            printf("x1!\n");
            break;
        case 4:
            debug_message = 0;
            printf("x1!\n");
            break;
        case 5:
            debug_message = 0;
            printf("x5!\n");
            break;

        default:
            break;
    }
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/