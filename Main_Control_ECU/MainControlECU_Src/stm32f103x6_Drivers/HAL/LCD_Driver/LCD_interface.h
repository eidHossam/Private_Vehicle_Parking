/*
**************************************************************************************************************************
* file		: LCD_interface.h
* brief     : This module contains functions for configuring and controlling a 16x2 LCD.	
* Author    : Hossam Eid
* Created on: Sep 4, 2023
**************************************************************************************************************************
* note: You can choose between 4_bit mode and 8_bit mode using the LCD_MODE_ macro in the "LCD MODE SELECTION" section.
**************************************************************************************************************************
*/

#ifndef HAL_LCD_DRIVER_LCD_INTERFACE_H_
#define HAL_LCD_DRIVER_LCD_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "stm32f103x6.h"
#include "GPIO/stm32f103x6_GPIO.h"
#include "Platform_Types.h"

/**************************************************************************************************************************
*===============================================
*               LCD MODE SELECTION
*===============================================
*/

#define EIGHT_BIT_MODE  8
#define FOUR_BIT_MODE   4
#define LCD_MODE_       FOUR_BIT_MODE

/**************************************************************************************************************************
*===============================================
*                   LCD ports
*===============================================
*/

#define LCD_DATA_PORT       GPIOA
#define LCD_CTRL_PORT       GPIOB

/**************************************************************************************************************************
*===============================================
*                   LCD signals
*===============================================
*/

#define LCD_RS_PIN      GPIO_PIN4         /*Select register PIN (INS, Data)*/
#define LCD_EN_PIN      GPIO_PIN5


#define LCD_D4          GPIO_PIN10
#define LCD_D5          GPIO_PIN11 
#define LCD_D6          GPIO_PIN12
#define LCD_D7          GPIO_PIN15

/**************************************************************************************************************************
*===============================================
*               LCD SIZE
*===============================================
*/
#define LCD_WIDTH   16
#define LCD_HEIGHT  4

/**************************************************************************************************************************
*===============================================
*         Macros Configuration References
*===============================================
*/

/*@ref LCD_SELECT_REG ======================================= */
#define LCD_INS_REG     GPIO_PIN_LOW
#define LCD_DATA_REG    GPIO_PIN_HIGH

/*@ref LCD_OPERATION ======================================= */
#define LCD_WRITE       GPIO_PIN_LOW
#define LCD_READ        GPIO_PIN_HIGH

/*@ref LCD_COMMAND======================================= */
#define LCD_CLEAR_SCREEN                           0x01
#define LCD_RETURN_HOME                            0x02
#define LCD_MOVE_CURSOR_RIGHT                      0x06
#define LCD_MOVE_CURSOR_LEFT                       0x08
#define LCD_SHIFT_DISPLAY_RIGHT                    0x1C
#define LCD_SHIFT_DISPLAY_LEFT                     0x18
#define LCD_DISPLAY_ON_CURSOR_BLINK                0x0F
#define LCD_CURSOR_OFF                             0x0C
#define LCD_CURSOR_ON                              0x0E
#define LCD_FUNC_4BIT_2LINES                       0x28
#define LCD_FUNC_8BIT_2LINES                       0x38
#define LCD_ENTRY_MODE                             0x06
#define LCD_Function_8_bit                         0x32
#define LCD_Set5x7FontSize                         0x20
#define LCD_BEGIN_AT_FIRST_ROW                     0x80
#define LCD_BEGIN_AT_SECOND_ROW                    0xC0
#define LCD_BEGIN_AT_THIRD_ROW                     0x90
#define LCD_BEGIN_AT_FOURTH_ROW                    0xD0

/*@ref LCD_LINE_INDEX======================================= */
#define LCD_FIRST_LINE          0
#define LCD_SECOND_LINE         1
#define LCD_THIRD_LINE          2
#define LCD_FOURTH_LINE         3

/**************************************************************************************************************************
*===============================================
*         Helping Macros Configuration
*===============================================
*/
#define stringfy(str) ((uint8 *)str)

/**************************************************************************************************************************
===============================================
*       APIs Supported by "HAL LCD DRIVER"
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
void LCD_Init(void);

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
void LCD_Send_Command(uint8 command);

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
void LCD_Send_Char(uint8 data);

/*
============================================================================================================
* @Func_name	:   LCD_Send_String
* @brief		:   Prints a string on the LCD 
* @param [in]	:   data: The string to be printted on the LCD
* @param [out]	:   none.
* @return_value :   none.
* Note			:   when you get to the end of the line the next character will be printed on the next line.
*               :   if the entire LCD is full the LCD will be cleared first then print the character.
============================================================================================================
*/
void LCD_Send_String(uint8* string);

/*
============================================================================================================
* @Func_name	:   LCD_Cursor_XY
* @brief		:   Moves the cursor to the specified position.
* @param [in]	:   line: the index of the line to be moved to must be a value of @ref LCD_LINE_INDEX.
* @param [in]	:   col: the index of the column to be moved to must be a value between [0 >> 15]
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
============================================================================================================
*/
void LCD_Cursor_XY(uint8 line, uint8 col);

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
void LCD_Busy_Wait();

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
void LCD_Clear_Screen();

#endif /* HAL_LCD_DRIVER_LCD_INTERFACE_H_ */
