/**
 * @file Gates_Communication.c
 * 
 * @brief This file contains all the functions definitions and APIs implementation  
 * for the module responsible for communicating with the entrance and exit gates
 * and its the bridge between the gates and the admin interface that is responsible  
 * for authenticating the IDs.
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

#define NUMBER_OF_GARAGE_SLOTS        3

/** @defgroup AUTHENTICATION_RESULT
  * @{
  */
#define AUTHENTICATION_RESULT_PASS     0xFFu
#define AUTHENTICATION_RESULT_FAIL     0x00u
/**
  * @}
  */

/** @defgroup GATES_ECUS_ADDRESSES
  * @{
  */
#define ENTRANCE_GATE_ECU_ADDRESS       0xE7u
#define ENTRANCE_GATE_ECU_SPI           SPI1

#define EXIT_GATE_ECU_ADDRESS           0x7Eu
#define EXIT_GATE_ECU_SPI               SPI2
/**
  * @}
  */
/**
  * @}
  */


/** @defgroup Local Variables
  * @{
  */

/**
 * @brief Queue to hold all the requests from the 2 gates to be processed
 *  by following the First In First Out schema.
 * 
 */
static sFIFO_Buf_t Glob_sQueueBuffer;
static sGateRequestInfo_t Glob_szGatesRequests[MAX_NUMBER_OF_REQUESTS];

static sGateRequestInfo_t Glob_sEntranceGateRequest;
static sGateRequestInfo_t Glob_sExitGateRequest;

/**
 * @brief Holds the address of the gate which has a request currenlty being processed.
 * 
 */
static uint8 Glob_u8ServedRequestGateAddress;

static uint8 Glob_u8AvailableSlots = 3;
/**
  * @}
  */



/** @defgroup ISR_CALLBACK_DEFINITIONS
  * @{
  */
void ENTRANCE_GATE_ECU_SPI_TXEmpty_ISR_Callback(void)
{
    static uint8 LOC_u8TransmitCounter = 0;
    static uint8 LOC_u8FailedTrasnsmissionCounter = 0;
    
    if(LOC_u8TransmitCounter == 0)
    {
        MCAL_SPI_ReceiveData(ENTRANCE_GATE_ECU_SPI, (uint16 *)&Glob_sEntranceGateRequest.GateAddress, PollingDisable);
        
        /*Wait the acknowledge byte from the slave*/
        if(Glob_sEntranceGateRequest.GateAddress != ENTRANCE_GATE_ECU_ADDRESS)
        {
            LOC_u8FailedTrasnsmissionCounter++;
            LOC_u8TransmitCounter--;
        }

    }else{
        MCAL_SPI_ReceiveData(ENTRANCE_GATE_ECU_SPI, 
                            (uint16 *)&Glob_sEntranceGateRequest.szDriverID[LOC_u8TransmitCounter - 1], PollingDisable);
    }

    LOC_u8TransmitCounter++;

    /*If we received all the required information add it to the queue*/
    if(LOC_u8TransmitCounter == 4 || LOC_u8FailedTrasnsmissionCounter == 10)
    {
        if(LOC_u8FailedTrasnsmissionCounter != 10)
        {
            Glob_sEntranceGateRequest.szDriverID[LOC_u8TransmitCounter - 1] = '\0';
            
            FIFO_enqueue(&Glob_sQueueBuffer, Glob_sEntranceGateRequest);
        }

            LOC_u8TransmitCounter = 0;
    }else{
        /*Dummy data to receive the information from the slave*/
        uint16 LOC_pu16TxBuffer = 0x0000u;

        MCAL_SPI_SendData(ENTRANCE_GATE_ECU_SPI, &LOC_pu16TxBuffer, PollingDisable);    
    }
}

