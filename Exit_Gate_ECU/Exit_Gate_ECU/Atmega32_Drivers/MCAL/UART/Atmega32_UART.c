/**
 * @file Atmega32_UART.c
 * 
 * @brief  This module contains functions for configuring and controlling the USART module.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 08-03-2024
 * 
 * @version 1.0
 */

/*
===============================================
*                   Includes
*===============================================
*/
#include "Atmega32_UART.h"
#include "Atmega32.h"

/**************************************************************************************************************************
===============================================
*           LOCAL MACROS
*===============================================
*/
/** @defgroup BAUDRATE_CALCULATION_MACROS
  * @{
  */
#define USART_NORMAL_MODE           16u
#define USART_2xSPEED_MODE          8u
#define USART_SYNCH_MODE            2u

#define USART_UBRR_VALUE(CLK, baudRate, mode)     ((uint16_t)((F_CPU / (mode * baudRate)) - 1))

#define USART_ASSERT_UBRR_VALUE(ubrr) ((ubrr >= 0) && (ubrr <= 4095))

/**
  * @}
  */

/**************************************************************************************************************************
===============================================
*           Local Variables
*===============================================
*/
static sUSART_config_t LOC_cfg;

static Ptr_Func LOC_fptr_RXC_callback  = NULL;
static Ptr_Func LOC_fptr_TXC_callback  = NULL;
static Ptr_Func LOC_fptr_UDRE_callback = NULL;

/**************************************************************************************************************************
===============================================
*           Private Functions
*===============================================
*/


