/*
 * APP.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Hossam Eid
 */

#include "APP.h"

/**************************************************************************************************************************
===============================================
*               APIs Definition
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   Dashboard_ECU_APP_SETUP
* @brief		:   Function to initialize all the components of the main control ECU.
* Note			:   none.
======================================================================================================================
*/
void Dashboard_ECU_APP_SETUP(void)
{
    st_Admin_DashboardInit();

    st_GatesComm_Init();
}

/**
======================================================================================================================
* @Func_name	:   Dashboard_ECU_APP_Loop
* @brief		:   Main functionality of the main dashboard ECU.
* Note			:   none.
======================================================================================================================
*/
void Dashboard_ECU_APP_Loop(void)
{
    Admin_Dashboard_State();

    fptr_GateCommState();
}





