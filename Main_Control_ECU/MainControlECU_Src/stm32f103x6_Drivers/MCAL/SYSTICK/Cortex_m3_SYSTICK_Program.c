/**
 * @name    Cortex_m3_SYSTICK_Program.c
 * @brief   
 * @date    Created on: Mar 3, 2024
 * @author  Hossam Eid
 */
#include "Cortex_m3_SYSTICK_Private.h"

/**************************************************************************************************************************
*===============================================
* Includes
*===============================================
*/
#include "Cortex_m3_SYSTICK_Config.h"
#include "Cortex_m3_SYSTICK_Interface.h"
#include "Cortex_m3_SYSTICK_Private.h"


/**************************************************************************************************************************
===============================================
*       Local MACROS
*===============================================
*/
/** @defgroup DELAY_TIME_UNIT
  * @{
  */
#define SYST_DELAY_US       (1000000UL)
#define SYST_DELAY_MS       (1000UL)
/**
  * @}
  */

/** @defgroup TIMER_MODE
  * @{
  */
#define SYST_SINGLE_MODE        0       /**!<If you want to use the timer only once>*/
#define SYST_PERIODIC_MODE      1       /**!<If you want the timer to start again when it's done>*/
/**
  * @}
  */


/**************************************************************************************************************************
===============================================
*       Local Variables
*===============================================
*/
static fptr_Callback Glob_SYSTCallback = NULL;
static uint8 Glob_SYSTMode = SYST_SINGLE_MODE;

/**************************************************************************************************************************
===============================================
*       Local Functions
*===============================================
*/
static uint32 MCAL_SYST_CalculateCLKFreq(uint32 copy_TimeUnit)
{
    uint32 LOC_SYST_Clk = 0;
    
    /*Calculates the clock of the systick timer*/
    #if SYST_CLKSRC == SYST_INTERNAL_CLK_DIV_1
        LOC_SYST_Clk = MCAL_RCC_GET_SYSCLK();
    #elif SYST_CLKSRC == SYST_INTERNAL_CLK_DIV_8
        LOC_SYST_Clk = (MCAL_RCC_GET_HCLK() / 8);
    #else
        #error "Please choose an acceptable clock source"
    #endif

    /*Divide by the time unit to avoid doing floating point operations*/
    LOC_SYST_Clk /= copy_TimeUnit;  

    return LOC_SYST_Clk;
}

static eStatus_t MCAL_SYST_GeneralBusyWaitDelay(uint32 copy_Time, uint32 copy_TimeUnit)
{
    eStatus_t LOC_eStatus = E_OK;
    uint64 LOC_u32TicksCount = 0;
    uint32 LOC_SYST_Clk = 0;
    
    LOC_SYST_Clk = MCAL_SYST_CalculateCLKFreq(copy_TimeUnit);
    
    LOC_u32TicksCount = copy_Time * LOC_SYST_Clk;

    if(SYST_ASSERT_RELOAD_VALUE(LOC_u32TicksCount))
    {
        MCAL_SYST_Init(LOC_u32TicksCount);
        
        /*Start the counter*/
        MCAL_SYST_Start();

        /*Halt the processor untill the count flag bit is set*/
        while(!READ_BIT(SYST->CSR, SYST_CSR_COUNT_FLAG_POS));

        /*Stop the counter again*/
        MCAL_SYST_Stop();
    }else{
        LOC_eStatus = E_NOK;
    }

    return LOC_eStatus;
}

