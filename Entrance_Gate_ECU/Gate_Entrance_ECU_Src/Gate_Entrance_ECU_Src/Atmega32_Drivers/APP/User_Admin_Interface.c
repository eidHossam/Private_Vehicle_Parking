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

/** @defgroup Local Macros
  * @{
  */
#define DRIVER_ID_SIZE      3
/**
  * @}
  */


/** @defgroup Local Variables
  * @{
  */
static uint8_t LOC_u8DriverID[DRIVER_ID_SIZE];
/**
  * @}
  */



/** @defgroup ISR_CALLBACK_DEFINITIONS
  * @{
  */

static void USART_RX_ISR_Callback(void)
{
    static uint8_t sLOC_u8CharCounter = 0;

    /*Get the character the user typed*/
    MCAL_UART_Get_Data((uint16_t *)(&LOC_u8DriverID[sLOC_u8CharCounter]), USART_PollingDisabled);

    /*Send the character again to show it on the terminal*/
    MCAL_UART_Send_Data((uint16_t *)(&LOC_u8DriverID[sLOC_u8CharCounter]), USART_PollingDisabled);
        
    sLOC_u8CharCounter++;

    if(sLOC_u8CharCounter == DRIVER_ID_SIZE)
    {
        sLOC_u8CharCounter = 0;
 
        /*Disable the UART to stop it from serving another customer 
          until processing this customer's request*/
        MCAL_UART_Disable();

        fptr_st_UserAdminInterface = st_UAI_SendIDToAdmin;
    }else{

    }
}

/**
  * @}
  */


/** @defgroup Private Functions
  * @{
  */
static void USART_Init()
{
    sUSART_config_t cfg;

    cfg.USART_CLKOperation = USART_CLKOP_NormalAsynch;
    cfg.USART_baudRate = USART_BAUD_RATE_9600;
    cfg.USART_Mode = USART_ModeTXRX;
    cfg.USART_wordLength = USART_8BitWord;
    cfg.USART_parityCTRL = USART_ParityMode_Disabled;
    cfg.USART_stopBits = USART_1StopBit;

    MCAL_UART_Init(&cfg);

    MCAL_UART_Interrupt_EN(USART_IRQ_RXC, USART_RX_ISR_Callback);

    /*Disable the UART until the initialization is done*/
    MCAL_UART_Disable();
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
 * @brief This state initializes the main components of the User_Admin interface module.
 * 
 */
void st_UAI_Init(void)
{
    /*Initialize the USART module to get the input from the user*/
    USART_Init();

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

    /*Enable the UART module to take the user input*/
    MCAL_UART_Enable();

    fptr_st_UserAdminInterface = st_UAI_Idle;
}


/**
 * @brief this state makes the module go into idle mode until some user action is done.
 * 
 */
void st_UAI_Idle(void)
{

}

/**
 * @brief this state sends the driver's ID to the Admin ECU for authentication. 
 * 
 */
void st_UAI_SendIDToAdmin(void)
{
    
}
