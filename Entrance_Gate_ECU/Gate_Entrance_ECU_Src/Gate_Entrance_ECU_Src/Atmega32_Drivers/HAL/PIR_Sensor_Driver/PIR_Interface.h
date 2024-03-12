/**
 * @file PIR_Interface.h
 * 
 * @brief This file contains the APIs for the HAL PIR (Passive InfraRed) sensor that is used as a motion detector.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */

#ifndef PIR_INTERFACE_H_
#define PIR_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "../MCAL/GPIO/Atmega32_GPIO.h"

/**
 * @brief This enum has the return status of the PIR sensor readings.
 * 
 * @param  PIR_MotionDetected:  If anything is detected infront of the sensor.
 * 
 * @param  PIR_NoMotionDetected:  If nothing is detected infront of the sensor.
 */
typedef enum{
    PIR_MotionDetected,
    PIR_NoMotionDetected
}ePIRStatus_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "HAL PIR DRIVER"
*===============================================
*/

/**
 * @brief This function initializes the PIR sensor driver. 
 * 
 * @param GPIOx : The GPIO port of that is connected to the PIR sensor.
 * @param copy_PIR_Pin : The GPIO pin of that is connected to the PIR sensor.
 */
void HAL_PIR_Init(volatile GPIO_typedef* GPIOx, uint8_t copy_PIR_Pin);

/**
 * @brief This function reads the status of the PIR sensor.
 * 
 * @param GPIOx : The GPIO port of that is connected to the PIR sensor.
 * @param copy_PIR_Pin : The GPIO pin of that is connected to the PIR sensor.
 * @return ePIRStatus_t :   PIR_MotionDetected if anything is detected infront of the sensor, 
 *                          PIR_NoMotionDetected otherwise.
 */
ePIRStatus_t HAL_PIR_ReadStatus(volatile GPIO_typedef* GPIOx, uint8_t copy_PIR_Pin);

#endif /* PIR_INTERFACE_H_ */