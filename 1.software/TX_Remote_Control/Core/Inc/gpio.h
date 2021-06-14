/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define LED     PCout(13)

#define KEY_A       Key_Scan(KEY1_GPIO_Port, KEY1_Pin, Long_press)
#define KEY_B       Key_Scan(KEY2_GPIO_Port, KEY2_Pin, Long_press)
#define KEY_C       Key_Scan(KEY3_GPIO_Port, KEY3_Pin, Long_press)
#define KEY_D       Key_Scan(KEY4_GPIO_Port, KEY4_Pin, Long_press)
#define KEY_E       Key_Scan(KEY9_GPIO_Port, KEY9_Pin, Short_press)
#define KEY_F       Key_Scan(KEY10_GPIO_Port, KEY10_Pin, Short_press)
#define KEY_G       Key_Scan(KEY5_GPIO_Port, KEY5_Pin, Short_press)
#define KEY_H       Key_Scan(KEY6_GPIO_Port, KEY6_Pin, Long_press)
#define KEY_I       Key_Scan(KEY7_GPIO_Port, KEY7_Pin, Short_press)
#define KEY_Z       Key_Scan(KEY8_GPIO_Port, KEY8_Pin, Long_press)
#define KEY_K       Key_Scan(KEY11_GPIO_Port, KEY11_Pin, Short_press)
#define KEY_L       Key_Scan(KEY12_GPIO_Port, KEY12_Pin, Short_press)



// Long_press代表长按，Short_press代表短按
#define Long_press          1
#define Short_press         0


/** 按键按下标置宏
* 按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
* 若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
*/
#define KEY_ON	1
#define KEY_OFF	0



/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t mode);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
