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
#define ENTRANCE_GATE_ECU_ADDRESS       0xE7u

#define DRIVER_ID_SIZE                  3

#define ADMIN_ECU_INTERRUPT_PORT        GPIOB
#define ADMIN_ECU_INTERRUPT_PIN         GPIO_PIN3

/** @defgroup Module_States
  * @{
  */
#define UAI_IDLE                            0
#define UAI_SENDING_ID                      1
#define UAI_WAITING_AUTHENTICATION_RESULT   2
/**
  * @}
  */

/** @defgroup AUTHENTICATION_RESULT
  * @{
  */
#define AUTHENTICATION_RESULT_PASS     0xFFu
#define AUTHENTICATION_RESULT_FAIL     0x00u
/**
  * @}
  */

/**
  * @}
  */


/** @defgroup Local Variables
  * @{
  */
static uint8_t Glob_u8ModuleCurrentState;

static uint8_t Glob_u8DriverID[DRIVER_ID_SIZE + 1];
static const uint8_t Glob_u8GateAddress = ENTRANCE_GATE_ECU_ADDRESS;
/**
  * @}
  */



/** @defgroup ISR_CALLBACK_DEFINITIONS
  * @{
  */

/**
======================================================================================================================
* @Func_name	:   USART_RX_ISR_Callback
* @brief		:   This function is the callback function for the USART receive buffer not empty interrupt it helps
*               :   reading the driver ID from the driver.
* @note			:   none.
======================================================================================================================
*/
static void USART_RX_ISR_Callback(void)
{
    static uint8_t sLOC_u8CharCounter = 0;

    /*Get the character the user typed*/
    MCAL_UART_Get_Data((uint16_t *)(&Glob_u8DriverID[sLOC_u8CharCounter]), USART_PollingDisabled);

    /*Send the character again to show it on the terminal*/
    MCAL_UART_Send_Data((uint16_t *)(&Glob_u8DriverID[sLOC_u8CharCounter]), USART_PollingDisabled);
        
    sLOC_u8CharCounter++;

    if(sLOC_u8CharCounter == DRIVER_ID_SIZE)
    {
        /*Add a NULL character at the end*/
        Glob_u8DriverID[sLOC_u8CharCounter] = '\0';

        sLOC_u8CharCounter = 0;
 
        /*Disable the UART to stop it from serving another customer 
          until processing this customer's request*/
        MCAL_UART_Disable();

        fptr_st_UserAdminInterface = st_UAI_SendIDToAdmin;
    }else{

    }
}

/**
======================================================================================================================
* @Func_name	:   SPI_SendingID
* @brief		:   Function to send the driver's ID to the admin through SPI interface.
* @note			:   none.
======================================================================================================================
*/
static void SPI_SendingID(void)
{
    static uint8_t sLOC_u8CharCounter = 0;

    if(sLOC_u8CharCounter == 0)
    {
        MCAL_SPI_SendData((uint8_t *)&Glob_u8GateAddress, PollingDisable);
    }else{
        MCAL_SPI_SendData(&Glob_u8DriverID[sLOC_u8CharCounter - 1], PollingDisable);
    }
            
    sLOC_u8CharCounter++;

    if(sLOC_u8CharCounter == (DRIVER_ID_SIZE + 1))
    {
        MCAL_TIMER0_Stop();

        sLOC_u8CharCounter = 0;
        
        Glob_u8ModuleCurrentState = UAI_WAITING_AUTHENTICATION_RESULT;
        
        /*Enable the timer to prevent getting stuck in this state forever*/
        MCAL_TIMER0_SetCounter(0x00);
        MCAL_TIMER0_Start();

        fptr_st_UserAdminInterface = st_UAI_Idle;
    }else{

    }
}

/**
======================================================================================================================
* @Func_name	:   SPI_GetAuthenticationResult
* @brief		:   This function checks the authentication process result.
======================================================================================================================
*/
void SPI_GetAuthenticationResult(void)
{
    static boolean LOC_boolDetectedGateAddress = FALSE;
    uint8_t LOC_u8RxBuffer = ENTRANCE_GATE_ECU_ADDRESS;

    MCAL_SPI_ExchangeData(&LOC_u8RxBuffer);

    /*If we already received the gate ID from the last transmission 
      then check the authentication result*/
    if(LOC_boolDetectedGateAddress)
    {
        LOC_boolDetectedGateAddress = FALSE;

        /*check if the data we got matches the successful authentication code*/
        if(LOC_u8RxBuffer == AUTHENTICATION_RESULT_PASS)
        {
            fptr_st_UserAdminInterface = st_UAI_IDAuthenticationPassed;
        }else{
            fptr_st_UserAdminInterface = st_UAI_IDAuthenticationFailed;
        }

        LOC_u8RxBuffer = 0x00u;
        
        /*Write zero in the transmit buffer to avoid confusion in the next time*/
        MCAL_SPI_SendData(&LOC_u8RxBuffer, PollingDisable);

    }else{

        /*check if the received data matches the the gate address*/
        if(LOC_u8RxBuffer == Glob_u8GateAddress)
        {
            LOC_boolDetectedGateAddress = TRUE;
        }else{

        }
    }
}

