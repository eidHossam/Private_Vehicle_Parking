/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the TIMER0 module.
* Author    : Hossam Eid
* Created on: 1/12/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the TIMER0 driver.
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

/*----------- @ref TIMER0_CLK_DEFINE ----------------*/
enum TIMER0_CLK_SRC{
    TIMER0_no_CLK_SRC,                   /*!< No clock source (TIMER0/Counter stopped).*/   
    TIMER0_Prescale_1,                   /*!< clkI/O/1 (No prescaling)*/
    TIMER0_Prescale_8,                   /*!< clkI/O/8 (From prescaler)*/
    TIMER0_Prescale_64,                  /*!< clkI/O/64 (From prescaler)*/
    TIMER0_Prescale_256,                 /*!< clkI/O/256 (From prescaler)*/
    TIMER0_Prescale_1024,                /*!< clkI/O/1024 (From prescaler)*/
    TIMER0_EXT_CLK_Falling,              /*!< External clock source on T0 pin. Clock on falling edge.*/
    TIMER0_EXT_CLK_Rising                /*!< External clock source on T0 pin. Clock on rising edge.*/
};
#define ASSERT_TIMER0_CLK(CLK)  (TIMER0_no_CLK_SRC <= CLK &&  \
                               (TIMER0_EXT_CLK_Rising >= CLK))

/*----------- @ref TIMER0_DEFINE_MODE ----------------*/
enum TIMER0_Mode{
    TIMER0_Normal_Mode,                                          /*!< TIMER0 in normal operating mode*/   
    TIMER0_PWM_Mode = TIMER0_TCCR_WGM0_MASK,                     /*!< TIMER0 in PWM mode */
    TIMER0_CTC_Mode = TIMER0_TCCR_WGM1_MASK,                     /*!< TIMER0 in Clear On Compare Match mode */
    TIMER0_FAST_PWM_Mode = (TIMER0_TCCR_WGM0_MASK |              /*!< TIMER0 in fast PWM mode */
                           TIMER0_TCCR_WGM1_MASK)                     

};
#define ASSERT_TIMER0_MODE(mode) ((TIMER0_Normal_Mode     == mode)    || \
                                 (TIMER0_CTC_Mode        == mode)    || \
                                 (TIMER0_PWM_Mode        == mode)    || \
                                 (TIMER0_FAST_PWM_Mode   == mode))


/*----------- @ref TIMER0_COM_DEFINE ----------------*/
/** @defgroup Non-PWM Mode
  * @{
  */
 /**
 * TIMER0_COM                    Description
 * TIMER0_COM_Disconnected : Normal port operation, OC0 disconnected.
 * TIMER0_COM_Toggle       : Toggle OC0 on Compare Match
 * TIMER0_COM_Clear        : Clear OC0 on Compare Match
 * TIMER0_COM_Set          : Set OC0 on Compare Match
 */
/**
  * @}
  */

/** @defgroup Fast PWM mode
  * @{
  */
 /**
 * TIMER0_COM                    Description
 * TIMER0_COM_Disconnected : Normal port operation, OC0 disconnected.
 * TIMER0_COM_Clear        : Clear OC0 on Compare Match, set OC0 at BOTTOM, ((non-inverting mode)
 * TIMER0_COM_Set          : Set OC0 on Compare Match, clear OC0 at BOTTOM, (inverting mode)
 */
/**
  * @}
  */

/** @defgroup  PWM mode
  * @{
  */
 /**
 * TIMER0_COM                    Description
 * TIMER0_COM_Disconnected : Normal port operation, OC0 disconnected.
 * TIMER0_COM_Clear        : Clear OC0 on Compare Match when up-counting. Set OC0 on Compare Match when downcounting
 * TIMER0_COM_Set          : Set OC0 on Compare Match when up-counting. Clear OC0 on Compare Match when downcounting.
 */
/**
  * @}
  */


