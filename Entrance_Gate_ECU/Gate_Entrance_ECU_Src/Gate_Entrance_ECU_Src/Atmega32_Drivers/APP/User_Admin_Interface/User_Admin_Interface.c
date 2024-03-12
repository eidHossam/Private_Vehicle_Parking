/**
 * @file User_Admin_Interface.c
 * 
 * @brief This file contains the APIs and the states declarations for the main module of the entrance gate ECU,
 * This module is responsible for the communication between this ECU and the main admin ECU, It's is also responsible
 * for sending the signals to the Gate_Control and Alarm_Manager modules.
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
/*Unique address of this gate*/
#define ENTRANCE_GATE_ECU_ADDRESS       0xE7u

/*The size of the driver's ID*/
#define DRIVER_ID_SIZE                  3

/** @defgroup The configuration of the pin connected to the EXTI line of th admin ECU
  * @{
  */
#define ADMIN_ECU_INTERRUPT_PORT        GPIOB
#define ADMIN_ECU_INTERRUPT_PIN         GPIO_PIN3
/**
  * @}
  */

/**
 * @brief Time delay in ms before considering the system to be stuck and reset it.
 * 
 */
#define TIME_BEFORE_RESET_MS            1000u      

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
* @Func_name	:  Timer0_SingleIntervalDelaycallback
* @brief		  :  This function is the callback function for the Timer0_SingleIntervalDelayms function.
======================================================================================================================
*/
static void Timer0_SingleIntervalDelaycallback(void)
{
  fptr_st_UserAdminInterface = st_UAI_ShowWelcomeMsg;
}

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
        MCAL_TIMER0_SingleIntervalDelayms(TIME_BEFORE_RESET_MS, Timer0_SingleIntervalDelaycallback);

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

    MCAL_SPI_ReceiveData(&LOC_u8RxBuffer, PollingEnable);

    /*If we already received the gate ID from the last transmission 
      then check the authentication result*/
    if(LOC_boolDetectedGateAddress)
    { 
        /*Stop the timer as we are already done from this state*/
        MCAL_TIMER0_Stop();

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
            MCAL_SPI_SendData(&LOC_u8RxBuffer , PollingEnable);
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
    /*Turn off the cursor for a more clean feel*/
    LCD_Send_Command(LCD_CURSOR_OFF);
    
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

    MCAL_TIMER0_SingleIntervalDelayms(TIME_BEFORE_RESET_MS, Timer0_SingleIntervalDelaycallback);

    /*Toggle the ADMIN_ECU_INTERRUPT_PIN to alert the admin that we need attention*/
    MCAL_GPIO_TogglePin(ADMIN_ECU_INTERRUPT_PORT, ADMIN_ECU_INTERRUPT_PIN);

    fptr_st_UserAdminInterface = st_UAI_Idle;
}


/**
 * @brief This state sends the open gate request and informs the driver that his ID is valid.
 * 
 */
void st_UAI_IDAuthenticationPassed(void)
{
    /*Send a signal to the alarm manager*/
    UAI_AM_ValidID();

    /*Send a signal to the gate controller to open the gate*/
    UAI_GC_OpenGateReuest();

    fptr_st_UserAdminInterface = st_UAI_Idle;
}

/**
 * @brief This state informs the driver that his ID is invalid.
 * 
 * 
 */
void st_UAI_IDAuthenticationFailed(void)
{
    /*Send a signal to the Alarm_Manager module.*/
    UAI_AM_InvalidID();    

    fptr_st_UserAdminInterface = st_UAI_Idle;
}


/** @defgroup Signals between the User_Admin_Interface and the Gate_Controller.
  * @{
  */

/**
 * @brief This is a signal from the Gate_Controller module to the User_Admin_Interface module to inform 
 * it that the car passed the gate and we are ready to serve the next driver.
 * 
 */
void GC_UAI_GateClosed(void)
{
  /*Send a signal to turn off the alarm*/
  UAI_AM_TurnOffAlarmGateClosed();

  /*Return to the original state to serve the next customer*/
  fptr_st_UserAdminInterface = st_UAI_ShowWelcomeMsg;
}

/**
  * @}
  */

 /** @defgroup Signals between the User_Admin_Interface and the Alarm_Manager modules.
   * @{
   */

/**
 * @brief  This is a signal from the Alarm_Manager module to the User_Admin_InterfaceA module to inform
 * it that the alarm duration has ended.
 * 
 */
void AM_UAI_AlarmOff()
{
 fptr_st_UserAdminInterface = st_UAI_ShowWelcomeMsg;
}

 /**
   * @}
   */