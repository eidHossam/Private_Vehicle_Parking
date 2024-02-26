/*
**************************************************************************************************************************
* file		: LCD_program.c
* brief     : This module contains functions for configuring and controlling a 16x2 LCD.	
* Author    : Hossam Eid
* Created on: Sep 4, 2023
**************************************************************************************************************************
*/

#include "LCD_interface.h"
#include "Bit_Math.h"

/*
*===============================================
*  				Global variables
*===============================================
*/
static uint8 charCounter = 0;
static uint8 lineCounter = 0;
GPIO_Pin_Config_t config;

/**************************************************************************************************************************
===============================================
*  				Local functions
*===============================================
*/

/*
============================================================================================================
 * @Func_name	:	_delay_ms
 * @brief		:	Delay a certain number of milliseconds.
 * @param [in]	:	delay_counter: the number of milliseconds to be delayed.
 * @param [out]	:	none.
 * @return_value :	none.
 * Note			:	This isn't an accurate function.
============================================================================================================
 */
void _delay_ms(uint8 delay_Counter)
{
	volatile uint8 i, j;
	for(i = 0; i < delay_Counter; i++)
	{
		for ( j = 0; j < 100; j++)
		{
		}
	}
}

/*
============================================================================================================
 * @Func_name	:	LCD_Enable_Pulse
 * @brief		:	A function to inform the LCD that there is new data being sent to it by pulsing the EN switch.
 * @param [in]	:	none.
 * @param [out]	:	none.
 * @return_value :	none.
 * Note			:	none.
============================================================================================================
 */
void LCD_Enable_Pulse()
{
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_HIGH);
	_delay_ms(50);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_LOW);
}

/*
============================================================================================================
 * @Func_name	:	Check_End_Of_Line
 * @brief		:	Check if we are at the end of the line to either go the next line or clear the screen.
 * @param [in]	:	none.
 * @param [out]	:	none.
 * @return_value :	none.
 * Note			:	none.
============================================================================================================
 */
void Check_End_Of_Line()
{
	//If the first line is full go to the next line
	if(charCounter >= LCD_WIDTH && lineCounter < LCD_HEIGHT - 1)
	{
		charCounter = 0;
		lineCounter++;
		LCD_Cursor_XY(lineCounter, 0);
	}else if(charCounter >= LCD_WIDTH && lineCounter == LCD_HEIGHT - 1)
	{
		LCD_Clear_Screen();
		LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW);
		charCounter = 0;
		lineCounter = 0;
	}
}

/**************************************************************************************************************************
===============================================
*  			APIs functions definitions
*===============================================
*/


/*
============================================================================================================
 * @Func_name	:   LCD_Init.
 * @brief		:   Intialization of the LCD in the mode selected in "LCD mode selection" part.
 * @param [in]	:   none.
 * @param [out]	:   none.
 * @return_value :   none.
 * Note			:   none.
============================================================================================================
 */
void LCD_Init(void)
{
	/*Wait for the VCC to rise to the required value*/
	_delay_ms(20);

	/*Set all CTRL bits as output*/
	config.pinNumber = LCD_RS_PIN;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);

	config.pinNumber = LCD_EN_PIN;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);


	/*Select ins register, Write operation and Enable zero*/
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, LCD_INS_REG);
	_delay_ms(15);

#if LCD_MODE_ == EIGHT_BIT_MODE
	/*In case of 8 bits mode all the data pins are Output*/
	config.pinNumber = GPIO_PIN0;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = GPIO_PIN1;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = GPIO_PIN2;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = GPIO_PIN3;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = LCD_D4;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = LCD_D5;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = LCD_D6;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = LCD_D7;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);

	LCD_Send_Command(LCD_FUNC_8BIT_2LINES);
