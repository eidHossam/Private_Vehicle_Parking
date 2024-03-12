/**
 * @file Buzzer_Driver_Program.c
 * 
 * @brief This file contains the APIs implementation for the HAL buzzer driver.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */


/*
*===============================================
*                   Includes
*===============================================
*/
#include "Buzzer_Driver_Interface.h"

/**************************************************************************************************************************
===============================================
*               APIs Definitions
*===============================================
*/

/**
 * @brief This function initializes the Buzzer to be ready for operation. 
 * 
 * @param GPIOx : The GPIO port that is connected to the Buzzer.
 * @param copy_BuzzerPin : The GPIO pin that is connected to the Buzzer.
 */
void HAL_Buzzer_Init(volatile GPIO_typedef* GPIOx, uint8_t copy_BuzzerPin)
{
    GPIO_Pin_Config_t cfg;

    cfg.pinMode = GPIO_MODE_OUTPUT;
    cfg.pinNumber = copy_BuzzerPin;

    MCAL_GPIO_Init(GPIOx, &cfg);
}

/**
 * @brief This function sets the state of the Buzzer.
 * 
 * @param GPIOx         :   The GPIO port that is connected to the Buzzer.
 * @param copy_BuzzerPin  :   The GPIO pin that is connected to the Buzzer.
 * @param copy_BuzzerState :   The new state of the Buzzer must be a value of @ref BUZZER_DEFINE.
 */
void HAL_Buzzer_SetState(volatile GPIO_typedef* GPIOx, uint8_t copy_BuzzerPin, eBuzzerState_t copy_BuzzerState)
{
    MCAL_GPIO_WritePin(GPIOx, copy_BuzzerPin, copy_BuzzerState);
}

/**
 * @brief This function toggles the current state of the buzzer. 
 * 
 * @param GPIOx         :   The GPIO port that is connected to the Buzzer.
 * @param copy_BuzzerPin  :   The GPIO pin that is connected to the Buzzer.
 */
void HAL_Buzzer_ToggleState(volatile GPIO_typedef* GPIOx, uint8_t copy_BuzzerPin)
{
    MCAL_GPIO_TogglePin(GPIOx, copy_BuzzerPin);
}
