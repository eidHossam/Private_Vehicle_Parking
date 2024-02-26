/*
 * Admin_Interface.c
 *
 *  Created on: Feb 26, 2024
 *      Author: Hossam Eid
 */

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Admin_Interface.h"

/** @defgroup local Macros
  * @{
  */
#define VALID_LOGIN_INFO          1
#define INVALID_LOGIN_INFO        0

/*Admin options*/
#define ADMIN_ADD_ID              '1'
#define ADMIN_REMOVE_ID           '2'
#define ADMIN_SAVE_ID             '3'
#define ADMIN_LOGOUT              '*'

/**
  * @}
  */

/** @defgroup Local Defines
  * @{
  */
typedef struct 
{
    uint8 adminUserID[ADMIN_USERID_SIZE + 1];
    uint8 adminPassword[ADMIN_PASSWORD_SIZE + 1];
}sAdmin_Info_t;
/**
  * @}
  */

/** @defgroup Local Variables
  * @{
  */
static uint8 pressedKey;    /*Input of keypad*/
static uint8 userInputCount = 0;

static uint8 Glob_userIDinput[ADMIN_USERID_SIZE + 1];
static uint8 Glob_passwordinput[ADMIN_PASSWORD_SIZE + 1];

static sAdmin_Info_t Glob_adminsList[NUMBER_OF_ADMINS] = ADMINS_LIST;

static uint8 loginAttemptsCounter = 1;

/**
  * @}
  */


/** @defgroup Local Functions
  * @{
  */

void Peripheral_Clock_Init()
{
	/*Enable GPIO_A*/
	APB2_PERI_CLOCK_EN(APB2_IOPA);

	/*Enable GPIO_B*/
	APB2_PERI_CLOCK_EN(APB2_IOPB);
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
======================================================================================================================
* @Func_name	  :   st_Admin_Dashboard_Init
* @brief		    :   This function initializes the required subsystem components for the admin dashboard.  
* @param [in]	  :   none.
* @param [out]	:   none.
* @return       :   none.
* Note			    :   none.
======================================================================================================================
*/
void st_Admin_DashboardInit(void)
{  
  /*Enable the required clocks*/
  Peripheral_Clock_Init();
 
  LCD_Init();
  Keypad_Init();
 
  /*Set the next state*/
  Admin_Dashboard_State = st_Admin_InitialMessage;
}

/**
======================================================================================================================
* @Func_name	:   st_Admin_Initial_Message
* @brief		  :   Function to display the initial welcome message to the user.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_InitialMessage(void)
{
    /*Print the initial message*/
    LCD_Clear_Screen();
    
    LCD_Cursor_XY(LCD_SECOND_LINE, 4);
    LCD_Send_String(stringfy("Press '*'"));

    LCD_Cursor_XY(LCD_THIRD_LINE, 4);
    LCD_Send_String(stringfy("to Login"));

    /*Set the next state*/
    Admin_Dashboard_State = st_Admin_GetUserInput;
}


/**
======================================================================================================================
* @Func_name	:   st_Admin_GetUserInput
* @brief		  :   Function to get the user action.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_GetUserInput(void)
{   
    pressedKey = Keypad_Get_Char();

    /*Set the next state*/
    if(pressedKey == '*')
    {
        Admin_Dashboard_State = st_Admin_LoginMessage;
    }else{
        Admin_Dashboard_State = st_Admin_GetUserInput;
    }
}


/**
======================================================================================================================
* @Func_name	:   st_Admin_LoginMessage
* @brief		  :   Function to get the user action.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_LoginMessage(void)
{
    /*Print the login message*/
    LCD_Clear_Screen();

    LCD_Send_String(stringfy("UserID:"));
    LCD_Cursor_XY(LCD_SECOND_LINE, 0);
    LCD_Send_String(stringfy("Password:"));

    if(loginAttemptsCounter > 1)
    {
      LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
      LCD_Send_String(stringfy("Wrong Login Info"));
    }
    /*Set next state*/
    Admin_Dashboard_State = st_Admin_GetUserID;
}

/**
======================================================================================================================
* @Func_name	:   st_Admin_GetUserID
* @brief		  :   Function to get the user input for the userID.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_GetUserID(void)
{
    LCD_Cursor_XY(LCD_FIRST_LINE, 7 + userInputCount);

    pressedKey = Keypad_Get_Char();

    /*Set the next state*/
    if(pressedKey != NULL_CHAR)
    {
        LCD_Send_Char(pressedKey);
        Glob_userIDinput[userInputCount++] = pressedKey;
    }else{
        
    }

    if(userInputCount >= ADMIN_USERID_SIZE)
    {
        Glob_userIDinput[userInputCount] = '\0';
        userInputCount = 0;

        /*Set next state*/
        Admin_Dashboard_State = st_Admin_GetUserPassword;
    }else{
        /*Stay in the same state*/
        Admin_Dashboard_State = st_Admin_GetUserID;
    }
}

