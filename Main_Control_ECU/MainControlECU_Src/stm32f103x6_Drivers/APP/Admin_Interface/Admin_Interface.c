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
#define ADMIN_MORE_OPTIONS        '4'
#define ADMIN_SHOW_IDS_LIST       '5'
#define ADMIN_LOGOUT              '*'

/**
  * @}
  */

/** @defgroup Local Defines
  * @{
  */

/**
 * @brief A struct to hold the admin login information.
 * 
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

/** @defgroup KEYPAD_INPUT
  * @{
  */
static uint8 pressedKey;    
static uint8 userInputCount = 0;
/**
  * @}
  */


/** @defgroup USER_INPUT
  * @{
  */
static uint8 Glob_userIDinput[ADMIN_USERID_SIZE + 1];
static uint8 Glob_passwordinput[ADMIN_PASSWORD_SIZE + 1];
/**
  * @}
  */

/** @defgroup ADMIN_INFO
  * @{
  */
/**
 * @brief This array holds the login information of all the authorized admins. 
 * 
 */
static sAdmin_Info_t Glob_adminsList[NUMBER_OF_ADMINS] = ADMINS_LIST;

static uint8 loginAttemptsCounter = 1;

/**
 * @brief Current operation being performed by the admin.
 * 
 */
static uint8 currentOperation;
/**
  * @}
  */

/** @defgroup DRIVER_IDS_INFO
  * @{
  */
static uint8 Glob_tempDriverIDinput[AUTHORIZED_ID_SIZE + 1];
static uint8 Glob_DriversIDsList[AUTHORIZED_IDS_MAX_COUNT][AUTHORIZED_ID_SIZE + 1];
static uint8 Glob_AuthIDsCount = 0;
/**
  * @}
  */

/**
  * @}
  */


/** @defgroup PRIVATE_FUNCTIONS_DEFENITIONS
  * @{
  */

/**
======================================================================================================================
* @Func_name	: Peripheral_Clock_Init
* @brief		  : Enable all the required peripherals clocks.
* Note			  : none.
======================================================================================================================
*/
void Peripheral_Clock_Init()
{
	/*Enable GPIO_A*/
	APB2_PERI_CLOCK_EN(APB2_IOPA);

	/*Enable GPIO_B*/
	APB2_PERI_CLOCK_EN(APB2_IOPB);
}

/**
======================================================================================================================
* @Func_name	: st_Admin_BacktoMainMenu
* @brief		  : Function to route the user back to the admin interface main menu.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_BacktoMainMenu(void)
{
   pressedKey = Keypad_Get_Char();

   if(pressedKey == '*')
   {
      Admin_Dashboard_State = st_Admin_ShowAdminOptions;
   }else{

   }
}

/**
======================================================================================================================
* @Func_name	: st_Admin_MoreOptions
* @brief		  : An extension for the function that prints the admin options on the LCD.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_MoreOptions()
{
    LCD_Clear_Screen();
    LCD_Send_String(stringfy("5.Show IDs list"));
    LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
    LCD_Send_String(stringfy("'*' To Logout"));

  Admin_Dashboard_State = st_Admin_GetAdminOption;
}

/**
======================================================================================================================
* @Func_name	: st_Admin_DisplayAddNewIDMessage
* @brief		  : A function to prompt the user to enter a new ID to be registered.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_DisplayAddNewIDMessage(void)
{
  LCD_Clear_Screen();

  if(Glob_AuthIDsCount < AUTHORIZED_IDS_MAX_COUNT)
  {
    LCD_Send_String(stringfy("Enter ID:"));

    Admin_Dashboard_State = st_Admin_AddNewID;
  }else{

    LCD_Send_String(stringfy("IDs count exceeded"));
    LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
    LCD_Send_String(stringfy("main menu => '*'"));

    Admin_Dashboard_State = st_Admin_BacktoMainMenu;
  }
}

/**
======================================================================================================================
* @Func_name	: st_Admin_AddedIDsuccessfully
* @brief		  : Function to tell the user that the process of adding a new ID had been successfull.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_AddedIDsuccessfully(void)
{
   /*Copy the ID into the main list*/
   strcpy((sint8 *)Glob_DriversIDsList[Glob_AuthIDsCount], (const sint8 *)Glob_tempDriverIDinput);

   /*Increase the IDs count in the system*/
   Glob_AuthIDsCount++;
   
   LCD_Clear_Screen();

   LCD_Send_String(stringfy("ID Added successfully"));
   LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
   LCD_Send_String(stringfy("main menu => '*'"));

  Admin_Dashboard_State = st_Admin_BacktoMainMenu;
}

