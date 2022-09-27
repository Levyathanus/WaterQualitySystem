/**
 ******************************************************************************
 * @file    stm32l0538_discovery_epd.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    18-June-2014
 * @brief   This file includes the EPD driver for Display Module of
 *          STM32L0538-DISCO kit (MB1143).
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stm32l0538_discovery_epd.h"
#include "stm32l0538_discovery.h"
#include <string.h>
#include "stdlib.h"
//#include "font20epd.c"
//#include "font16epd.c"
//#include "font12epd.c"
//#include "font8epd.c"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32L0538_DISCOVERY
 * @{
 */

/** @defgroup STM32L0538_DISCOVERY_EPD
 * @{
 */

/** @defgroup STM32L0538_DISCOVERY_EPD_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @defgroup STM32L0538_DISCOVERY_EPD_Private_Defines
 * @{
 */
/**
 * @}
 */

/** @defgroup STM32L0538_DISCOVERY_EPD_Private_Variables
 * @{
 */
static sFONT           *pFont;
static EPD_DrvTypeDef  *epd_drv;
/**
 * @}
 */

/** @defgroup STM32L0538_DISCOVERY_EPD_Private_FunctionPrototypes
 * @{
 */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c);
/**
 * @}
 */

/** @defgroup STM32L0538_DISCOVERY_EPD_Private_Functions
 * @{
 */

/**
 * @brief  Initializes the EPD.
 * @param  None
 * @retval EPD state
 */
uint8_t BSP_EPD_Init(void)
{
	uint8_t ret = EPD_ERROR;

	/* Default value for the Font */
	pFont = &Font16;

	epd_drv = &gde021a1_drv;

	/* EPD Init */
	epd_drv->Init();

	/* Clear the EPD screen */
	BSP_EPD_Clear(EPD_COLOR_WHITE);

	/* Initialize the font */
	BSP_EPD_SetFont(&EPD_DEFAULT_FONT);

	ret = EPD_OK;

	return ret;
}

/**
 * @brief  Gets the EPD X size.
 * @param  None
 * @retval EPD X size
 */
uint32_t BSP_EPD_GetXSize(void)
{
	return(epd_drv->GetEpdPixelWidth());
}

/**
 * @brief  Gets the EPD Y size.
 * @param  None
 * @retval EPD Y size
 */
uint32_t BSP_EPD_GetYSize(void)
{
	return(epd_drv->GetEpdPixelHeight());
}

/**
 * @brief  Sets the Text Font.
 * @param  pFonts: specifies the layer font to be used.
 * @retval None
 */
void BSP_EPD_SetFont(sFONT *pFonts)
{
	pFont = pFonts;
}

/**
 * @brief  Gets the Text Font.
 * @param  None.
 * @retval the used layer font.
 */
sFONT *BSP_EPD_GetFont(void)
{
	return pFont;
}

/**
 * @brief  Clears the hole EPD.
 * @param  Color: Color of the background
 * @retval None
 */
void BSP_EPD_Clear(uint16_t Color)
{
	uint32_t index = 0;

	epd_drv->SetDisplayWindow(0, 0, 171, 17);

	for(index = 0; index < 3096; index++)
	{
		epd_drv->WritePixel(Color);
	}
}

/**
 * @brief  Displays one character.
 * @param  Xpos: start column address.
 * @param  Ypos: the Line where to display the character shape.
 * @param  Ascii: character ascii code, must be between 0x20 and 0x7E.
 * @retval None
 */
void BSP_EPD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
	Ascii -= 32;

	DrawChar(Xpos, Ypos, &pFont->table[Ascii * ((pFont->Height) * (pFont->Width))]);
}

/**
 * @brief  Displays characters on the EPD.
 * @param  Xpos: X position
 * @param  Ypos: Y position
 * @param  Text: Pointer to string to display on EPD
 * @param  Mode: Display mode
 *          This parameter can be one of the following values:
 *            @arg  CENTER_MODE
 *            @arg  RIGHT_MODE
 *            @arg  LEFT_MODE
 * @retval None
 */
void BSP_EPD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode)
{
	uint16_t refcolumn = 1, i = 0;
	uint32_t size = 0, xsize = 0;
	uint8_t  *ptr = Text;

	/* Get the text size */
	while (*ptr++) size ++ ;

	/* Characters number per line */
	xsize = (BSP_EPD_GetXSize()/pFont->Width);

	switch (Mode)
	{
	case CENTER_MODE:
	{
		refcolumn = Xpos + ((xsize - size)* pFont->Width) / 2;
		break;
	}
	case LEFT_MODE:
	{
		refcolumn = Xpos;
		break;
	}
	case RIGHT_MODE:
	{
		refcolumn =  - Xpos + ((xsize - size)*pFont->Width);
		break;
	}
	default:
	{
		refcolumn = Xpos;
		break;
	}
	}

	/* Send the string character by character on EPD */
	while ((*Text != 0) & (((BSP_EPD_GetXSize() - (i*pFont->Width)) & 0xFFFF) >= pFont->Width))
	{
		/* Display one character on EPD */
		BSP_EPD_DisplayChar(refcolumn, Ypos, *Text);
		/* Decrement the column position by 16 */
		refcolumn += pFont->Width;
		/* Point on the next character */
		Text++;
		i++;
	}
}

