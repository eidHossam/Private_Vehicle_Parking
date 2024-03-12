/**
 * @file Gate_Control_Interface.h
 * 
 * @brief This file contains the APIs and states declarations for the module responsible for controlling the entrance
 * gate
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */

#ifndef GATE_CONTROL_INTERFACE_H_
#define GATE_CONTROL_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
/** @defgroup APP
  * @{
  */
#include "Interface.h"

/**
  * @}
  */

/** @defgroup MCAL
  * @{
  */
#include "../MCAL/Timer0/Atmega32_Timer0.h"
/**
  * @}
  */

/** @defgroup HAL
  * @{
  */
#include "../HAL/Servo_Motor_Driver/Servo_Motor_Interface.h"
#include "../HAL/PIR_Sensor_Driver/PIR_Interface.h"
/**
  * @}
  */

/**************************************************************************************************************************
===============================================
*       Current state of "Gate_Controller"
*===============================================
*/

/**
 * @brief This function pointer points to the current state of "Gate_Controller"
 * 
 */
void (* fptr_st_GateController)(void);


/**************************************************************************************************************************
===============================================
*       States Supported by "Gate_Controller"
*===============================================
*/

/**
 * @brief This state initializes the required peripherals in this module 
 * and sets the initial state of the module.
 * 
 */
void st_GateController_Init(void);

/**
 * @brief This state puts the module in an idle state 
 * waiting for a signal from the User_Admin_Interface module. 
 * 
 */
void st_GateController_Idle(void);


/**
 * @brief This state opens the garage's entrance gate.
 * 
 */
void st_GateController_OpenGate(void);

/**
 * @brief This state checks if the car passed the gate 
 * to avoid closing the gate while the car is under it.
 * 
 */
void st_GateController_CheckCarPassed(void);

/**
 * @brief This state closes the garage's entrance gate and 
 * sends a GateClosed signal to the User_Admin_Interface moudle.
 * 
 */
void st_GateController_CloseGate(void);

#endif /* GATE_CONTROL_INTERFACE_H_ */