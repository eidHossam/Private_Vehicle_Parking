/**
 * @file APP.h
 * 
 * @brief This files contains the APIs for the application running on the exit gate ECU
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 12-03-2024
 * 
 * @version 1.0
 */

#ifndef APP_H_
#define APP_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "User_Admin_Interface//User_Admin_Interface.h"
#include "Gate_Controller/Gate_Controller_Interface.h"
#include "Alarm_Manager/Alarm_Manager_Interface.h"
/**************************************************************************************************************************
===============================================
*               APIs Declaration
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   ExitGate_ECU_APP_SETUP
* @brief		:   Function to initialize all the components of the exit gate control ECU.
* Note			:   none.
======================================================================================================================
*/
void ExitGate_ECU_APP_SETUP(void);

/**
======================================================================================================================
* @Func_name	:   ExitGate_ECU_APP_Loop
* @brief		:   Main functionality of the exit Gate ECU.
* Note			:   none.
======================================================================================================================
*/
void ExitGate_ECU_APP_Loop(void);





#endif /* APP_H_ */