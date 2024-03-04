/**
 * @name    Cortex_m3_SYSTICK_Interface.h
 * @brief   
 * @date    Created on: Mar 3, 2024
 * @author  Hossam Eid
 */

#ifndef MCAL_SYSTICK_CORTEX_M3_SYSTICK_INTERFACE_H_
#define MCAL_SYSTICK_CORTEX_M3_SYSTICK_INTERFACE_H_

/** @defgroup INCLUDES
  * @{
  */
#include "Platform_Types.h"
#include "RCC/stm32f103x6_RCC.h"

/**
  * @}
  */

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL SYSTICK DRIVER"
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_Init
* @brief		  :   Function to initialize the systick timer with the parameters specified in the Config file.
* @param [in]	:   copy_ReloadVal: Value to be set in the reload register which the counter will start counting from.
* @return     :    E_OK on success, E_NOK on failure.
* @note			  :   Actual timer duration is based on the clock frequency.
======================================================================================================================
*/
eStatus_t MCAL_SYST_Init(uint32 copy_ReloadVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_vInit
* @brief		  :   Function to initialize the systick timer with the parameters specified in the Config file.
* @param [in]	:   none.
* @return     :   none.
* @note			  :   Actual timer duration is based on the clock frequency.
======================================================================================================================
*/
void MCAL_SYST_vInit(void);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_Reset
* @brief		  :   Function to disable the timer and reset the counter and reload register values to zero.
* @param [in]	:   none.
* @return     :   none.
* @note			  :   This function also stops the systick timer.
======================================================================================================================
*/
void MCAL_SYST_Reset(void);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_Start
* @brief		  :   Function to start the timer counting process.
* @param [in]	:   none.
* @return     :   none.
* @note			  :   none.
======================================================================================================================
*/
void MCAL_SYST_Start(void);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_Stop
* @brief		  :   Function to stop the timer counting process.
* @param [in]	:   none.
* @return     :   none.
* @note			  :   none.
======================================================================================================================
*/
void MCAL_SYST_Stop(void);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_SetReloadValue
* @brief		  :   Function to set the value of the reload register.
* @param [in]	:   copy_ReloadValue:Value to be set in the reload register which the counter will start counting from.
* @return     :    E_OK on success, E_NOK on failure.
* @note			  :   This function will the stop the counter you have to restart is using the "MCAL_SYST_Start" function.
======================================================================================================================
*/
eStatus_t MCAL_SYST_SetReloadValue(uint32 copy_ReloadValue);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_GetRemainingTicks
* @brief		  :   Function to return the remaining number of ticks until the counter reaches zero.
* @param [in]	:   none.
* @return     :   The current value of the systick counter.
* @note			  :   none.
======================================================================================================================
*/
uint32 MCAL_SYST_GetRemainingTicks(void);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_GetElapsedTicks
* @brief		  :   Function to return the elapsed number of ticks from the start of the count.
* @param [in]	:   none.
* @return     :   The elapsed number of ticks.
* @note			  :   none.
======================================================================================================================
*/
uint32 MCAL_SYST_GetElapsedTicks(void);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_BusyWaitDelay_us
* @brief		  :   Function to halt the process for a specified amount of time in microseconds.
* @param [in]	:   copy_Microseconds: specifies the amount of time to wait in microseconds,
* @return     :   E_OK on success, E_NOK on failure.
* @note			  :   This function will block the CPU for the specified amount of time.
======================================================================================================================
*/
eStatus_t MCAL_SYST_BusyWaitDelay_us(uint32 copy_Microseconds);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_BusyWaitDelay_ms
* @brief		  :   Function to halt the process for a specified amount of time in copy_Millieseconds.
* @param [in]	:   copy_Millieseconds: specifies the amount of time to wait in copy_Millieseconds,
* @return     :   E_OK on success, E_NOK on failure.
* @note			  :   This function will block the CPU for the specified amount of time.
======================================================================================================================
*/
eStatus_t MCAL_SYST_BusyWaitDelay_ms(uint32 copy_Millieseconds);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_SetIntervalSingle
* @brief		  :   Function to start the counting process for a specified amount of time in microseconds, 
*                   An interrupt will rise at the end of the time period and the counter will be disabled.
* @param [in]	:   copy_Microseconds: Specifies the amount of time to wait in microseconds,
* @param [in]	:   fptr_Callback: Pointer to the ISR that to be called at the end of the time period.
* @return     :   E_OK on success, E_NOK on failure.
* @note			  :   none.
======================================================================================================================
*/
eStatus_t MCAL_SYST_SetIntervalSingle(uint32 copy_Microseconds, fptr_Callback);

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_SetIntervalPeriodic
* @brief		  :   Function to start the counting process for a specified amount of time in microseconds, 
*                 An interrupt will rise at the end of the time period and a new counting process will start.
* @param [in]	:   copy_Microseconds: Specifies the amount of time to wait in microseconds,
* @param [in]	:   fptr_Callback: Pointer to the ISR that to be called at the end of the time period.
* @return     :   E_OK on success, E_NOK on failure.
* @note			  :   none.
======================================================================================================================
*/
eStatus_t MCAL_SYST_SetIntervalPeriodic(uint32 copy_Microseconds, fptr_Callback);
#endif /* MCAL_SYSTICK_CORTEX_M3_SYSTICK_INTERFACE_H_ */
