/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "stm32f4xx.h"

// Defines for RCC (Reset and Clock Control) register values
#define RCC_GPIOA_ENR (0b01)
#define RCC_GPIOD_ENR (0b01 << 3)
#define RCC_TIM2_ENR (0b01)

// Define for GPIOD Pin 14 (Red LED)
#define GPIOD_PORT14_OUTPUT (0b01 << 28)

// Defines for EXTI (External Interrupt) configuration
#define EXTI_RTSR_PORTA0 (0b01)
#define EXTI_IMR_PORTA0 (0b01)
#define PORT14_GPIOD (0b01 << 14)

// Defines for TIM2 (Timer 2) configuration
#define TIM2_CR1_CE (0b01)
#define TIM2_DIER_UIE (0b01)
#define TIM2_DIER_TIE (0b01 << 6)
#define TIM2_SR_UIF (0b01)


// Function prototypes
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void TIM2_Init(void);
void Error_Handler(void);
void TIM2_IRQHandler(void);



int main(void)
{

	SystemClock_Config();
	MX_GPIO_Init();
	TIM2_Init();
    while (1)
    {
	   // Main application loop
    }

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
// Function to configure the system clock
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
// Function to initialize GPIO pins
static void MX_GPIO_Init(void)
{
    // Enable clock for GPIOD
    RCC->AHB1ENR |= RCC_GPIOD_ENR;

    // Configure GPIOD Pin 14 (Red LED) as an output
    GPIOD->MODER |= GPIOD_PORT14_OUTPUT;

    // Enable TIM2_IRQn (TIM2 global interrupt) in NVIC
    NVIC_EnableIRQ(TIM2_IRQn);

    // Set initial state for GPIOD Pin 14 (Red LED)
    GPIOD->BSRR |= PORT14_GPIOD;
}


// Function to initialize TIM2 (Timer 2)
static void TIM2_Init(void)
{
	// Enable clock for TIM2
	RCC->APB1ENR |= RCC_TIM2_ENR;

	// Configure TIM2 settings (interrupts, prescaler, and auto-reload value)
	TIM2->DIER |= TIM2_DIER_UIE ;
	TIM2->DIER |= TIM2_DIER_TIE ;
	TIM2->PSC=0xFF;			 // Prescaler value
	TIM2->ARR=50625;		 // Auto-reload value for a 270ms delay

	 // Enable TIM2_IRQn (TIM2 global interrupt) in NVIC
	 NVIC_EnableIRQ(TIM2_IRQn);

	 // Start the timer by enabling the counter
	 TIM2->CR1 |= TIM2_CR1_CE;
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
// Function to handle errors (e.g., HAL errors)
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

// TIM2 interrupt handler
void TIM2_IRQHandler(void)
{
	// Clear the update interrupt flag for TIM2
	TIM2->SR &= ~(TIM2_SR_UIF);
    static int i=0;
    i++;

    // Toggle the state of GPIOD Pin 14 (Red LED) based on 'i'
    if(i % 2)
    {
	  GPIOD->BSRR |= PORT14_GPIOD;		 // Turn on the Red LED

    }
    else
    {

	  GPIOD->BSRR |= PORT14_GPIOD <<16 ;	// Turn off the Red LED
    }
}


