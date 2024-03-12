/**
**************************************************************************************************************************
* @brief     : This module contains functions for configuring and controlling the Timer0 module.
* @author    : Hossam Eid
* @date      : 1/12/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the Timer0 driver.
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32_Timer0.h"

/** @defgroup Private Macros and defines
  * @{
  */

#define TIMER0_OC0_PORT       GPIOB
#define TIMER0_OC0_PIN        GPIO_PIN3
/**
  * @}
  */

/** @defgroup Global variables
  * @{
  */
static sTIMER0_Config_t timer0_CFG;

static uint32_t overflowCounter = 0;
static uint32_t Glob_u32DelayInMilliseconds;

static Ptr_Func overflowCallback;
static Ptr_Func outputCompareMatchCallback;
static Ptr_Func Glob_fptrInterruptedDelayCallback;

/**
  * @}
  */

/** @defgroup Local functions
  * @{
  */
static void Timer0_SingleIntervalDelayCallback(void)
{
    static uint32_t LOC_u32CTCcounter = 0;

    if(LOC_u32CTCcounter < Glob_u32DelayInMilliseconds)
    {
        LOC_u32CTCcounter++;
        
        /*Clear the flag*/
        SET_BIT(TIFR, TIMER0_TIFR_OCF0_POS);
    }else{
        LOC_u32CTCcounter = 0;
        MCAL_TIMER0_Stop();

        /*Execute the user's function*/
        Glob_fptrInterruptedDelayCallback();
    }
    
}

/**
  * @}
  */

/**************************************************************************************************************************
*===============================================
*  			APIs functions definitions
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_Init
* @brief		:   Intializes the timer peripheral with the specified parameters in the config struct.
* @param [in]	:   timerCFG: Configuration structure.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_Init(sTIMER0_Config_t* timerCFG)
{
    eStatus_t status = E_OK;

    if(NULL == timerCFG)
    {
        status = E_NOK;
    
    }/*Assert all the parameters in the configuration struct*/
    else if(!ASSERT_TIMER0_CLK(timerCFG->TIMER0_CLK_SRC) || !ASSERT_TIMER0_MODE(timerCFG->TIMER0_Mode) ||
            !ASSERT_TIMER0_COM(timerCFG->TIMER0_COM)     || !ASSERT_TIMER0_TOIE(timerCFG->TIMER0_OIE)  ||
            !ASSERT_TIMER0_TOCIE(timerCFG->TIMER0_OCIE)){
                
        status = E_NOK;
    }else{

        /*Store the configuration struct for later use*/
        timer0_CFG = * timerCFG;

        /*Clear the register*/
        TIMER0->TCCR0 = 0;
        
        TIMER0->TCCR0 = ((timerCFG->TIMER0_CLK_SRC) | (timerCFG->TIMER0_Mode) | (timerCFG->TIMER0_COM)) ;

        /*Clear the interrupt mask bits*/
        TIMSK &= ~(TIMER0_TIMSK_OCIE0_MASK | TIMER0_TIMSK_TOIE0_MASK);
        TIMSK |= ((timerCFG->TIMER0_OIE) | (timerCFG->TIMER0_OCIE));

        if(TIMER0_COM_Disconnected != timerCFG->TIMER0_COM)
        {
            /*
            *   the Data Direction Register (DDR) bit corresponding to the OC0 
            *   pin must be set in order to enable the output driver.
            */
            GPIO_Pin_Config_t cfg = {TIMER0_OC0_PIN, GPIO_MODE_OUTPUT};
            MCAL_GPIO_Init(TIMER0_OC0_PORT, &cfg);
        }

        if((TIMER0_TOCI_Enable == timerCFG->TIMER0_OCIE) || (TIMER0_TOI_Enable == timerCFG->TIMER0_OIE))
        {
            /*Enable the global interrupt*/
            G_INTERRUPT_ENABLE;
        }      
    }

    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_Stop
