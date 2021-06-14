/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t status = 0;         //用于判断接收/发送状态
uint8_t txbuf[32];     //发送缓冲
uint8_t rxbuf[32];     //接收缓冲
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint32_t i;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
    RetargetInit(&huart1);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

    /*初始化NRF*/
    SPI_NRF_Init();

    /*检测 NRF 模块与 MCU 的连接*/
    status = NRF_Check();
    /*判断连接状态*/
    if (status == SUCCESS) {
        printf("\r\n      NRF与MCU连接成功！\r\n");
        LED = 0;
    } else {
        printf("\r\n  NRF与MCU连接失败，请重新检查接线。\r\n");
        LED = 1;
    }


    NRF_RX_Mode();    // NRF 进入接收模式





//    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 150);    //修改比较值，修改占空比
//    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 150);    //修改比较值，修改占空比
//    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 200);    //修改比较值，修改占空比
//    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 250);    //修改比较值，修改占空比


    motor_pwm_init();

    robot_arm_init();

    printf("\r\n RX.\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

        /* 等待接收数据 */
        status = NRF_Rx_Dat(rxbuf);

        /* 判断接收状态 */
        /*
        if (status == RX_DR) {
//            printf("\r\n 接收数据为：\r\n");
            for (i = 0; i < 32; i++) {
//                printf("\r\n 接收数据为：%d \r\n", rxbuf[i]);
                if (rxbuf[i] != 0) {
                    printf("rxbuf[%d] = %d.\n", i, rxbuf[i]);
                }
//                printf("%d,", rxbuf[i]);
            }
//            printf(" \r\n");
//            printf("\r\n 接收数据完成 \r\n");
        }
        */

        if ((rxbuf[0] == 0) && (rxbuf[2] == 0)) {
            vehicle_stop;//车，停止
        }
        /*------------处理车的前进后退----------------*/
        //rxbuf[0]为1，前进；为2，后退
        if (rxbuf[2] == 0) {
            switch (rxbuf[0]) {
                case 1:
                    //车,前进
                    DEBUG("前进.\n");
                    vehicle_forward;
                    break;
                case 2:
                    //车,后退
                    DEBUG("后退.\n");
                    vehicle_backward;
                    break;
                default:
                    break;
            }
        }
        /*----------------------------------------------*/

        /*------------处理车的左右----------------*/
        //rxbuf[2]为1，右边；为2，左边
        if (rxbuf[0] == 0) {
            switch (rxbuf[2]) {
                case 1:
                    //车,右边
                    DEBUG("右边.\n");
                    vehicle_right;
                    break;
                case 2:
                    //车,左边
                    DEBUG("左边.\n");
                    vehicle_left;
                    break;
                default:
                    break;
            }
        }

        /*----------------------------------------------*/

        if ((rxbuf[0] == 1) && (rxbuf[2] == 1)) {
            vehicle_right;
        }
        if ((rxbuf[0] == 1) && (rxbuf[2] == 2)) {
            vehicle_left;
        }
        if ((rxbuf[0] == 2) && (rxbuf[2] == 2)) {
            vehicle_left;
        }
        if ((rxbuf[0] == 2) && (rxbuf[2] == 1)) {
            vehicle_right;
        }


        /*-------------------按键，左边-------------------*/
        //rxbuf[4]，按键左边上下，B(2)、D(4)
        switch (rxbuf[4]) {
            case 1:
                //按键左边上,B(2)
                DEBUG("按键左边上.\n");
                if (Chassis_price > 50) {
                    Chassis_price -= 2;
                    Forearm_PMW(Chassis_price);
                    arm_delay;
                }
                break;
            case 2:
                //按键左边下,D(4)
                DEBUG("按键左边下.\n");
                if (Chassis_price < 50) {
                    Chassis_price += 2;
                    Forearm_PMW(Chassis_price);
                    arm_delay;
                }
                break;
            default:
                break;
        }
        //rxbuf[5]，按键左边左右，A(1)、D(3)
        switch (rxbuf[5]) {
            case 1:
                //按键左边左,A(1)
                DEBUG("按键左边左.\n");
                if (Chassis_price < 250) {
                    Chassis_price += 2;
                    Chassis_PMW(Chassis_price);
                    arm_delay;
                }
                break;
            case 2:
                //按键左边右,D(3)
                DEBUG("按键左边右.\n");
                if (Chassis_price > 50) {
                    Chassis_price -= 2;
                    Chassis_PMW(Chassis_price);
                    arm_delay;
                }
                break;
            default:
                break;
        }
        /*----------------------------------------------*/

        /*-------------------按键，右边-------------------*/
        //rxbuf[6]，按键右边上下，H(6)、Z(8)
        switch (rxbuf[6]) {
            case 1:
                //按键右边上,H(6)
                LED = 1;
                DEBUG("按键右边上.\n");
                rxbuf[6] = 0;
                break;
            case 2:
                //按键右边下,Z(8)
                LED = 0;
                DEBUG("按键右边下.\n");
                rxbuf[6] = 0;
                break;
            default:
                break;
        }
        //rxbuf[7]，按键右边左右，G(5)、I(7)
        switch (rxbuf[7]) {
            case 1:
                //按键右边左,G(5)
                LED = 1;
                DEBUG("按键右边左.\n");
                rxbuf[7] = 0;
                break;
            case 2:
                //按键右边右,I(7)
                LED = 0;
                DEBUG("按键右边右.\n");
                rxbuf[7] = 0;
                break;
            default:
                break;
        }
        /*----------------------------------------------*/

        /*-------------------按键，中间-------------------*/
        //rxbuf[8]，按键中间左右，E(9)、F(10)
        switch (rxbuf[8]) {
            case 1:
                //按键中间左,E(9)
                LED = 1;
                DEBUG("按键中间左.\n");
                rxbuf[8] = 0;
                break;
            case 2:
                //按键中间右,F(10)
                LED = 0;
                DEBUG("按键中间右.\n");
                rxbuf[8] = 0;
                break;
            default:
                break;
        }
        /*----------------------------------------------*/

        /*-------------------摇杆按键，左右-------------------*/
        //rxbuf[9]，摇杆按键，左右，K(11)、L(12)
        switch (rxbuf[9]) {
            case 1:
                //摇杆按键，左,K(11)
                LED = 1;
                DEBUG("摇杆按键，左.\n");
                rxbuf[9] = 0;
                break;
            case 2:
                //摇杆按键，右,L(12)
                LED = 0;
                DEBUG("摇杆按键，右.\n");
                rxbuf[9] = 0;
                break;
            default:
                break;
        }
        /*----------------------------------------------*/

    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
