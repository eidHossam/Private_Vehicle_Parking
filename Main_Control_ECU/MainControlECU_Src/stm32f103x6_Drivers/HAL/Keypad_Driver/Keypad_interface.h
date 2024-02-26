/*
 **************************************************************************************************************************
 * file		 :  Keypad_interface.h
 * brief     :  This module contains functions for configuring and controlling a 3*4 Keypad.
 * Author    :  Hossam Eid
 * Created on:  Sep 5, 2023
 **************************************************************************************************************************
 */

#ifndef HAL_KEYPAD_DRIVER_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_DRIVER_KEYPAD_INTERFACE_H_

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
*                   Keypad Ports
*===============================================
*/
#define KEYPAD_DATA_PORT        GPIOB

/*
*===============================================
*                   KEYPAD PINS
*===============================================
*/
#define KEYPAD_ROW0     GPIO_PIN12
#define KEYPAD_ROW1     GPIO_PIN13
#define KEYPAD_ROW2     GPIO_PIN14
#define KEYPAD_ROW3     GPIO_PIN15

#define KEYPAD_COL0     GPIO_PIN11
#define KEYPAD_COL1     GPIO_PIN9
#define KEYPAD_COL2     GPIO_PIN8

/*
*===============================================
*                   KEYPAD DIMENSION
*===============================================
*/
#define KEYPAD_ROW_SIZE 4
#define KEYPAD_COL_SIZE 3

/*
*===============================================
*                   KEYPAD CHARACTERS
*===============================================
*/
/*NOTE: Put the characters in the same order of 
the keys on the keypad.*/
#define KEYPAD_KEYS { \
    '3', '2', '1', \
    '6', '5', '4', \
    '9', '8', '7', \
    '#', '0', '*'} 

#define NULL_CHAR 'N'
/**************************************************************************************************************************
===============================================
*       APIs Supported by "HAL KEYPAD DRIVER"
*===============================================
*/

/**
============================================================================================================
* @Func_name	:   Keypad_Init
* @brief		:   Initializes the keypad by making the keypad row pins as input and the column pins as output. 
* @param [in]	:   none.      
* @param [out]	:   none.
* @return       :   none.
* Note			:   none.
============================================================================================================
*/
void Keypad_Init(void);

/**
============================================================================================================
* @Func_name	:   Keypad_Get_Char
* @brief		:   Get the input character from the keypad.
* @param [in]	:   none.
* @param [out]	:   none.
* @return       :   The pressed character on the keypad which will be a value of @ref KEYPAD CHARACTERS
                :   Or NULL_CHAR if no key was pressed.
* Note			:   none.
============================================================================================================
*/
uint8 Keypad_Get_Char(void);

#endif /* HAL_KEYPAD_DRIVER_KEYPAD_INTERFACE_H_ */
