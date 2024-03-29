/**
 * @file APP.c
 * 
 * @brief this file implements 
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 08-03-2024
 * 
 * @version 1.0
 */

/*
*===============================================
*                   Includes
*===============================================
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
void EntranceGate_ECU_APP_SETUP(void)
{
    st_UAI_Init();

    st_GateController_Init();

    st_AlarmManager_Init();
}

/**
======================================================================================================================
* @Func_name	:   Dashboard_ECU_APP_Loop
* @brief		:   Main functionality of the main dashboard ECU.
* Note			:   none.
======================================================================================================================
*/
void EntranceGate_ECU_APP_Loop(void)
{
    fptr_st_UserAdminInterface();

    fptr_st_GateController();

    fptr_st_AlarmManager();
}
