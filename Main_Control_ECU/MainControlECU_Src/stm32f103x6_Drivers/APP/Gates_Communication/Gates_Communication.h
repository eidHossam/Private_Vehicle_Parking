/**
 * @file Gates_Communication.h
 * 
 * @brief This file contains  the APIs for the module responsible for communicating with the entrance 
 * and exit gates and its the bridge between the gates and the admin interface that is responsible for 
 * authenticating the IDs.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 09-03-2024
 * 
 * @version 1.0
 */

#ifndef APP_GATES_COMMUNICATION_GATES_COMMUNICATION_H_
#define APP_GATES_COMMUNICATION_GATES_COMMUNICATION_H_

/*
*===============================================
*                   Includes
*===============================================
*/

/** @defgroup APP
  * @{
  */
#include "../Interface.h"
#include "string.h"
/**
  * @}
  */

/** @defgroup MCAL
  * @{
  */
#include "SPI/stm32f103x8_SPI.h"
#include "EXTI/stm32f103x6_EXTI.h"
/**
  * @}
  */

/** @defgroup HAL
  * @{
  */
#include "LCD_Driver/LCD_interface.h"
#include "Seven_Segment_Display_Driver/Seven_Seg_Driver_Interface.h"
/**
  * @}
  */

/** @defgroup Service
  * @{
  */
#include "FIFO_Buffer_Driver/FIFO_Buff.h"
/**
  * @}
  */

/** @defgroup Gates_Communication_Current_State
  * @{
  */
void (* fptr_GateCommState)(void);
/**
  * @}
  */

/**************************************************************************************************************************
===============================================
*       States Supported by "Gates_Communication"
*===============================================
*/

/**
 * @brief This state initializes the main components needed for the communication module.
 * 
 */
void st_GatesComm_Init(void);

/**
 * @brief This state checks if there are any pending requests that needs processing.
 * 
 */
void st_GatesComm_CheckPendingRequests(void);

/**
 * @brief This state sends the request approval signal to the gate ECUs and to the 7-segment display to be updated.
 * 
 */
void st_GatesComm_SendIDApprovedSignal(void);

/**
 * @brief This state sends the request disapproval to the gate ECU.
 * 
 */
void st_GatesComm_SendIDDisapprovedSignal(void);

#endif /* APP_GATES_COMMUNICATION_GATES_COMMUNICATION_H_ */
