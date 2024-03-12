/**
 * @file LED_Driver_Interface.h
 * 
 * @brief This file contains the APIs for the HAL LED driver.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */

#ifndef LED_DRIVER_INTERFACE_H_
#define LED_DRIVER_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "../MCAL/GPIO/Atmega32_GPIO.h"

/**
 * @ref LED_DEFINE
 * 
 * @brief This enum has the allowed states of the LED.
 * 
 * @param  LED_On:  To turn the LED on.
 * @param  LED_Off:  To turn the LED off.
 */
typedef enum{
    LED_On = GPIO_PIN_HIGH,
    LED_Off = GPIO_PIN_LOW
}eLEDStatus_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "HAL LED DRIVER"
*===============================================
*/

/**
 * @brief This function initializes the LED to be ready for operation. 
 * 
 * @param GPIOx : The GPIO port that is connected to the LED.
 * @param copy_LED_Pin : The GPIO pin that is connected to the LED.
 */
void HAL_LED_Init(volatile GPIO_typedef* GPIOx, uint8_t copy_LED_Pin);

/**
 * @brief This function sets the state of the LED.
 * 
 * @param GPIOx         :   The GPIO port that is connected to the LED.
 * @param copy_LED_Pin  :   The GPIO pin that is connected to the LED.
 * @param copy_LEDState :   The new state of the LED must be a value of @ref LED_DEFINE.
 */
void HAL_LED_SetState(volatile GPIO_typedef* GPIOx, uint8_t copy_LED_Pin, eLEDStatus_t copy_LEDState);

/**
 * @brief This function toggles the current state of the LED. 
 * 
 * @param GPIOx         :   The GPIO port that is connected to the LED.
 * @param copy_LED_Pin  :   The GPIO pin that is connected to the LED.
 */
void HAL_LED_ToggleState(volatile GPIO_typedef* GPIOx, uint8_t copy_LED_Pin);

#endif /* LED_DRIVER_INTERFACE_H_ */