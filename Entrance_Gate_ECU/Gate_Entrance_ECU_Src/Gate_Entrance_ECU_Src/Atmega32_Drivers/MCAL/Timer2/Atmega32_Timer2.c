/**
**************************************************************************************************************************
* @brief     : This module contains functions for configuring and controlling the Timer2 module.
* @author    : Hossam Eid
* @date      : 1/12/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the Timer2 driver.
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32_Timer2.h"

/** @defgroup Private Macros and defines
  * @{
  */

#define Timer2_OC0_PORT       GPIOB
#define Timer2_OC0_PIN        GPIO_PIN3
/**
  * @}
  */

/** @defgroup Global variables
  * @{
  */
static sTIMER2_Config_t Timer2_CFG;

static uint32_t overflowCounter = 0;

static Ptr_Func overflowCallback;
static Ptr_Func outputCompareMatchCallback;

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
* @Func_name	:   MCAL_TIMER2_Init
* @brief		:   Intializes the timer peripheral with the specified parameters in the config struct.
* @param [in]	:   timerCFG: Configuration structure.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_Init(sTIMER2_Config_t* timerCFG)
{
    eStatus_t status = E_OK;

    if(NULL == timerCFG)
    {
        status = E_NOK;
    
    }/*Assert all the parameters in the configuration struct*/
    else if(!ASSERT_Timer2_CLK(timerCFG->Timer2_CLK_SRC) || !ASSERT_Timer2_MODE(timerCFG->Timer2_Mode) ||
            !ASSERT_Timer2_COM(timerCFG->Timer2_COM)     || !ASSERT_Timer2_TOIE(timerCFG->Timer2_OIE)  ||
            !ASSERT_Timer2_TOCIE(timerCFG->Timer2_OCIE)){
                
        status = E_NOK;
    }else{

        /*Store the configuration struct for later use*/
        Timer2_CFG = * timerCFG;

        /*Clear the register*/
        TIMER2->TCCR2 = 0;
        
        TIMER2->TCCR2 = ((timerCFG->Timer2_CLK_SRC) | (timerCFG->Timer2_Mode) | (timerCFG->Timer2_COM)) ;

        /*Clear the interrupt mask bits*/
        TIMSK &= ~(TIMER2_TIMSK_OCIE2_MASK | TIMER2_TIMSK_OCIE2_MASK);
        TIMSK |= ((timerCFG->Timer2_OIE) | (timerCFG->Timer2_OCIE));

        if(Timer2_COM_Disconnected != timerCFG->Timer2_COM)
        {
            /*
            *   the Data Direction Register (DDR) bit corresponding to the OC0 
            *   pin must be set in order to enable the output driver.
            */
            GPIO_Pin_Config_t cfg = {Timer2_OC0_PIN, GPIO_MODE_OUTPUT};
            MCAL_GPIO_Init(Timer2_OC0_PORT, &cfg);
        }

        if((Timer2_TOCI_Enable == timerCFG->Timer2_OCIE) || (Timer2_TOI_Enable == timerCFG->Timer2_OIE))
        {
            /*Enable the global interrupt*/
            G_INTERRUPT_ENABLE;
        }      
    }

    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_Stop
* @brief		:   Stop the Timer peripheral from counting.
* @Note         :   This function doesn't reset the peripheral it only stops the counting process.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_Stop()
{
    eStatus_t status = E_OK;

    /*Disable the clock to stop the timer*/
    TIMER2->TCCR2 &= ~(TIMER2_TCCR_CS_MASK);

    return status;
}

/**
======================================================================================================================
* @Func_name	  :   MCAL_TIMER2_Start
* @brief		    :   start the counter from the same value we Stopped at.
* @Note         :   none.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_Start()
{
    eStatus_t status = E_OK;

    /*Enable the clock to start the timer*/
    TIMER2->TCCR2 |= Timer2_CFG.Timer2_CLK_SRC;

    return status;
}


