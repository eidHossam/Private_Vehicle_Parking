/*
 * Admin_Interface_cfg.h
 *
 *  Created on: Feb 26, 2024
 *      Author: hp
 */

#ifndef APP_ADMIN_INTERFACE_ADMIN_INTERFACE_CFG_H_
#define APP_ADMIN_INTERFACE_ADMIN_INTERFACE_CFG_H_

/** @defgroup INCLUDES
  * @{
  */

#include "../Interface.h"

/**
  * @}
  */

/**************************************************************************************************************************
*===============================================
*           Configuration Macros 
*===============================================
*/

/** @defgroup ADMIN_CONFIGURATIONS
  * @{
  */

/*Set the maximum allowed login attempts before timeour*/
#define ADMIN_MAX_LOGIN_ATTEMPTS    3

/*Admin login info size restriction*/
#define ADMIN_USERID_SIZE           4
#define ADMIN_PASSWORD_SIZE         4

/*Set the number of admins in the system*/
#define NUMBER_OF_ADMINS            2

/*A list of all the admins info {userID, password}*/
#define ADMINS_LIST                 {{"1234", "0000"},\
                                    {"1482", "6666"}}   
/**
  * @}
  */
 
/** @defgroup DRIVERS_CONFIGURATION
   * @{
   */
  
/*Set the maximum allowed number of authorized IDs*/
#define AUTHORIZED_IDS_MAX_COUNT     5
 /**
   * @}
   */


#endif  /* APP_ADMIN_INTERFACE_ADMIN_INTERFACE_CFG_H_ */
