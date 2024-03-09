/*
**************************************************************************************************************************
* file		: stm32f103x6_EXTI.c
* brief     : This file contains functions to setup the EXTI peripheral.
* Author    : Hossam Eid
* Created on: Sep 8, 2023
**************************************************************************************************************************
* note: This module is intended for use with the STM32F103xx microcontroller series, but may be adapted for use with
* other compatible processors.
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/
#include "stm32f103x6_EXTI.h"

/**************************************************************************************************************************
===============================================
*  				Global variables
*===============================================
*/
void (* GP_callback_func[16])(void);      /*An array to hold all the ISR callback functions*/

/**************************************************************************************************************************
*===============================================
*  			APIs functions definitions
*===============================================
*/

/*
======================================================================================================================
* @Func_name	:   MCAL_EXTI_Enable
* @brief		:   This function enables the specified external interrupt with the specified options.
* @param [in]	:   EXTI_Config: External interrupt configuration
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_EXTI_Enable(EXTI_config_t* EXTI_Config)
{
    /*Configure the GPIO Pin to be alternative function input (Floating input)*/
	GPIO_Pin_Config_t config;
    config.pinNumber = EXTI_Config->PinConfig.GPIO_pinNumber;
    config.pinMode = GPIO_MODE_INPUT_FLOATING;
    MCAL_GPIO_Init(EXTI_Config->PinConfig.GPIO_PORT, &config);

    /*Map the pin to the EXTI line through AFIO module*/
    MCAL_AFIO_EXTI_Init(EXTI_Config->PinConfig.EXTI_lineNumber, EXTI_Config->PinConfig.AFIO_Port_config);

    /*Clear the rising and falling edge triggers*/
    CLEAR_BIT(EXTI->RTSR, EXTI_Config->PinConfig.EXTI_lineNumber);
    CLEAR_BIT(EXTI->FTSR, EXTI_Config->PinConfig.EXTI_lineNumber);

    /*Configure the triggering edge of the interrupt*/
    if(EXTI_Config->EXTI_Trigger_Mode == EXTI_TRIGGER_RISING_EDGE ||
       EXTI_Config->EXTI_Trigger_Mode == EXTI_TRIGGER_BOTH_EDGES)
    {
        SET_BIT(EXTI->RTSR, EXTI_Config->PinConfig.EXTI_lineNumber);
    }

    if(EXTI_Config->EXTI_Trigger_Mode == EXTI_TRIGGER_FALLING_EDGE ||
       EXTI_Config->EXTI_Trigger_Mode == EXTI_TRIGGER_BOTH_EDGES)
    {
        SET_BIT( EXTI->FTSR, EXTI_Config->PinConfig.EXTI_lineNumber);
    }

    /*Set the priority of the interrupt in NVIC*/
    MCAL_NVIC_SetPriority(EXTI_Config->PinConfig.EXTI_IVT_index, EXTI_Config->EXTI_Priority);

    /*Set the callback function*/
    GP_callback_func[EXTI_Config->PinConfig.EXTI_lineNumber] = EXTI_Config->P_callback_func;

    if(EXTI_Config->EXTI_En == EXTI_ENABLE)
    {
        /*Enable the interrupt mask in the EXTI peripheral*/
        SET_BIT(EXTI->IMR, EXTI_Config->PinConfig.EXTI_lineNumber);

        /*Enable the interrupt mask in the NVIC peripheral*/
        MCAL_NVIC_EnableIRQ(EXTI_Config->PinConfig.EXTI_IVT_index);
    }else
    {
        /*Disable the interrupt mask in the EXTI peripheral*/
        CLEAR_BIT(EXTI->IMR, EXTI_Config->PinConfig.EXTI_lineNumber);

        /*Disable the interrupt mask in the NVIC peripheral*/
        MCAL_NVIC_DisableIRQ(EXTI_Config->PinConfig.EXTI_IVT_index);
    }
}

/*
======================================================================================================================
* @Func_name	:   MCAL_EXTI_Update_Config
* @brief		:   This function updates the specified external interrupt configuration.
* @param [in]	:   EXTI_Config: External interrupt configuration
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_EXTI_Update_Config(EXTI_config_t* EXTI_Config)
{
    MCAL_EXTI_Enable(EXTI_Config);
}

/*
======================================================================================================================
* @Func_name	:   MCAL_EXTI_Disable
* @brief		:   Disable the specified MCAL external interrupt.
* @param [in]	:   EXTI_lineNumber: specifies the interrupt line number, must be value of @ref EXTI_LINE_DEFINE.
* @param [in]	:   EXTI_IVT_index: The index of the interrupt in the IVT, must be value of @ref NVIC_MODULE_IVT_INDEX.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_EXTI_Disable(uint8 EXTI_lineNumber, uint8 EXTI_IVT_index)
{
    /*Disable the interrupt mask in the EXTI peripheral*/
    CLEAR_BIT(EXTI->IMR, EXTI_lineNumber);

    /*Disable the interrupt mask in the NVIC peripheral*/
    MCAL_NVIC_DisableIRQ(EXTI_IVT_index);
}

