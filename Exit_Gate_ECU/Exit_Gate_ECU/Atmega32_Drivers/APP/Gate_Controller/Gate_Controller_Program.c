/**
 * @file Gate_Controller_Program.c
 * 
 * @brief This file contains the implementation of the APIs and functionality of the module controlling 
 * the exit gate.
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
#include "Gate_Controller_Interface.h"

/** @defgroup LOCAL_MACROS
  * @{
  */

/** @defgroup PIR CONFIGURATION
  * @{
  */
#define PIR_PORT        GPIOB
#define PIR_PIN         GPIO_PIN2
/**
  * @}
  */

/**
 * @brief Specifies the time the gate should stay open for in milliseconds.
 * 
 */
#define GATE_OPENED_TIME_MS             500

/**
  * @}
  */


/** @defgroup ISR_CALLBACK_FUNCTIONS
  * @{
  */
static void Timer0_DelaycheckCar_Callback(void)
{
    fptr_st_GateController = st_GateController_CheckCarPassed;
}

/**
  * @}
  */
/**************************************************************************************************************************
===============================================
*       States Definitions
*===============================================
*/

/**
 * @brief This state initializes the required peripherals in this module 
 * and sets the initial state of the module.
 * 
 */
void st_GateController_Init(void)
{
    /*Initialize the gates servo motor to be on the 0 degree position*/
    HAL_ServoMotorInit();
    
    /*Initialize the PIR sensor to detect when the car successfully passes the gate*/
    HAL_PIR_Init(PIR_PORT, PIR_PIN);

    /*Set the initial state to be idle until there is a request to be processed*/
    fptr_st_GateController = st_GateController_Idle;
}


/**
 * @brief This state puts the module in an idle state 
 * waiting for a signal from the User_Admin_Interface module. 
 * 
 */
void st_GateController_Idle(void)
{

}

/**
 * @brief This state opens the garage's exit gate.
 * 
 * @note :The gate opens by turning the servo motor +90 degree
 */
void st_GateController_OpenGate(void)
{   
    /*Turns the servo motor to open the gate*/
    HAL_ServoMotorTurn(ServoMotor_90Degree);

    /** TODO: Wait for 3 seconds then move to the state that 
     * checks if the car already passed the gate using the PIR sensor.
    */
    MCAL_TIMER0_SingleIntervalDelayms(GATE_OPENED_TIME_MS, Timer0_DelaycheckCar_Callback);

    /*Idle until the delay is over*/
    fptr_st_GateController = st_GateController_Idle;
}

/**
 * @brief This state checks if the car passed the gate 
 * to avoid closing the gate while the car is under it.
 * 
 */
void st_GateController_CheckCarPassed(void)
{
    ePIRStatus_t LOC_ePIRStatus;

    LOC_ePIRStatus = HAL_PIR_ReadStatus(PIR_PORT, PIR_PIN);

    /*If no motion is detected then the car passed so we should close the gate*/
    if(PIR_NoMotionDetected == LOC_ePIRStatus)
    {

      fptr_st_GateController = st_GateController_CloseGate;

    }else{ /*If the car didn't pass the gate yet then we should wait for another 
             gate timer interval.*/

      MCAL_TIMER0_SingleIntervalDelayms(GATE_OPENED_TIME_MS, Timer0_DelaycheckCar_Callback);

      /*Return to the idle state*/
      fptr_st_GateController = st_GateController_Idle;
    }
      
}

/**
 * @brief This state closes the garage's exit gate and 
 * sends a GateClosed signal to the User_Admin_Interface moudle.
 * 
 */
void st_GateController_CloseGate(void)
{
    /*Turns the servo motor to close the gate*/
    HAL_ServoMotorTurn(ServoMotor_0Degree);

    /*Sends a signal to the User_Admin_Interface to inform it that the gate closed*/
    GC_UAI_GateClosed();

    /*Go back to the idle state to wait for another request*/
    fptr_st_GateController = st_GateController_Idle;
}

/** @defgroup Signals between the Gate_Controller and the User_Admin_Interface.
  * @{
  */

/**
 * @brief This is an outgoing signal from the User_Admin_Interface module to the Gate_Controller module
 * to request it to open the gate.
 * 
 */
void UAI_GC_OpenGateReuest(void)
{
    fptr_st_GateController = st_GateController_OpenGate;
}

/**
  * @}
  */