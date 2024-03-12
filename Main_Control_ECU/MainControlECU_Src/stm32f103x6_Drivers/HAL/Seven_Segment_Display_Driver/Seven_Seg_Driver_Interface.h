/**
 * @file Seven_Seg_Driver_Interface.h
 * 
 * @brief this file contains the APIs of the binary coded 7 segment driver. 
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */

#ifndef HAL_SEVEN_SEGMENT_DISPLAY_DRIVER_SEVEN_SEG_DRIVER_INTERFACE_H_
#define HAL_SEVEN_SEGMENT_DISPLAY_DRIVER_SEVEN_SEG_DRIVER_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "GPIO/stm32f103x6_GPIO.h"

/**************************************************************************************************************************
*===============================================
*        7 Segment Display ports and pins
*===============================================
*/

#define SEVEN_SEGMEN_A_PORT         GPIOA
#define SEVEN_SEGMEN_A_PIN          GPIO_PIN0
#define SEVEN_SEGMEN_B_PORT         GPIOA
#define SEVEN_SEGMEN_B_PIN          GPIO_PIN1
#define SEVEN_SEGMEN_C_PORT         GPIOA
#define SEVEN_SEGMEN_C_PIN          GPIO_PIN2
#define SEVEN_SEGMEN_D_PORT         GPIOA
#define SEVEN_SEGMEN_D_PIN          GPIO_PIN3


/**************************************************************************************************************************
===============================================
*       APIs Supported by "HAL Seven Segment DRIVER"
*===============================================
*/

/**
 * @brief This function initializes the binary coded seven segment display.
 * 
 */
void HAL_SevenSeg_Init(void);

/**
 * @brief This function displays a given number onto the display.
 * 
 * @param copy_Number : Number to be displayed must be between 0 and 9.
 */
void HAL_SevenSeg_DisplayNumber(uint8 copy_Number);

/**
 * @brief This function increments the number displayed on the display by one.
 * 
 */
void HAL_SevenSeg_Increment();

/**
 * @brief This function decrements the number displayed on the display by one.
 * 
 */
void HAL_SevenSeg_Decrement();

#endif /* HAL_SEVEN_SEGMENT_DISPLAY_DRIVER_SEVEN_SEG_DRIVER_INTERFACE_H_ */
