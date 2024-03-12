/**
 * @file PIR_Program.c
 * 
 * @brief This file contains the APIs implementation for the PIR (Passive InfraRed) sensor
 *  that is used as a motion detector.
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
#include "PIR_Interface.h"

/**************************************************************************************************************************
===============================================
*               APIs Definitions
*===============================================
*/

/**
 * @brief This function initializes the PIR sensor driver. 
 * 
 * @param GPIOx : The GPIO port of that is connected to the PIR sensor.
 * @param copy_PIR_Pin : The GPIO pin of that is connected to the PIR sensor.
 */
void HAL_PIR_Init(volatile GPIO_typedef* GPIOx, uint8_t copy_PIR_Pin)
{
    GPIO_Pin_Config_t cfg;

    cfg.pinMode = GPIO_MODE_INPUT_FLOATING;
    cfg.pinNumber = copy_PIR_Pin;

    MCAL_GPIO_Init(GPIOx, &cfg);
}

/**
 * @brief This function reads the status of the PIR sensor.
 * 
 * @param GPIOx : The GPIO port of that is connected to the PIR sensor.
 * @param copy_PIR_Pin : The GPIO pin of that is connected to the PIR sensor.
 * @return ePIRStatus_t :   PIR_MotionDetected if anything is detected infront of the sensor, 
 *                          PIR_NoMotionDetected otherwise.
 */
ePIRStatus_t HAL_PIR_ReadStatus(volatile GPIO_typedef* GPIOx, uint8_t copy_PIR_Pin)
{
    ePIRStatus_t LOC_u8PIRStatus;
    uint8_t LOC_u8PinStatus;
    
    /*Read the value of the pin conected to the sensor*/
    LOC_u8PinStatus = MCAL_GPIO_ReadPin(GPIOx, copy_PIR_Pin);

    /*Determine the status of the PIR sensor*/
    LOC_u8PIRStatus = (LOC_u8PinStatus == GPIO_PIN_HIGH)? PIR_MotionDetected : PIR_NoMotionDetected;

    return LOC_u8PIRStatus;
}
