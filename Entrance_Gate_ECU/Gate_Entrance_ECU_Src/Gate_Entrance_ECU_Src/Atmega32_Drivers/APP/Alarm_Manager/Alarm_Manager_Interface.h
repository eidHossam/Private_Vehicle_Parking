/**
 * @file Alarm_Manager_Interface.h
 * 
 * @brief this file implements 
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */

#ifndef ALARM_MANAGER_INTERFACE_H_
#define ALARM_MANAGER_INTERFACE_H_

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
#include "Timer0/Atmega32_Timer0.h"
/**
  * @}
  */

/** @defgroup HAL
  * @{
  */
#include "LCD_Driver/LCD_interface.h"
#include "LED_Driver/LED_Driver_Interface.h"
#include "Buzzer_Driver/Buzzer_Driver_Interface.h"
/**
  * @}
  */

/**************************************************************************************************************************
===============================================
*       Current state of "Alarm_Manager"
*===============================================
*/

/**
 * @brief This function pointer points to the current state of "Alarm_Manager"
 * 
 */
void (* fptr_st_AlarmManager)(void);

/**************************************************************************************************************************
===============================================
*       States Supported by "Alarm_Manager"
*===============================================
*/

/**
 * @brief This state initializes the main components of the Alarm_Manager module.
 * 
 */
void st_AlarmManager_Init(void);

/**
 * @brief this state makes the module go into idle mode until some user action is done.
 * 
 */
void st_AlarmManager_Idle(void);

/**
 * @brief This state informs the driver that his ID is invalid.
 * 
 */
void st_AlarmManager_FailedIDAuthentication(void);

/**
 * @brief This state informs the driver that his ID is valid.
 * 
 */
void st_AlarmManager_SuccessfullIDAuthentication(void);

#endif /* ALARM_MANAGER_INTERFACE_H_ */