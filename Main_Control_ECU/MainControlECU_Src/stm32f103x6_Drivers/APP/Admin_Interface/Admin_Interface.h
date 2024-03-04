/*
 * Admin_Interface.h
 *
 *  Created on: Feb 26, 2024
 *      Author: Hossam Eid
 */

#ifndef APP_ADMIN_INTERFACE_H_
#define APP_ADMIN_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
/** @defgroup APP
  * @{
  */
#include "string.h"
#include "Admin_Interface_cfg.h"
/**
  * @}
  */

/** @defgroup MCAL
  * @{
  */
#include "SYSTICK/Cortex_m3_SYSTICK_Interface.h"
/**
  * @}
  */

/** @defgroup HAL
  * @{
  */
#include "Keypad_Driver/Keypad_interface.h"
#include "LCD_Driver/LCD_interface.h"
/**
  * @}
  */



/** @defgroup Admin_Interface_Current_State
  * @{
  */
void (* Admin_Dashboard_State)(void);
/**
  * @}
  */



/**************************************************************************************************************************
===============================================
*       States Supported by "Admin_Interface"
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   st_Admin_Dashboard_Init
* @brief		  :   This function initializes the required subsystem components for the admin dashboard.  
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_DashboardInit(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_Initial_Message
* @brief		  :   Function to display the initial welcome message to the user.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_InitialMessage(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_GetUserInput
* @brief		  :   Function to get the user action.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_GetUserInput(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_LoginMessage
* @brief		  :   Function to get the user action.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_LoginMessage(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_GetUserID
* @brief		  :   Function to get the user input for the userID.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_GetUserID(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_GetUserPassword
* @brief		  :   Function to get the user input for the password.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_GetUserPassword(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_GetUserPassword
* @brief		  :   Function to get the user input for the password.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_CheckLoginInfo(void);

/**
======================================================================================================================
* @Func_name	: st_Admin_LoginTimeout
* @brief		  : Timeout the user from tying to login after passing the maximum number of allowed login attempts.
* @note			  : The only way to get out of this state is through the SYSTICK timer handler.
======================================================================================================================
*/
void st_Admin_LoginTimeout(void);

/**
======================================================================================================================
* @Func_name	: st_Admin_Idle
* @brief	    : Function to make the ECU go into idle mode.
* @note			  :
======================================================================================================================
*/
void st_Admin_Idle(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_ShowAdminOptions
* @brief		  :   Function to get display the available admin operations on the LCD screen.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_ShowAdminOptions(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_GetAdminOption
* @brief		  :   Function to get the required action to be done from the user.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_GetAdminOption(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_AddNewID
* @brief		  :   Function to add a new authorized ID to the garage.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_AddNewID(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_RemoveID
* @brief		  :   Function to remove an existing authorized ID from the garage.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_RemoveID(void);

/**
======================================================================================================================
* @Func_name	:   st_Admin_ShowIDsList
* @brief		  :   Function to show all the authorized IDs in the system.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_ShowIDsList(void);



#endif /* APP_ADMIN_INTERFACE_H_ */
