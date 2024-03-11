/**
 * @file Servo_Motor_Interface.h
 * 
 * @brief This file holds the APIs definitions of the PWM controlled servo motor.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 10-03-2024
 * 
 * @version 1.0
 */

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Servo_Motor_Interface.h"



/**************************************************************************************************************************
*===============================================
*  			APIs functions definitions
*===============================================
*/

/**
 * @brief This function does the required initialization to use the servo motor.
 * 
 * @return eStatus_t: E_OK if the initialization was successful, E_NOK otherwise.
 */
eStatus_t HAL_ServoMotorInit(void)
{
    eStatus_t LOC_sStatus = E_OK;

    sTIMER2_Config_t timer2_Config;
    GPIO_Pin_Config_t GPIO_cfg;

    GPIO_cfg.pinNumber = GPIO_PIN7;
    GPIO_cfg.pinMode = GPIO_MODE_OUTPUT;
    MCAL_GPIO_Init(GPIOD, &GPIO_cfg);

    timer2_Config.Timer2_CLK_SRC = Timer2_Prescale_1024;
    timer2_Config.Timer2_Mode = Timer2_FAST_PWM_Mode;
    timer2_Config.Timer2_COM = Timer2_COM_Set;
    timer2_Config.Timer2_OCIE = Timer2_TOCI_Disable;
    timer2_Config.Timer2_OIE = Timer2_TOI_Disable;

    MCAL_TIMER2_SetCompare(ServoMotor_0Degree);

    LOC_sStatus = MCAL_TIMER2_Init(& timer2_Config);


    return LOC_sStatus;
}


/**
 * @brief This function turn the servo motor with the specified degree. 
 * 
 * @param copy_eDegree : Degree to turn the servo motor with.
 * @return eStatus_t   : Status of the operation.
 */
eStatus_t HAL_ServoMotorTurn(eServoMotorDegree_t copy_eDegree)
{
    eStatus_t LOC_sStatus = E_OK;
    
    MCAL_TIMER2_SetCompare(copy_eDegree);

    return LOC_sStatus;
}