#elif LCD_MODE_ == FOUR_BIT_MODE
	/*In case of 4 bits mode the upper 4 pins of the port are output*/
	config.pinNumber = LCD_D4;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = LCD_D5;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = LCD_D6;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);
	
	config.pinNumber = LCD_D7;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_DATA_PORT, &config);

	_delay_ms(5);

	LCD_Send_Command(LCD_RETURN_HOME);
	LCD_Send_Command(LCD_FUNC_4BIT_2LINES);
#endif

	LCD_Send_Command(LCD_ENTRY_MODE);
	LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Send_Command(LCD_DISPLAY_ON_CURSOR_BLINK);
}

/*
============================================================================================================
 * @Func_name	:   LCD_Send_Command
 * @brief		:   Sends a command to the LCD display
 * @param [in]	:   command: the required command to be executed by the LCD must be a part of @ref LCD_Command
 * @param [out]	:   none.
 * @return_value :   none.
 * Note			:   none.
============================================================================================================
 */
void LCD_Send_Command(uint8 command)
{
	/*Check if the LCD is busy*/
	/*LCD_Busy_Wait();*/

	/*Select ins register, Write operation and Enable zero*/
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, LCD_INS_REG);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_LOW);

#if LCD_MODE_ == EIGHT_BIT_MODE
	MCAL_GPIO_WritePin(LCD_DATA_PORT, GPIO_PIN0, READ_BIT(command, 0));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, GPIO_PIN1, READ_BIT(command, 1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, GPIO_PIN2, READ_BIT(command, 2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, GPIO_PIN3, READ_BIT(command, 3));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D4, READ_BIT(command, 4));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D5, READ_BIT(command, 5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D6, READ_BIT(command, 6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D7, READ_BIT(command, 7));

	LCD_Enable_Pulse();
#elif LCD_MODE_ == FOUR_BIT_MODE
	/*Send the command upper nibble first*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D4, READ_BIT(command, 4));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D5, READ_BIT(command, 5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D6, READ_BIT(command, 6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D7, READ_BIT(command, 7));
	LCD_Enable_Pulse();

	/*Send the command lower nibble first*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D4, READ_BIT(command, 0));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D5, READ_BIT(command, 1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D6, READ_BIT(command, 2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D7, READ_BIT(command, 3));
	LCD_Enable_Pulse();
#endif
}

/*
============================================================================================================
* @Func_name	:   LCD_Send_Char
* @brief		:   Prints a character on the LCD
* @param [in]	:   data: The character to be printted on the LCD
* @param [out]	:   none.
* @return_value :   none.
* Note			:   when you get to the end of the line the next character will be printed on the next line.
*               :   if the entire LCD is full the LCD will be cleared first then print the character.
============================================================================================================
 */
void LCD_Send_Char(uint8 data)
{
	/*Check if the LCD is busy*/
	/*LCD_Busy_Wait();*/
	Check_End_Of_Line();

	/*Data reigster, Write operation and Enable zero*/
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, LCD_DATA_REG);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_LOW);


