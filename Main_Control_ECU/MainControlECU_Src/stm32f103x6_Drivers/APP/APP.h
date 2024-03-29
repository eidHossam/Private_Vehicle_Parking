/*
 * APP.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Hossam Eid
 */

#ifndef APP_APP_H_
#define APP_APP_H_
/*
*===============================================
*                   Includes
*===============================================
*/
#include "Admin_Interface/Admin_Interface.h"
#include "Gates_Communication/Gates_Communication.h"

/**************************************************************************************************************************
===============================================
*               APIs Declaration
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   Dashboard_ECU_APP_SETUP
* @brief		:   Function to initialize all the components of the main control ECU.
* Note			:   none.
======================================================================================================================
*/
void Dashboard_ECU_APP_SETUP(void);

/**
======================================================================================================================
* @Func_name	:   Dashboard_ECU_APP_Loop
* @brief		:   Main functionality of the main dashboard ECU.
* Note			:   none.
======================================================================================================================
*/
void Dashboard_ECU_APP_Loop(void);


#endif /* APP_APP_H_ */