* @brief		:   Stop the Timer peripheral from counting.
* @Note         :   This function doesn't reset the peripheral it only stops the counting process.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_Stop()
{
    eStatus_t status = E_OK;

    /*Disable the clock to stop the timer*/
    TIMER0->TCCR0 &= ~(TIMER0_TCCR_CS_MASK);

    return status;
}

/**
======================================================================================================================
* @Func_name	  :   MCAL_TIMER0_Start
* @brief		    :   start the counter from the same value we Stopped at.
* @Note         :   none.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_Start()
{
    eStatus_t status = E_OK;

    /*Enable the clock to start the timer*/
    TIMER0->TCCR0 |= timer0_CFG.TIMER0_CLK_SRC;

    return status;
}


/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_GetCompare
* @brief		:   Get the value stored in the output compare register.
* @param [out]	:   compareVal: pointer to store the returned value in.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_GetCompare(uint8_t* compareVal)
{
    eStatus_t status = E_OK;
    *compareVal = TIMER0->OCR0;
    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_SetCompare
* @brief		:   Set the value of the output compare register.
* @param [in]	:   compareVal: The value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_SetCompare(uint8_t compareVal)
{
    eStatus_t status = E_OK;
    TIMER0->OCR0 = compareVal;
    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_GetCounter
* @brief		:   Get the value stored in the counter register.
* @param [out]	:   counterVal: pointer to store the returned value in.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_GetCounter(uint8_t* counterVal)
{
    eStatus_t status = E_OK;
    *counterVal = TIMER0->TCNT0;
    return status;

}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_SetCounter
* @brief		:   Set the value of the counter register.
* @param [in]	:   counterVal: The value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_SetCounter(uint8_t counterVal)
{
    eStatus_t status = E_OK;
    TIMER0->TCNT0 = counterVal;
    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_GetOverflow
* @brief		:   Get the number of overflows value.
* @param [out]	:   overflowVal:  pointer to store the returned value in
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_GetOverflow(uint32_t* overflowVal)
{
    eStatus_t status = E_OK;
    *overflowVal = overflowCounter;
    return status;

}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_SetOverflow
* @brief		:   Set the value of the overflow.
* @param [in]	:   overflowVal: value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_SetOverflow(uint32_t overflowVal)
{
    eStatus_t status = E_OK;
    overflowCounter = overflowVal;
    return status;

}

/**
======================================================================================================================
* @Func_name	: MCAL_TIMER0_BusyWaitDelayms
* @brief		  : Function to delay the timer for a certain amount of time.
* @param [in]	: copy_Milliseconds number of milliseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER0_BusyWaitDelayms(uint32_t copy_Milliseconds)
{
    sTIMER0_Config_t Timer0_cfg;
    uint8_t LOC_u8CompareValue;
    uint32_t LOC_u32CTCcounter = 0;

    Timer0_cfg.TIMER0_CLK_SRC = TIMER0_Prescale_64;
    Timer0_cfg.TIMER0_Mode = TIMER0_CTC_Mode;
    Timer0_cfg.TIMER0_COM = TIMER0_COM_Disconnected;
    Timer0_cfg.TIMER0_OCIE = TIMER0_TOCI_Disable;
    Timer0_cfg.TIMER0_OIE = TIMER0_TOI_Disable;

    /*Delay of one millisecond*/
    LOC_u8CompareValue = (uint8_t)(((F_CPU / 1000) / 64) - 1);
    MCAL_TIMER0_SetCompare(LOC_u8CompareValue);

    MCAL_TIMER0_Init(&Timer0_cfg);

    while(LOC_u32CTCcounter < copy_Milliseconds)
    {
        while(!READ_BIT(TIFR, TIMER0_TIFR_OCF0_POS));

        LOC_u32CTCcounter++;
        
        /*Clear the flag*/
        SET_BIT(TIFR, TIMER0_TIFR_OCF0_POS);
    }

}

/**
======================================================================================================================
* @Func_name	: MCAL_TIMER0_SingleIntervalDelayms
* @brief		  : Function to delay the TIMER0 for a certain amount of time without halting the CPU.
* @param [in]	: copy_Milliseconds number of milliseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER0_SingleIntervalDelayms(uint32_t copy_Milliseconds, Ptr_Func func)
{
    sTIMER0_Config_t Timer0_cfg;
    uint8_t LOC_u8CompareValue;

    Timer0_cfg.TIMER0_CLK_SRC = TIMER0_Prescale_64;
    Timer0_cfg.TIMER0_Mode = TIMER0_CTC_Mode;
    Timer0_cfg.TIMER0_COM = TIMER0_COM_Disconnected;
    Timer0_cfg.TIMER0_OCIE = TIMER0_TOCI_Enable;
    Timer0_cfg.TIMER0_OIE = TIMER0_TOI_Disable;

    /*Delay of one millisecond*/
    LOC_u8CompareValue = (uint8_t)(((F_CPU / 1000) / 64) - 1);
    MCAL_TIMER0_SetCompare(LOC_u8CompareValue);
    MCAL_TIMER0_SetCounter(0x00);
    
    MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(Timer0_SingleIntervalDelayCallback);    

    Glob_u32DelayInMilliseconds = copy_Milliseconds;
    Glob_fptrInterruptedDelayCallback = func;
    MCAL_TIMER0_Init(&Timer0_cfg);
}


/**
======================================================================================================================
* @Func_name	: MCAL_TIMER0_BusyWaitDelayus
* @brief		  : Function to delay the timer for a certain amount of time.
* @param [in]	: copy_Microseconds number of microseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER0_BusyWaitDelayus(uint32_t copy_Microseconds)
{
    sTIMER0_Config_t Timer0_cfg;
    uint8_t LOC_u8CompareValue;
    uint32_t LOC_u32CTCcounter = 0;

    Timer0_cfg.TIMER0_CLK_SRC = TIMER0_Prescale_1;
    Timer0_cfg.TIMER0_Mode = TIMER0_CTC_Mode;
    Timer0_cfg.TIMER0_COM = TIMER0_COM_Disconnected;
    Timer0_cfg.TIMER0_OCIE = TIMER0_TOCI_Disable;
    Timer0_cfg.TIMER0_OIE = TIMER0_TOI_Disable;

    /*Delay of one millisecond*/
    LOC_u8CompareValue = (uint8_t)(((F_CPU / 1000000)) - 1);
    MCAL_TIMER0_SetCompare(LOC_u8CompareValue);

    MCAL_TIMER0_Init(&Timer0_cfg);
    
    copy_Microseconds = (copy_Microseconds / 2) + 1;

    while(LOC_u32CTCcounter < copy_Microseconds)
    {
        while(!READ_BIT(TIFR, TIMER0_TIFR_OCF0_POS));

        LOC_u32CTCcounter++;
        
        /*Clear the flag*/
        SET_BIT(TIFR, TIMER0_TIFR_OCF0_POS);
    }

}


/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT
* @brief		:   Set the overflow interrupt callback function.
* @param [in]	:   callback: the overflow interrupt callback function.
======================================================================================================================
*/
void MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback)
{
    overflowCallback = callback;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT
* @brief		:   Set the output compare match interrupt callback function.
* @param [in]	:   callback: the output compare match interrupt callback function.
======================================================================================================================
*/
void MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback)
{
    outputCompareMatchCallback = callback;
}


/**************************************************************************************************************************
===============================================
*               Timer0 ISR functions
*===============================================
*/

/*Timer/Counter0 Compare Match (Vector number in the datasheet - 1)*/
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){
    
    outputCompareMatchCallback();
}

/*Timer/Counter0 Overflow*/
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void){

    overflowCounter++;
    overflowCallback();
}
