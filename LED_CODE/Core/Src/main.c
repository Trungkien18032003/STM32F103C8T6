/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef struct{
	uint16_t pintoTurnON;
	uint16_t pintoTurnOFF;
	uint32_t delayTime;
}TrafficState;

#define TIME_GREEN  3000
#define TIME_YELLOW 2000


TrafficState states[4] = {
    // -------------------------------------------------------------------------
    // STATE 0: Trục 1 XANH, Trục 2 ĐỎ
    // Trục 1 (PA7 sáng, PA5-6 tắt) | Trục 2 (PA8 sáng, PA9-10 tắt)
    // -------------------------------------------------------------------------
    {
        (LED_GREEN_Pin | LED_RED1_Pin),                                 // BẬT: Xanh 1, Đỏ 2
        (LED_RED_Pin | LED_YELLOW_Pin | LED_YELLOW1_Pin | LED_GREEN1_Pin),      // TẮT: Đỏ 1, Vàng 1, Vàng 2, Xanh 2
        TIME_GREEN
    },

    // -------------------------------------------------------------------------
    // STATE 1: Trục 1 VÀNG, Trục 2 ĐỎ
    // Trục 1 (PA6 sáng, PA5&7 tắt) | Trục 2 (PA8 sáng, PA9-10 tắt)
    // -------------------------------------------------------------------------
    {
        (LED_YELLOW_Pin | LED_RED1_Pin),                                 // BẬT: Vàng 1, Đỏ 2
        (LED_RED_Pin | LED_GREEN_Pin | LED_YELLOW1_Pin | LED_GREEN1_Pin),      // TẮT: Đỏ 1, Xanh 1, Vàng 2, Xanh 2
        TIME_YELLOW
    },

    // -------------------------------------------------------------------------
    // STATE 2: Trục 1 ĐỎ, Trục 2 XANH
    // Trục 1 (PA5 sáng, PA6-7 tắt) | Trục 2 (PA10 sáng, PA8-9 tắt)
    // -------------------------------------------------------------------------
    {
        (LED_RED_Pin | LED_GREEN1_Pin),                                // BẬT: Đỏ 1, Xanh 2
        (LED_GREEN_Pin | LED_YELLOW_Pin | LED_RED1_Pin | LED_YELLOW1_Pin),       // TẮT: Vàng 1, Xanh 1, Đỏ 2, Vàng 2
        TIME_GREEN
    },

    // -------------------------------------------------------------------------
    // STATE 3: Trục 1 ĐỎ, Trục 2 VÀNG
    // Trục 1 (PA5 sáng, PA6-7 tắt) | Trục 2 (PA9 sáng, PA8&10 tắt)
    // -------------------------------------------------------------------------
    {
        (LED_RED_Pin | LED_YELLOW1_Pin),                                 // BẬT: Đỏ 1, Vàng 2
        (LED_GREEN_Pin | LED_YELLOW_Pin | LED_RED1_Pin | LED_GREEN1_Pin),      // TẮT: Vàng 1, Xanh 1, Đỏ 2, Xanh 2
        TIME_YELLOW
    }
};
/* USER CODE END PD */



/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void TrafficLight_run_cycle(void)
{
	for (int i =0; i<4; i++)
	{
		HAL_GPIO_WritePin(GPIOA, states[i].pintoTurnOFF, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, states[i].pintoTurnON, GPIO_PIN_SET);
		HAL_Delay(states[i].delayTime);
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	//TODO ex3.1 using struct, point



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

	  TrafficLight_run_cycle();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|LED_RED1_Pin
                          |LED_YELLOW1_Pin|LED_GREEN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED_Pin LED_YELLOW_Pin LED_GREEN_Pin LED_RED1_Pin
                           LED_YELLOW1_Pin LED_GREEN1_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin|LED_RED1_Pin
                          |LED_YELLOW1_Pin|LED_GREEN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
