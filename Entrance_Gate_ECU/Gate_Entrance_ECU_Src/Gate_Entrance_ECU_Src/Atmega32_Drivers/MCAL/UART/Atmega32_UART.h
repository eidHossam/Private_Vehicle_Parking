/**
 * @file    Atmega32_UART.h
 * 
 * @brief  This module contains functions for configuring and controlling the USART module.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 08-03-2024
 * 
 * @version 1.0
 */

#ifndef ATMEGA32_UART_H_
#define ATMEGA32_UART_H_

/*===============================================
* Includes
*===============================================
*/
#ifndef F_CPU
#define F_CPU  8000000UL
#endif

#include "Atmega32.h"

/**************************************************************************************************************************
*===============================================
*         Configuration References
*===============================================
*/

/**
 * @ref USART_CLKOP_DEFINE
 * 
 * @brief This enum specifies the configuration for the USART module clock (Asynchronous - Synchronous)
 * 
 * @param USART_CLKOP_NormalAsynch : Normal operation mode for the USART with no use of a clock and normal speed.
 * 
 * @param USART_CLKOP_2xSpeedAsynch: Normal operation mode for the USART with no use of a clock and double speed. 
 * 
 * @param USART_CLKOP_Synch  : synchronous operation for the USART with a clock generated from xCKn pin.
 *  
 */
typedef enum {
    USART_CLKOP_NormalAsynch,
    USART_CLKOP_2xSpeedAsynch,
    USART_CLKOP_Synch
}eUSART_Clockoperation_t;

/**
 * @ref USART_MODE_DEFINE
 * 
 * @brief This enum specifies the which communication mode to be enabled.
 */
typedef enum{
    USART_ModeTX    =  USART_UCSRB_TXEN_MASK,
    USART_ModeRX    =  USART_UCSRB_RXEN_MASK,
    USART_ModeTXRX  =  USART_UCSRB_TXEN_MASK | USART_UCSRB_RXEN_MASK
}eUSART_TXRX_t;

/**
 * @ref     UART_BAUD_RATE_DEFINE
 * 
 * @brief This enum defines the baud rate of the USART module.
 */
typedef enum{
    USART_BAUD_RATE_2400     = 2400,
    USART_BAUD_RATE_9600     = 9600,
    USART_BAUD_RATE_19200    = 19200,
    USART_BAUD_RATE_57600    = 57600,
    USART_BAUD_RATE_115200   = 115200,
    USART_BAUD_RATE_230400   = 230400,
    USART_BAUD_RATE_460800   = 460800,
    USART_BAUD_RATE_921600   = 921600,
    USART_BAUD_RATE_2250000  = 2250000,
    USART_BAUD_RATE_4500000  = 4500000
}eUSART_BaudRate_t;

/**
 * @ref USART_DEFINE_WORD
 * 
 * @brief This enum specifies the size of the word transmitted and received via the USART module.
 * 
 */
typedef enum {
    USART_5BitWord,
    USART_6BitWord = USART_UCSRC_UCSZ0_MASK,
    USART_7BitWord = USART_UCSRC_UCSZ1_MASK,
    USART_8BitWord = USART_UCSRC_UCSZ_MASK,
    USART_9BitWord
}eUSART_WordLenght_t;

/**
 * @ref USART_DEFINE_STOPBIT
 * 
 * @brief This enum specifies the number of stop bits in the USART payload.
 */
typedef enum {
    USART_1StopBit,
    USART_2StopBit = USART_UCSRC_USBS_MASK
}eUSART_StopBits_t;


/**
 * @ref USART_PARITYMODE_DEFINE
 * 
 * @brief This enum specifies the parity mode of the USART.
 */
typedef enum {
    USART_ParityMode_Disabled,
    USART_ParityMode_Even = USART_UCSRC_UPM1_MASK,
    USART_ParityMode_Odd  = USART_UCSRC_UPM_MASK 
}eUSART_ParityMode_t;


/**
 * @brief This enum specifies if we are working with interrupts or polling mode.
 * 
 */
typedef enum{
    USART_PollingEnabled,
    USART_PollingDisabled
}eUSART_PollingMode_t;

