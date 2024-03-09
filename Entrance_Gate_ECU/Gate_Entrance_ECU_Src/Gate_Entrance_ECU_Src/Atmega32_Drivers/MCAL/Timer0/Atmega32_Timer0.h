/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the Timer0 module.
* Author    : Hossam Eid
* Created on: 1/12/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the Timer0 driver.
**************************************************************************************************************************
*/

#ifndef ATMEGA32_TIMER0_H_
#define ATMEGA32_TIMER0_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32.h"
#include "GPIO/Atmega32_GPIO.h"

/**************************************************************************************************************************
*===============================================
*         Enum Configuration References
*===============================================
*/

/*----------- @ref TIMER_CLK_DEFINE ----------------*/
enum Timer_CLK_SRC{
    Timer_no_CLK_SRC,                   /*!< No clock source (Timer/Counter stopped).*/   
    Timer_Prescale_1,                   /*!< clkI/O/1 (No prescaling)*/
    Timer_Prescale_8,                   /*!< clkI/O/8 (From prescaler)*/
    Timer_Prescale_64,                  /*!< clkI/O/64 (From prescaler)*/
    Timer_Prescale_256,                 /*!< clkI/O/256 (From prescaler)*/
    Timer_Prescale_1024,                /*!< clkI/O/1024 (From prescaler)*/
    Timer_EXT_CLK_Falling,              /*!< External clock source on T0 pin. Clock on falling edge.*/
    Timer_EXT_CLK_Rising                /*!< External clock source on T0 pin. Clock on rising edge.*/
};
#define ASSERT_TIMER_CLK(CLK)  (Timer_no_CLK_SRC <= CLK &&  \
                               (Timer_EXT_CLK_Rising >= CLK))

/*----------- @ref TIMER_DEFINE_MODE ----------------*/
enum Timer_Mode{
    Timer_Normal_Mode,                                          /*!< Timer in normal operating mode*/   
    Timer_PWM_Mode = TIMER0_TCCR_WGM0_MASK,                     /*!< Timer in PWM mode */
    Timer_CTC_Mode = TIMER0_TCCR_WGM1_MASK,                     /*!< Timer in Clear On Compare Match mode */
    Timer_FAST_PWM_Mode = (TIMER0_TCCR_WGM0_MASK |              /*!< Timer in fast PWM mode */
                           TIMER0_TCCR_WGM1_MASK)                     

};
#define ASSERT_TIMER_MODE(mode) ((Timer_Normal_Mode     == mode)    || \
                                 (Timer_CTC_Mode        == mode)    || \
                                 (Timer_PWM_Mode        == mode)    || \
                                 (Timer_FAST_PWM_Mode   == mode))


/*----------- @ref TIMER_COM_DEFINE ----------------*/
/** @defgroup Non-PWM Mode
  * @{
  */
 /**
 * Timer_COM                    Description
 * Timer_COM_Disconnected : Normal port operation, OC0 disconnected.
 * Timer_COM_Toggle       : Toggle OC0 on Compare Match
 * Timer_COM_Clear        : Clear OC0 on Compare Match
 * Timer_COM_Set          : Set OC0 on Compare Match
 */
/**
  * @}
  */

/** @defgroup Fast PWM mode
  * @{
  */
 /**
 * Timer_COM                    Description
 * Timer_COM_Disconnected : Normal port operation, OC0 disconnected.
 * Timer_COM_Clear        : Clear OC0 on Compare Match, set OC0 at BOTTOM, ((non-inverting mode)
 * Timer_COM_Set          : Set OC0 on Compare Match, clear OC0 at BOTTOM, (inverting mode)
 */
/**
  * @}
  */

/** @defgroup  PWM mode
  * @{
  */
 /**
 * Timer_COM                    Description
 * Timer_COM_Disconnected : Normal port operation, OC0 disconnected.
 * Timer_COM_Clear        : Clear OC0 on Compare Match when up-counting. Set OC0 on Compare Match when downcounting
 * Timer_COM_Set          : Set OC0 on Compare Match when up-counting. Clear OC0 on Compare Match when downcounting.
 */
/**
  * @}
  */


enum Timer_COM{
    Timer_COM_Disconnected,                                       /*!< Normal port operation, OC0 disconnected*/   
    Timer_COM_Toggle    = TIMER0_TCCR_COM0_MASK,                  /*!< Toggle OC0 on Compare Match*/
    Timer_COM_Clear     = TIMER0_TCCR_COM1_MASK,                  /*!< Clear OC0 on Compare Match */
    Timer_COM_Set       = TIMER0_TCCR_COM_MASK                    /*!< Set OC0 on Compare Match */
};
#define ASSERT_TIMER_COM(com)  ((Timer_COM_Disconnected == com)     || \
                                (Timer_COM_Toggle       == com)     || \
                                (Timer_COM_Clear        == com)     || \
                                (Timer_COM_Set          == com))      