/**************************************************************************************************************************
===============================================
*           APIs functions definitions
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Init
* @brief		:   Intitialization of UART instance using the specified parameters in the config structure.
* @param [in]	:   config: specifies the configuration parameters for the specified UART instance.
* @return       :   eStatus_t: E_OK if the initialization was successfull, E_NOK otherwise
* @note		    :   To enable any of the interrupts use the function "MCAL_UART_Interrupt_EN".
* @note         :   In case of synchronous operation the xCKn pin have to be configured manually.
======================================================================================================================
*/
eStatus_t MCAL_UART_Init(sUSART_config_t* config)
{
    eStatus_t LOC_status = E_OK;
    uint16_t  LOC_u16BaudRate = 0;
    uint8_t   LOC_u8BaudRateDivisor = 0;
    uint8_t   LOC_u8TempReg = 0;

    LOC_cfg = *config;

    /*1. Calculate the baud-rate*/
    /*Determina the appropriate divisor based on the clock mode*/
    LOC_u8BaudRateDivisor = (config->USART_CLKOperation == USART_CLKOP_NormalAsynch)? USART_NORMAL_MODE :
                            (config->USART_CLKOperation == USART_CLKOP_2xSpeedAsynch)? USART_2xSPEED_MODE : USART_SYNCH_MODE; 

    /*Calculate the baudrate*/
    LOC_u16BaudRate = USART_UBRR_VALUE(F_CPU, config->USART_baudRate, LOC_u8BaudRateDivisor);
    
    if(USART_ASSERT_UBRR_VALUE(LOC_u16BaudRate))
    {
        USART->UBRRL = (uint8_t)(LOC_u16BaudRate);
        
        if(LOC_u16BaudRate > 255)
        {
            USART_UBRRH = (((uint8_t)0x0F) & ((uint8_t)(LOC_u16BaudRate >> 8)));
        }else{

        }

        /** @defgroup Configuring the UCSRC frame format
          * @{
          */
        LOC_u8TempReg |= (USART_UCSRC_URSEL_MASK);

        /*Set the clock operation mode for the USART*/
        if(config->USART_CLKOperation == USART_CLKOP_Synch)
        {
            LOC_u8TempReg |= (USART_UCSRC_UMSEL_MASK);
        }else{
            LOC_u8TempReg &= ~(USART_UCSRC_UMSEL_MASK);

            if(config->USART_CLKOperation == USART_CLKOP_2xSpeedAsynch)
            {
                /*Enbale the 2x speed mode*/
                USART->UCSRA |= USART_UCSRA_U2X_MASK;
            }else{

                USART->UCSRA &= ~USART_UCSRA_U2X_MASK;
            }
        }
        LOC_u8TempReg |= config->USART_parityCTRL;  /*Setting the parity control*/

        LOC_u8TempReg |= config->USART_stopBits;    /*Setting the number of stop bits*/

        /*Setting the word length*/
        if(config->USART_wordLength == USART_9BitWord)
        {
            LOC_u8TempReg |= USART_UCSRC_UCSZ_MASK;

            USART->UCSRB = USART_UCSRB_UCSZ2_MASK;
        }else{
            LOC_u8TempReg |= config->USART_wordLength;
        }

        USART_UCSRC = (1 << 7) | LOC_u8TempReg;
        /**
          * @}
          */ 
        

        /** @defgroup Configuring UCSRB TX - RX
          * @{
          */
        LOC_u8TempReg = 0;
        LOC_u8TempReg |= config->USART_Mode;

        USART->UCSRB = LOC_u8TempReg;
        /**
          * @}
          */
    }else{
        LOC_status = E_NOK;
    }

    return LOC_status;
} 

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_RESET
* @brief		:   Reset the specified UART instance to its original state.
* @@note			:   none.
======================================================================================================================
*/
void MCAL_UART_RESET()
{
    USART->UDR   = 0x00u;
    USART->UCSRA = 0x20u;
    USART->UCSRB = 0x00u;
    USART_UCSRC  = 0x82u;
    USART->UBRRL = 0x00u;
    USART_UBRRH  = 0x00u;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Disable
* @brief		:   Function to disable the UART TX and RX channels.
* @note			:   none
======================================================================================================================
*/
void MCAL_UART_Disable()
{
    USART->UCSRB &= ~(USART_UCSRB_RXEN_MASK | USART_UCSRB_TXEN_MASK);
}

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Enable
* @brief		:   Function to enable the UART TX and RX channels (Based on the user configuration).
* @note			:   none.
======================================================================================================================
*/
void MCAL_UART_Enable()
{
    USART->UCSRB |= LOC_cfg.USART_Mode;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Send_Data
* @brief		:   Sends data through the UART instance.
* @param [in]	:   pTxBuffer: pointer to the data to be sent.
* @param [in]	:   PollingEn: Whether to use the polling mechanism or not, must be set based on @ref UART_POLLING_DEFINE.
* @return       :   none.
* @note			:   none.
======================================================================================================================
*/
void MCAL_UART_Send_Data(uint16_t* pTxBuffer, eUSART_PollingMode_t PollingEn)
{
    if(PollingEn == USART_PollingEnabled)
    {
        while(!(READ_BIT(USART->UCSRA, USART_UCSRA_UDRE_POS)))
        {

        }
    }else{

    }

    if(LOC_cfg.USART_wordLength == USART_9BitWord)
    {
        USART->UCSRB &= ~(USART_UCSRB_TXB8_MASK);

        USART->UCSRB |= (uint8_t)(USART_UCSRB_TXB8_MASK & (*(pTxBuffer) >> 8));
    }else{

    }

    USART->UDR = (uint8_t)(*(pTxBuffer));
}

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Get_Data
* @brief		:   Receives the data from the UART.
* @param [in]	:   PollingEn: Whether to use the polling mechanism or not, must be set based on @ref UART_POLLING_DEFINE.
* @param [out]	:   pRxBuffer: pointer to the buffer to receive the data in.
* @return       :   eStatus_t: E_OK if the initialization was successfull, E_NOK otherwise
* @note			:   none.
======================================================================================================================
*/
eStatus_t MCAL_UART_Get_Data(uint16_t* pRxBuffer, eUSART_PollingMode_t PollingEn)
{
    eStatus_t LOC_eStatus = E_OK;

    if(PollingEn == USART_PollingEnabled)
    {
        /* Wait for data to be received */
        while(!(READ_BIT(USART->UCSRA, USART_UCSRA_RXC_POS)))
        {

        }
    }else{

    }
    
    /* Get status and 9th bit, then data */
    /* from buffer */

    if(READ_BIT(USART->UCSRA, USART_UCSRA_FE_POS) || 
       READ_BIT(USART->UCSRA, USART_UCSRA_PE_POS) ||
       READ_BIT(USART->UCSRA, USART_UCSRA_DOR_POS))
    {
        LOC_eStatus = E_NOK;

    }else{
        *pRxBuffer = 0;
        
        if(LOC_cfg.USART_wordLength == USART_9BitWord)
        {
            /*Read 9th bit*/
            *pRxBuffer |=  (READ_BIT(USART->UCSRB, USART_UCSRB_RXB8_POS) << 8);
        }else{

        }

        *pRxBuffer = (uint16_t)USART->UDR;
    }
    
    return LOC_eStatus;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_USART_Send_String
* @brief		:   Sends a string through the USART.
* @param [in]	:   string to send.
* @param [out]	:   none.
* @return       :   none.
* @note			:   This function works with the polling mechanism.
======================================================================================================================
*/
void MCAL_USART_Send_String(uint8_t* string)
{
    while(*string)
    {
        MCAL_UART_Send_Data((uint16_t *)string, USART_PollingEnabled);
		
		string++;
    }
}

/**
======================================================================================================================
* @Func_name	:   MCAL_USART_Get_String
* @brief		:   Receives a string through the USART.
* @param [in]	:   buffer the buffer to store the string in.
* @param [in]	:   bufferSize: maximum length of the string to be received.
* @return       :   none.
* @note			:   This function will receive characters until the end of the string or until the return carriage *               :   character is pressed.
======================================================================================================================
*/
void MCAL_USART_Get_String(uint8_t* buffer, uint8_t bufferSize)
{
    uint8_t count = 0, input;
    while(count < bufferSize - 1)
    {
        input = MCAL_UART_Get_Data((uint16_t*)&input, USART_PollingEnabled);
        if(input == '\r')
        {
            break;
        }
        buffer[count++] = input; 
    }

    buffer[count] = '\0';
}

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_WAIT_TC
* @brief		:   This function waits for the transmission of data from the UART to be completed.
* @param [in]	:   none.
* @param [out]	:   none.
* @return       :   none.
* @note			:   none.
======================================================================================================================
*/
void MCAL_UART_WAIT_TC()
{
    /*Wait until the transmission complete flag is set*/
    while(!READ_BIT(USART->UCSRA, USART_UCSRA_TXC_POS))
    {

    }
}

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Interrupt_EN
* @brief		:   Enable a specific interrupt and set its callback function.
* @param [in]	:   IRQ: specifies the interrupt to be enabled, must be set based on @ref USART_IRQ_DEFINE.
* @param [in]	:   p_IRQ_callback: pointer to the callback function to be executed.
* @return       :   eStatus_t: E_OK if the initialization was successfull, E_NOK otherwise
* @note			:   none.
======================================================================================================================
*/
eStatus_t MCAL_UART_Interrupt_EN(eUSART_IRQ_t IRQ, Ptr_Func callback)
{
    eStatus_t LOC_eStatus = E_OK;

    if(callback)
    {   
        /*Enable general interrupts*/
        G_INTERRUPT_ENABLE;

        switch (IRQ)
        {
        case USART_IRQ_RXC:
            SET_BIT(USART->UCSRB, USART_UCSRB_RXCIE_POS);
            LOC_fptr_RXC_callback = callback;
            break;

        case USART_IRQ_TXC:
            SET_BIT(USART->UCSRB, USART_UCSRB_TXCIE_POS);
            LOC_fptr_TXC_callback = callback;
            break;

        case USART_IRQ_UDRE:
            SET_BIT(USART->UCSRB, USART_UCSRB_UDREIE_POS);
            LOC_fptr_UDRE_callback = callback;
            break;
        
        default:
            LOC_eStatus = E_NOK;
            break;
        }

    }else{
        LOC_eStatus = E_NOK;
    }

    return LOC_eStatus;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Interrupt_Disable
* @brief		:   Disable a specific interrupt
* @param [in]	:   IRQ: specifies the interrupt to be disabled, must be set based on @ref USART_IRQ_DEFINE.
* @return       :   none.
* @note			:   none.
======================================================================================================================
*/
void MCAL_UART_Interrupt_Disable(eUSART_IRQ_t IRQ)
{
    switch (IRQ)
    {
    case USART_IRQ_RXC:
        CLEAR_BIT(USART->UCSRB, USART_UCSRB_RXCIE_POS);
        break;
    
    case USART_IRQ_TXC:
        CLEAR_BIT(USART->UCSRB, USART_UCSRB_TXCIE_POS);
        break;
    
    case USART_IRQ_UDRE:
        CLEAR_BIT(USART->UCSRB, USART_UCSRB_UDREIE_POS);
        break;
    
    default:
        break;
    }
}


/**************************************************************************************************************************
===============================================
*               SPI ISR Definitions
*===============================================
*/

/**
 * @brief This is the ISR for the USART RXC (USART, Rx Complete) 
 * 
 */
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void){

  	LOC_fptr_RXC_callback();
}

/**
 * @brief This is the ISR for the USART UDRE (USART Data Register Empty) 
 * 
 */
void __vector_14 (void) __attribute__((signal));
void __vector_14 (void){

  	LOC_fptr_UDRE_callback();
}

/**
 * @brief This is the ISR for the USART TXC (USART, Tx Complete) 
 * 
 */
void __vector_15 (void) __attribute__((signal));
void __vector_15 (void){

  	LOC_fptr_TXC_callback();
}