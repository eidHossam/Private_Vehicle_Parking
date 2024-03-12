/**
 * @file Interface.h
 * 
 * @brief This file contains the incoming and outgoing signals between the Admin_Interface and 
 * Gates_Communication modules.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 09-03-2024
 * 
 * @version 1.0
 */

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/** @defgroup INCLUDES
  * @{
  */
#include "Platform_Types.h"
/**
  * @}
  */

/**************************************************************************************************************************
*===============================================
*           Configuration Macros 
*===============================================
*/

/** @defgroup DRIVERS_CONFIGURATION
   * @{
   */
  
/*Set the maximum size of an authorized IDs*/
#define AUTHORIZED_ID_SIZE          3

 /**
   * @}
   */


/** @defgroup Signals between the Admin_Interface and Gates_Communication modules
  * @{
  */

/**
======================================================================================================================
* @Func_name:   st_Admin_AuthenticateID
* @brief		:   Function to authenticate the ID of the driver that wants to enter/exit the garage.
* @note		:   This function is called by the Gates_Communcation module.
======================================================================================================================
*/
void st_Admin_AuthenticateID(void);

/**
======================================================================================================================
* @Func_name	:  AI_GC_SendIDForAuthentication
* @brief		   :  Function to send the Driver ID to be authroized
* @param [in]	:  ptr_DriverID: pointer to the array holding the Driver ID
* @note			:  none.
======================================================================================================================
*/
void AI_GC_SendIDForAuthentication(uint8* ptr_DriverID);

/**
======================================================================================================================
* @Func_name	:  AI_GC_IDApproved
* @brief		   :  Function to inform that the authentication process has been approved and the ID is valid.
* @note			:  none
======================================================================================================================
*/
void AI_GC_IDApproved(void);

/**
======================================================================================================================
* @Func_name	:  AI_GC_IDApproved
* @brief		   :  Function to inform that the authentication process has been approved and the ID is valid.
* @note			:  none
======================================================================================================================
*/
void AI_GC_IDDisapproved(void);

/**
  * @}
  */
#endif /* APP_INTERFACE_H_ */
