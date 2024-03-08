/**
 * @file User_Admin_Interface.h
 * 
 * @brief this file implements 
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 08-03-2024
 * 
 * @version 1.0
 */

#ifndef USER_ADMIN_INTERFACE_H_
#define USER_ADMIN_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
/** @defgroup APP
  * @{
  */
/**
  * @}
  */

/** @defgroup MCAL
  * @{
  */
#include "../MCAL/GPIO/Atmega32_GPIO.h"
#include "UART/Atmega32_UART.h"

/**
  * @}
  */

/** @defgroup HAL
  * @{
  */
#include "LCD_Driver/LCD_interface.h"
/**
  * @}
  */

/**************************************************************************************************************************
===============================================
*       Current state of "User_Admin_Interface"
*===============================================
*/

/**
 * @brief This function pointer points to the current state of "User_Admin_Interface"
 * 
 */
void (* fptr_st_UserAdminInterface)(void);


/**************************************************************************************************************************
===============================================
*       States Supported by "User_Admin_Interface"
*===============================================
*/

/**
 * @brief This state initializes the main components of the User_Admin interface module.
 * 
 */
void st_UAI_Init(void);

/**
 * @brief this state prints the welcome message to guide the user on what to do.  
 * 
 */
void st_UAI_ShowWelcomeMsg(void);

/**
 * @brief this state makes the module go into idle mode until some user action is done.
 * 
 */
void st_UAI_Idle(void);

/**
 * @brief this state sends the driver's ID to the Admin ECU for authentication. 
 * 
 */
void st_UAI_SendIDToAdmin(void);
#endif /* USER_ADMIN_INTERFACE_H_ */