/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_GetCompare
* @brief		:   Get the value stored in the output compare register.
* @param [out]	:   compareVal: pointer to store the returned value in.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_GetCompare(uint8_t* compareVal)
{
    eStatus_t status = E_OK;
    *compareVal = TIMER2->OCR2;
    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_SetCompare
* @brief		:   Set the value of the output compare register.
* @param [in]	:   compareVal: The value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_SetCompare(uint8_t compareVal)
{
    eStatus_t status = E_OK;
    TIMER2->OCR2 = compareVal;
    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_GetCounter
* @brief		:   Get the value stored in the counter register.
* @param [out]	:   counterVal: pointer to store the returned value in.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_GetCounter(uint8_t* counterVal)
{
    eStatus_t status = E_OK;
    *counterVal = TIMER2->TCNT2;
    return status;

}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_SetCounter
* @brief		:   Set the value of the counter register.
* @param [in]	:   counterVal: The value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_SetCounter(uint8_t counterVal)
{
    eStatus_t status = E_OK;
    TIMER2->TCNT2 = counterVal;
    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_GetOverflow
* @brief		:   Get the number of overflows value.
* @param [out]	:   overflowVal:  pointer to store the returned value in
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_GetOverflow(uint32_t* overflowVal)
{
    eStatus_t status = E_OK;
    *overflowVal = overflowCounter;
    return status;

}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_SetOverflow
* @brief		:   Set the value of the overflow.
* @param [in]	:   overflowVal: value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_SetOverflow(uint32_t overflowVal)
{
    eStatus_t status = E_OK;
    overflowCounter = overflowVal;
    return status;

}

/**
======================================================================================================================
* @Func_name	: MCAL_TIMER2_Delayms
* @brief		  : Function to delay the timer for a certain amount of time.
* @param [in]	: copy_Milliseconds number of milliseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER2_BusyWaitDelayms(uint32_t copy_Milliseconds)
{
    sTIMER2_Config_t Timer2_Config;
    uint8_t LOC_u8CompareValue;
    uint32_t LOC_u32CTCcounter = 0;

    Timer2_Config.Timer2_CLK_SRC = Timer2_Prescale_64;
    Timer2_Config.Timer2_Mode = Timer2_CTC_Mode;
    Timer2_Config.Timer2_COM = Timer2_COM_Disconnected;
    Timer2_Config.Timer2_OCIE = Timer2_TOCI_Disable;
    Timer2_Config.Timer2_OIE = Timer2_TOI_Disable;

    /*Delay of one millisecond*/
    LOC_u8CompareValue = (uint8_t)(((F_CPU / 1000) / 64) - 1);
    MCAL_TIMER2_SetCompare(LOC_u8CompareValue);

    MCAL_TIMER2_Init(&Timer2_Config);

    while(LOC_u32CTCcounter < copy_Milliseconds)
    {
        while(!READ_BIT(TIFR, TIMER2_TIFR_OCF2_POS));

        LOC_u32CTCcounter++;
        
        /*Clear the flag*/
        SET_BIT(TIFR, TIMER2_TIFR_OCF2_POS);
    }

}

/**
======================================================================================================================
* @Func_name	: MCAL_TIMER2_Delayus
* @brief		  : Function to delay the timer for a certain amount of time.
* @param [in]	: copy_Microseconds number of microseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER2_BusyWaitDelayus(uint32_t copy_Microseconds)
{
    sTIMER2_Config_t Timer2_Config;
    uint8_t LOC_u8CompareValue;
    uint32_t LOC_u32CTCcounter = 0;

    Timer2_Config.Timer2_CLK_SRC = Timer2_Prescale_1;
    Timer2_Config.Timer2_Mode = Timer2_CTC_Mode;
    Timer2_Config.Timer2_COM = Timer2_COM_Disconnected;
    Timer2_Config.Timer2_OCIE = Timer2_TOCI_Disable;
    Timer2_Config.Timer2_OIE = Timer2_TOI_Disable;

    /*Delay of one microsecond*/
    LOC_u8CompareValue = (uint8_t)(((F_CPU / 1000000)) - 1);
    MCAL_TIMER2_SetCompare(LOC_u8CompareValue);

    MCAL_TIMER2_Init(&Timer2_Config);

    copy_Microseconds = (copy_Microseconds / 2) + 1;
    while(LOC_u32CTCcounter < copy_Microseconds)
    {
        while(!READ_BIT(TIFR, TIMER2_TIFR_OCF2_POS));

        LOC_u32CTCcounter++;
        
        /*Clear the flag*/
        SET_BIT(TIFR, TIMER2_TIFR_OCF2_POS);
    }

}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_CALLBACK_Overflow_INTERRUPT
* @brief		:   Set the overflow interrupt callback function.
* @param [in]	:   callback: the overflow interrupt callback function.
======================================================================================================================
*/
void MCAL_TIMER2_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback)
{
    overflowCallback = callback;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_CALLBACK_CompareMatch_INTERRUPT
* @brief		:   Set the output compare match interrupt callback function.
* @param [in]	:   callback: the output compare match interrupt callback function.
======================================================================================================================
*/
void MCAL_TIMER2_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback)
{
    outputCompareMatchCallback = callback;
}


/**************************************************************************************************************************
===============================================
*               Timer2 ISR functions
*===============================================
*/

/*Timer/Counter2 Compare Match (Vector number in the datasheet - 1)*/
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void){
    
    outputCompareMatchCallback();
}

/*Timer/Counter2 Overflow*/
void __vector_5 (void) __attribute__((signal));
void __vector_5 (void){

    overflowCounter++;
    overflowCallback();
}
