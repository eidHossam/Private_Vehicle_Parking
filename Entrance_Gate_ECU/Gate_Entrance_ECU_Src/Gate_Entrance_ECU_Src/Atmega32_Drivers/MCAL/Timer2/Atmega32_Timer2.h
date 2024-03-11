/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the TIMER2 module.
* Author    : Hossam Eid
* Created on: 1/12/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the TIMER2 driver.
**************************************************************************************************************************
*/

#ifndef ATMEGA32_TIMER2_H_
#define ATMEGA32_TIMER2_H_

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

/*----------- @ref Timer2_CLK_DEFINE ----------------*/
enum Timer2_CLK_SRC{
    Timer2_no_CLK_SRC,                   /*!< No clock source (Timer2/Counter stopped).*/   
    Timer2_Prescale_1,                   /*!< clkI/O/1 (No prescaling)*/
    Timer2_Prescale_8,                   /*!< clkI/O/8 (From prescaler)*/
    Timer2_Prescale_32,                   /*!< clkI/O/8 (From prescaler)*/
    Timer2_Prescale_64,                  /*!< clkI/O/64 (From prescaler)*/
    Timer2_Prescale_128,                  /*!< clkI/O/64 (From prescaler)*/
    Timer2_Prescale_256,                 /*!< clkI/O/256 (From prescaler)*/
    Timer2_Prescale_1024,                /*!< clkI/O/1024 (From prescaler)*/
    Timer2_EXT_CLK_Falling,              /*!< External clock source on T0 pin. Clock on falling edge.*/
    Timer2_EXT_CLK_Rising                /*!< External clock source on T0 pin. Clock on rising edge.*/
};
#define ASSERT_Timer2_CLK(CLK)  (Timer2_no_CLK_SRC <= CLK &&  \
                               (Timer2_EXT_CLK_Rising >= CLK))

/*----------- @ref Timer2_DEFINE_MODE ----------------*/
enum Timer2_Mode{
    Timer2_Normal_Mode,                                          /*!< Timer2 in normal operating mode*/   
    Timer2_PWM_Mode      = TIMER2_TCCR_WGM0_MASK,                     /*!< Timer2 in PWM mode */
    Timer2_CTC_Mode      = TIMER2_TCCR_WGM1_MASK,                     /*!< Timer2 in Clear On Compare Match mode */
    Timer2_FAST_PWM_Mode = (TIMER2_TCCR_WGM0_MASK |              /*!< Timer2 in fast PWM mode */
                           TIMER2_TCCR_WGM1_MASK)                     

};
#define ASSERT_Timer2_MODE(mode) ((Timer2_Normal_Mode     == mode)    || \
                                 (Timer2_CTC_Mode        == mode)    || \
                                 (Timer2_PWM_Mode        == mode)    || \
                                 (Timer2_FAST_PWM_Mode   == mode))


/*----------- @ref Timer2_COM_DEFINE ----------------*/
/** @defgroup Non-PWM Mode
  * @{
  */
 /**
 * Timer2_COM                    Description
 * Timer2_COM_Disconnected : Normal port operation, OC0 disconnected.
 * Timer2_COM_Toggle       : Toggle OC0 on Compare Match
 * Timer2_COM_Clear        : Clear OC0 on Compare Match
 * Timer2_COM_Set          : Set OC0 on Compare Match
 */
/**
  * @}
  */

/** @defgroup Fast PWM mode
  * @{
  */
 /**
 * Timer2_COM                    Description
 * Timer2_COM_Disconnected : Normal port operation, OC0 disconnected.
 * Timer2_COM_Clear        : Clear OC0 on Compare Match, set OC0 at BOTTOM, ((non-inverting mode)
 * Timer2_COM_Set          : Set OC0 on Compare Match, clear OC0 at BOTTOM, (inverting mode)
 */
/**
  * @}
  */

/** @defgroup  PWM mode
  * @{
  */
 /**
 * Timer2_COM                    Description
 * Timer2_COM_Disconnected : Normal port operation, OC0 disconnected.
 * Timer2_COM_Clear        : Clear OC0 on Compare Match when up-counting. Set OC0 on Compare Match when downcounting
 * Timer2_COM_Set          : Set OC0 on Compare Match when up-counting. Clear OC0 on Compare Match when downcounting.
 */
/**
  * @}
  */


enum Timer2_COM{
    Timer2_COM_Disconnected,                                       /*!< Normal port operation, OC0 disconnected*/   
    Timer2_COM_Toggle    = TIMER2_TCCR_COM0_MASK,                  /*!< Toggle OC0 on Compare Match*/
    Timer2_COM_Clear     = TIMER2_TCCR_COM1_MASK,                  /*!< Clear OC0 on Compare Match */
    Timer2_COM_Set       = TIMER2_TCCR_COM_MASK                    /*!< Set OC0 on Compare Match */
};
#define ASSERT_Timer2_COM(com)  ((Timer2_COM_Disconnected == com)     || \
                                (Timer2_COM_Toggle       == com)     || \
                                (Timer2_COM_Clear        == com)     || \
                                (Timer2_COM_Set          == com))      