void EXIT_GATE_ECU_SPI_TXEmpty_ISR_Callback(void)
{
    static uint8 LOC_u8TransmitCounter = 0;
    static uint8 LOC_u8FailedTrasnsmissionCounter = 0;
    
    if(LOC_u8TransmitCounter == 0)
    {
        MCAL_SPI_ReceiveData(EXIT_GATE_ECU_SPI, (uint16 *)&Glob_sExitGateRequest.GateAddress, PollingDisable);
        
        /*Wait the acknowledge byte from the slave*/
        if(Glob_sExitGateRequest.GateAddress != EXIT_GATE_ECU_ADDRESS)
        {
            LOC_u8FailedTrasnsmissionCounter++;
            LOC_u8TransmitCounter--;
        }

    }else{
        MCAL_SPI_ReceiveData(EXIT_GATE_ECU_SPI, 
                            (uint16 *)&Glob_sExitGateRequest.szDriverID[LOC_u8TransmitCounter - 1], PollingDisable);
    }

    LOC_u8TransmitCounter++;

    /*If we received all the required information add it to the queue*/
    if(LOC_u8TransmitCounter == 4 || LOC_u8FailedTrasnsmissionCounter == 10)
    {
        if(LOC_u8FailedTrasnsmissionCounter != 10)
        {
            Glob_sExitGateRequest.szDriverID[LOC_u8TransmitCounter - 1] = '\0';
            
            FIFO_enqueue(&Glob_sQueueBuffer, Glob_sExitGateRequest);
        }

            LOC_u8TransmitCounter = 0;
    }else{
        /*Dummy data to receive the information from the slave*/
        uint16 LOC_pu16TxBuffer = 0x0000u;

        MCAL_SPI_SendData(EXIT_GATE_ECU_SPI, &LOC_pu16TxBuffer, PollingDisable);    
    }
}

/**
 * @brief The callback function for the external interrupt line connected to the 
 * entrance gate ECU. 
 * 
 */
void EXTI_Line4_ISR_Callback(void)
{
    uint16 LOC_pu16TxBuffer = 0xFFFFu;

    MCAL_SPI_SendData(ENTRANCE_GATE_ECU_SPI, &LOC_pu16TxBuffer, PollingDisable);
}

/**
 * @brief The callback function for the external interrupt line connected to the 
 * exit gate ECU. 
 * 
 */
void EXTI_Line12_ISR_Callback(void)
{
    uint16 LOC_pu16TxBuffer = 0xFFFFu;

    MCAL_SPI_SendData(EXIT_GATE_ECU_SPI, &LOC_pu16TxBuffer, PollingDisable);
}
/**
  * @}
  */


/** @defgroup Private Functions
  * @{
  */
void SPI_Init(void)
{
    SPI_Config_t config;

    /*Entrance Gate SPI*/
    config.SPI_Mode = SPI_MODE_MASTER;
	  config.SPI_Direction = SPI_DIRECTION_2LINES_FULL_DUPLEX;
	  config.SPI_DataSize = SPI_DATA_SIZE_8BIT;
	  config.SPI_BitOrder = SPI_FIRST_BIT_LSB;
	  config.SPI_ClockPolarity = SPI_IDLE_HIGH;
	  config.SPI_ClockPhase = SPI_SAMPLE_SECOND_EDGE;
	  config.SPI_NSS_Managment = SPI_NSS_SW_SET;
	  config.SPI_BR_Prescaler = SPI_BAUD_RATE_PRESCALER_8;

	  MCAL_SPI_Init(ENTRANCE_GATE_ECU_SPI, &config);
    
    MCAL_SPI_Interrupt_EN(ENTRANCE_GATE_ECU_SPI, SPI_IRQ_TXEIE, ENTRANCE_GATE_ECU_SPI_TXEmpty_ISR_Callback);

    /*Give the SPI interrupt higher priority as it's more important*/
    MCAL_NVIC_SetPriority(NVIC_SPI1_IVT_INDEX, NVIC_PRIORITY_5);

    /*Exit Gate SPI*/
	  MCAL_SPI_Init(EXIT_GATE_ECU_SPI, &config);
    
    MCAL_SPI_Interrupt_EN(EXIT_GATE_ECU_SPI, SPI_IRQ_TXEIE, EXIT_GATE_ECU_SPI_TXEmpty_ISR_Callback);

    /*Give the SPI interrupt higher priority as it's more important*/
    MCAL_NVIC_SetPriority(NVIC_SPI1_IVT_INDEX, NVIC_PRIORITY_6);
}

