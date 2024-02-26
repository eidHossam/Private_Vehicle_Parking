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
#include "Admin_Interface_cfg.h"
#include "Keypad_Driver/Keypad_interface.h"
#include "LCD_Driver/LCD_interface.h"
#include "string.h"

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
* @Func_name	:   st_Admin_SaveOnEEPROM
* @brief		  :   Function to save the authorized IDs on the external memory.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_SaveOnEEPROM(void);



#endif /* APP_ADMIN_INTERFACE_H_ */
