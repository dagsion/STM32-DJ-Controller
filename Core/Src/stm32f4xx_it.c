/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern int8_t current_col;
extern int which;
extern char message[100];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

extern TIM_HandleTypeDef htim6;  // Ensure timer is declared
extern int playback_index;
extern int direction;
extern int tempo;

void EXTI4_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(COL0_Pin)) {
	    __HAL_GPIO_EXTI_CLEAR_IT(COL0_Pin);  // Clear flag
	    HAL_TIM_Base_Start_IT(&htim6);
	    print_msg("Timer Started\n");
	}

	// Identify row based on `which` variable
	switch (which) {
		case 0: print_msg("row0\n"); break;
		case 1: print_msg("row1\n"); break;
		case 2: print_msg("row2\n"); break;
		case 3: print_msg("row3\n"); break;
		default: print_msg("Unknown row\n"); break;
	}

	// Delay for debouncing
	HAL_Delay(30);
	print_msg("IRQ4 \n");

	HAL_GPIO_EXTI_IRQHandler(COL0_Pin);
	HAL_GPIO_EXTI_IRQHandler(COL1_Pin);
	HAL_GPIO_EXTI_IRQHandler(COL2_Pin);
	HAL_GPIO_EXTI_IRQHandler(COL3_Pin);
}

void EXTI9_5_IRQHandler(void) {


    if (__HAL_GPIO_EXTI_GET_FLAG(COL1_Pin)) {  // Stop Timer Button
    	__HAL_GPIO_EXTI_CLEAR_IT(COL1_Pin);
		HAL_TIM_Base_Stop_IT(&htim6);
		print_msg("Timer Stopped\n");
    }
    else if (__HAL_GPIO_EXTI_GET_FLAG(COL2_Pin)) {
    	__HAL_GPIO_EXTI_CLEAR_IT(COL2_Pin);  // Clear flag
		HAL_TIM_Base_Start_IT(&htim6);
		print_msg("Col2: Timer Started\n");

		switch (which) {
			case 0: print_msg("row0\n");
					playback_index = 0;

					break;
			case 1: print_msg("row1\n");
					playback_index = 10000;
					break;
			case 2: print_msg("row2\n");
					playback_index = 20000;
					break;
			case 3: print_msg("row3\n");
					playback_index = 35000;
					break;
			default: print_msg("Unknown row\n"); break;
		}
    }
    else if (__HAL_GPIO_EXTI_GET_FLAG(COL3_Pin)) {
    	__HAL_GPIO_EXTI_CLEAR_IT(COL3_Pin);

		print_msg("COL3: Timer Stopped\n");

		switch (which) {
			case 0: print_msg("row0\n");
					vinyl_stop_effect();
					break;
			case 1: print_msg("row1\n");
					tempo = tempo*0.8;
					__HAL_TIM_SET_AUTORELOAD(&htim6, (uint32_t)(124*tempo));
					break;
			case 2: print_msg("row2\n");
					HAL_TIM_Base_Stop_IT(&htim6);
					break;
			case 3: print_msg("row3\n");
					HAL_TIM_Base_Stop_IT(&htim6);
					break;
			default: print_msg("Unknown row\n"); break;

		}

        // Add any functionality for COL3 here
    }

    // Identify row based on `which` variable


    print_msg("IRQ9-5 \n");

    // Delay for debouncing
    HAL_Delay(30);

    // Clear the interrupt flags
    HAL_GPIO_EXTI_IRQHandler(COL0_Pin);
    HAL_GPIO_EXTI_IRQHandler(COL1_Pin);
    HAL_GPIO_EXTI_IRQHandler(COL2_Pin);
    HAL_GPIO_EXTI_IRQHandler(COL3_Pin);
}


void TIM6_DAC_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim6);
}


void vinyl_stop_effect() {
    float slowdown_factor = 1.0f;
    float slowdown_step = 0.02f;

    while (slowdown_factor > 0) {
        playback_index++;
        HAL_Delay(10);
        slowdown_factor -= slowdown_step;
        if (slowdown_factor < 0) slowdown_factor = 0;

        __HAL_TIM_SET_AUTORELOAD(&htim6, (uint32_t)(124 / slowdown_factor));
    }

    print_msg("Vinyl Stop Complete\n");
    HAL_TIM_Base_Stop_IT(&htim6);
    HAL_Delay(500);
    __HAL_TIM_SET_AUTORELOAD(&htim6, (uint32_t)(124));
}

/* USER CODE END 1 */
