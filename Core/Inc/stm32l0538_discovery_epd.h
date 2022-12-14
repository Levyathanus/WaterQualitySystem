/**
 ******************************************************************************
 * @file    stm32l0538_discovery_epd.h
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    18-June-2014
 * @brief   This file contains all the functions prototypes for the
 *          stm32l0538_discovery_epd.c driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0538_DISCOVERY_EPD_H
#define __STM32L0538_DISCOVERY_EPD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "..\Components\gde021a1\gde021a1.h"
#include "fontsepd.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32L0538_DISCOVERY
 * @{
 */

/** @defgroup STM32L053_DISCOVERY_EPD
 * @{
 */


/** @defgroup STM32L0538_DISCOVERY_EPD_Exported_Types
 * @{
 */
typedef enum
{
	EPD_OK = 0,
	EPD_ERROR = 1,
	EPD_TIMEOUT = 2
} EPD_StatusTypeDef;

/**
 * @brief  Line mode structures definition
 */
typedef enum
{
	CENTER_MODE             = 0x01,    /*!< Center mode */
	RIGHT_MODE              = 0x02,    /*!< Right mode  */
	LEFT_MODE               = 0x03     /*!< Left mode   */
} Text_AlignModeTypdef;

/**
 * @brief Max. characters per line for each font size
 */
#define FONT_8_MAX_LENGTH  	34
#define FONT_12_MAX_LENGTH	24
#define FONT_16_MAX_LENGTH 	15
#define FONT_20_MAX_LENGTH	12

/**
 * @brief Max. number of lines for each font size
 */
#define FONT_8_MAX_LINES	9 	// 0 .. 8
#define FONT_12_MAX_LINES	6	// 0 .. 5
#define FONT_16_MAX_LINES 	4	// 0 .. 3
#define FONT_20_MAX_LINES	3	// 0 .. 2
/**
 * @}
 */

/** @defgroup STM32L0538_DISCOVERY_EPD_Exported_Constants
 * @{
 */

/**
 * @brief  EPD color
 */
#define EPD_COLOR_BLACK         0x00
#define EPD_COLOR_DARKGRAY      0x55
#define EPD_COLOR_LIGHTGRAY     0xAA
#define EPD_COLOR_WHITE         0xFF

/**
 * @brief EPD default font
 */
#define EPD_DEFAULT_FONT         Font12

typedef enum {
	FONT_8_SIZE =   8,
	FONT_12_SIZE = 12,
	FONT_16_SIZE = 16,
	FONT_20_SIZE = 20
} sFONT_t;

/**
 * @}
 */

/** @defgroup STM32L0538_DISCOVERY_EPD_Exported_Functions
 * @{
 */
uint8_t  BSP_EPD_Init(void);
uint32_t BSP_EPD_GetXSize(void);
uint32_t BSP_EPD_GetYSize(void);

void     BSP_EPD_SetFont(sFONT *pFonts);
sFONT    *BSP_EPD_GetFont(void);

void     BSP_EPD_Clear(uint16_t Color);

void     BSP_EPD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
void     BSP_EPD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *pText, Text_AlignModeTypdef mode);
void     BSP_EPD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);

void     BSP_EPD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_EPD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_EPD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void     BSP_EPD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_EPD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_EPD_DrawTriangle(uint16_t Xpos1, uint16_t Ypos1, uint16_t Xpos2,uint16_t Ypos2,
				uint16_t Xpos3,uint16_t Ypos3);
void 	 BSP_EPD_FillTriangle(uint16_t Xpos1, uint16_t Ypos1, uint16_t Xpos3,uint16_t Ypos3,
				float points);
				
				
void     BSP_EPD_RefreshDisplay(void);

void     BSP_EPD_CloseChargePump(void);

void     BSP_EPD_DrawImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata);

void 	 BSP_EPD_FormatToLine(char* buf, sFONT_t fontSize);

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0538_DISCOVERY_EPD_H */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