/*----------- @ref TIMER_TOIE_DEFINE ----------------*/
enum Timer_TOIE{
    Timer_TOI_Disable,                                              /*!< Timer Overflow interrupt disable */
    Timer_TOI_Enable = TIMER0_TIMSK_TOIE0_MASK,                     /*!< Timer Overflow interrupt enable*/   
};
#define ASSERT_TIMER_TOIE(TOIE) ((Timer_TOI_Disable == TOIE)     || \
                                 (Timer_TOI_Enable  == TOIE))


/*----------- @ref TIMER_TOCIE_DEFINE ----------------*/
enum Timer_TOCIE{
    Timer_TOCI_Disable,                                          /*!< Timer Output compare match interrupt disable */
    Timer_TOCI_Enable = TIMER0_TIMSK_OCIE0_MASK,                 /*!< Timer Output compare match interrupt enable*/   
};

#define ASSERT_TIMER_TOCIE(TOCIE) ((Timer_TOCI_Disable == TOCIE)     || \
                                  (Timer_TOCI_Enable  == TOCIE))

/**************************************************************************************************************************
*===============================================
* User type definitions (structures)
*===============================================
*/

typedef struct{
    enum Timer_CLK_SRC  Timer_CLK_SRC;        /*!<Specifies the input clock source of the timer
                                            This parameter must be a value of @ref TIMER_CLK_DEFINE*/

    enum Timer_Mode   Timer_Mode;             /*Specifies the operation mode of the timer peripheral
                                            This parameter must be a value of @ref TIMER_DEFINE_MODE*/

    enum Timer_COM   Timer_COM;              /*Specifies the output compare pin (OC0) behavior
                                            This parameter must be a value of @ref TIMER_COM_DEFINE*/   

    enum Timer_TOIE  Timer_OIE;              /*Specifies if the overflow interrupt should be enabled
                                            This parameter   must be a value of @ref TIMER_TOIE_DEFINE*/  
   
    enum Timer_TOCIE Timer_OCIE;              /*Specifies if the output compare match interrupt should be enabled 
                                            This parameter must be a value of @ref TIMER_TOCIE_DEFINE*/  
}sTimer0_Config_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL Timer0 DRIVER"
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_Init
* @brief		  :   Intializes the timer peripheral with the specified parameters in the config struct.
* @param [in]	:   timerCFG: Configuration structure.
* @return     :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_Init(sTimer0_Config_t* timerCFG);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_Stop
* @brief		:   Stop the Timer peripheral from counting.
* @Note         :   This function doesn't reset the peripheral it only stops the counting process.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_Stop();

/**
======================================================================================================================
* @Func_name	  :   MCAL_TIMER0_Start
* @brief		    :   start the counter from the same value we Stopped at.
* @Note         :   none.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_Start();

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_GetCompare
* @brief		:   Get the value stored in the output compare register.
* @param [out]	:   compareVal: pointer to store the returned value in.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_GetCompare(uint8_t* compareVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_SetCompare
* @brief		:   Set the value of the output compare register.
* @param [in]	:   compareVal: The value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_SetCompare(uint8_t compareVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_GetCounter
* @brief		:   Get the value stored in the counter register.
* @param [out]	:   counterVal: pointer to store the returned value in.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_GetCounter(uint8_t* counterVal);
/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_SetCounter
* @brief		:   Set the value of the counter register.
* @param [in]	:   counterVal: The value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_SetCounter(uint8_t counterVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_GetOverflow
* @brief		:   Get the number of overflows value.
* @param [out]	:   overflowVal:  pointer to store the returned value in
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_GetOverflow(uint32_t* overflowVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_SetOverflow
* @brief		:   Set the value of the overflow.
* @param [in]	:   overflowVal: value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_SetOverflow(uint32_t overflowVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT
* @brief		:   Set the overflow interrupt callback function.
* @param [in]	:   callback: the overflow interrupt callback function.
======================================================================================================================
*/
void MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback);
/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT
* @brief		:   Set the output compare match interrupt callback function.
* @param [in]	:   callback: the output compare match interrupt callback function.
======================================================================================================================
*/
void MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback);

#endif /* ATMEGA32_TIMER0_H_ */