/**
======================================================================================================================
* @Func_name	:   st_Admin_GetUserPassword
* @brief		  :   Function to get the user input for the password.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_GetUserPassword(void)
{
    LCD_Cursor_XY(LCD_SECOND_LINE, 9 + userInputCount);
    
    pressedKey = Keypad_Get_Char();

    /*Set the next state*/
    if(pressedKey != NULL_CHAR)
    {   
        LCD_Send_Char('*');
        Glob_passwordinput[userInputCount++] = pressedKey;
    }else{
        
    }

    if(userInputCount >= ADMIN_PASSWORD_SIZE)
    {
        Glob_passwordinput[userInputCount] = '\0';
        userInputCount = 0;

        /*Set next state*/
        Admin_Dashboard_State = st_Admin_CheckLoginInfo;
    }else{
        /*Stay in the same state*/
        Admin_Dashboard_State = st_Admin_GetUserPassword;
    }
}

/**
======================================================================================================================
* @Func_name	:   st_Admin_CheckLoginInfo
* @brief		  :   Function to check if the given login info is valid or not.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_CheckLoginInfo(void)
{
  uint8 validInfo = INVALID_LOGIN_INFO;

  uint8 i;
  for(i = 0; i < NUMBER_OF_ADMINS; i++)
  {
     if(!strcmp((const sint8 *)Glob_adminsList[i].adminUserID, (const sint8 *)Glob_userIDinput) && 
        !strcmp((const sint8 *)Glob_adminsList[i].adminPassword, (const sint8 *)Glob_passwordinput)) 
     {
        validInfo = VALID_LOGIN_INFO;
        break;
        
     }else{

     }
  }

  if(validInfo == VALID_LOGIN_INFO)
  {
    loginAttemptsCounter = 1;

    /*Set next state*/
    Admin_Dashboard_State = st_Admin_ShowAdminOptions;
  }else{

    /*If we didn't exceed the maximum allowed attempts*/
    if(loginAttemptsCounter < ADMIN_MAX_LOGIN_ATTEMPTS)
    {
        loginAttemptsCounter++;
        Admin_Dashboard_State = st_Admin_LoginMessage;

    }else{

        loginAttemptsCounter = 1;

      /*TODO: Timeout and error message*/

        Admin_Dashboard_State = st_Admin_InitialMessage;
    }
  }

}


/**
======================================================================================================================
* @Func_name	:   st_Admin_ShowAdminOptions
* @brief		  :   Function to get display the available admin operations on the LCD screen.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_ShowAdminOptions(void)
{
    LCD_Clear_Screen();

    LCD_Send_String(stringfy("1.Add new ID"));
    LCD_Cursor_XY(LCD_SECOND_LINE, 0);
    LCD_Send_String(stringfy("2.Remove an ID"));
    LCD_Cursor_XY(LCD_THIRD_LINE, 0);
    LCD_Send_String(stringfy("3.Save on EEPROM"));
    LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
    LCD_Send_String(stringfy("'*' to logout: "));

    Admin_Dashboard_State = st_Admin_GetAdminOption;
}

/**
======================================================================================================================
* @Func_name	:   st_Admin_GetAdminOption
* @brief		  :   Function to get the required action to be done from the user.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_GetAdminOption(void)
{
  pressedKey = Keypad_Get_Char();

  switch (pressedKey)
  {
  case ADMIN_ADD_ID:
    Admin_Dashboard_State = st_Admin_AddNewID;
    break;
  case ADMIN_REMOVE_ID:
    Admin_Dashboard_State = st_Admin_RemoveID;
    break;
  case ADMIN_SAVE_ID:
    Admin_Dashboard_State = st_Admin_SaveOnEEPROM;
    break;
  case ADMIN_LOGOUT:
    Admin_Dashboard_State = st_Admin_InitialMessage;
    break;
  
  default:
    break;
  }
}

/**
======================================================================================================================
* @Func_name	:   st_Admin_AddNewID
* @brief		  :   Function to add a new authorized ID to the garage.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_AddNewID(void)
{

}

/**
======================================================================================================================
* @Func_name	:   st_Admin_RemoveID
* @brief		  :   Function to remove an existing authorized ID from the garage.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_RemoveID(void)
{

}

/**
======================================================================================================================
* @Func_name	:   st_Admin_SaveOnEEPROM
* @brief		  :   Function to save the authorized IDs on the external memory.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_SaveOnEEPROM(void)
{

}

