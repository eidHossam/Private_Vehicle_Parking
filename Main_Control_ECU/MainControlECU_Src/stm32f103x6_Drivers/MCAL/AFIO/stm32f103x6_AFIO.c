/*
**************************************************************************************************************************
* file		 : stm32f103x6_AFIO.c
* brief     : This file contains functions to configure the GPIO pins alternative functionality.
* Author    : Hossam Eid
* Created on: Sep 8, 2023
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/

#include "stm32f103x6_AFIO.h"

/**************************************************************************************************************************
*===============================================
*  			APIs functions definitions
*===============================================
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
void MCAL_AFIO_EXTI_Init(uint8 EXTI_Number, uint8 EXTI_Port)
{
    uint8 CR_Index = EXTI_Number / 4;
    uint8 CR_Shift = (EXTI_Number % 4) * 4;

    AFIO->EXTICR[CR_Index] = (AFIO->EXTICR[CR_Index] & ~(0xF << CR_Shift)) | (EXTI_Port << CR_Shift); 
}