/*----------- @ref Timer2_TOIE_DEFINE ----------------*/
enum Timer2_TOIE{
    Timer2_TOI_Disable,                                              /*!< Timer2 Overflow interrupt disable */
    Timer2_TOI_Enable = TIMER2_TIMSK_TOIE2_MASK,                     /*!< Timer2 Overflow interrupt enable*/   
};
#define ASSERT_Timer2_TOIE(TOIE) ((Timer2_TOI_Disable == TOIE)     || \
                                 (Timer2_TOI_Enable  == TOIE))


/*----------- @ref Timer2_TOCIE_DEFINE ----------------*/
enum Timer2_TOCIE{
    Timer2_TOCI_Disable,                                          /*!< Timer2 Output compare match interrupt disable */
    Timer2_TOCI_Enable = TIMER2_TIMSK_OCIE2_MASK,                 /*!< Timer2 Output compare match interrupt enable*/   
};

#define ASSERT_Timer2_TOCIE(TOCIE) ((Timer2_TOCI_Disable == TOCIE)     || \
                                  (Timer2_TOCI_Enable  == TOCIE))

/**************************************************************************************************************************
*===============================================
* User type definitions (structures)
*===============================================
*/

typedef struct{
    enum Timer2_CLK_SRC  Timer2_CLK_SRC;        /*!<Specifies the input clock source of the Timer2
                                            This parameter must be a value of @ref Timer2_CLK_DEFINE*/

    enum Timer2_Mode   Timer2_Mode;             /*Specifies the operation mode of the Timer2 peripheral
                                            This parameter must be a value of @ref Timer2_DEFINE_MODE*/

    enum Timer2_COM   Timer2_COM;              /*Specifies the output compare pin (OC0) behavior
                                            This parameter must be a value of @ref Timer2_COM_DEFINE*/   

    enum Timer2_TOIE  Timer2_OIE;              /*Specifies if the overflow interrupt should be enabled
                                            This parameter   must be a value of @ref Timer2_TOIE_DEFINE*/  
   
    enum Timer2_TOCIE Timer2_OCIE;              /*Specifies if the output compare match interrupt should be enabled 
                                            This parameter must be a value of @ref Timer2_TOCIE_DEFINE*/  
}sTIMER2_Config_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL TIMER2 DRIVER"
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_Init
* @brief		  :   Intializes the Timer2 peripheral with the specified parameters in the config struct.
* @param [in]	:   Timer2CFG: Configuration structure.
* @return     :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_Init(sTIMER2_Config_t* Timer2CFG);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_Stop
* @brief		:   Stop the Timer2 peripheral from counting.
* @Note         :   This function doesn't reset the peripheral it only stops the counting process.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_Stop();

/**
======================================================================================================================
* @Func_name	  :   MCAL_TIMER2_Start
* @brief		    :   start the counter from the same value we Stopped at.
* @Note         :   none.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_Start();

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_GetCompare
* @brief		:   Get the value stored in the output compare register.
* @param [out]	:   compareVal: pointer to store the returned value in.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_GetCompare(uint8_t* compareVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_SetCompare
* @brief		:   Set the value of the output compare register.
* @param [in]	:   compareVal: The value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_SetCompare(uint8_t compareVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_GetCounter
* @brief		:   Get the value stored in the counter register.
* @param [out]	:   counterVal: pointer to store the returned value in.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_GetCounter(uint8_t* counterVal);
/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_SetCounter
* @brief		:   Set the value of the counter register.
* @param [in]	:   counterVal: The value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_SetCounter(uint8_t counterVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_GetOverflow
* @brief		:   Get the number of overflows value.
* @param [out]	:   overflowVal:  pointer to store the returned value in
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_GetOverflow(uint32_t* overflowVal);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_SetOverflow
* @brief		:   Set the value of the overflow.
* @param [in]	:   overflowVal: value to be set.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER2_SetOverflow(uint32_t overflowVal);

/**
======================================================================================================================
* @Func_name	: MCAL_TIMER2_Delayms
* @brief		  : Function to delay the Timer2 for a certain amount of time.
* @param [in]	: copy_Milliseconds number of milliseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER2_BusyWaitDelayms(uint32_t copy_Milliseconds);


/**
======================================================================================================================
* @Func_name	: MCAL_TIMER2_Delayus
* @brief		  : Function to delay the Timer2 for a certain amount of time.
* @param [in]	: copy_Microeconds number of microseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER2_BusyWaitDelayus(uint32_t copy_Microeconds);


/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_CALLBACK_Overflow_INTERRUPT
* @brief		:   Set the overflow interrupt callback function.
* @param [in]	:   callback: the overflow interrupt callback function.
======================================================================================================================
*/
void MCAL_TIMER2_CALLBACK_Overflow_INTERRUPT(Ptr_Func callback);
/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER2_CALLBACK_CompareMatch_INTERRUPT
* @brief		:   Set the output compare match interrupt callback function.
* @param [in]	:   callback: the output compare match interrupt callback function.
======================================================================================================================
*/
void MCAL_TIMER2_CALLBACK_CompareMatch_INTERRUPT(Ptr_Func callback);

#endif /* ATMEGA32_TIMER2_H_ */