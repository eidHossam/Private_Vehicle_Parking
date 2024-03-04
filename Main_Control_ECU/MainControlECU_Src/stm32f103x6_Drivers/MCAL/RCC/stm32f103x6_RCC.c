/*
**************************************************************************************************************************
* file		: stm32f103x6_RCC.c
* brief     : This file contains functions to configure and get the current clock frequency for the different busses. 
* Author    : Hossam Eid
* Created on: Sep 19, 2023
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/
#include "stm32f103x6_RCC.h"

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
uint32 MCAL_RCC_GET_SYSCLK(void)
{
	uint32 LOC_CLKFreq = 0;
    /*
	Bits 3:2 SWS[1:0]: System clock switch status
	Set and cleared by hardware to indicate which clock source is used as system clock.
	00: HSI oscillator used as system clock
	01: HSE oscillator used as system clock
	10: PLL used as system clock
	11: Not applicable
    */
	switch  ( (RCC->CFGR  >> 2  ) & 0b11 )
	{
	case 0:

		LOC_CLKFreq = HSI_RC_Clk ;
		break ;

	case 1:

		/*todo need to calculate  it "HSE User Should Specify it"*/
		LOC_CLKFreq = HSE_Clock ;
		break ;

	case 2:

		/*todo need to calculate  it PLLCLK and PLLMUL & PLL Source MUX*/
		LOC_CLKFreq = 16000000 ;
		break ;

	}

	return LOC_CLKFreq;
}

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
uint32 MCAL_RCC_GET_HCLK(void)
{
    /*Set and cleared by software to control AHB clock division factor.
        0xxx: SYSCLK not divided
        1000: SYSCLK divided by 2
        1001: SYSCLK divided by 4
        1010: SYSCLK divided by 8
        1011: SYSCLK divided by 16
        1100: SYSCLK divided by 64
        1101: SYSCLK divided by 128
        1110: SYSCLK divided by 256
        1111: SYSCLK divided by 512*/

    /*Get the the bus prescale value from the register*/
    uint8 AHB_PreScaler = (((RCC->CFGR & (0xF << 4) ) >> 4));

    if(AHB_PreScaler <= 7)
    {
        return MCAL_RCC_GET_SYSCLK();
    }

    AHB_PreScaler = pow(2, AHB_PreScaler - 7);
    AHB_PreScaler *= (AHB_PreScaler >= 32)? 2: 1;   /*Make up for the jump from 16 to 64*/

    return (MCAL_RCC_GET_SYSCLK() / AHB_PreScaler);
}

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
uint32 MCAL_RCC_GET_PCLK1(void)
{
    /*Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
        0xx: HCLK not divided
        100: HCLK divided by 2
        101: HCLK divided by 4
        110: HCLK divided by 8
        111: HCLK divided by 16*/

    /*Get the the bus prescale value from the register*/
    uint8 APB1_PreScaler = (((RCC->CFGR & (0b111 << 8)) >> 8));
    if(APB1_PreScaler <= 3)
    {
        return MCAL_RCC_GET_HCLK();
    }

    APB1_PreScaler = pow(2, APB1_PreScaler - 3);
    return (MCAL_RCC_GET_HCLK() / APB1_PreScaler);
}

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
uint32 MCAL_RCC_GET_PCLK2(void)
{
    /*Set and cleared by software to control the division factor of the APB Low speed clock (PCLK2).
        0xx: HCLK not divided
        100: HCLK divided by 2
        101: HCLK divided by 4
        110: HCLK divided by 8
        111: HCLK divided by 16*/

    /*Get the the bus prescale value from the register*/
    uint8 APB2_PreScaler = (((RCC->CFGR & (0b111 << 11) ) >> 11));
    if(APB2_PreScaler <= 3)
    {
        return MCAL_RCC_GET_HCLK();
    }

    APB2_PreScaler = pow(2, APB2_PreScaler - 3);
    return (MCAL_RCC_GET_HCLK() / APB2_PreScaler);
}

