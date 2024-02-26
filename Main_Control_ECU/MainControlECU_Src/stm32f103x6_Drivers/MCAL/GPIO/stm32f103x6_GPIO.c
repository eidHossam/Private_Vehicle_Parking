/**
 **************************************************************************************************************************
 * brief     : This module contains functions for configuring and controlling General Purpose Input/Output (GPIO) pins.
 * Author    : Hossam Eid
 * Created on: 2 sep 2023
 **************************************************************************************************************************
 * This module provides functions for configuring the mode, speed, and pull-up/down resistors
 * of GPIO pins, as well as reading and writing their values.
 *
 * It is designed to be used with ARM Cortex-M processors, and may not be compatible with
 * other architectures.
 *
 * note: This module is intended for use with the STM32F103xx MCU series,
 * but may be adapted for use with other compatible processors.
 **************************************************************************************************************************
 */
/*
===============================================
*                   Includes
*===============================================
*/
#include "stm32f103x6_GPIO.h"

/*
===============================================
*               Local functions
*===============================================
*/

/**************************************************************************************************************************
===============================================
*           APIs functions definitions
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
void MCAL_GPIO_Init(volatile GPIO_t* GPIOx ,GPIO_Pin_Config_t* pinConfig)
{
    vuint32_t* CTRL;
    uint8 shift;
    /*
    Choose the correct control register based on the pin number
    CRL for pin(0 >> 7)
    CRH for pin(8 >> 15)
     */
    CTRL = (pinConfig->pinNumber < 8)? &(GPIOx->CRL) : &(GPIOx->CRH);

    /*Get the needed shift for each pin as each pin takes 4 bits in the register*/
    shift = ((pinConfig->pinNumber % 8) * 4);


    *(CTRL) &= ~(0xF << shift);                /*Clear the bits assigned for the required pin number*/

    /*Input pull-up and pull-down have the same configuration code*/
    if(pinConfig->pinMode == GPIO_MODE_INPUT_PD)
    {
        *(CTRL) |= (GPIO_MODE_INPUT_PU << shift);
        CLEAR_BIT(GPIOx->ODR, pinConfig->pinNumber);
    }else{

        *(CTRL) |= (pinConfig->pinMode << shift);  /*Set the mode*/

        /*Set the pull-up resistance if needed*/
        if(pinConfig->pinMode == GPIO_MODE_INPUT_PU)
        {
            SET_BIT(GPIOx->ODR, pinConfig->pinNumber);
        }
    }
}

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_DeInit.
* @brief		:   Deinitialization function that resets the entire port.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_DeInit(volatile GPIO_t* GPIOx)
{
    if(GPIOx == GPIOA)
    {
        APB2_PERI_RESET(APB2_IOPA);
    }else if(GPIOx == GPIOB)
    {
        APB2_PERI_RESET(APB2_IOPB);
    }else if(GPIOx == GPIOC)
    {
        APB2_PERI_RESET(APB2_IOPC);
    }else if(GPIOx == GPIOD)
    {
        APB2_PERI_RESET(APB2_IOPD);
    }else if(GPIOx == GPIOE)
    {
        APB2_PERI_RESET(APB2_IOPE);
    }else{
    }
}

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
uint8 MCAL_GPIO_ReadPin(volatile GPIO_t* GPIOx, uint16 pinNumber)
{
    uint8 status;
    status = (READ_BIT(GPIOx->IDR, pinNumber))? (uint8)(GPIO_PIN_HIGH): (uint8)(GPIO_PIN_LOW);

    return status;
}

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_ReadPort.
* @brief		:   Reads the status of the entire GPIOx.
* @param [in]	:   GPIOx where x can be (A >> E) to select the GPIO peripheral.
* @return_value :   Current port value.
* Note			:   none.
*===============================================
*/
uint16 MCAL_GPIO_ReadPort(volatile GPIO_t* GPIOx)
{
    uint16 status;
    status = (uint16)(GPIOx->IDR & 0xFFFFU);

    return status;
}

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
void MCAL_GPIO_WritePin(volatile GPIO_t* GPIOx, uint16 pinNumber, uint8 value)
{
    if(value == GPIO_PIN_HIGH)
    {
        SET_BIT(GPIOx->ODR, pinNumber);
    }else{
        CLEAR_BIT(GPIOx->ODR, pinNumber);
    }
}

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
void MCAL_GPIO_WritePort(volatile GPIO_t* GPIOx, uint16 value)
{
    GPIOx->ODR = (uint32)value;
}

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
void MCAL_GPIO_WriteByte(volatile GPIO_t * GPIOx, uint8 value, uint8 bytePosition)
{
    GPIOx->ODR = (GPIOx->ODR & ~(0xFF << bytePosition)) | (value << bytePosition);
}

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
void MCAL_GPIO_TogglePin(volatile GPIO_t* GPIOx, uint16 pinNumber)
{
    TOGGLE_BIT(GPIOx->ODR,  pinNumber);
}

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
uint8 MCAL_GPIO_LockPin_Config(volatile GPIO_t* GPIOx, uint16 pinNumber)
{
    uint8 status;
    /*Bit 16 LCKK[16]: Lock key
    This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
    0: Port configuration lock key not active
    1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
    LOCK key writing sequence:
    Write 1
    Write 0
    Write 1
    Read 0
    Read 1 (this read is optional but confirms that the lock is active)
    Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.*/

    SET_BIT(GPIOx->LCKR, pinNumber);

    /*Write 1*/
    SET_BIT(GPIOx->LCKR, GPIO_LOCK_PIN);

    /*Write 0*/
    CLEAR_BIT(GPIOx->LCKR, GPIO_LOCK_PIN);

    /*Write 1*/
    SET_BIT(GPIOx->LCKR, GPIO_LOCK_PIN);

    /*Read 0*/
    status = READ_BIT(GPIOx->LCKR, GPIO_LOCK_PIN);

    /*Read 1 if successful*/
    status = READ_BIT(GPIOx->LCKR, GPIO_LOCK_PIN);

    return status;
}
