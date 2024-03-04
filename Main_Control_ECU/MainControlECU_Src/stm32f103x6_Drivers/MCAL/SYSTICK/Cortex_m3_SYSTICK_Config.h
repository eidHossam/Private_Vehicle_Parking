/**
 * @name    Cortex_m3_SYST_Config.h
 * @brief   
 * @date    Created on: Mar 3, 2024
 * @author  Hossam Eid
 */

#ifndef MCAL_SYST_CORTEX_M3_SYST_CONFIG_H_
#define MCAL_SYST_CORTEX_M3_SYST_CONFIG_H_

/**************************************************************************************************************************
*===============================================
*                   Includes
*===============================================        
*/
#include "Cortex_m3_SYSTICK_Private.h"


/**************************************************************************************************************************
*===============================================
*           SYST_TIMER_CONFIG_MACROS
*===============================================
*/
/**
 * @brief This option configures the the SYST timer input clock.
 * 
 * @options:
 * 
 * @param SYST_INTERNAL_CLK_DIV_1    Clock source is the processor clock.
 * @param SYST_INTERNAL_CLK_DIV_8    Clock source is the processor clock divided by 8.
 * 
 */
#define SYST_CLKSRC   SYST_INTERNAL_CLK_DIV_1


/**
 * @brief This option configures the the SYST timer exception request.
 * 
 * @options:
 * 
 * @param SYST_TICKINT_ENABLE    Enable the SYST exception request.
 * @param SYST_TICKINT_DISABLE   Disable the SYST exception request.
 * 
 */
#define SYST_TICKINT SYST_TICKINT_ENABLE

#endif /* MCAL_SYST_CORTEX_M3_SYST_CONFIG_H_ */
