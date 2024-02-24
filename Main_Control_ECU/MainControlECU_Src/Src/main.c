/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Hossam Eid
 * @brief          : This program tests the functionality of the admin interface LCD and keypad.
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

#include "Keypad_Driver/Keypad_interface.h"
#include "LCD_Driver/LCD_interface.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void clock_init();

int main(void)
{
   uint8 pressedKey;
   clock_init();
   LCD_Init();
   Keypad_Init();
	
  
  while (1) 
	{
		  pressedKey = Keypad_Get_Char();
		  if(pressedKey != 'N')
		  {
		  	if(pressedKey == '#')
		  	{
		  		LCD_Clear_Screen();
		  	}else{
		  		LCD_Send_Char(pressedKey);
		  	}
		  }

  }
}

void clock_init()
{
	/*Enable GPIO_A*/
	APB2_PERI_CLOCK_EN(APB2_IOPA);

	/*Enable GPIO_B*/
	APB2_PERI_CLOCK_EN(APB2_IOPB);
}
