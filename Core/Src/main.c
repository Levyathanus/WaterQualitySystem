/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_hal_rcc.h"
#include "stm32l0538_discovery.h"
#include "stm32l0538_discovery_epd.h"
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PH_VALUES 		128
#define NTU_VALUES 		128
#define TDS_VALUES 		128

#define GREEN_LED_PORT 	LD_G_GPIO_Port
#define GREEN_LED_PIN 	LD_G_Pin

#define SENSOR_NUMBER 	3
/**
 * @brief  Time to wait for display information to disappear
 */
#define EPD_INFO_TIME 	10000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
/* USER CODE BEGIN PV */
uint8_t ntuCounter = 0;
uint8_t phCounter = 0;
uint8_t tdsCounter = 0;
const float TURBIDITY_VOLTAGE_CALIBRATION = 1.0244;
const float PH_VOLTAGE_CALIBRATION = 1.012;
const float PH_SLOPE = -4.4522;
const float TDS_CALIBRATION_COEFFICIENT = 0.75;
float temperature = 25.0;
float ntus[NTU_VALUES];
float pHs[PH_VALUES];
float tdsS[TDS_VALUES];
char msg[512];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */
static float Avg_Array(float*, int);
void Show_Measure(void);
void Show_Water_Quality(float, uint16_t, uint16_t);
void ADC_Select_Channel(uint32_t, uint32_t*);
void ADC_Calibrate(void);
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
	MX_ADC_Init();
	/* USER CODE BEGIN 2 */
	BSP_EPD_Init();
	BSP_EPD_Clear(EPD_COLOR_WHITE);
	BSP_EPD_RefreshDisplay();

	// Entering STOP mode with Low Power Regulator
	HAL_SuspendTick();
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

	// Showing results when exiting STOP mode
	Show_Measure();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {}
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
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

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
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
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief ADC Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC_Init(void)
{

	/* USER CODE BEGIN ADC_Init 0 */

	/* USER CODE END ADC_Init 0 */

	ADC_ChannelConfTypeDef sConfig = {0};

	/* USER CODE BEGIN ADC_Init 1 */

	/* USER CODE END ADC_Init 1 */

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc.Instance = ADC1;
	hadc.Init.OversamplingMode = DISABLE;
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.DMAContinuousRequests = DISABLE;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	hadc.Init.LowPowerAutoWait = DISABLE;
	hadc.Init.LowPowerFrequencyMode = DISABLE;
	hadc.Init.LowPowerAutoPowerOff = DISABLE;
	if (HAL_ADC_Init(&hadc) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure for the selected ADC regular channel to be converted.
	 */
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure for the selected ADC regular channel to be converted.
	 */
	sConfig.Channel = ADC_CHANNEL_4;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure for the selected ADC regular channel to be converted.
	 */
	sConfig.Channel = ADC_CHANNEL_5;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN ADC_Init 2 */

	/* USER CODE END ADC_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD_G_GPIO_Port, LD_G_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA1 */
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : LD_G_Pin */
	GPIO_InitStruct.Pin = LD_G_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD_G_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

}

/* USER CODE BEGIN 4 */
void ADC_Select_Channel(uint32_t channel, uint32_t* channelsToDisable)
{
	ADC_ChannelConfTypeDef enableConfig = {0};
	ADC_ChannelConfTypeDef disableConfig = {0};

	enableConfig.Channel = channel;
	enableConfig.Rank = 1;

	for(uint8_t i = 0; i < SENSOR_NUMBER - 1; i++)
	{
		disableConfig.Channel = channelsToDisable[i];
		disableConfig.Rank = ADC_RANK_NONE;
		if(HAL_ADC_ConfigChannel(&hadc, &disableConfig) != HAL_OK)
		{
			Error_Handler();
		}
	}

	if(HAL_ADC_ConfigChannel(&hadc, &enableConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

void ADC_Calibrate(void)
{
	/* (1) Ensure that ADEN = 0 */
	/* (2) Clear ADEN */
	/* (3) Set ADCAL=1 */
	/* (4) Wait until EOCAL=1 */
	/* (5) Clear EOCAL */
	if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
	{
		ADC1->CR |= ADC_CR_ADDIS; /* (2) */
	}
	ADC1->CR |= ADC_CR_ADCAL; /* (3) */
	while ((ADC1->ISR & ADC_ISR_EOCAL) == 0); /* (4) */
	ADC1->ISR |= ADC_ISR_EOCAL; /* (5) */
}

static float Avg_Array(float* arr, int values) {
	if(values == 0)
	{
		return 0.0;
	}
	float sum = 0;
	for(int i = 0; i < values; i++) {
		sum += arr[i];
	}

	return sum/values;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_1)
	{
		// Wake up from STOP mode
		SystemClock_Config();
		HAL_ResumeTick();
		HAL_GPIO_TogglePin(GREEN_LED_PORT, GREEN_LED_PIN);
	}

}

void Show_Measure(void)
{
	__disable_irq();
	uint16_t phRawValue, ntuRawValue, tdsRawValue;
	float phVoltage, ntuVoltage, tdsVoltage;
	float ntu, pH, tds;
	uint16_t ntuAvgValue, tdsAvgValue;
	float pHAvgValue;

	ADC_Calibrate();

	uint32_t channelsToDisable[2] = { ADC_CHANNEL_0, ADC_CHANNEL_5 };
	ADC_Select_Channel(ADC_CHANNEL_4, channelsToDisable);
	while(phCounter < PH_VALUES)
	{
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
		phRawValue = HAL_ADC_GetValue(&hadc); // (7pH, 2048), (4pH, 2600) @ 25°C -> N.B. pH decreases with temperature
		phVoltage = ((float)phRawValue) / 4095 * 5.0 * PH_VOLTAGE_CALIBRATION; // Voltage conversion: 12 bit ADC (2^12 = 4096), 5V power

		// y = m*x + q, with m = -4.4522 and q = 18.73
		pH =  PH_SLOPE * phVoltage + 18.73;
		pHs[phCounter++] = pH;
	}
	HAL_ADC_Stop(&hadc);

	channelsToDisable[1] = ADC_CHANNEL_4;
	ADC_Select_Channel(ADC_CHANNEL_5, channelsToDisable);
	while(ntuCounter < NTU_VALUES)
	{
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
		ntuRawValue = HAL_ADC_GetValue(&hadc);
		ntuVoltage = ((float)ntuRawValue) / 4095 * 5.0 * TURBIDITY_VOLTAGE_CALIBRATION; // Voltage conversion: 12 bit ADC (2^12 = 4096), 5V power

		if(ntuVoltage < 2.63)
		{
			ntu = 3000;
		} else {
			// y = -1120.4 * x^2 + 5742.3 * x - 4353.8
			ntu = -1120.4 * ntuVoltage * ntuVoltage + 5742.3 * ntuVoltage - 4353.8;
			if (ntu < 0)
			{
				ntu = 0;
			}
		}
		if(ntu > 3000)
		{
			ntu = 3000;
		}
		ntus[ntuCounter++] = ntu;
	}
	HAL_ADC_Stop(&hadc);

	channelsToDisable[0] = ADC_CHANNEL_5;
	ADC_Select_Channel(ADC_CHANNEL_0, channelsToDisable);
	while(tdsCounter < TDS_VALUES)
	{
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

		tdsRawValue = HAL_ADC_GetValue(&hadc);
		tdsVoltage = ((float)tdsRawValue) / 4095 * 5.0;

		float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
		float compensationVoltage = tdsVoltage / compensationCoefficient; //temperature compensation
		tds = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage
				- 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5 * TDS_CALIBRATION_COEFFICIENT; //convert voltage value to tds value

		tdsS[tdsCounter++] = tds;

	}
	HAL_ADC_Stop(&hadc);
	__enable_irq();

	pHAvgValue = Avg_Array(pHs, PH_VALUES);
	ntuAvgValue = (uint16_t) Avg_Array(ntus, NTU_VALUES);
	tdsAvgValue = (uint16_t) Avg_Array(tdsS, TDS_VALUES);

	BSP_EPD_SetFont(&Font16);
	BSP_EPD_Clear(EPD_COLOR_WHITE);
	sprintf(msg, "Turb.: %d NTU", ntuAvgValue);
	BSP_EPD_FormatToLine(msg, FONT_16_SIZE);
	BSP_EPD_DisplayStringAtLine(FONT_16_MAX_LINES - 1, (uint8_t*) msg);
	sprintf(msg, "pH: %.1f", pHAvgValue);
	BSP_EPD_FormatToLine(msg, FONT_16_SIZE);
	BSP_EPD_DisplayStringAtLine(FONT_16_MAX_LINES - 2, (uint8_t*) msg);
	sprintf(msg, "TDS: %d ppm", tdsAvgValue);
	BSP_EPD_FormatToLine(msg, FONT_16_SIZE);
	BSP_EPD_DisplayStringAtLine(FONT_16_MAX_LINES - 3, (uint8_t*) msg);
	BSP_EPD_RefreshDisplay();

	HAL_Delay(EPD_INFO_TIME);
	Show_Water_Quality(pHAvgValue, ntuAvgValue, tdsAvgValue);
}

void Show_Water_Quality(float pH, uint16_t ntu, uint16_t tds)
{
	float qualityPoints = 0.0;
	int group;

	if(pH <= 8.5 && pH >= 6.5 && tds <= 400)
	{
		// NTU points +5 boost
		if(ntu <= 10)
		{
			qualityPoints += 5.0;
		}

		// pH points (1.5)
		if(pH >= 7.0 && pH <= 7.5)
		{
			qualityPoints += 1.5;
		} else if(pH > 7.5) {
			qualityPoints += (9.0 - pH);
		} else {
			qualityPoints += 1.5 - 2 * (7.0 - pH); // pH 6.5 -> 0.5, pH 6.9 -> 1.3
		}

		// TDS points (3.5)
		// 0 - 100 -> 3.5
		// 100 - 170 -> min. 3.1
		// 170 - 200 -> -0.1 -> 2.8
		// 200 - 300 -> 100/14 (7) -0.1
		// 300 - 400 -> 100/14 (7) -0.1
		if(tds >= 0 && tds <= 100){
			qualityPoints += 3.5;
		} else if(tds > 100 && tds <= 170){
			/*101 è il minimo valore dell'intervallo
			17.5 è lo scarto tra due gruppi -> (170-100)/4=17.5
			0 <= group <= 3*/
			group = (tds - 101)/17.5;
			qualityPoints += 3.4 - 0.1 * group;
		} else if(tds > 170 && tds <= 200){
			group = (tds - 171)/10;
			qualityPoints += 3.0 - 0.1 * group;
		} else if(tds > 200 && tds <= 300){
			group = (tds - 201)/7.14;
			qualityPoints += 2.7 - 0.1 * group;
		} else if(tds > 300 && tds <= 400){
			group = (tds - 301)/7.14;
			qualityPoints += 1.3 - 0.1 * group;
		}

	}

	BSP_EPD_SetFont(&Font12);
	BSP_EPD_Clear(EPD_COLOR_WHITE);
	sprintf(msg, "Water quality scale");
	BSP_EPD_FormatToLine(msg, FONT_12_SIZE);
	BSP_EPD_DisplayStringAt(105, 15,(uint8_t*) msg, CENTER_MODE);
	BSP_EPD_DrawTriangle(34, 3, 134, 3, 134, 13);
	BSP_EPD_FillTriangle(34, 3, 134, 13, qualityPoints);
	BSP_EPD_RefreshDisplay();
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