/**
======================================================================================================================
* @Func_name	: st_Admin_IDalreadyExists
* @brief		  : A function to warn the admin if he tries to register an already registered ID.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_IDalreadyExists(void)
{
  LCD_Clear_Screen();
  LCD_Send_String(stringfy("ID already exist"));
  LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
  LCD_Send_String(stringfy("main menu => '*'"));
  
  Admin_Dashboard_State = st_Admin_BacktoMainMenu;
}

/**
======================================================================================================================
* @Func_name	: st_Admin_RemovedIDsuccessfully
* @brief		  : A function to warn the admin if he tries to register an already registered ID.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_RemovedIDsuccessfully(void)
{
  LCD_Clear_Screen();
  LCD_Send_String(stringfy("ID Deleted!"));
  LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
  LCD_Send_String(stringfy("main menu => '*'"));
  
  Admin_Dashboard_State = st_Admin_BacktoMainMenu;
}

/**
======================================================================================================================
* @Func_name	: st_Admin_IDnotFound
* @brief		  : Function to inform the user that the required ID doesn't exist.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_IDnotFound(void)
{
  LCD_Clear_Screen();
  LCD_Send_String(stringfy("ID Doesn't Exist"));
  LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
  LCD_Send_String(stringfy("main menu => '*'"));
  
  Admin_Dashboard_State = st_Admin_BacktoMainMenu;

}

/**
======================================================================================================================
* @Func_name	: deleteID
* @brief		  : Function to remove an element from the list by copying the last element in its place.
* @param [in]	: IDindex: index of the element to be removed.
* Note			  : The order of the elements in the list does not matter.
======================================================================================================================
*/
void deleteID(uint8 IDindex)
{
  /*If the ID to be deleted is in the end of the list just decrease the IDs count*/
  if(IDindex < Glob_AuthIDsCount - 1)
  {
    /*Delete the required ID from the list*/
    strcpy((sint8  *)Glob_DriversIDsList[IDindex], (const sint8 *)Glob_DriversIDsList[Glob_AuthIDsCount - 1]);
  }else{

  }

  Glob_AuthIDsCount--;
}

/**
======================================================================================================================
* @Func_name	: st_Admin_CheckRepeatedID
* @brief		  : FUnction to check if the ID to be registered already exists in the system.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_CheckRepeatedID(void)
{
  static uint8 counter = 0;
  boolean repeated = FALSE;

  if(!strcmp((const sint8 *)Glob_tempDriverIDinput, (const sint8 *)Glob_DriversIDsList[counter]))
  {
      repeated = TRUE;
  }else{

  }

  if(repeated)
  {
    if(currentOperation == ADMIN_ADD_ID)
    {
      Admin_Dashboard_State = st_Admin_IDalreadyExists;
    }else if(currentOperation == ADMIN_REMOVE_ID)
    {
      deleteID(counter);
      Admin_Dashboard_State = st_Admin_RemovedIDsuccessfully;
    }else{

    }

    counter = 0;    

  }else{
    counter++;

    /*Check the other IDs in the system if there is any*/
    if(counter < Glob_AuthIDsCount)
    {
      Admin_Dashboard_State = st_Admin_CheckRepeatedID;
    }else{
      counter = 0;

      if(currentOperation == ADMIN_ADD_ID)
      {
        Admin_Dashboard_State = st_Admin_AddedIDsuccessfully;
      }else if(currentOperation == ADMIN_REMOVE_ID)
      { 
        Admin_Dashboard_State = st_Admin_IDnotFound;
      }else{

      }
    }
  }
}


