/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the SPI module.
* Author    : Hossam Eid
* Created on: 9/29/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the SPI driver.
**************************************************************************************************************************
*/

#ifndef ATMEGA32_SPI_H_
#define ATMEGA32_SPI_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32.h"
#include "GPIO/Atmega32_GPIO.h"


/**************************************************************************************************************************
*===============================================
* User type definitions (structures)
*===============================================
*/
typedef struct{
   uint8_t  SPI_Mode;                   /*Specifies the SPI operation mode
                                            This parameter must be a value of @ref SPI_MODE_DEFINE*/

   uint8_t  SPI_DataOrder;              /*Specifies the order of the SPI payload bits sent first(LSB or MSB)
                                            This parameter must be a value of @ref SPI_FIRST_BIT_DEFINE*/

   uint8_t  SPI_CPOL;                   /*Specifies the polarity of the SPI idle state
                                            This parameter must be a value of @ref SPI_IDLE_DEFINE*/   

    uint8_t SPI_CPHA;                   /*Specifies the edge to sample the data at
                                            This parameter must be a value of @ref SPI_SAMPLE_DEFINE_EDGE*/  
   
   uint8_t SPI_BaudRate;                /*Specifies the SPI baud-rate prescaler value 
                                            This parameter must be a value of @ref SPI_BAUD_RATE_PRESCALER_DEFINE*/  
   
   uint8_t SPI_DoubleSpeed_EN;          /*Specifies if the SPI speed should be doubled or not
                                            This parameter must be a value of @ref SPI_2XSPEED_DEFINE*/
   
   uint8_t SPI_IRQ_EN;                  /*Specifies if the SPI interrupt should enabled or disabled
                                            This parameter must be a value of @ref SPI_IRQ_DEFINE*/ 

    void (* SPI_IRQHandler)(void);      /*Specifies the SPI ISR if enabled*/
}SPI_Config_t;

/**************************************************************************************************************************
*===============================================
*         Macros Configuration References
*===============================================
*/

/*----------- @ref SPI_MODE_DEFINE ----------------*/
enum SPI_Mode{
    SPI_MODE_SLAVE,
    SPI_MODE_MASTER = 0x10
};

/*----------- @ref SPI_FIRST_BIT_DEFINE -----------*/
enum SPI_DataOrder{
    SPI_FIRST_BIT_MSB,
    SPI_FIRST_BIT_LSB = 0x20
};

/*----------- @ref SPI_IDLE_DEFINE ----------------*/
enum SPI_CPOL{
    SPI_IDLE_LOW,
    SPI_IDLE_HIGH = 0x08
};

/*----------- @ref SPI_SAMPLE_DEFINE_EDGE ----------*/
enum SPI_SampleEdge{
    SPI_SAMPLE_FIRST_EDGE,
    SPI_SAMPLE_SECOND_EDGE = 0x04
};

/*----------- @ref SPI_BAUD_RATE_PRESCALER_DEFINE ---*/
/*Note: When the SPI is configured as
Slave, the SPI is only guaranteed to work at fosc/4 or lower*/
enum SPI_BR{
    SPI_BAUD_RATE_PRESCALER_4,
    SPI_BAUD_RATE_PRESCALER_16,
    SPI_BAUD_RATE_PRESCALER_64,
    SPI_BAUD_RATE_PRESCALER_128
};

/*----------- @ref SPI_2XSPEED_DEFINE ----------------*/
/*Note: When the SPI is configured as
Slave, the SPI is only guaranteed to work at fosc/4 or lower*/
enum SPI_DoubleSpeed {
    SPI_2XSPEED_DISABLE,
    SPI_2XSPEED_ENABLE
};

/*----------- @ref SPI_IRQ_DEFINE ----------------*/
enum SPI_IRQ{
    SPI_IRQ_DISABLE,
    SPI_IRQ_ENABLE = 0x80
};

enum Polling_mechanism{
    PollingEnable,
    PollingDisable
};

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL SPI DRIVER"
*===============================================
*/

/*
======================================================================================================================
* @Func_name	:   SPI_Config_t
* @brief		:   Initialization function for the SPI peripheral using the parameters in the configuration structure.
* @param [in]	:   config: specifies the configuration parameters for the specified SPI instance.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_Init(SPI_Config_t* config);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Reset
* @brief		:   Reset the specified SPI instance to its original state.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_Reset();

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_SendData
* @brief		:   Send data through SPI.
* @param [in]	:   pTxBuffer: Pointer to buffer storing the data to be transmitted.
* @param [in]	:   polling: Enable or disable polling mechanism.
* @return_value :   none.
* Note			:   In case of the master operation you need to toggle the SS pin yourself.
======================================================================================================================
*/
void MCAL_SPI_SendData(uint8_t* pTxBuffer, enum Polling_mechanism polling);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_RecieveData
* @brief		:   Receive data from the specified SPI channel.
* @param [in]	:   polling: Enable or disable polling mechanism.
* @param [out]	:   pRxBuffer: Pointer to buffer to store the received data in.
* @return_value :   none.
* Note			:   In case of the master operation you need to toggle the SS pin yourself.
======================================================================================================================
*/
void MCAL_SPI_ReceiveData(uint8_t* pRxBuffer, enum Polling_mechanism polling);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_ExchangeData
* @brief		:   Send and Receive data from the specified SPI channel.
* @param [in]	:   polling: Enable or disable polling mechanism.
* @param [in]	:   pBuffer: Pointer to the buffer holding data to be send.
* @param [out]	:   pBuffer: Pointer to the buffer to store the received data in.
* @return_value :   none.
* Note			:   This function works with a polling mechanism.
======================================================================================================================
*/
void MCAL_SPI_ExchangeData( uint8_t* pBuffer);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Enable
* @brief		:   Enable the SPI peripheral.
======================================================================================================================
*/
void MCAL_SPI_Enable();

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Disable
* @brief		:   Disable the SPI peripheral.
======================================================================================================================
*/
void MCAL_SPI_Disable();
#endif /* ATMEGA32_SPI_H_ */