enum TIMER0_COM{
    TIMER0_COM_Disconnected,                                       /*!< Normal port operation, OC0 disconnected*/   
    TIMER0_COM_Toggle    = TIMER0_TCCR_COM0_MASK,                  /*!< Toggle OC0 on Compare Match*/
    TIMER0_COM_Clear     = TIMER0_TCCR_COM1_MASK,                  /*!< Clear OC0 on Compare Match */
    TIMER0_COM_Set       = TIMER0_TCCR_COM_MASK                    /*!< Set OC0 on Compare Match */
};
#define ASSERT_TIMER0_COM(com)  ((TIMER0_COM_Disconnected == com)     || \
                                (TIMER0_COM_Toggle       == com)     || \
                                (TIMER0_COM_Clear        == com)     || \
                                (TIMER0_COM_Set          == com))      


/*----------- @ref TIMER0_TOIE_DEFINE ----------------*/
enum TIMER0_TOIE{
    TIMER0_TOI_Disable,                                              /*!< TIMER0 Overflow interrupt disable */
    TIMER0_TOI_Enable = TIMER0_TIMSK_TOIE0_MASK,                     /*!< TIMER0 Overflow interrupt enable*/   
};
#define ASSERT_TIMER0_TOIE(TOIE) ((TIMER0_TOI_Disable == TOIE)     || \
                                 (TIMER0_TOI_Enable  == TOIE))


/*----------- @ref TIMER0_TOCIE_DEFINE ----------------*/
enum TIMER0_TOCIE{
    TIMER0_TOCI_Disable,                                          /*!< TIMER0 Output compare match interrupt disable */
    TIMER0_TOCI_Enable = TIMER0_TIMSK_OCIE0_MASK,                 /*!< TIMER0 Output compare match interrupt enable*/   
};

#define ASSERT_TIMER0_TOCIE(TOCIE) ((TIMER0_TOCI_Disable == TOCIE)     || \
                                  (TIMER0_TOCI_Enable  == TOCIE))

/**************************************************************************************************************************
*===============================================
* User type definitions (structures)
*===============================================
*/

typedef struct{
    enum TIMER0_CLK_SRC  TIMER0_CLK_SRC;        /*!<Specifies the input clock source of the TIMER0
                                            This parameter must be a value of @ref TIMER0_CLK_DEFINE*/

    enum TIMER0_Mode   TIMER0_Mode;             /*Specifies the operation mode of the TIMER0 peripheral
                                            This parameter must be a value of @ref TIMER0_DEFINE_MODE*/

    enum TIMER0_COM   TIMER0_COM;              /*Specifies the output compare pin (OC0) behavior
                                            This parameter must be a value of @ref TIMER0_COM_DEFINE*/   

    enum TIMER0_TOIE  TIMER0_OIE;              /*Specifies if the overflow interrupt should be enabled
                                            This parameter   must be a value of @ref TIMER0_TOIE_DEFINE*/  
   
    enum TIMER0_TOCIE TIMER0_OCIE;              /*Specifies if the output compare match interrupt should be enabled 
                                            This parameter must be a value of @ref TIMER0_TOCIE_DEFINE*/  
}sTIMER0_Config_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL TIMER0 DRIVER"
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_Init
* @brief		  :   Intializes the TIMER0 peripheral with the specified parameters in the config struct.
* @param [in]	:   TIMER0CFG: Configuration structure.
* @return     :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_TIMER0_Init(sTIMER0_Config_t* TIMER0CFG);

/**
======================================================================================================================
* @Func_name	:   MCAL_TIMER0_Stop
* @brief		:   Stop the TIMER0 peripheral from counting.
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
* @Func_name	: MCAL_TIMER0_Delayms
* @brief		  : Function to delay the TIMER0 for a certain amount of time.
* @param [in]	: copy_Milliseconds number of milliseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER0_BusyWaitDelayms(uint32_t copy_Milliseconds);

/**
======================================================================================================================
* @Func_name	: MCAL_TIMER0_SingleIntervalDelayms
* @brief		  : Function to delay the TIMER0 for a certain amount of time without halting the CPU.
* @param [in]	: copy_Milliseconds number of milliseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER0_SingleIntervalDelayms(uint32_t copy_Milliseconds, Ptr_Func func);

/**
======================================================================================================================
* @Func_name	: MCAL_TIMER02_Delayus
* @brief		  : Function to delay the TIMER0 for a certain amount of time.
* @param [in]	: copy_Microseconds number of microseconds to delay.
======================================================================================================================
*/
void MCAL_TIMER0_BusyWaitDelayus(uint32_t copy_Microseconds);

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