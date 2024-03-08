/*
**************************************************************************************************************************
* file		 : stm32f103x6_AFIO.h
* brief     : This file contains functions to configure the GPIO pins alternative functionality.
* Author    : Hossam Eid
* Created on: Sep 8, 2023
**************************************************************************************************************************
*/
#ifndef MCAL_AFIO_STM32F103X6_AFIO_H_
#define MCAL_AFIO_STM32F103X6_AFIO_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "stm32f103x6.h"
#include "Platform_Types.h"

/*============================================================================*/
/*
*=========================================================
*         Macros Configuration References
*=========================================================
*/

/*-------------@ref AFIO_EXTI_NUMBER---------------*/
#define AFIO_EXTI0          0
#define AFIO_EXTI1          1
#define AFIO_EXTI2          2
#define AFIO_EXTI3          3
#define AFIO_EXTI4          4
#define AFIO_EXTI5          5
#define AFIO_EXTI6          6
#define AFIO_EXTI7          7
#define AFIO_EXTI8          8
#define AFIO_EXTI9          9
#define AFIO_EXTI10         10
#define AFIO_EXTI11         11
#define AFIO_EXTI12         12
#define AFIO_EXTI13         13
#define AFIO_EXTI14         14
#define AFIO_EXTI15         15

/*-------------@ref AFIO_EXTI_PORT---------------*/
/*
These bits are written by software to select the source input for EXTIx external interrupt.
0000: PA[x] pin
0001: PB[x] pin
0010: PC[x] pin
0011: PD[x] pin
0100: PE[x] pin
*/
#define AFIO_PORTA    0b0000
#define AFIO_PORTB    0b0001
#define AFIO_PORTC    0b0010
#define AFIO_PORTD    0b0011
#define AFIO_PORTE    0b0100

/*============================================================================*/
/*
==========================================================
*          APIs Supported by "MCAL AFIO DRIVER"
*=========================================================
*/

/*
====================================================================================================================
* @Func_name	:   MCAL_AFIO_EXTI_Init
* @brief		:   Map the specified external interrupt to the specified port.
* @param [in]	:   EXTI_Number: the requested external interrupt number must be a val of @ref AFIO_EXTI_NUMBER.
* @param [in]	:   EXTI_Port: Specifies the port to be mapped to this EXTI must be a val of @ref AFIO_EXTI_PORT.
* @return_value :   none.
* Note			:   Stm32F103C6 MCU has GPIO A,B,C,D,E Modules,
* 				:	But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU.
====================================================================================================================
*/
void MCAL_AFIO_EXTI_Init(uint8 EXTI_Number, uint8 EXTI_Port);

#endif /* MCAL_AFIO_STM32F103X6_AFIO_H_ */
