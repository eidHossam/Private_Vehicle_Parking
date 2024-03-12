/**
 **************************************************************************************************************************
 * brief     : This module contains functions for configuring and controlling General Purpose Input/Output (GPIO) pins.
 * Author    : Hossam Eid
 * Created on: 9/11/2023
 **************************************************************************************************************************
 * This module provides functions for configuring the mode, and pull-up/down resistors of GPIO pins,
 * as well as reading and writing their values. It is designed to be used with AVR processors, and may not be
 * compatible with other architectures.
 *
 * note: This module is intended for use with the Atmega32 microcontroller series, but may be adapted for use with
 * other compatible processors.
 **************************************************************************************************************************
 */

#ifndef ATMEGA32_GPIO_H_
#define ATMEGA32_GPIO_H_

/*===============================================
* Includes
*===============================================*/
#include "Atmega32.h"

/****************************************************************/
/*
*===============================================
* User type definitions (structures)
*===============================================
*/

typedef struct{
    uint8_t pinNumber;      /*Choose the pin to be configured
                            This parameter must be a value of @ref GPIO_PIN_define*/

    uint8_t pinMode;         /*Choose the operating mode of the pin to be configured
                             This parameter must be a value of @ref GPIO_MODE_define*/
}GPIO_Pin_Config_t;


/****************************************************************/
/*===============================================
* Macros Configuration References
*===============================================*/

/*@ref GPIO_PIN_define------------*/
#define GPIO_PIN0   	0
#define GPIO_PIN1   	1
#define GPIO_PIN2   	2
#define GPIO_PIN3   	3
#define GPIO_PIN4   	4
#define GPIO_PIN5       5
#define GPIO_PIN6       6
#define GPIO_PIN7       7

/*@ref GPIO_MODE_define-------------*/

/*If DDxn is written logic one, Pxn is
configured as an output pin. 

If DDxn is written logic zero, Pxn is
configured as an input pin

Note: in case of input pull-up, we need to
enable PUD in the SFIOR.
*/

#define GPIO_MODE_INPUT_FLOATING        0   /*Floating input*/
#define GPIO_MODE_OUTPUT                1   /*Output mode*/
#define GPIO_MODE_INPUT_PU              2   /*Input pull-up mode*/


/*@ref GPIO_PIN_STATUS-----------*/
#define GPIO_PIN_HIGH 1
#define GPIO_PIN_LOW  0

/********************************************************
===============================================
* APIs Supported by "MCAL GPIO DRIVER"
*===============================================
*/

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_Init.
* @brief		:   Initialization function for the GPIOx PINy peripheral specified in the parameters.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @param [in]	:   Pointer to the GPIO_Pin_Config_t struct that contains the configuration information.
* @return_value :   none
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_Init(volatile GPIO_typedef* GPIOx ,GPIO_Pin_Config_t* pinConfig);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_DeInit.
* @brief		:   Deinitialization function that resets the entire port.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_DeInit(volatile GPIO_typedef * GPIOx);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_ReadPin.
* @brief		:   Reads the status of GPIOx PINy.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @param [in]	:   The number of the pin to be read must be a value of @ref GPIO_PIN_define.
* @return_value :   Current pin status which can be a value of @ref GPIO_PIN_STATUS.
* Note			:   none.
*===============================================
*/
uint8_t MCAL_GPIO_ReadPin(volatile GPIO_typedef * GPIOx, uint8_t pinNumber);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_ReadPort.
* @brief		:   Reads the status of the entire GPIOx.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @return_value :   Current port value.
* Note			:   none.
*===============================================
*/
uint8_t MCAL_GPIO_ReadPort(volatile GPIO_typedef * GPIOx);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_WritePin.
* @brief		:   Write a value on GPIOx PINy.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @param [in]	:   The number of the pin to be read must be a value of @ref GPIO_PIN_define.
* @param [in]	:   The pin value to be must be a vale of @ref GPIO_PIN_STATUS.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_WritePin(volatile GPIO_typedef * GPIOx, uint8_t pinNumber, uint8_t value);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_WritePort.
* @brief		:   Writes a value on the entire GPIOx port.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @param [in]	:   The value to be set on the port.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_WritePort(volatile GPIO_typedef * GPIOx, uint8_t value);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_TogglePin.
* @brief		:   Toggle the value of GPIOx PINy.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @param [in]	:   The number of the pin to be read must be a value of @ref GPIO_PIN_define.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_TogglePin(volatile GPIO_typedef * GPIOx, uint8_t pinNumber);

#endif /* ATMEGA32_GPIO_H_ */