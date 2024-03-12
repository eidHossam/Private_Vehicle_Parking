/**
 * @file APP.c
 * 
 * @brief This files contains the implementation of the APIs for the application running on the exit gate ECU
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 12-03-2024
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
* @brief		:   Function to initialize all the components of the exit gate control ECU.
* Note			:   none.
======================================================================================================================
*/
void ExitGate_ECU_APP_SETUP(void)
{
    st_UAI_Init();

    st_GateController_Init();

    st_AlarmManager_Init();
}

/**
======================================================================================================================
* @Func_name	:   Dashboard_ECU_APP_Loop
* @brief		:   Main functionality of the exit gate ECU.
* Note			:   none.
======================================================================================================================
*/
void ExitGate_ECU_APP_Loop(void)
{
    fptr_st_UserAdminInterface();

    fptr_st_GateController();

    fptr_st_AlarmManager();
}
