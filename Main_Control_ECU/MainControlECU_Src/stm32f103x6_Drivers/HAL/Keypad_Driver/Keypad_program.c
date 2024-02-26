/*
**************************************************************************************************************************
 * file		 :  Keypad_program.c
 * brief     :  This module contains functions for configuring and controlling a 4*4 Keypad.
 * Author    :  Hossam Eid
 * Created on:  Sep 5, 2023
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/

#include "Keypad_Driver/Keypad_interface.h"

/*
===============================================
*  				Global variables
*===============================================
*/

/**************************************************************************************************************************
================================================
 *           APIs functions definitions
 *===============================================
 */

/*
============================================================================================================
 * @Func_name	:   Keypad_Init
 * @brief		:   Initializes the keypad by making the keypad row pins as input and the column pins as output.
 * @param [in]	:   none.
 * @param [out]	:   none.
 * @return_value:   none.
 * Note			:   none.
============================================================================================================
 */
void Keypad_Init(void)
{
	GPIO_Pin_Config_t config;

	/*Keypad row pins as input with pull-up resistance*/
	config.pinNumber = KEYPAD_ROW0;
	config.pinMode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &config);

	config.pinNumber = KEYPAD_ROW1;
	config.pinMode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &config);

	config.pinNumber = KEYPAD_ROW2;
	config.pinMode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &config);

	config.pinNumber = KEYPAD_ROW3;
	config.pinMode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &config);

	/*Keypad column pins as output*/
	config.pinNumber = KEYPAD_COL0;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &config);

	config.pinNumber = KEYPAD_COL1;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &config);

	config.pinNumber = KEYPAD_COL2;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &config);
}

/*
============================================================================================================
 * @Func_name	:   Keypad_Get_Char
 * @brief		:   Get the input character from the keypad.
 * @param [in]	:   none.
 * @param [out]	:   none.
 * @return_value:   The pressed character on the keypad which will be a value of @ref KEYPAD CHARACTERS
                :   Or NULL_CHAR if no key was pressed.
 * Note			:   none.
============================================================================================================
 */
uint8 Keypad_Get_Char(void)
{
	uint8 keypad_chars[] = KEYPAD_KEYS;

 	uint8 KeypadRowPins[] = {KEYPAD_ROW0, KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3};
 	uint8 KeypadColPins[] = {KEYPAD_COL0, KEYPAD_COL1, KEYPAD_COL2};

	uint8 col, row, pressedKey;

	pressedKey = NULL_CHAR;
	for(col = 0; col <  KEYPAD_COL_SIZE; col++)
	{
		/*High on all column pins */
		MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, KEYPAD_COL0, GPIO_PIN_HIGH);
		MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, KEYPAD_COL1, GPIO_PIN_HIGH);
		MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, KEYPAD_COL2, GPIO_PIN_HIGH);

		/*Low output on the column to be tested.*/
		MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, KeypadColPins[col], GPIO_PIN_LOW);

		for(row = 0; row < KEYPAD_ROW_SIZE; row++)
		{
			/*Loop on all the buttons in this coloumn to
            see if any of them dropped to ground*/
			if(MCAL_GPIO_ReadPin(KEYPAD_DATA_PORT, KeypadRowPins[row]) == GPIO_PIN_LOW)
			{
				while(MCAL_GPIO_ReadPin(KEYPAD_DATA_PORT, KeypadRowPins[row]) == GPIO_PIN_LOW)
				{

				}

				pressedKey = keypad_chars[(row * KEYPAD_COL_SIZE) + col];
				break;
			}
		}

		if(pressedKey != NULL_CHAR)
		{
			break;
		}
	}
	return pressedKey;
}
