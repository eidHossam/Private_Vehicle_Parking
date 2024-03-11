/**
 * @file Servo_Motor_Interface.h
 * 
 * @brief This file holds the interface and APIs to use a PWM controlled servo motor.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 10-03-2024
 * 
 * @version 1.0
 */

#ifndef SERVO_MOTOR_INTERFACE_H_
#define SERVO_MOTOR_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "../../MCAL/Timer2/Atmega32_Timer2.h"

/**************************************************************************************************************************
*===============================================
*         Enum Configuration References
*===============================================
*/

typedef enum{
    ServoMotor_0Degree = 240,
    ServoMotor_90Degree = 250,
    ServoMotor_180Degree = 230
}eServoMotorDegree_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "HAL SERVO MOTOR DRIVER"
*===============================================
*/

/**
 * @brief This function does the required initialization to use the servo motor.
 * 
 * @return eStatus_t: E_OK if the initialization was successful, E_NOK otherwise.
 */
eStatus_t HAL_ServoMotorInit(void);

/**
 * @brief This function turn the servo motor with the specified degree. 
 * 
 * @param copy_eDegree : Degree to turn the servo motor with.
 * @return eStatus_t   : Status of the operation.
 */
eStatus_t HAL_ServoMotorTurn(eServoMotorDegree_t copy_eDegree);

#endif /* SERVO_MOTOR_INTERFACE_H_ */