/**
 * @brief  Displays a character on the EPD.
 * @param  Line: Line where to display the character shape
 *          This parameter can be one of the following values:
 *            @arg  0..8: if the Current fonts is Font8
 *            @arg  0..5: if the Current fonts is Font12
 *            @arg  0..3: if the Current fonts is Font16
 *            @arg  0..2: if the Current fonts is Font20
 * @param  ptr: Pointer to string to display on EPD
 * @retval None
 */
void BSP_EPD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr)
{
	BSP_EPD_DisplayStringAt(0, LINE(Line), ptr, LEFT_MODE);
}

/**
 * @brief  Draws an horizontal line.
 * @param  Xpos: X position
 * @param  Ypos: Y position
 * @param  Length: line length
 * @retval None
 */
void BSP_EPD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t index = 0;

	epd_drv->SetDisplayWindow(Xpos, Ypos, Xpos + Length, Ypos);

	for(index = 0; index < Length; index++)
	{
		/* Prepare the register to write data on the RAM */
		epd_drv->WritePixel(0x3F);
	}
}

/**
 * @brief  Draws a vertical line.
 * @param  Xpos: X position
 * @param  Ypos: Y position
 * @param  Length: line length.
 * @retval None
 */
void BSP_EPD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t index = 0;

	epd_drv->SetDisplayWindow(Xpos, Ypos, Xpos, Ypos + Length);

	for(index = 0; index < Length; index++)
	{
		/* Prepare the register to write data on the RAM */
		epd_drv->WritePixel(0x00);
	}
}

/**
  * @brief  Draws an uni-line (between two points).
  * @param  x1: Point 1 X position
  * @param  y1: Point 1 Y position
  * @param  x2: Point 2 X position
  * @param  y2: Point 2 Y position
  * @retval None
 */
void BSP_EPD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, y_prev = 0, xinc1 = 0, xinc2 = 0,
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, num_add = 0, num_pixels = 0,
  curpixel = 0;

  deltax = abs(x2 - x1);        /* The difference between the x's */
  deltay = abs(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;						/* Start y off at the first pixel */
  y_prev = y;


  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }

  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    num_add = deltay;
    num_pixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    num_add = deltax;
    num_pixels = deltay;         /* There are more y-values than x-values */
  }

  for (curpixel = 0; curpixel <= num_pixels; curpixel++)
  {
    //BSP_LCD_DrawPixel(x, y, DrawProp[ActiveLayer].TextColor);   /* Draw the current pixel */
	epd_drv->SetDisplayWindow(x, y, x, y);
	if(y != y_prev){
		y_prev = y;
		epd_drv->WritePixel(0x2f);
	} else{
		epd_drv->WritePixel(0xf7);
	}

	num += num_add;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;
  }
}

/**
 * @brief  Draws a rectangle.
 * @param  Xpos: X position
 * @param  Ypos: Y position
 * @param  Height: rectangle height
 * @param  Width: rectangle width
 * @retval None
 */
void BSP_EPD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	/* Draw horizontal lines */
	BSP_EPD_DrawHLine(Xpos, Ypos, Width);
	BSP_EPD_DrawHLine(Xpos, (Ypos + Height), (Width + 1));

	/* Draw vertical lines */
	BSP_EPD_DrawVLine(Xpos, Ypos, Height);
	BSP_EPD_DrawVLine((Xpos + Width), Ypos , Height);
}

/**
 * @brief  Displays a full rectangle.
 * @param  Xpos: X position.
 * @param  Ypos: Y position.
 * @param  Height: display rectangle height.
 * @param  Width: display rectangle width.
 * @retval None
 */
void BSP_EPD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint16_t index = 0;

	/* Set the rectangle */
	epd_drv->SetDisplayWindow(Xpos, Ypos, (Xpos + Width), (Ypos + Height));

	for(index = 0; index < 3096; index++)
	{
		epd_drv->WritePixel(0xFF);
	}
}

/**
 * @brief  Draws a triangle (between 3 points).
 * @param  Xpos1: Point 1 X position
 * @param  Ypos1: Point 1 Y position
 * @param  Xpos2: Point 2 X position
 * @param  Ypos2: Point 2 Y position
 * @param  Xpos3: Point 3 X position
 * @param  Ypos3: Point 3 Y position
 * @retval None
 */