/**************************************************************************************************************************
===============================================
*       APIs Definition
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_Init
* @brief		:   Function to initialize the systick timer with the parameters specified in the Config file.
* @param [in]	:   copy_ReloadVal: Value to be set in the reload register which the counter will start counting from.
* @return       :    E_OK on success, E_NOK on failure..
* @note			:   Actual timer duration is based on the clock frequency.
======================================================================================================================
*/
eStatus_t MCAL_SYST_Init(uint32 copy_ReloadVal)
{
    eStatus_t LOC_estatus = E_OK;
    
    if((SYST_ASSERT_RELOAD_VALUE(copy_ReloadVal)) &&
       (SYST_ASSERT_CLK(SYST_CLKSRC)) && (SYST_ASSERT_TICKINT(SYST_TICKINT)))
    {
        /*Disable the systick timer*/
        MCAL_SYST_Stop();
        
        /*1. Program reload value.*/
        SYST->RVR = copy_ReloadVal;
        
        /*2. Clear current value.
            A write of any value clears the field to 0,
            and also clears the SYST_CSR COUNTFLAG bit to 0.
        */
        SYST->CVR = 0;

        /*3. Program Control and Status register.*/
        SYST->CSR |= (SYST->CSR & ~(SYST_CSR_CLKSRC_MASK | SYST_CSR_TICKINT_MASK)); /*Clear the CLKSRC and TICKINT bits*/
        SYST->CSR |= (SYST_CLKSRC | SYST_TICKINT);
    }else{
        LOC_estatus = E_NOK;
    }

    return LOC_estatus;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_vInit
* @brief		:   Function to initialize the systick timer with the parameters specified in the Config file.
* @param [in]	:   none.
* @return       :   none.
* @note			:   The initial reload value will be the maximum which is 0x00FFFFFF.
======================================================================================================================
*/
void MCAL_SYST_vInit(void)
{
    MCAL_SYST_Init(SYST_MAX_RELOAD_VALUE);
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_Reset
* @brief		:   Function to disable the timer and reset the counter and reload register values to zero.
* @param [in]	:   none.
* @return       :   none.
* @note			:   This function also stops the systick timer.
======================================================================================================================
*/
void MCAL_SYST_Reset(void)
{
    MCAL_SYST_Stop();

    SYST->RVR = 0;

    SYST->CVR = 0;

    SYST->CSR = 0;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_Start
* @brief		:   Function to start the timer counting process.
* @param [in]	:   none.
* @return       :   none.
* @note			:   none.
======================================================================================================================
*/
void MCAL_SYST_Start(void)
{
    SYST->CSR |= SYST_CSR_EN_MASK;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_Stop
* @brief		:   Function to stop the timer counting process.
* @param [in]	:   none.
* @return       :   none.
* @note			:   none.
======================================================================================================================
*/
void MCAL_SYST_Stop(void)
{
    SYST->CSR &= ~SYST_CSR_EN_MASK;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_SetReloadValue
* @brief		:   Function to set the value of the reload register.
* @param [in]	:   copy_ReloadValue:Value to be set in the reload register which the counter will start counting from.
* @return       :    E_OK on success, E_NOK on failure.
* @note			:   This function will the stop the counter you have to restart is using the "MCAL_SYST_Start" function.
======================================================================================================================
*/
eStatus_t MCAL_SYST_SetReloadValue(uint32 copy_ReloadValue)
{
    eStatus_t LOC_estatus = E_OK;

    if(SYST_ASSERT_RELOAD_VALUE(copy_ReloadValue))
    {
        MCAL_SYST_Stop();

        SYST->RVR = copy_ReloadValue;
    }else{
        LOC_estatus = E_NOK;
    }

    return LOC_estatus;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_GetRemainingTicks
* @brief		:   Function to return the remaining number of ticks until the counter reaches zero.
* @param [in]	:   none.
* @return       :   The current value of the systick counter.
* @note			:   none.
======================================================================================================================
*/
uint32 MCAL_SYST_GetRemainingTicks(void)
{
    uint32 LOC_u32RemainingTicks = 0;
    LOC_u32RemainingTicks = SYST->CVR;
    return LOC_u32RemainingTicks;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_GetElapsedTicks
* @brief		:   Function to return the elapsed number of ticks from the start of the count.
* @param [in]	:   none.
* @return       :   The elapsed number of ticks.
* @note			:   none.
======================================================================================================================
*/
uint32 MCAL_SYST_GetElapsedTicks(void)
{
    uint32 LOC_u32ElapsedTicks = 0;
    LOC_u32ElapsedTicks = SYST->RVR - SYST->CVR;
    return LOC_u32ElapsedTicks;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_BusyWaitDelay_us
* @brief		:   Function to halt the process for a specified amount of time in microseconds.
* @param [in]	:   copy_Microseconds: specifies the amount of time to wait in microseconds,
* @return       :   E_OK on success, E_NOK on failure.
* @note			:   This function will block the CPU for the specified amount of time.
======================================================================================================================
*/
eStatus_t MCAL_SYST_BusyWaitDelay_us(uint32 copy_Microseconds)
{
    eStatus_t LOC_eStatus;

    LOC_eStatus = MCAL_SYST_GeneralBusyWaitDelay(copy_Microseconds, SYST_DELAY_US);

    return LOC_eStatus;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_BusyWaitDelay_ms
* @brief		:   Function to halt the process for a specified amount of time in copy_Millieseconds.
* @param [in]	:   copy_Millieseconds: specifies the amount of time to wait in copy_Millieseconds,
* @return       :   E_OK on success, E_NOK on failure.
* @note			:   This function will block the CPU for the specified amount of time.
======================================================================================================================
*/
eStatus_t MCAL_SYST_BusyWaitDelay_ms(uint32 copy_Millieseconds)
{
    eStatus_t LOC_eStatus;

    LOC_eStatus = MCAL_SYST_GeneralBusyWaitDelay(copy_Millieseconds, SYST_DELAY_MS);

    return LOC_eStatus;  
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_SetIntervalSingle
* @brief		:   Function to start the counting process for a specified amount of time in microseconds, 
*                   An interrupt will rise at the end of the time period and the counter will be disabled.
* @param [in]	:   copy_Microseconds: Specifies the amount of time to wait in microseconds,
* @param [in]	:   fptr_Callback: Pointer to the ISR that to be called at the end of the time period.
* @return       :   E_OK on success, E_NOK on failure.
* @note			:   none.
======================================================================================================================
*/
eStatus_t MCAL_SYST_SetIntervalSingle(uint32 copy_Microseconds, fptr_Callback callback)
{
    eStatus_t LOC_eStatus = E_OK;
    uint64 LOC_u32TicksCount = 0;
    uint32 LOC_SYST_Clk = 0;
    
    LOC_SYST_Clk = MCAL_SYST_CalculateCLKFreq(SYST_DELAY_US);
    
    /*Calculate the required number of ticks*/
    LOC_u32TicksCount = copy_Microseconds * LOC_SYST_Clk;

    if(SYST_ASSERT_RELOAD_VALUE(LOC_u32TicksCount) && callback)
    {
        
        MCAL_SYST_Init(LOC_u32TicksCount);

        /*Set the callback function to be called when the interrupt is raised*/
        Glob_SYSTCallback = callback;

        /*Set the timer mode*/
        Glob_SYSTMode = SYST_SINGLE_MODE;
    
        /*Enable the interrupt and set the clock source*/
        SYST->CSR |= SYST_CSR_TICKINT_MASK;

        /*Start the counter*/
        MCAL_SYST_Start();

    }else{
        LOC_eStatus = E_NOK;
    }

    return LOC_eStatus;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_SYST_SetIntervalPeriodic
* @brief		:   Function to start the counting process for a specified amount of time in microseconds, 
*                   An interrupt will rise at the end of the time period and a new counting process will start.
* @param [in]	:   copy_Microseconds: Specifies the amount of time to wait in microseconds,
* @param [in]	:   fptr_Callback: Pointer to the ISR that to be called at the end of the time period.
* @return       :   E_OK on success, E_NOK on failure.
* @note			:   none.
======================================================================================================================
*/
eStatus_t MCAL_SYST_SetIntervalPeriodic(uint32 copy_Microseconds, fptr_Callback callback)
{
    eStatus_t LOC_eStatus = E_OK;
    uint64 LOC_u32TicksCount = 0;
    uint32 LOC_SYST_Clk = 0;
    
    LOC_SYST_Clk = MCAL_SYST_CalculateCLKFreq(SYST_DELAY_US);
    
    /*Calculate the required number of ticks*/
    LOC_u32TicksCount = copy_Microseconds * LOC_SYST_Clk;

    if(SYST_ASSERT_RELOAD_VALUE(LOC_u32TicksCount) && callback)
    {
        MCAL_SYST_Init(LOC_u32TicksCount);

        /*Set the callback function to be called when the interrupt is raised*/
        Glob_SYSTCallback = callback;

        /*Set the timer mode*/
        Glob_SYSTMode = SYST_PERIODIC_MODE;
    
        /*Enable the interrupt*/
        SYST->CSR |= SYST_CSR_TICKINT_MASK;

        /*Start the counter*/
        MCAL_SYST_Start();

    }else{
        LOC_eStatus = E_NOK;
    }

    return LOC_eStatus;
}

/**************************************************************************************************************************
===============================================
*       SYSTICK_ISR_DEFINITION
*===============================================
*/

void SysTick_Handler(void)
{   
    /*Stop the counter if we are in the single use mode*/
    if(Glob_SYSTMode == SYST_SINGLE_MODE)
    {
        MCAL_SYST_Stop();
    }

    if(Glob_SYSTCallback)
    {
        Glob_SYSTCallback();
    }

    SYST->CSR &= ~SYST_CSR_COUNT_FLAG_MASK;
}