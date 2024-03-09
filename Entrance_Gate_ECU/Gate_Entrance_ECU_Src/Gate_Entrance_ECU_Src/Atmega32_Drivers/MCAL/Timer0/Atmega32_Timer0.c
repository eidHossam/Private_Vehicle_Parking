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
sTimer0_Config_t timer0_CFG;

uint32_t overflowCounter = 0;

Ptr_Func overflowCallback;
Ptr_Func outputCompareMatchCallback;

/**
  * @}
  */

/** @defgroup Local functions
  * @{
  */


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
eStatus_t MCAL_TIMER0_Init(sTimer0_Config_t* timerCFG)
{
    eStatus_t status = E_OK;

    if(NULL == timerCFG)
    {
        status = E_NOK;
    
    }/*Assert all the parameters in the configuration struct*/
    else if(!ASSERT_TIMER_CLK(timerCFG->Timer_CLK_SRC) || !ASSERT_TIMER_MODE(timerCFG->Timer_Mode) ||
            !ASSERT_TIMER_COM(timerCFG->Timer_COM)     || !ASSERT_TIMER_TOIE(timerCFG->Timer_OIE)  ||
            !ASSERT_TIMER_TOCIE(timerCFG->Timer_OCIE)){
                
        status = E_NOK;
    }else{

        /*Store the configuration struct for later use*/
        timer0_CFG = * timerCFG;

        /*Clear the register*/
        TIMER0->TCCR0 = 0;
        
        TIMER0->TCCR0 = ((timerCFG->Timer_CLK_SRC) | (timerCFG->Timer_Mode) | (timerCFG->Timer_COM)) ;

        /*Clear the interrupt mask bits*/
        TIMSK &= ~(TIMER0_TIMSK_OCIE0_MASK | TIMER0_TIMSK_TOIE0_MASK);
        TIMSK |= ((timerCFG->Timer_OIE) | (timerCFG->Timer_OCIE));

        if(Timer_COM_Disconnected != timerCFG->Timer_COM)
        {
            /*
            *   the Data Direction Register (DDR) bit corresponding to the OC0 
            *   pin must be set in order to enable the output driver.
            */
            GPIO_Pin_Config_t cfg = {TIMER0_OC0_PIN, GPIO_MODE_OUTPUT};
            MCAL_GPIO_Init(TIMER0_OC0_PORT, &cfg);
        }

        if((Timer_TOCI_Enable == timerCFG->Timer_OCIE) || (Timer_TOI_Enable == timerCFG->Timer_OIE))
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
    TIMER0->TCCR0 |= timer0_CFG.Timer_CLK_SRC;

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