void BSP_EPD_DrawTriangle(uint16_t Xpos1, uint16_t Ypos1, uint16_t Xpos2,uint16_t Ypos2,
		uint16_t Xpos3,uint16_t Ypos3)
{
	uint16_t Width = Xpos2 - Xpos1;
	uint16_t Height = Ypos3 - Ypos2;
	BSP_EPD_DrawHLine(Xpos1, Ypos1, Width); //cateto maggiore
	BSP_EPD_DrawVLine(Xpos2, Ypos2, Height); //cateto minore

	BSP_EPD_DrawLine(Xpos1, Ypos1, Xpos3, Ypos3);

}


/**
 * @brief  Displays a full triangle.
 * @param  Xpos1: Point 1 X position
 * @param  Ypos1: Point 1 Y position
 * @param  Xpos3: Point 3 X position
 * @param  Ypos3: Point 3 Y position
 * @param  points: points corresponding to quality of water
 * @retval None
 */
void BSP_EPD_FillTriangle(uint16_t Xpos1, uint16_t Ypos1, uint16_t Xpos3,uint16_t Ypos3,
		float points)
{
	uint16_t intPoints = points * 10; // intPoints is the conversion of points base 100
	float y = 0;
	for(uint16_t x = Xpos1; x < intPoints+Xpos1; x++){
		/*
		 * y is the vertical coordinate of the point belonging to the line passing
		 * through point of the hypotenuse
		 */
		y = ((float)(x-Xpos1)/(float)(Xpos3 - Xpos1));
		y = ((float)y * (float)(Ypos3 - Ypos1));
		y = y + Ypos1;

		uint16_t yInt = (uint16_t) y;
		uint16_t height = yInt-Ypos1;
		BSP_EPD_DrawVLine(x, Ypos1, height);

	}


}

/**
 * @brief  Draws an Image.
 * @param  Xpos: X position in the EPD
 * @param  Ypos: Y position in the EPD
 * @param  Xsize: X size in the EPD
 * @param  Ysize: Y size in the EPD
 * @param  pdata: Pointer to the Image address
 * @retval None
 */
void BSP_EPD_DrawImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata)
{
	/* Set display window */
	epd_drv->SetDisplayWindow(Xpos, Ypos, (Xpos+Ysize-1), (Ypos+(Xsize/4)-1));

	if(epd_drv->DrawImage != NULL)
	{
		epd_drv->DrawImage(Xpos, Ypos, Xsize, Ysize, pdata);
	}
	epd_drv->SetDisplayWindow(0, 0, BSP_EPD_GetXSize(), BSP_EPD_GetYSize());
}

/**
 * @brief  Disables the clock and the charge pump.
 * @param  None
 * @retval None
 */
void BSP_EPD_CloseChargePump(void)
{
	/* Close charge pump */
	epd_drv->CloseChargePump();

	/* Add a 400 ms delay */
	EPD_Delay(400);
}

/**
 * @brief  Updates the display from the data located into the RAM.
 * @param  None
 * @retval None
 */
void BSP_EPD_RefreshDisplay(void)
{
	/* Refresh display sequence */
	epd_drv->RefreshDisplay();

	/* Poll on the BUSY signal and wait for the EPD to be ready */
	while (HAL_GPIO_ReadPin(EPD_BUSY_GPIO_PORT, EPD_BUSY_PIN) != (uint16_t)RESET);

	/*  EPD reset pin mamagement */
	EPD_RESET_HIGH();

	/* Add a 10 ms Delay after EPD pin Reset */
	EPD_Delay(10);
}

/**
 * @brief  Fills the buffer with empty spaces until the end of the line.
 * @param  buf: the message buffer
 * @param  fontSize: the current display font size
 * @retval None
 */
void BSP_EPD_FormatToLine(char* buf, sFONT_t fontSize)
{
	uint8_t diff = 0;
	diff = fontSize - strlen(buf);
	if(diff > 0)
	{
		while(--diff)
		{
			strcat(buf, " ");
		}
	}
}
/*******************************************************************************
                            Static Functions
 *******************************************************************************/

/**
 * @brief  Draws a character on EPD.
 * @param  Xpos: specifies the X position, can be a value from 0 to 171
 * @param  Ypos: specifies the Y position, can be a value from 0 to 17
 * @param  c: pointer to the character data
 * @retval None
 */
static void  DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c)
{
	uint32_t index = 0;
	uint32_t data_length = 0;
	uint16_t height = 0;
	uint16_t width = 0;

	width  = pFont->Width;
	height = pFont->Height;

	/* Set the Character display window */
	epd_drv->SetDisplayWindow(Xpos, Ypos, (Xpos + width - 1), (Ypos + height - 1));

	data_length = (height * width);

	for(index = 0; index < data_length; index++)
	{
		epd_drv->WritePixel(c[index]);
	}
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
