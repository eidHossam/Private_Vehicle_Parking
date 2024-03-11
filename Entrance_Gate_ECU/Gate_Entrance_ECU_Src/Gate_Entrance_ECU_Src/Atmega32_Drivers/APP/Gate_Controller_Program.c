/*
 * Gate_Control_Program.c
 *
 * Created: 3/11/2024 12:52:10 AM
 *  Author: hp
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

/**
 * @brief Specifies the time the gate should stay open for in milliseconds.
 * 
 */
#define GATE_OPENED_TIME_MS             3000
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
 * @brief This state opens the garage's entrance gate.
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
    /*Turns the servo motor to open the gate*/
    HAL_ServoMotorTurn(ServoMotor_0Degree);

    GC_UAI_GateClosed();
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