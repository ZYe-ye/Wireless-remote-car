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
#include "adc.h"
#include "dma.h"
#include "spi.h"
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
uint8_t tf = 0;


uint16_t adcBuf[4];//保存adc转后的值

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
int main(void) {
    /* USER CODE BEGIN 1 */

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
    MX_DMA_Init();
    MX_USART1_UART_Init();
//    MX_SPI1_Init();
    MX_ADC1_Init();
    /* USER CODE BEGIN 2 */

    HAL_UART_Receive_IT(&huart1, (uint8_t *) &UART_RxBuffer, 1);
    printf("\r\n TX.\r\n");
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adcBuf, 4);

    /*初始化NRF*/
    SPI_NRF_Init();

    /*检测 NRF 模块与 MCU 的连接*/
    status = NRF_Check();
    /*判断连接状态*/
    if (status == SUCCESS) {
        printf("\r\n      NRF与MCU连接成功！\r\n");
        LED = 0;
    } else
        printf("\r\n  NRF与MCU连接失败，请重新检查接线。\r\n");

    NRF_TX_Mode();    // NRF 进入发送模式

    printf("\r\n TX.\r\n");
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

//        printf("%d %d %d %d.\n", adcBuf[0], adcBuf[1], adcBuf[2], adcBuf[3]);
//        HAL_Delay(1000);
/*
        if (adcBuf[0] <10) {
            printf("adcBuf[0] = %d.\n", adcBuf[0]);
        }
        if (adcBuf[0] >4000) {
            printf("adcBuf[0] = %d.\n", adcBuf[0]);
        }

        if (adcBuf[2] <10) {
            printf("adcBuf[2] = %d.\n", adcBuf[2]);
        }
        if (adcBuf[2] >4000) {
            printf("adcBuf[2] = %d.\n", adcBuf[2]);
        }
*/
        /*----------------------------------------------*/
        //txbuf[0]控制车的前进后退
        if (adcBuf[1] < 10) {
//            printf("adcBuf[1] = %d.\n", adcBuf[1]);
            txbuf[0] = 1;//前进
        }
        if (adcBuf[1] > 4000) {
//            printf("adcBuf[1] = %d.\n", adcBuf[1]);
            txbuf[0] = 2;//后退
        }
        //txbuf[2]控制车的左右
        if (adcBuf[2] < 10) {
//            printf("adcBuf[3] = %d.\n", adcBuf[3]);
            txbuf[2] = 1;//右边
        }
        if (adcBuf[2] > 4000) {
//            printf("adcBuf[3] = %d.\n", adcBuf[3]);
            txbuf[2] = 2;//左边
        }
        /*----------------------------------------------*/


        /*-------------------按键，左边-------------------*/
        //txbuf[4]，按键左边上下，B(2)、D(4)
        if (KEY_B == KEY_ON) {
            txbuf[4] = 1;
            DEBUG("B,2.\n");
        }
        if (KEY_D == KEY_ON) {
            txbuf[4] = 2;
            DEBUG("D,4\n");
        }
        //txbuf[5]，按键左边左右，A(1)、C(3)
        if (KEY_A == KEY_ON) {
            txbuf[5] = 1;
            DEBUG("A,1.\n");
        }
        if (KEY_C == KEY_ON) {
            txbuf[5] = 2;
            DEBUG("C,3.\n");
        }
        /*----------------------------------------------*/


        /*-------------------按键，右边-------------------*/
        //txbuf[6]，按键右边上下，H(6)、Z(8)
        if (KEY_H == KEY_ON) {
            txbuf[6] = 1;
            DEBUG("H,6.\n");
        }
        if (KEY_Z == KEY_ON) {
            txbuf[6] = 2;
            DEBUG("Z,8.\n");
        }
        //txbuf[7]，按键右边左右，G(5)、I(7)
        if (KEY_G == KEY_ON) {
            txbuf[7] = 1;
            DEBUG("G,5.\n");
        }
        if (KEY_I == KEY_ON) {
            txbuf[7] = 2;
            DEBUG("I,7.\n");
        }
        /*----------------------------------------------*/

        /*-------------------按键，中间-------------------*/
        //txbuf[8]，按键中间左右，E(9)、F(10)
        if (KEY_E == KEY_ON) {
            txbuf[8] = 1;
            DEBUG("E,9.\n");
        }
        if (KEY_F == KEY_ON) {
            txbuf[8] = 2;
            DEBUG("F,10.\n");
        }
        /*----------------------------------------------*/

        /*-------------------摇杆按键，左右-------------------*/
        //txbuf[9]，摇杆按键，左右，K(11)、L(12)
        if (KEY_K == KEY_ON) {
            txbuf[9] = 1;
            DEBUG("K,11.\n");
        }
        if (KEY_L == KEY_ON) {
            txbuf[9] = 2;
            DEBUG("L,12.\n");
        }
        /*----------------------------------------------*/

//        Serial_debugging();

//        if (tf = 1) {
        status = NRF_Tx_Dat(txbuf);
        /* 发送数据的状态 */
        /*
        if (status == TX_DS) {
//            printf("\r\n发送数据成功\r\n");
        } else {
//                printf("\r\n发送数据失败  %d\r\n", status);
//            printf("\r\n发送数据失败\r\n");
        }
         */
        for (int i = 0; i < 32; ++i) {
            txbuf[i] = 0;
        }
//        tf = 0;
//        }
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
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
