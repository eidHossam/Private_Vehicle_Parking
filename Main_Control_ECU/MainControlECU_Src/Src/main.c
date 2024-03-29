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
#include "APP.h"

int main(void)
{

	Dashboard_ECU_APP_SETUP();
  
  	while (1) 
	{
		Dashboard_ECU_APP_Loop();
 	}
}
