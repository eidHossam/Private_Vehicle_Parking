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
/**
  * @}
  */


/** @defgroup Local Variables
  * @{
  */
static uint8_t LOC_u8DriverID[DRIVER_ID_SIZE + 1];
static const uint8_t LOC_u8GateAddress = ENTRANCE_GATE_ECU_ADDRESS;
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
        /*Add a NULL character at the end*/
        LOC_u8DriverID[sLOC_u8CharCounter] = '\0';

        sLOC_u8CharCounter = 0;
 
        /*Disable the UART to stop it from serving another customer 
          until processing this customer's request*/
        MCAL_UART_Disable();

        fptr_st_UserAdminInterface = st_UAI_SendIDToAdmin;
    }else{

    }
}

static void SPI_ISR_Callback(void)
{
    static uint8_t sLOC_u8CharCounter = 0;

    if(sLOC_u8CharCounter == 0)
    {
        MCAL_SPI_SendData((uint8_t *)&LOC_u8GateAddress, PollingDisable);
    }else{
        MCAL_SPI_SendData(&LOC_u8DriverID[sLOC_u8CharCounter - 1], PollingDisable);
    }
            
    sLOC_u8CharCounter++;

    if(sLOC_u8CharCounter == (DRIVER_ID_SIZE + 1))
    {
        sLOC_u8CharCounter = 0;

        fptr_st_UserAdminInterface = st_UAI_Idle;
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
    
    LCD_Clear_Screen();
    LCD_Cursor_XY(LCD_SECOND_LINE, 4);
    LCD_Send_String(stringfy("Processing!"));

    /*Toggle the ADMIN_ECU_INTERRUPT_PIN to alert the admin that we need attention*/
    MCAL_GPIO_TogglePin(ADMIN_ECU_INTERRUPT_PORT, ADMIN_ECU_INTERRUPT_PIN);
        
    
    fptr_st_UserAdminInterface = st_UAI_Idle;
}
