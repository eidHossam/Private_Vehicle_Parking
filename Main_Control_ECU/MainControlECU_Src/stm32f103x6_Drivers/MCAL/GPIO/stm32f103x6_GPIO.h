/**
 **************************************************************************************************************************
 * brief     : This module contains functions for configuring and controlling General Purpose Input/Output (GPIO) pins.
 * Author    : Hossam Eid
 * Created on: 26 Feb 2022
 **************************************************************************************************************************
 * This module provides functions for configuring the mode, speed, and pull-up/down resistors of GPIO pins,
 * as well as reading and writing their values. It is designed to be used with ARM Cortex-M processors, and may not be
 * compatible with other architectures.
 *
 * note: This module is intended for use with the STM32F103xx microcontroller series, but may be adapted for use with
 * other compatible processors.
 **************************************************************************************************************************
 */

#ifndef STM32F103X6_DRIVERS_MCAL_INC_STM32F103X6_GPIO_H_
#define STM32F103X6_DRIVERS_MCAL_INC_STM32F103X6_GPIO_H_

/*===============================================
* Includes
*===============================================*/
#include "stm32f103x6.h"

/****************************************************************/
/*
*===============================================
* User type definitions (structures)
*===============================================
*/

typedef struct{
    uint16 pinNumber;      /*Choose the pin to be configured
                            This parameter must be a value of @ref GPIO_PIN_define*/

    uint16 pinMode;         /*Choose the operating mode of the pin to be configured
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
#define GPIO_PIN8       8
#define GPIO_PIN9       9
#define GPIO_PIN10      10
#define GPIO_PIN11      11
#define GPIO_PIN12      12
#define GPIO_PIN13      13
#define GPIO_PIN14      14
#define GPIO_PIN15      15

/*@ref GPIO_MODE_define-------------*/

/*Bits [0 , 1]:
00: Input mode (reset state)
01: Output mode, max speed 10 MHz.
10: Output mode, max speed 2 MHz.
11: Output mode, max speed 50 MHz.

Bits [2, 3]:
In input mode (MODE[1:0]=00):
00: Analog mode
01: Floating input (reset state)
10: Input with pull-up / pull-down
11: Reserved*/
#define GPIO_MODE_INPUT_ANALOG              0b0000 /*Input analog mode*/
#define GPIO_MODE_INPUT_FLOATING            0b0100 /*Floating input (reset state)*/
#define GPIO_MODE_INPUT_PU                  0b1000 /*Input pull-up mode*/
#define GPIO_MODE_INPUT_PD                  0b10000 /*Input pull-down mode*/

/*Bits [2, 3]:
In output mode (MODE[1:0] > 00):
00: General purpose output push-pull
01: General purpose output Open-drain
10: Alternate function output Push-pull
11: Alternate function output Open-drain
*/

/*Output mode, max speed 10 MHz.*/
#define GPIO_MODE_GP_OUTPUT_PP_10MHZ        0b0001 /*General purpose output push-pull, max speed 10 MHZ*/
#define GPIO_MODE_GP_OUTPUT_OD_10MHZ        0b0101 /*General purpose output open-drain, max speed 10 MHZ*/
#define GPIO_MODE_AF_OUTPUT_PP_10MHZ        0b1001 /*Alternate function output push-pull, max speed 10 MHZ*/
#define GPIO_MODE_AF_OUTPUT_OD_10MHZ        0b1101 /*Alternate function output open-drain, max speed 10 MHZ*/

/*Output mode, max speed 2 MHz.*/
#define GPIO_MODE_GP_OUTPUT_PP_2MHZ         0b0010 /*General purpose output push-pull, max speed 2 MHZ*/
#define GPIO_MODE_GP_OUTPUT_OD_2MHZ         0b0110 /*General purpose output open-drain, max speed 2 MHZ*/
#define GPIO_MODE_AF_OUTPUT_PP_2MHZ         0b1010 /*Alternate function output push-pull, max speed 2 MHZ*/
#define GPIO_MODE_AF_OUTPUT_OD_2MHZ         0b1110 /*Alternate function output open-drain, max speed 2 MHZ*/

/*Output mode, max speed 50 MHz.*/
#define GPIO_MODE_GP_OUTPUT_PP_50MHZ        0b0011 /*General purpose output push-pull, max speed 50 MHZ*/
#define GPIO_MODE_GP_OUTPUT_OD_50MHZ        0b0111 /*General purpose output open-drain, max speed 50 MHZ*/
#define GPIO_MODE_AF_OUTPUT_PP_50MHZ        0b1011 /*Alternate function output push-pull, max speed 50 MHZ*/
#define GPIO_MODE_AF_OUTPUT_OD_50MHZ        0b1111 /*Alternate function output open-drain, max speed 50 MHZ*/

/*@ref GPIO_PIN_STATUS-----------*/
#define GPIO_PIN_HIGH 1
#define GPIO_PIN_LOW  0

/*@ref GPIO_LOCK_STATUS----------*/
#define GPIO_LOCK_FAILED    0
#define GPIO_LOCK_SUCCESS   1

/*@ref GPIO_LOCK_PIN----------*/
#define GPIO_LOCK_PIN 16

/********************************************************
===============================================
* APIs Supported by "MCAL GPIO DRIVER"
*===============================================
*/

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_Init.
* @brief		:   Initialization function for the GPIOx PINy peripheral specified in the parameters.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @param [in]	:   Pointer to the GPIO_Pin_Config_t struct that contains the configuration information.
* @return_value :   none
* Note			:   Stm32F103C6 MCU has GPIO A,B,C,D,E Modules,
* 				:	But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
*===============================================
*/
void MCAL_GPIO_Init(volatile GPIO_t* GPIOx ,GPIO_Pin_Config_t* pinConfig);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_DeInit.
* @brief		:   Deinitialization function that resets the entire port.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_DeInit(volatile GPIO_t * GPIOx);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_ReadPin.
* @brief		:   Reads the status of GPIOx PINy.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @param [in]	:   The number of the pin to be read must be a value of @ref GPIO_PIN_define.
* @return_value :   Current pin status which can be a value of @ref GPIO_PIN_STATUS.
* Note			:   none.
*===============================================
*/
uint8 MCAL_GPIO_ReadPin(volatile GPIO_t * GPIOx, uint16 pinNumber);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_ReadPort.
* @brief		:   Reads the status of the entire GPIOx.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @return_value :   Current port value.
* Note			:   none.
*===============================================
*/
uint16 MCAL_GPIO_ReadPort(volatile GPIO_t * GPIOx);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_WritePin.
* @brief		:   Write a value on GPIOx PINy.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @param [in]	:   The number of the pin to be read must be a value of @ref GPIO_PIN_define.
* @param [in]	:   The pin value to be must be a vale of @ref GPIO_PIN_STATUS.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_WritePin(volatile GPIO_t * GPIOx, uint16 pinNumber, uint8 value);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_WritePort.
* @brief		:   Writes a value on the entire GPIOx port.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @param [in]	:   The value to be set on the port.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_WritePort(volatile GPIO_t * GPIOx, uint16 value);

/*
================================================================================================
* @Func_name	:   MCAL_GPIO_WriteByte.
* @brief		:   Writes a byte on the GPIOx port.
* @param [in]	:   GPIOx: where x can be (A >> E) to select the GPIO peripheral.
* @param [in]	:   value: The value to be set on the port.
* @param [in]	:   bytePosition: The first pin of the byte.
* @return_value :   none.
* Note			:   none.
*================================================================================================
*/
void MCAL_GPIO_WriteByte(volatile GPIO_t * GPIOx, uint8 value, uint8 bytePosition);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_TogglePin.
* @brief		:   Toggle the value of GPIOx PINy.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @param [in]	:   The number of the pin to be read must be a value of @ref GPIO_PIN_define.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_TogglePin(volatile GPIO_t * GPIOx, uint16 pinNumber);

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_LockPin_Config.
* @brief		:   Lock the configuration settings of GPIOx PINy.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @param [in]	:   The number of the pin to be read must be a value of @ref GPIO_PIN_define.
* @return_value :   Lock status which will be a value of @ref GPIO_LOCK_STATUS.
* Note			:   none.
*===============================================
*/
uint8 MCAL_GPIO_LockPin_Config(volatile GPIO_t * GPIOx, uint16 pinNumber);


#endif /* STM32F103X6_DRIVERS_MCAL_INC_STM32F103X6_GPIO_H_ */