/**
 * @ref UART_POLLING_DEFINE.
 * 
 * @brief This enum specifies what interrupt we are working with.
 * 
 * @param USART_IRQ_RXC : USART Receive Complete, Raise an interrupt when there are unread data in the receive buffer.
 * 
 * @param USART_IRQ_TXC : USART Transmit Complete, Raise an interrupt when the entire frame in the Transmit Shift
 *  Register has been shifted out
 * 
 * @param USART_IRQ_UDRE: USART Data Register Empty, Raise an interrupt when the transmit buffer (UDR) is ready to receive
 *  new data.
 */
typedef enum{
    USART_IRQ_RXC  = (1 << 7),
    USART_IRQ_TXC  = (1 << 6),
    USART_IRQ_UDRE = (1 << 5)
}eUSART_IRQ_t;

/**************************************************************************************************************************
*===============================================
* User type definitions (structures)
*===============================================
*/
typedef struct{
    eUSART_Clockoperation_t     USART_CLKOperation;    /** Specifies the clock operating mode of the USART 
                                                        must be set based on @ref USART_CLKOP_DEFINE*/

    eUSART_TXRX_t               USART_Mode;            /** Specifies the operating mode of the USART (TX - RX - TXRX)
                                                        must be set based on @ref USART_MODE_DEFINE*/

    eUSART_BaudRate_t           USART_baudRate;       /** Specifies the operating baud rate of the USART 
                                                        must be set based on @ref UART_BAUD_RATE_DEFINE*/ 

    eUSART_WordLenght_t         USART_wordLength;     /** Specifies the data word length of the USART payload 
                                                        must be set based on @ref USART_DEFINE_WORD*/

    eUSART_StopBits_t           USART_stopBits;       /** Specifies the number of stop bits of the USART frame 
                                                        must be set based on @ref USART_DEFINE_STOPBIT*/
    
    eUSART_ParityMode_t         USART_parityCTRL;     /** Specifies the parity of the UART frame 
                                                        must be set based on @ref USART_PARITYMODE_DEFINE*/
}sUSART_config_t;


/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL USART DRIVER"
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Init
* @brief		:   Intitialization of UART instance using the specified parameters in the config structure.
* @param [in]	:   config: specifies the configuration parameters for the specified UART instance.
* @return       :   eStatus_t: E_OK if the initialization was successfull, E_NOK otherwise.
* @@note	    :   To enable any of the interrupts use the function "MCAL_UART_Interrupt_EN".
======================================================================================================================
*/
eStatus_t MCAL_UART_Init( sUSART_config_t* config);

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_RESET
* @brief		:   Reset the specified UART instance to its original state.
* @@note			:   none.
======================================================================================================================
*/
void MCAL_UART_RESET();

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Disable
* @brief		:   Function to disable the UART TX and RX channels.
* @note			:   none
======================================================================================================================
*/
void MCAL_UART_Disable();

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Enable
* @brief		:   Function to enable the UART TX and RX channels (Based on the user configuration).
* @note			:   none.
======================================================================================================================
*/
void MCAL_UART_Enable();

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
void MCAL_UART_Send_Data(uint16_t* pTxBuffer, eUSART_PollingMode_t PollingEn);

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
eStatus_t MCAL_UART_Get_Data(uint16_t* pRxBuffer, eUSART_PollingMode_t PollingEn);


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
void MCAL_USART_Send_String(uint8_t* string);

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
void MCAL_USART_Get_String(uint8_t* buffer, uint8_t bufferSize);

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
void MCAL_UART_WAIT_TC();

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
eStatus_t MCAL_UART_Interrupt_EN(eUSART_IRQ_t IRQ, Ptr_Func callback);

/**
======================================================================================================================
* @Func_name	:   MCAL_UART_Interrupt_Disable
* @brief		:   Disable a specific interrupt
* @param [in]	:   IRQ: specifies the interrupt to be disabled, must be set based on @ref USART_IRQ_DEFINE.
* @return       :   none.
* @note			:   none.
======================================================================================================================
*/
void MCAL_UART_Interrupt_Disable(eUSART_IRQ_t IRQ);

#endif /* ATMEGA32_UART_H_ */