/**
 * @file Buzzer_Driver_Interface.h
 * 
 * @brief This file contains the APIs for the HAL buzzer driver.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */

#ifndef BUZZER_DRIVER_INTERFACE_H_
#define BUZZER_DRIVER_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "../MCAL/GPIO/Atmega32_GPIO.h"

/**
 * @ref BUZZER_DEFINE
 * 
 * @brief This enum has the allowed states of the Buzzer.
 * 
 * @param  Buzzer_On:  To turn the Buzzer on.
 * @param  Buzzer_Off:  To turn the Buzzer off.
 */
typedef enum{
    BUZZER_On = GPIO_PIN_HIGH,
    BUZZER_Off = GPIO_PIN_LOW
}eBuzzerState_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "HAL Buzzer DRIVER"
*===============================================
*/

/**
 * @brief This function initializes the Buzzer to be ready for operation. 
 * 
 * @param GPIOx : The GPIO port that is connected to the Buzzer.
 * @param copy_BuzzerPin : The GPIO pin that is connected to the Buzzer.
 */
void HAL_Buzzer_Init(volatile GPIO_typedef* GPIOx, uint8_t copy_BuzzerPin);

/**
 * @brief This function sets the state of the Buzzer.
 * 
 * @param GPIOx         :   The GPIO port that is connected to the Buzzer.
 * @param copy_BuzzerPin  :   The GPIO pin that is connected to the Buzzer.
 * @param copy_BuzzerState :   The new state of the Buzzer must be a value of @ref BUZZER_DEFINE.
 */
void HAL_Buzzer_SetState(volatile GPIO_typedef* GPIOx, uint8_t copy_BuzzerPin, eBuzzerState_t copy_BuzzerState);

/**
 * @brief This function toggles the current state of the buzzer. 
 * 
 * @param GPIOx         :   The GPIO port that is connected to the Buzzer.
 * @param copy_BuzzerPin  :   The GPIO pin that is connected to the Buzzer.
 */
void HAL_Buzzer_ToggleState(volatile GPIO_typedef* GPIOx, uint8_t copy_BuzzerPin);

#endif /* BUZZER_DRIVER_INTERFACE_H_ */