#if LCD_MODE_ == EIGHT_BIT_MODE
	MCAL_GPIO_WritePin(LCD_DATA_PORT, GPIO_PIN0, READ_BIT(data, 0));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, GPIO_PIN1, READ_BIT(data, 1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, GPIO_PIN2, READ_BIT(data, 2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, GPIO_PIN3, READ_BIT(data, 3));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D4, READ_BIT(data, 4));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D5, READ_BIT(data, 5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D6, READ_BIT(data, 6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D7, READ_BIT(data, 7));

	LCD_Enable_Pulse();
#elif LCD_MODE_ == FOUR_BIT_MODE
	/*Send the data upper nibble first*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D4, READ_BIT(data, 4));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D5, READ_BIT(data, 5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D6, READ_BIT(data, 6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D7, READ_BIT(data, 7));
	LCD_Enable_Pulse();

	/*Send the data lower nibble first*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D4, READ_BIT(data, 0));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D5, READ_BIT(data, 1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D6, READ_BIT(data, 2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_D7, READ_BIT(data, 3));
	LCD_Enable_Pulse();
#endif
	charCounter++;
}

/*
============================================================================================================
 * @Func_name	:   LCD_Send_String
 * @brief		:   Prints a string on the LCD
 * @param [in]	:   data: The string to be printted on the LCD
 * @param [out]	:   none.
 * @return_value:   none.
 * Note			:   when you get to the end of the line the next character will be printed on the next line.
 *              :   if the entire LCD is full the LCD will be cleared first then print the character.
============================================================================================================
 */
void LCD_Send_String(uint8* string)
{
	while(*string)
	{
		LCD_Send_Char(*string++);
	}
}

/*
============================================================================================================
 * @Func_name	:   LCD_Cursor_XY
 * @brief		:   Moves the cursor to the specified position.
 * @param [in]	:   line: the index of the line to be moved to must be a value of @ref LCD_LINE_INDEX.
 * @param [in]	:   col: the index of the column to be moved to must be a value between [0 >> 15]
 * @param [out]	:   none.
 * @return_value:   none.
 * Note			:   none.
============================================================================================================
 */
void LCD_Cursor_XY(uint8 line, uint8 col)
{
	/*Check if the arguments are in the allowed range*/
	if(((col >= 0) && (col < LCD_WIDTH)) && ((line >= 0) && (line < LCD_HEIGHT)))
	{
		switch (line)
		{
		case LCD_FIRST_LINE:
			LCD_Send_Command(LCD_BEGIN_AT_FIRST_ROW + col);
			break;
		case LCD_SECOND_LINE:
			LCD_Send_Command(LCD_BEGIN_AT_SECOND_ROW + col);
			break;
		case LCD_THIRD_LINE:
			LCD_Send_Command(LCD_BEGIN_AT_THIRD_ROW + col);
			break;
		case LCD_FOURTH_LINE:
			LCD_Send_Command(LCD_BEGIN_AT_FOURTH_ROW + col);
			break;

		default:
			break;
		}

		lineCounter = line;
		charCounter = col;
	}
}

/*
============================================================================================================
* @Func_name	:   LCD_Busy_Wait
* @brief		:   Makes sure the LCD is done executing the previous command before sending another command.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
============================================================================================================
 */
void LCD_Busy_Wait()
{
#if LCD_MODE_ == EIGHT_BIT_MODE
	/*In case of 8 bits mode all the data pins are input*/
	config.pinNumber = GPIO_PIN0;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = GPIO_PIN1;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = GPIO_PIN2;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = GPIO_PIN3;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D4;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D5;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D6;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D7;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);

#elif LCD_MODE_ == FOUR_BIT_MODE
	/*In case of 4 bits mode the upper 4 pins of the port are input*/
	config.pinNumber = LCD_D4;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D5;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D6;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D7;
	config.pinMode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
#endif
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, LCD_INS_REG); 	/*RS = 0      INS register*/

	LCD_Enable_Pulse();

#if LCD_MODE_ == EIGHT_BIT_MODE
	/*In case of 8 bits mode all the data pins are output*/
	config.pinNumber = GPIO_PIN0;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = GPIO_PIN1;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = GPIO_PIN2;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = GPIO_PIN3;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D4;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D5;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D6;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D7;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);

#elif LCD_MODE_ == FOUR_BIT_MODE
	/*In case of 4 bits mode the upper 4 pins of the port are output*/
	config.pinNumber = LCD_D4;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D5;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D6;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
	
	config.pinNumber = LCD_D7;
	config.pinMode = GPIO_MODE_GP_OUTPUT_PP_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &config);
#endif
}

/*
============================================================================================================
 * @Func_name	:   LCD_Clear_Screen
 * @brief		:   Clears the LCD screen.
 * @param [in]	:   none.
 * @param [out]	:   none.
 * @return_value :   none.
 * Note			:   none.
============================================================================================================
 */
void LCD_Clear_Screen()
{
	LCD_Send_Command(LCD_CLEAR_SCREEN);
	charCounter = 0;
	lineCounter = 0;
}


