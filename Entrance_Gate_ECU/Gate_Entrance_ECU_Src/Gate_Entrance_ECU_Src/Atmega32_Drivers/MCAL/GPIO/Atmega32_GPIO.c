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
/*
===============================================
*                   Includes
*===============================================
*/
#include "Atmega32_GPIO.h"

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
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @param [in]	:   Pointer to the GPIO_Pin_Config_t struct that contains the configuration information.
* @return_value :   none
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_Init(volatile GPIO_typedef* GPIOx ,GPIO_Pin_Config_t* pinConfig)
{   
    if(pinConfig->pinMode == GPIO_MODE_OUTPUT)
    {
        /*write logic one to be output*/
        SET_BIT(GPIOx->DDR, pinConfig->pinNumber);  
    }else
    {
        /*write logic zero to be input*/
        CLEAR_BIT(GPIOx->DDR, pinConfig->pinNumber);  

        if(pinConfig->pinMode == GPIO_MODE_INPUT_PU)
        {
            /*Enable the PU resistance*/
            SFIOR &= ~(1 < GPIO_PIN2); 
            SET_BIT(GPIOx->PORT, pinConfig->pinNumber);
        }
    }
}

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_DeInit.
* @brief		:   Deinitialization function that resets the entire port.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @return_value :   none.
* Note			:   none.
*===============================================
*/
void MCAL_GPIO_DeInit(volatile GPIO_typedef * GPIOx)
{
    GPIOx->DDR  = 0;
    GPIOx->PORT = 0; 
    GPIOx->DDR  = 0;
}

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
uint8_t MCAL_GPIO_ReadPin(volatile GPIO_typedef * GPIOx, uint8_t pinNumber)
{
    uint8_t status;
    status = (READ_BIT(GPIOx->PIN, pinNumber))? (uint8_t)(GPIO_PIN_HIGH): (uint8_t)(GPIO_PIN_LOW);

    return status;
}

/*
===============================================================+
* @Func_name	:   MCAL_GPIO_ReadPort.
* @brief		:   Reads the status of the entire GPIOx.
* @param [in]	:   GPIOx where x can be (A >> D) to select the GPIO peripheral.
* @return_value :   Current port value.
* Note			:   none.
*===============================================
*/
uint8_t MCAL_GPIO_ReadPort(volatile GPIO_typedef * GPIOx)
{
    uint8_t status;
    status = (uint8_t)(GPIOx->PIN & 0xFF);

    return status;
}

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
void MCAL_GPIO_WritePin(volatile GPIO_typedef * GPIOx, uint8_t pinNumber, uint8_t value)
{
    if(value == GPIO_PIN_HIGH)
    {
        SET_BIT(GPIOx->PORT, pinNumber);
    }else{
        CLEAR_BIT(GPIOx->PORT, pinNumber);
    }
}

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
void MCAL_GPIO_WritePort(volatile GPIO_typedef * GPIOx, uint8_t value)
{
    GPIOx->PORT = (uint8_t)value;
}

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
void MCAL_GPIO_TogglePin(volatile GPIO_typedef * GPIOx, uint8_t pinNumber)
{
    TOGGLE_BIT(GPIOx->PORT,  pinNumber);
}