/**
======================================================================================================================
* @Func_name	:   SPI_ISR_Callback
* @brief		:   This is the callback function for the SPI interrupt.
* @note			:   none.
======================================================================================================================
*/
static void SPI_ISR_Callback(void)
{
    switch (Glob_u8ModuleCurrentState)
    {
    case UAI_IDLE:
        /* If we didn't send a request just ignore this interrupt as it's probably
           done to communicate with the other gate ECU. (Can be changed later if needed)*/
        break;

    case UAI_SENDING_ID:
        SPI_SendingID();
        break;

    case UAI_WAITING_AUTHENTICATION_RESULT:
        SPI_GetAuthenticationResult();
        break;
    
    default:
        break;
    }   
}

static void Timer0_callback(void)
{
    static uint32_t counter;

	if(counter == 4000)
    {
        counter = 0;

        fptr_st_UserAdminInterface = st_UAI_ShowWelcomeMsg;

        MCAL_TIMER0_Stop();
    }

    counter++;
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

static void SPI_Init()
{
    SPI_Config_t LOC_sSPI_cfg;
    GPIO_Pin_Config_t LOC_sGPIO_CFG;

    LOC_sSPI_cfg.SPI_Mode       = SPI_MODE_SLAVE;
    LOC_sSPI_cfg.SPI_DataOrder  = SPI_FIRST_BIT_LSB;
    LOC_sSPI_cfg.SPI_CPOL       = SPI_IDLE_HIGH;
    LOC_sSPI_cfg.SPI_CPHA       = SPI_SAMPLE_SECOND_EDGE;
    LOC_sSPI_cfg.SPI_IRQ_EN     = SPI_IRQ_ENABLE;
    LOC_sSPI_cfg.SPI_IRQHandler = SPI_ISR_Callback;

    MCAL_SPI_Init(&LOC_sSPI_cfg);

    /*Configure the pin to be used to interrupt the admin ECU to request attention*/
    LOC_sGPIO_CFG.pinMode = GPIO_MODE_OUTPUT;
    LOC_sGPIO_CFG.pinNumber = ADMIN_ECU_INTERRUPT_PIN;
    MCAL_GPIO_Init(ADMIN_ECU_INTERRUPT_PORT, &LOC_sGPIO_CFG);

}

static void Timer0_Init(void)
{    
    /*Set the callback function for the CTC mode*/
	MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(Timer0_callback);
    sTimer0_Config_t config = { Timer_Prescale_8, Timer_CTC_Mode, Timer_COM_Disconnected,
                                Timer_TOI_Disable, Timer_TOCI_Enable};
    
    MCAL_TIMER0_SetCompare(250);
    MCAL_TIMER0_Init(&config);

    MCAL_TIMER0_Stop();
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

    /*Initialize the SPI module to communicate with the admin ECU*/
    SPI_Init();

    /*Initialize the LCD module to print messages to the driver*/
    LCD_Init();

    /*Initialize the Timer module to help us get out of any undesired state*/
    Timer0_Init();

    /*Set the initial state*/
    fptr_st_UserAdminInterface = st_UAI_ShowWelcomeMsg;
}

/**
 * @brief this state prints the welcome message to guide the user on what to do.  
 * 
 */
void st_UAI_ShowWelcomeMsg(void)
{
    Glob_u8ModuleCurrentState = UAI_IDLE; 

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
    
    LCD_Clear_Screen();
    LCD_Cursor_XY(LCD_SECOND_LINE, 4);
    LCD_Send_String(stringfy("Processing!"));

    /*Set the current state of the module*/
    Glob_u8ModuleCurrentState = UAI_SENDING_ID;

    /*Toggle the ADMIN_ECU_INTERRUPT_PIN to alert the admin that we need attention*/
    MCAL_GPIO_TogglePin(ADMIN_ECU_INTERRUPT_PORT, ADMIN_ECU_INTERRUPT_PIN);

    /*Enable the timer to prevent getting stuck in this state forever*/
    MCAL_TIMER0_SetCounter(0x00);
    MCAL_TIMER0_Start();

    fptr_st_UserAdminInterface = st_UAI_Idle;
}


/**
 * @brief This state sends the open gate request and informs the driver that his ID is valid.
 * 
 */
void st_UAI_IDAuthenticationPassed(void)
{
    LCD_Clear_Screen();

    LCD_Cursor_XY(LCD_SECOND_LINE, 4);
    LCD_Send_String(stringfy("VALID ID!"));

    /** @defgroup Testing to be deleted
      * @{
      */
        MCAL_TIMER0_SetCounter(0x00);
        MCAL_TIMER0_Start();

        fptr_st_UserAdminInterface = st_UAI_Idle;
    /**
      * @}
      */
}

/**
 * @brief This state informs the driver that his ID is invalid.
 * 
 * 
 */
void st_UAI_IDAuthenticationFailed(void)
{
    LCD_Clear_Screen();

    LCD_Cursor_XY(LCD_SECOND_LINE, 3);
    LCD_Send_String(stringfy("INVALID ID!"));

    MCAL_TIMER0_SetCounter(0x00);
    MCAL_TIMER0_Start();

    fptr_st_UserAdminInterface = st_UAI_Idle;
}