/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
void (*pTask) (void);
uint32_t delay ;
uint32_t period ;
uint8_t runme;
uint32_t taskID ;
} sTask ;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0
sTask SCH_tasks_G [SCH_MAX_TASKS];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
unsigned char error_code_G=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void SCH_Init (void) {
unsigned char i ;
for (i = 0; i < SCH_MAX_TASKS; i++) {
SCH_Delete_Task(i);
}
// Reset the global error variable
// − SCH_Delete_Task () will generate an error code
// ( because the task array is empty)
Error_code_G = 0;
Timer_init ();
Watchdog_init ();
}

unsigned char SCH_Add_Task ( void (*pFunction) () , unsigned int DELAY, unsigned int PERIOD){
	unsigned char ind=0;
	while((SCH_tasks_G[ind].pTask)!=0 && ind<SCH_MAX_TASKS)
	{
		ind++;
	}
	if(ind==SCH_MAX_TASKS)
	{
		error_code_G=ERROR_SCH_TOO_MANY_TASKS;
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G [ind].pTask = pFunction ;
	SCH_tasks_G [ind].delay = DELAY;
	SCH_tasks_G [ind].period = PERIOD;
	SCH_tasks_G [ind].runme = 0;
	return ind;
}
void SCH_dispatch_tasks(void)
{
	unsigned char ind;
	for(ind=0; ind<SCH_MAX_TASKS; ind++)
	{
		if(SCH_tasks_G[ind].runme>0)
		{
			(*SCH_tasks_G[ind].pTask)();
			SCH_tasks_G[ind].runme-=1;
			if(SCH_tasks_G[ind].period==0)
			{
				SCH_delete_task(ind);
			}
		}
	}
	SCH_rp_status();
	SCH_goto_sleep();
}

unsigned char SCH_delete_task (const tByte TASK_INDEX) {
	unsigned char rt_code;
	if(SCH_tasks_G[TASK_INDEX].pTask==0){
		error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		rt_code = RETURN_ERROR;
	}else{
		rt_code = RETURN_NORMAL;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].delay = 0;
	SCH_tasks_G[TASK_INDEX].period = 0;
	SCH_tasks_G[TASK_INDEX].runme = 0;
	return rt_code;
}

void SCH_goto_sleep(void)
{

}
void SCH_rp_status(void)
{

#ifdef SCH_REPORT_ERRORS
	if(error_code_G!=Last_error_code_G)
	{
		error_post=255-error_code_G;
		Last_error_code_G=error_code_G;
		if(error_code_G!=0){
			Error_tick_count_G = 60000;
		}else{
			Error_tick_count_G = 0;
		}
	}else{
		if(Error_tick_count_G!=0){
			if(--Error_tick_count_G = 0;)
			{
				error_code_G=0;
			}
		}
	}
#endif
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  SCH_dispatch_tasks();

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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/* USER CODE BEGIN 4 */
void SCH_Update(void){
	unsigned char ind;
	for(ind=0; ind<SCH_MAX_TASKS; ind++)
	{
		if(SCH_tasks_G[ind].pTask){
			if(SCH_tasks_G[ind].delay==0){
				SCH_tasks_G[ind].runme+=1;
				if(SCH_tasks_G[ind].period){
					SCH_tasks_G[ind].delay=SCH_tasks_G[ind].period;
					}
			}else
				{
				SCH_tasks_G[ind].delay-=1;
				}
			}
		}
	}
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	runTimer();
	SCH_Update();
}
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
