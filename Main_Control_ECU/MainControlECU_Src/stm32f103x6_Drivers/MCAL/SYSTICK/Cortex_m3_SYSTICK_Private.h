/**
 * @name    Cortex_m3_SYSTICK_Private.h
 * @brief   
 * @date    Created on: Mar 3, 2024
 * @author  Hossam Eid
 */

#ifndef MCAL_SYSTICK_CORTEX_M3_SYSTICK_PRIVATE_H_
#define MCAL_SYSTICK_CORTEX_M3_SYSTICK_PRIVATE_H_

/**************************************************************************************************************************
*===============================================
* Includes
*===============================================
*/
#include "Platform_Types.h"


/**************************************************************************************************************************
*===============================================
*               SYSTICK_MACROS
*===============================================
*/
#define SYST_MAX_RELOAD_VALUE       0x00FFFFFFUL


/**************************************************************************************************************************
*===============================================
*           User type definitions 
*===============================================
*/

/**
 * @brief This structure contains the SYSTICK Timer Registers.
 * 
 */
typedef struct{
    vuint32_t CSR;          /**!<SysTick Control and Status Register>*/
    vuint32_t RVR;          /**!<SysTick Reload Value Register>*/
    vuint32_t CVR;          /**!<SysTick Current Value Register>*/
    vuint32_t CALIB;        /**!<SysTick Calibration Value Register>*/
}sSYST_Typedef;



/**************************************************************************************************************************
*===============================================
*               SYSTICK_INSTANCE
*===============================================
*/
#define SYST_BASE       0xE000E010UL                              /*!<SYSTICK Timer Base Address>*/
#define SYST           ((volatile sSYST_Typedef *)(SYST_BASE))    /*!<SYSTICK Instance>*/



/**************************************************************************************************************************
*===============================================
*        SYSTICK_REGISTERS_BIT_DEFENITIONS
*===============================================
*/

/** @defgroup SYST_CSR
  * @{
  */
#define SYST_CSR_EN_POS             0                               /*!<SYSTICK Enable Bit Postion>*/
#define SYST_CSR_EN_MASK            (1 << SYST_CSR_EN_POS)          /*!<SYSTICK Enable Bit Mask>*/
#define SYST_CSR_TICKINT_POS        1                               /*!<SYSTICK Tick Interrupt Enable Bit Postion>*/
#define SYST_CSR_TICKINT_MASK       (1 << SYST_CSR_TICKINT_POS)     /*!<SYSTICK Tick Interrupt Enable Bit Mask>*/
#define SYST_CSR_CLKSRC_POS         2                               /*!<SYSTICK Clock Source Bit Postion>*/
#define SYST_CSR_CLKSRC_MASK       (1 << SYST_CSR_CLKSRC_POS)     /*!<SYSTICK Tick Interrupt Enable Bit Mask>*/
#define SYST_CSR_COUNT_FLAG_POS     16                              /*!<SYSTICK Count Flag Bit Postion>*/
#define SYST_CSR_COUNT_FLAG_MASK    (1 << SYST_CSR_COUNT_FLAG_POS)  /*!<SYSTICK Count Flag Bit Mask>*/
/**
  * @}
  */


/**************************************************************************************************************************
*===============================================
*           SYSTICK_CONFIGURATION_MACROS
*===============================================
*/

/**
 * @brief Specifies the clock source for the SysTick timer.
 *
 * This option determines what clock the SysTick timer uses.
 *
 * @param SYST_INTERNAL_CLK_DIV_1 Clock source is the processor clock.
 * @param SYST_INTERNAL_CLK_DIV_8 Clock source is the processor clock divided by 8.
 */
#define SYST_INTERNAL_CLK_DIV_1          SYST_CSR_CLKSRC_MASK            
#define SYST_INTERNAL_CLK_DIV_8          0
#define SYST_ASSERT_CLK(CLK)    (CLK == SYST_INTERNAL_CLK_DIV_1) || \
                                (CLK == SYST_INTERNAL_CLK_DIV_8)


/**
 * @brief Specifies the SysTick timer exception request.
 *
 * This option determines if the tick interrupt is enabled or disabled.
 *
 * @param SYST_TICKINT_ENABLE    Enable the SYSTICK exception request.
 * @param SYST_TICKINT_DISABLE   Disables the SYSTICK exception request.
 */
#define SYST_TICKINT_ENABLE          SYST_CSR_TICKINT_MASK            
#define SYST_TICKINT_DISABLE          0
#define SYST_ASSERT_TICKINT(INT)    (INT == SYST_TICKINT_ENABLE) || \
                                    (INT == SYST_TICKINT_DISABLE)


#define SYST_ASSERT_RELOAD_VALUE(VALUE) ((VALUE >= 0) && (VALUE <= SYST_MAX_RELOAD_VALUE))
#endif /* MCAL_SYSTICK_CORTEX_M3_SYSTICK_PRIVATE_H_ */
