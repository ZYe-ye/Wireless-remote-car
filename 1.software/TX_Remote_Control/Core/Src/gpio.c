/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = KEY1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                             PBPin PBPin PBPin PBPin
                             PBPin PBPin PBPin */
    GPIO_InitStruct.Pin = KEY7_Pin | KEY8_Pin | KEY9_Pin | KEY10_Pin
                          | KEY11_Pin | KEY12_Pin | KEY2_Pin | KEY3_Pin
                          | KEY4_Pin | KEY5_Pin | KEY6_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/**
  * @brief   ����Ƿ��а�������
  * @param   ����Ķ˿ںͶ˿�λ
  *		@arg GPIOx: x�����ǣ�A...G��
  *		@arg GPIO_PIN ������GPIO_PIN_x��x������1...16��
  *		@arg mode:Long_press��������Short_press����̰�
  * @retval  ������״̬
  *		@arg KEY_ON:��������
  *		@arg KEY_OFF:����û����
  */
uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t mode) {
    /*����Ƿ��а������� */
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == KEY_ON) {
        /*�ȴ������ͷ� */
        if (mode == 0) {
            while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == KEY_ON);
            return KEY_ON;
        } else if (mode == 1) {
            if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == KEY_ON)
                return KEY_ON;
        }
    } else
        return KEY_OFF;
}


/**
 * @brief  EXIT�жϻص�����
 * @param GPIO_Pin ���� �����жϵ�����
 * @retval none
*/

/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {
        //�߼�����
        printf("1.\n");
        txbuf[0] = 1;
        tf = 1;
        //����жϱ�־λ
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
    }


    if (GPIO_Pin == GPIO_PIN_9) {
        //�߼�����
        printf("6.\n");
        //����жϱ�־λ
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
    }
    if (GPIO_Pin == GPIO_PIN_10) {
        //�߼�����
        printf("7.\n");
        txbuf[0] = 7;
        tf = 1;
        //����жϱ�־λ
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
    }
    if (GPIO_Pin == GPIO_PIN_11) {
        //�߼�����
        printf("8.\n");
        txbuf[0] = 8;
        tf = 1;
        //����жϱ�־λ
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
    }
    if (GPIO_Pin == GPIO_PIN_12) {
        //�߼�����
        printf("9.\n");
        txbuf[0] = 9;
        tf = 1;
        //����жϱ�־λ
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
    }
    if (GPIO_Pin == GPIO_PIN_13) {
        //�߼�����
        printf("10.\n");
        //����жϱ�־λ
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
    }
    if (GPIO_Pin == GPIO_PIN_14) {
        //�߼�����
        printf("11.\n");
        //����жϱ�־λ
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
    }
    if (GPIO_Pin == GPIO_PIN_15) {
        //�߼�����
        printf("12.\n");
        //����жϱ�־λ
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
    }
}

*/

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