/**
======================================================================================================================
* @Func_name	: st_Admin_DisplayRemoveIDMessage
* @brief		  : A function to prompt the user to enter a an ID to be deleted from the system.
* Note			  : none.
======================================================================================================================
*/
void st_Admin_DisplayRemoveIDMessage(void)
{
  LCD_Clear_Screen();

  if(Glob_AuthIDsCount > 0)
  {
    LCD_Send_String(stringfy("Enter ID:"));

    Admin_Dashboard_State = st_Admin_RemoveID;
  }else{

    LCD_Send_String(stringfy("IDs List Empty"));
    LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
    LCD_Send_String(stringfy("main menu => '*'"));

    Admin_Dashboard_State = st_Admin_BacktoMainMenu;
  }
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
    LCD_Send_String(stringfy("4.More options"));

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
    Admin_Dashboard_State = st_Admin_DisplayAddNewIDMessage;
    break;
  case ADMIN_REMOVE_ID:
    Admin_Dashboard_State = st_Admin_DisplayRemoveIDMessage;
    break;
  case ADMIN_SAVE_ID:
    Admin_Dashboard_State = st_Admin_SaveOnEEPROM;
    break;
  case ADMIN_MORE_OPTIONS:
    Admin_Dashboard_State = st_Admin_MoreOptions;
    break;
  case ADMIN_SHOW_IDS_LIST:
    LCD_Clear_Screen();
    Admin_Dashboard_State = st_Admin_ShowIDsList;   
    break;
  case ADMIN_LOGOUT:
    Admin_Dashboard_State = st_Admin_InitialMessage;
    break;
  
  default:
    break;
  }

  currentOperation = pressedKey;
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
    LCD_Cursor_XY(LCD_FIRST_LINE, 9 + userInputCount);
    
    pressedKey = Keypad_Get_Char();

    if(pressedKey != NULL_CHAR)
    {   
        LCD_Send_Char(pressedKey);
        Glob_tempDriverIDinput[userInputCount] = pressedKey;
        userInputCount++;
    }else{
        
    }

    if(userInputCount >= AUTHORIZED_ID_SIZE)
    {
        Glob_tempDriverIDinput[userInputCount] = '\0';
        userInputCount = 0;

        /*If there is no registerd IDs in the system no need to check if the ID is repeated*/
        if(Glob_AuthIDsCount == 0)
        {
          /*Set next state*/
          Admin_Dashboard_State = st_Admin_AddedIDsuccessfully;
        }else{
          Admin_Dashboard_State = st_Admin_CheckRepeatedID;
        }

    }else{
        /*Stay in the same state*/
        Admin_Dashboard_State = st_Admin_AddNewID;
    }
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
LCD_Cursor_XY(LCD_FIRST_LINE, 9 + userInputCount);
    
    pressedKey = Keypad_Get_Char();

    if(pressedKey != NULL_CHAR)
    {   
        LCD_Send_Char(pressedKey);
        Glob_tempDriverIDinput[userInputCount] = pressedKey;
        userInputCount++;
    }else{
        
    }

    if(userInputCount >= AUTHORIZED_ID_SIZE)
    {
        Glob_tempDriverIDinput[userInputCount] = '\0';
        userInputCount = 0;

        Admin_Dashboard_State = st_Admin_CheckRepeatedID;
    }else{
        /*Stay in the same state*/
        Admin_Dashboard_State = st_Admin_AddNewID;
    }
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

/**
======================================================================================================================
* @Func_name	:   st_Admin_ShowIDsList
* @brief		  :   Function to show all the authorized IDs in the system.
* Note			  :   none.
======================================================================================================================
*/
void st_Admin_ShowIDsList(void)
{
  static uint8 printedIDcounter = 0;

  if(Glob_AuthIDsCount > 0)
  {
    LCD_Send_String(Glob_DriversIDsList[printedIDcounter]);
    LCD_Send_Char(',');

    printedIDcounter++;
  }else{

    LCD_Send_String(stringfy("List Empty"));
  }


  if(printedIDcounter >= Glob_AuthIDsCount)
  {
    printedIDcounter = 0;

    LCD_Cursor_XY(LCD_FOURTH_LINE, 0);
    LCD_Send_String(stringfy("main menu => '*'"));

    Admin_Dashboard_State = st_Admin_BacktoMainMenu;
  }else{

    Admin_Dashboard_State = st_Admin_ShowIDsList;
  }
}
