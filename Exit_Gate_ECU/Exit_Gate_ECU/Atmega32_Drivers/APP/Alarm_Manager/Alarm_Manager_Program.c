/**
 * @file Alarm_Manager_Program.c
 * 
 * @brief This file contains the implementation of the APIs for the Alarm Manager module
 *  controlling the LEDs and buzzer.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 12-03-2024
 * 
 * @version 1.0
 */

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Alarm_Manager_Interface.h"

/** @defgroup LOCAL_MACROS
  * @{
  */
#define FAILED_ID_ALARM_TOGGLE_COUNT    3

#define GREEN_LED_PORT                  GPIOC   
#define GREEN_LED_PIN                   GPIO_PIN0

#define RED_LED_PORT                    GPIOC   
#define RED_LED_PIN                     GPIO_PIN1

#define BUZZER_PORT                     GPIOC
#define BUZZER_PIN                      GPIO_PIN2
/**
  * @}
  */

/** @defgroup Global_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup ISR_CALLBACK
  * @{
  */
static void Timer0_DelayCallback(void)
{
    fptr_st_AlarmManager = st_AlarmManager_FailedIDAuthentication;
}

/**
  * @}
  */

/**************************************************************************************************************************
===============================================
*           States Definitions
*===============================================
*/

/**
 * @brief This state initializes the main components of the Alarm_Manager module.
 * 
 */
void st_AlarmManager_Init(void)
{

    /*Initialize the green LED used to indicate a successfull ID authentication*/
    HAL_LED_Init(GREEN_LED_PORT, GREEN_LED_PIN);

    /*Initialize the red LED used to indicate a failed ID authentication*/
    HAL_LED_Init(RED_LED_PORT, RED_LED_PIN);

    /*Initialize the buzzer HAL driver*/
    HAL_Buzzer_Init(BUZZER_PORT, BUZZER_PIN);

    /*Set the initial state of the module to be idle waiting for an incoming signal*/
    fptr_st_AlarmManager = st_AlarmManager_Idle;
}

/**
 * @brief this state makes the module go into idle mode until some user action is done.
 * 
 */
void st_AlarmManager_Idle(void)
{

}


/**
 * @brief This state indicates the driver that his ID is invalid.
 * 
 * @note This state toggles both the red LED and the buzzer 3 times.
 */
void st_AlarmManager_FailedIDAuthentication(void)
{
    static uint8_t LOC_u8ToggleCount = 0;

    /*Turn on both the red LED and the buzzer*/
    HAL_LED_ToggleState(RED_LED_PORT, RED_LED_PIN);
    HAL_Buzzer_ToggleState(BUZZER_PORT, BUZZER_PIN);

    if(LOC_u8ToggleCount == 0)
    {
        LCD_Clear_Screen();

        LCD_Cursor_XY(LCD_SECOND_LINE, 3);
        LCD_Send_String(stringfy("INVALID ID!"));
    }

    if(LOC_u8ToggleCount < FAILED_ID_ALARM_TOGGLE_COUNT)
    {
        MCAL_TIMER0_SingleIntervalDelayms(333, Timer0_DelayCallback);
        LOC_u8ToggleCount++;
    }else{

        LOC_u8ToggleCount = 0;

        AM_UAI_AlarmOff();
    }

    fptr_st_AlarmManager = st_AlarmManager_Idle;
}


/**
 * @brief This state informs the driver that his ID is valid.
 * 
 */
void st_AlarmManager_SuccessfullIDAuthentication(void)
{
    static uint8_t LOC_u8Counter = 0;
    eLEDStatus_t LOC_eLEDState;

    if(LOC_u8Counter == 0)
    {
        LCD_Clear_Screen();

        LCD_Cursor_XY(LCD_SECOND_LINE, 4);
        LCD_Send_String(stringfy("VALID ID!"));

        LOC_eLEDState = LED_On;

        LOC_u8Counter++;
    }else{
        LOC_eLEDState = LED_Off;

        LOC_u8Counter = 0;
    }

    HAL_LED_SetState(GREEN_LED_PORT, GREEN_LED_PIN, LOC_eLEDState);

    fptr_st_AlarmManager = st_AlarmManager_Idle;
}



/** @defgroup Signals between the Alarm_Manager and the User_Admin_Interface_Modules.
  * @{
  */

/**
 * @brief This is a signal from the User_Admin_Interface module to the Alarm_Manager module to inform
 * it that ID authentication process is a failure.
 * 
 */
void UAI_AM_InvalidID(void)
{
    fptr_st_AlarmManager = st_AlarmManager_FailedIDAuthentication;
}


/**
 * @brief This is a signal from the User_Admin_Interface module to the Alarm_Manager module to inform
 * it that ID authentication process is a failure.
 * 
 */
void UAI_AM_ValidID(void)
{
    fptr_st_AlarmManager =st_AlarmManager_SuccessfullIDAuthentication;
}


/**
 * @brief This is a signal from the User_Admin_Interface module to the Alarm_manager module to inform 
 * it that the car passed the gate and we need to turn off the alarm.
 * 
 */
void UAI_AM_TurnOffAlarmGateClosed(void)
{
    fptr_st_AlarmManager = st_AlarmManager_SuccessfullIDAuthentication;
}

/**
  * @}
  */