void EXTI_Init(void)
{
    EXTI_config_t config;

    /*Entrance gate ECU EXTI*/
    config.PinConfig = EXTI_GPIOA_PIN4;
    config.EXTI_Trigger_Mode = EXTI_TRIGGER_BOTH_EDGES;
    config.EXTI_En = EXTI_ENABLE;
    config.EXTI_Priority = NVIC_PRIORITY_10;
    config.P_callback_func = EXTI_Line4_ISR_Callback;

    MCAL_EXTI_Enable(&config);

    /*Exit gate ECU EXTI*/
    config.PinConfig = EXTI_GPIOB_PIN12;
    config.EXTI_Priority = NVIC_PRIORITY_11;
    config.P_callback_func = EXTI_Line12_ISR_Callback;

    MCAL_EXTI_Enable(&config);
}


void FIFOBuff_Init(void)
{
    FIFO_init(&Glob_sQueueBuffer, Glob_szGatesRequests, MAX_NUMBER_OF_REQUESTS);
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

    HAL_SevenSeg_Init();

    HAL_SevenSeg_DisplayNumber(NUMBER_OF_GARAGE_SLOTS);
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

    /*If there are any requests in the queue start processing them*/
    if(Glob_sQueueBuffer.size > 0)
    {
        /*Remove the request from the queue*/
        FIFO_dequeue(&Glob_sQueueBuffer, &request);

        /*Save the gate address*/
        Glob_u8ServedRequestGateAddress = request.GateAddress;

        AI_GC_SendIDForAuthentication(request.szDriverID);

        fptr_GateCommState = st_Admin_AuthenticateID;
    }
}

/**
 * @brief This state sends the request approval signal to the gate ECUs and to the 7-segment display to be updated.
 * 
 */
void st_GatesComm_SendIDApprovedSignal(void)
{
    uint16 LOC_u16TxBuffer = Glob_u8ServedRequestGateAddress;
    uint8 LOC_u8FailedTransmissionCount = 0;
    volatile SPI_Typedef* SPIx;
    fptr_Callback callback;

    /*Determine which SPI instance to used based on the gate being served*/
    if(Glob_u8ServedRequestGateAddress == ENTRANCE_GATE_ECU_ADDRESS)
    {
        SPIx = ENTRANCE_GATE_ECU_SPI;
        callback = ENTRANCE_GATE_ECU_SPI_TXEmpty_ISR_Callback;

        /* Decrease the number of slots available on the 7-segment display
           note: if the number of available slots is 0 (garage full) the 
           gate will open but the number of available slots won't change*/
        if(Glob_u8AvailableSlots > 0)
        {
          HAL_SevenSeg_Decrement();
          Glob_u8AvailableSlots--;
        }else{

        }
    }else{
        SPIx = EXIT_GATE_ECU_SPI;

        callback = EXIT_GATE_ECU_SPI_TXEmpty_ISR_Callback;

        /*Increase the number of slots available on the 7-segment display
          note: if the number of available slots is 3 (garage empty) the 
          gate will open but the number of available slots won't change*/
        if(Glob_u8AvailableSlots < NUMBER_OF_GARAGE_SLOTS)
        {
          HAL_SevenSeg_Increment();
          Glob_u8AvailableSlots++;

        }else{

        }
    }
        
    /*Disable the interrupts to send the signal using polling*/
    MCAL_SPI_Interrupt_Disable(SPIx, SPI_IRQ_TXEIE);

    do
    {
        LOC_u16TxBuffer = Glob_u8ServedRequestGateAddress;

        /*Send the address of the gate being served to act as the start of the frame*/
        MCAL_SPI_ExchangeData(SPIx, (uint16 *)&LOC_u16TxBuffer);

        /*Put a limit on the number of failed tries to avoid getting stuck in this loop*/
        LOC_u8FailedTransmissionCount++;

    } while ((LOC_u16TxBuffer != Glob_u8ServedRequestGateAddress) && 
              LOC_u8FailedTransmissionCount < 10);
    
    /*Check if we failed to get an aknowledge from the slave then abort*/
    if(LOC_u8FailedTransmissionCount < 10)
    {
        /*Send the successful authentication code*/
        LOC_u16TxBuffer = AUTHENTICATION_RESULT_PASS;
        MCAL_SPI_SendData(SPIx, &LOC_u16TxBuffer, PollingEnable);
    }else{

    }

    /*Enable the interrupts again*/
    MCAL_SPI_Interrupt_EN(SPIx, SPI_IRQ_TXEIE, callback);

    fptr_GateCommState = st_GatesComm_CheckPendingRequests;
}

