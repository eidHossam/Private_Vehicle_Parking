/*
**************************************************************************************************************************
* file		:  stm32f103x6_RCC.h
* brief     :  This file contains functions to configure and get the current clock frequency for the different busses. 
* Author    :  Hossam Eid
* Created on:  Sep 19, 2023
**************************************************************************************************************************
*/
#ifndef MCAL_RCC_STM32F103X6_RCC_H_
#define MCAL_RCC_STM32F103X6_RCC_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "math.h"
#include "stm32f103x6.h"
#include "Platform_Types.h"


/**************************************************************************************************************************
*===============================================
*               SYSCLK Macros
*===============================================
*/
#define  HSE_Clock			(uint32)16000000        /*Should be specified by the user*/
#define  HSI_RC_Clk			(uint32)8000000

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL RCC DRIVER"
*===============================================
*/

/*
======================================================================================================================
* @Func_name	:   MCAL_RCC_GET_SYSCLK
* @brief		:   Gets the current clock frequency of the system.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   The system clock frequency.
* Note			:   none.
======================================================================================================================
*/
uint32 MCAL_RCC_GET_SYSCLK(void);

/*
======================================================================================================================
* @Func_name	:   MCAL_RCC_GET_HCLK
* @brief		:   Gets the current clock frequency of the AHB peripheral bus.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   the current clock frequency of the AHB peripheral bus.
* Note			:   none.
======================================================================================================================
*/
uint32 MCAL_RCC_GET_HCLK(void);

/*
======================================================================================================================
* @Func_name	:   MCAL_RCC_GET_PCLK1
* @brief		:   Gets the current clock frequency of the APB1 peripheral bus.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   the current clock frequency of the APB1 peripheral bus.
* Note			:   none.
======================================================================================================================
*/
uint32 MCAL_RCC_GET_PCLK1(void);

/*
======================================================================================================================
* @Func_name	:   MCAL_RCC_GET_PCLK2
* @brief		:   Gets the current clock frequency of the APB2 peripheral bus. 
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   the current clock frequency of the APB2 peripheral bus.
* Note			:   none.
======================================================================================================================
*/
uint32 MCAL_RCC_GET_PCLK2(void);

#endif /* MCAL_RCC_STM32F103X6_RCC_H_ */
