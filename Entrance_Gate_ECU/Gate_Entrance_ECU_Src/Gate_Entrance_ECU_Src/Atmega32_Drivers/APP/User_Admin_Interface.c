/**
 * @file User_Admin_Interface.c
 * 
 * @brief this file implements 
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 08-03-2024
 * 
 * @version 1.0
 */

/*
*===============================================
*                   Includes
*===============================================
*/
#include "User_Admin_Interface.h"

/**************************************************************************************************************************
===============================================
*       States Definitions
*===============================================
*/

/**
 * @brief This state initializes the main components of the User_Admin interface module.
 * 
 */
void st_UAI_Init(void)
{
    /*Initialize the LCD module to print messages to the driver*/
    LCD_Init();

    /*Set the initial state*/
    fptr_st_UserAdminInterface = st_UAI_ShowWelcomeMsg;
}

/**
 * @brief this state prints the welcome message to guide the user on what to do.  
 * 
 */
void st_UAI_ShowWelcomeMsg(void)
{
    LCD_Clear_Screen();

    LCD_Cursor_XY(LCD_FIRST_LINE, 4);
    LCD_Send_String(stringfy("Welcome!"));

    LCD_Cursor_XY(LCD_THIRD_LINE, 0);
    LCD_Send_String(stringfy("Please enter the 3 digits ID"));

    fptr_st_UserAdminInterface = st_UAI_Idle;
}


/**
 * @brief this state makes the module go into idle mode until some user action is done.
 * 
 */
void st_UAI_Idle(void)
{

}