/*
======================================================================================================================
* @Func_name	:   MCAL_EXTI_Reset
* @brief		:   Reset the EXTI peripheral by resetting all its registers.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_EXTI_Reset()
{
    EXTI->IMR   = 0;
    EXTI->EMR   = 0;
    EXTI->RTSR  = 0;
    EXTI->FTSR  = 0;
    EXTI->SWIER = 0;

    /*Cleared by writing one on it*/
    EXTI->PR    = 0xFFFFFFFF;

    /*Disable EXTI IRQ From NVIC*/
    MCAL_NVIC_DisableIRQ(NVIC_EXTI0_IVT_INDEX);
    MCAL_NVIC_DisableIRQ(NVIC_EXTI1_IVT_INDEX);
    MCAL_NVIC_DisableIRQ(NVIC_EXTI2_IVT_INDEX);
    MCAL_NVIC_DisableIRQ(NVIC_EXTI3_IVT_INDEX);
    MCAL_NVIC_DisableIRQ(NVIC_EXTI4_IVT_INDEX);
    MCAL_NVIC_DisableIRQ(NVIC_EXTI9_5_IVT_INDEX);
    MCAL_NVIC_DisableIRQ(NVIC_EXTI15_10_IVT_INDEX);
}

/**************************************************************************************************************************
===============================================
*               EXTI ISR functions
*===============================================
*/

/*-----------@defgroup EXTI ISR------------------------ */
void EXTI0_IRQHandler(void)
{
    /*Clear the pending bit in EXTI_PR */
    SET_BIT(EXTI->PR, 0);
    
    /*Jump to the ISR*/
    GP_callback_func[0]();
}

void EXTI1_IRQHandler(void)
{
    /*Clear the pending bit in EXTI_PR */
    SET_BIT(EXTI->PR, 1);
    
    /*Jump to the ISR*/
    GP_callback_func[1]();
}

void EXTI2_IRQHandler(void)
{
    /*Clear the pending bit in EXTI_PR */
    SET_BIT(EXTI->PR, 2);
    
    /*Jump to the ISR*/
    GP_callback_func[2]();
}

void EXTI3_IRQHandler(void)
{
    /*Clear the pending bit in EXTI_PR */
    SET_BIT(EXTI->PR, 3);
    
    /*Jump to the ISR*/
    GP_callback_func[3]();
}

void EXTI4_IRQHandler(void)
{
    /*Clear the pending bit in EXTI_PR */
    SET_BIT(EXTI->PR, 4);
    
    /*Jump to the ISR*/
    GP_callback_func[4]();
}

void EXTI9_5_IRQHandler(void)
{
    if(READ_BIT(EXTI->PR, 5) == 1){SET_BIT(EXTI->PR, 5); GP_callback_func[5]();}
    if(READ_BIT(EXTI->PR, 6) == 1){SET_BIT(EXTI->PR, 6); GP_callback_func[6]();}
    if(READ_BIT(EXTI->PR, 7) == 1){SET_BIT(EXTI->PR, 7); GP_callback_func[7]();}
    if(READ_BIT(EXTI->PR, 8) == 1){SET_BIT(EXTI->PR, 8); GP_callback_func[8]();}
    if(READ_BIT(EXTI->PR, 9) == 1){SET_BIT(EXTI->PR, 9); GP_callback_func[9]();}
}

void EXTI15_10_IRQHandler(void)
{
    if(READ_BIT(EXTI->PR, 10) == 1){SET_BIT(EXTI->PR, 10); GP_callback_func[10]();}
    if(READ_BIT(EXTI->PR, 11) == 1){SET_BIT(EXTI->PR, 11); GP_callback_func[11]();}
    if(READ_BIT(EXTI->PR, 12) == 1){SET_BIT(EXTI->PR, 12); GP_callback_func[12]();}
    if(READ_BIT(EXTI->PR, 13) == 1){SET_BIT(EXTI->PR, 13); GP_callback_func[13]();}
    if(READ_BIT(EXTI->PR, 14) == 1){SET_BIT(EXTI->PR, 14); GP_callback_func[14]();}
    if(READ_BIT(EXTI->PR, 15) == 1){SET_BIT(EXTI->PR, 15); GP_callback_func[15]();}
}