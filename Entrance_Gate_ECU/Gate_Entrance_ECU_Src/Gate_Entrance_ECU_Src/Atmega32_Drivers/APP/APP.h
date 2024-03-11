/**
 * @file APP.h
 * 
 * @brief this file implements 
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 08-03-2024
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
#include "User_Admin_Interface.h"
#include "Gate_Controller_Interface.h"

/**************************************************************************************************************************
===============================================
*               APIs Declaration
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   EntranceGate_ECU_APP_SETUP
* @brief		:   Function to initialize all the components of the entrance gate control ECU.
* Note			:   none.
======================================================================================================================
*/
void EntranceGate_ECU_APP_SETUP(void);

/**
======================================================================================================================
* @Func_name	:   EntranceGate_ECU_APP_Loop
* @brief		:   Main functionality of the Entrance Gate ECU.
* Note			:   none.
======================================================================================================================
*/
void EntranceGate_ECU_APP_Loop(void);





#endif /* APP_H_ */