/**
 * @brief This state sends the request disapproval to the gate ECU.
 * 
 */
void st_GatesComm_SendIDDisapprovedSignal(void)
{
    uint16 LOC_u16TxBuffer = Glob_u8ServedRequestGateAddress;
    uint8 LOC_u8FailedTransmissionCount = 0;
    volatile SPI_Typedef* SPIx;
    fptr_Callback callback;

    /*Determine which SPI instance to used based on the gate being served*/
    if(Glob_u8ServedRequestGateAddress == ENTRANCE_GATE_ECU_ADDRESS)
    {
        SPIx = ENTRANCE_GATE_ECU_SPI;
        callback = ENTRANCE_GATE_ECU_SPI_TXEmpty_ISR_Callback;

    }else{

        SPIx = EXIT_GATE_ECU_SPI;
        callback = EXIT_GATE_ECU_SPI_TXEmpty_ISR_Callback;
    }
        

    /*Disable the interrupts to send the signal using polling*/
    MCAL_SPI_Interrupt_Disable(SPIx, SPI_IRQ_TXEIE);

    do
    {
        LOC_u16TxBuffer = Glob_u8ServedRequestGateAddress;

        /*Send the address of the gate being served to act as the start of the frame*/
        MCAL_SPI_ExchangeData(SPIx, (uint16 *)&LOC_u16TxBuffer);

        /*Put a limit on the number of failed tries to avoid getting stuck in this loop*/
        LOC_u8FailedTransmissionCount++;

    } while ((LOC_u16TxBuffer != Glob_u8ServedRequestGateAddress) &&
              LOC_u8FailedTransmissionCount < 10);
    
    if(LOC_u8FailedTransmissionCount < 10)
    {
        /*Send the failed authentication code*/
        LOC_u16TxBuffer = AUTHENTICATION_RESULT_FAIL;
        MCAL_SPI_SendData(SPIx, &LOC_u16TxBuffer, PollingEnable);
    }else{

    }

    /*Enable the interrupts again*/
    MCAL_SPI_Interrupt_EN(SPIx, SPI_IRQ_TXEIE, callback);

    fptr_GateCommState = st_GatesComm_CheckPendingRequests;
}

/** @defgroup Signals between the Admin_Interface and Gates_Communication modules
  * @{
  */

/**
======================================================================================================================
* @Func_name	:  AI_GC_IDApproved
* @brief		   :  Function to inform that the authentication process has been approved and the ID is valid.
* @note			:  none
======================================================================================================================
*/
void AI_GC_IDApproved(void)
{
    fptr_GateCommState = st_GatesComm_SendIDApprovedSignal;
}

/**
======================================================================================================================
* @Func_name	:  AI_GC_IDApproved
* @brief		   :  Function to inform that the authentication process has been approved and the ID is valid.
* @note			:  none
======================================================================================================================
*/
void AI_GC_IDDisapproved(void)
{
    fptr_GateCommState = st_GatesComm_SendIDDisapprovedSignal;
}

/**
  * @}
  */
