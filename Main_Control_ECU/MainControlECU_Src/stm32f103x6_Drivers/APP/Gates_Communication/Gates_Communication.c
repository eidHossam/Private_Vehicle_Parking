/**
 * @file Gates_Communication.c
 * 
 * @brief this file implements 
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 09-03-2024
 * 
 * @version 1.0
 */

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Gates_Communication.h"

/** @defgroup Local Macros
  * @{
  */
#define MAX_NUMBER_OF_REQUESTS        2
/**
  * @}
  */


/** @defgroup Local Variables
  * @{
  */
static sGateRequestInfo_t LOC_szGatesRequests[MAX_NUMBER_OF_REQUESTS];
static sFIFO_Buf_t LOC_sQueueBuffer;

static sGateRequestInfo_t LOC_sTempRequest;
/**
  * @}
  */



/** @defgroup ISR_CALLBACK_DEFINITIONS
  * @{
  */
void SPI_TXEmpty_ISR_Callback(void)
{
    static uint8 LOC_u8TransmitCounter = 0;
    
    
    if(LOC_u8TransmitCounter == 0)
    {
        MCAL_SPI_ReceiveData(SPI1, (uint16 *)&LOC_sTempRequest.GateAddress, PollingDisable);
    }else{
        MCAL_SPI_ReceiveData(SPI1, (uint16 *)&LOC_sTempRequest.szDriverID[LOC_u8TransmitCounter - 1], PollingDisable);
    }

    LOC_u8TransmitCounter++;

    /*If we received all the required information add it to the queue*/
    if(LOC_u8TransmitCounter == 4)
    {
        LOC_sTempRequest.szDriverID[LOC_u8TransmitCounter - 1] = '\0';
        
        LOC_u8TransmitCounter = 0;

        FIFO_enqueue(&LOC_sQueueBuffer, LOC_sTempRequest);
    }else{
        /*Dummy data to receive the information from the slave*/
        uint16 *LOC_pu16TxBuffer;
        *LOC_pu16TxBuffer = 0x0000u;

        MCAL_SPI_SendData(SPI1, LOC_pu16TxBuffer, PollingDisable);    
    }
}

void EXTI_Line4_ISR_Callback(void)
{
    uint16 *LOC_pu16TxBuffer;
    *LOC_pu16TxBuffer = 0xFFFFu;


    MCAL_SPI_SendData(SPI1, LOC_pu16TxBuffer, PollingDisable);
}
/**
  * @}
  */


/** @defgroup Private Functions
  * @{
  */
void SPI_Init(void)
{
    uint16 *dummy;
    SPI_Config_t config;
	config.SPI_Mode = SPI_MODE_MASTER;
	config.SPI_Direction = SPI_DIRECTION_2LINES_FULL_DUPLEX;
	config.SPI_DataSize = SPI_DATA_SIZE_8BIT;
	config.SPI_BitOrder = SPI_FIRST_BIT_LSB;
	config.SPI_ClockPolarity = SPI_IDLE_HIGH;
	config.SPI_ClockPhase = SPI_SAMPLE_SECOND_EDGE;
	config.SPI_NSS_Managment = SPI_NSS_SW_SET;
	config.SPI_BR_Prescaler = SPI_BAUD_RATE_PRESCALER_8;

	MCAL_SPI_Init(SPI1, &config);
    *dummy = 0x0000;
    MCAL_SPI_SendData(SPI1, dummy, PollingEnable);
    
    MCAL_SPI_Interrupt_EN(SPI1, SPI_IRQ_TXEIE, SPI_TXEmpty_ISR_Callback);

    /*Give the SPI interrupt higher priority as it's more important*/
    MCAL_NVIC_SetPriority(NVIC_SPI1_IVT_INDEX, NVIC_PRIORITY_5);
}

void EXTI_Init(void)
{
    EXTI_config_t config;

    config.PinConfig = EXTI_GPIOA_PIN4;
    config.EXTI_Trigger_Mode = EXTI_TRIGGER_BOTH_EDGES;
    config.EXTI_En = EXTI_ENABLE;
    config.EXTI_Priority = NVIC_PRIORITY_10;
    config.P_callback_func = EXTI_Line4_ISR_Callback;

    MCAL_EXTI_Enable(&config);
}


void FIFOBuff_Init(void)
{
    FIFO_init(&LOC_sQueueBuffer, LOC_szGatesRequests, MAX_NUMBER_OF_REQUESTS);
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
 * @brief This state initializes the main components needed for the communication module.
 * 
 */
void st_GatesComm_Init(void)
{
    /*Initialize the SPI module to communicate with the gates ECUs*/
    SPI_Init();

    /*Initialize the EXTI module to communicate with the gates ECUs*/
    EXTI_Init();

    /*Initialize the queue to store the gates requests*/
    FIFOBuff_Init();

    /*Set the initial state*/
    fptr_GateCommState = st_GatesComm_CheckPendingRequests;
}

/**
 * @brief This state checks if there are any pending requests that needs processing.
 * 
 */
void st_GatesComm_CheckPendingRequests(void)
{
    sGateRequestInfo_t request;
    if(LOC_sQueueBuffer.size == 2)
    {
        LCD_Cursor_XY(LCD_FIRST_LINE, 0);

        FIFO_dequeue(&LOC_sQueueBuffer, &request);
        LCD_Send_Char(request.GateAddress);
        LCD_Send_String(request.szDriverID);

        LCD_Cursor_XY(LCD_SECOND_LINE, 0);
        FIFO_dequeue(&LOC_sQueueBuffer, &request);
        LCD_Send_String(request.szDriverID);
        LCD_Send_Char(request.GateAddress);
    }
}
