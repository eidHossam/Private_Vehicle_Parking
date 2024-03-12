/**
 * @file LED_Driver_Program.c
 * 
 * @brief This file contains the APIs implementation for the LED driver.
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
#include "LED_Driver_Interface.h"

/**************************************************************************************************************************
===============================================
*               APIs Definitions
*===============================================
*/

/**
 * @brief This function initializes the LED to be ready for operation. 
 * 
 * @param GPIOx : The GPIO port that is connected to the LED.
 * @param copy_LED_Pin : The GPIO pin that is connected to the LED.
 */
void HAL_LED_Init(volatile GPIO_typedef* GPIOx, uint8_t copy_LED_Pin)
{
    GPIO_Pin_Config_t cfg;

    cfg.pinMode = GPIO_MODE_OUTPUT;
    cfg.pinNumber = copy_LED_Pin;

    MCAL_GPIO_Init(GPIOx, &cfg);
}

/**
 * @brief This function sets the state of the LED.
 * 
 * @param GPIOx         :   The GPIO port that is connected to the LED.
 * @param copy_LED_Pin  :   The GPIO pin that is connected to the LED.
 * @param copy_LEDState :   The new state of the LED must be a value of @ref LED_DEFINE.
 */
void HAL_LED_SetState(volatile GPIO_typedef* GPIOx, uint8_t copy_LED_Pin, eLEDStatus_t copy_LEDState)
{
    MCAL_GPIO_WritePin(GPIOx, copy_LED_Pin, copy_LEDState);
}


/**
 * @brief This function toggles the current state of the LED. 
 * 
 * @param GPIOx         :   The GPIO port that is connected to the LED.
 * @param copy_LED_Pin  :   The GPIO pin that is connected to the LED.
 */
void HAL_LED_ToggleState(volatile GPIO_typedef* GPIOx, uint8_t copy_LED_Pin)
{
    MCAL_GPIO_TogglePin(GPIOx, copy_LED_Pin);
}
