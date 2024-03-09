/*
**************************************************************************************************************************
* file		: stm32f103x8_SPI.h
* brief     : Header file for the SPI peripheral Driver.
* Author    : Hossam Eid
* Created on: Sep 26, 2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the SPI driver.
**************************************************************************************************************************
*/
#ifndef MCAL_SPI_STM32F103X8_SPI_H_
#define MCAL_SPI_STM32F103X8_SPI_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "stm32f103x6.h"
#include "GPIO/stm32f103x6_GPIO.h"
#include "NVIC/stm32f103x6_NVIC.h"

/**************************************************************************************************************************
*===============================================
* User type definitions (structures)
*===============================================
*/

typedef struct {
    uint16  SPI_Mode;           /*Specifies the SPI operation mode
                                    This parameter must be a value of @ref SPI_MODE_DEFINE*/
    
    uint16  SPI_Direction;      /*Specifies the SPI direction (uinidirectional or bidirectional)
                                    This parameter must be a value of @ref SPI_DIRECTION_DEFINE*/

    uint16  SPI_DataSize;       /*Specifies the size of the SPI payload
                                    This parameter must be a value of @ref SPI_DATA_SIZE_DEFINE*/

    uint16  SPI_BitOrder;       /*Specifies the order of the SPI payload bits sent first(LSB or MSB)
                                    This parameter must be a value of @ref SPI_FIRST_BIT_DEFINE*/

    uint16  SPI_ClockPolarity;  /*Specifies the polarity of the SPI idle state
                                    This parameter must be a value of @ref SPI_IDLE_DEFINE*/           

    uint16  SPI_ClockPhase;     /*Specifies the edge to sample the data at
                                    This parameter must be a value of @ref SPI_SAMPLE_DEFINE_EDGE*/

    uint16  SPI_NSS_Managment;  /*Specifies the management of the NSS line
                                    This parameter must be a value of @ref SPI_NSS_DEFINE*/

    uint16 SPI_BR_Prescaler;    /*Specifies the SPI baud-rate prescaler value 
                                    This parameter must be a value of @ref SPI_BAUD_RATE_PRESCALER_DEFINE*/        
                          
}SPI_Config_t;

/**************************************************************************************************************************
*===============================================
*         Macros Configuration References
*===============================================
*/

/*----------- @ref SPI_MODE_DEFINE --------------------------*/
#define SPI_MODE_SLAVE                      0x00000000UL             
#define SPI_MODE_MASTER                     0x00000004UL

/*----------- @ref SPI_DIRECTION_DEFINE ---------------------*/
#define SPI_DIRECTION_2LINES_FULL_DUPLEX    0x00000000UL
#define SPI_DIRECTION_2LINES_RX_ONLY        0x00000400UL
#define SPI_DIRECTION_1LINE_TX              0x0000C000UL    /*Half duplex transmit mode*/
#define SPI_DIRECTION_1LINE_RX              0x00008000UL    /*Half duplex receive mode*/

/*----------- @ref SPI_DATA_SIZE_DEFINE ---------------------*/
#define SPI_DATA_SIZE_8BIT                  0x00000000UL
#define SPI_DATA_SIZE_16BIT                 0x00000800UL

/*----------- @ref SPI_FIRST_BIT_DEFINE ---------------------*/
#define SPI_FIRST_BIT_MSB                   0x00000000UL
#define SPI_FIRST_BIT_LSB                   0x00000080UL

/*----------- @ref SPI_IDLE_DEFINE --------------------------*/
#define SPI_IDLE_LOW                        0x00000000UL
#define SPI_IDLE_HIGH                       0x00000002UL

/*----------- @ref SPI_SAMPLE_DEFINE_EDGE ---------------------*/
#define SPI_SAMPLE_FIRST_EDGE               0x00000000UL
#define SPI_SAMPLE_SECOND_EDGE              0x00000001UL

/*----------- @ref SPI_NSS_DEFINE -----------------------------*/
#define SPI_NSS_HW_OUTPUT                   0x00000004UL    
#define SPI_NSS_HW_INPUT                    0x00000000UL    /*This configuration allows multimaster capability*/
                                                                /* for devices operating in master mode*/

#define SPI_NSS_SW_SET                      0x00000300UL
#define SPI_NSS_SW_RESET                    0x00000200UL
                                                             
/*----------- @ref SPI_BAUD_RATE_PRESCALER_DEFINE ------------*/
#define SPI_BAUD_RATE_PRESCALER_2           0x00000000UL
#define SPI_BAUD_RATE_PRESCALER_4           0x00000008UL
#define SPI_BAUD_RATE_PRESCALER_8           0x00000010UL
#define SPI_BAUD_RATE_PRESCALER_16          0x00000018UL
#define SPI_BAUD_RATE_PRESCALER_32          0x00000020UL
#define SPI_BAUD_RATE_PRESCALER_64          0x00000028UL
#define SPI_BAUD_RATE_PRESCALER_128         0x00000030UL
#define SPI_BAUD_RATE_PRESCALER_256         0x00000038UL

/*----------- @ref SPI_IRQ_DEFINE ------------*/
#define SPI_IRQ_TXEIE                       0x00000080UL    
#define SPI_IRQ_RXNEIE                      0x00000040UL    
#define SPI_IRQ_ERRIE                       0x00000020UL    

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
* @Func_name	:   MCAL_SPI_Init
* @brief		:   Initialization function for the SPI peripheral using the parameters in the configuration structure.
* @param [in]	:   SPIx: specifies the SPI instance to be initialized can be (SPI1, SPI2).
* @param [in]	:   config: specifies the configuration parameters for the specified SPI instance.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_Init(volatile SPI_Typedef* SPIx, SPI_Config_t* config);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Reset
* @brief		:   Reset the specified SPI instance to its original state.
* @param [in]	:   SPIx: specifies the SPI instance to be initialized can be (SPI1, SPI2).
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_Reset(volatile SPI_Typedef* SPIx);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_SendData
* @brief		:   Send data through SPI.
* @param [in]	:   SPIx: specifies the SPI instance to be initialized can be (SPI1, SPI2).
* @param [in]	:   pTxBuffer: Pointer to buffer storing the data to be transmitted.
* @param [in]	:   polling: Enable or disable polling mechanism.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_SendData(volatile SPI_Typedef* SPIx, uint16* pTxBuffer, enum Polling_mechanism polling);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_RecieveData
* @brief		:   Receive data from the specified SPI channel.
* @param [in]	:   SPIx: specifies the SPI instance to be initialized can be (SPI1, SPI2).
* @param [in]	:   polling: Enable or disable polling mechanism.
* @param [out]	:   pRxBuffer: Pointer to buffer to store the received data in.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_ReceiveData(volatile SPI_Typedef* SPIx, uint16* pRxBuffer, enum Polling_mechanism polling);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_ExchangeData
* @brief		:   Send and Receive data from the specified SPI channel.
* @param [in]	:   SPIx: specifies the SPI instance to be initialized can be (SPI1, SPI2).
* @param [in]	:   pBuffer: Pointer to the buffer holding data to be send.
* @param [out]	:   pBuffer: Pointer to the buffer to store the received data in.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_ExchangeData(volatile SPI_Typedef* SPIx, uint16* pBuffer);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_WAIT_TC
* @brief		:   This function waits for the transmission of data from the SPI to be completed.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_WAIT_TC(USART_Typedef * SPIx);

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Interrupt_EN
* @brief		:   Enable a specific interrupt and set its callback function.
* @param [in]	:   SPI: specifies the SPI instance, can be (SPI1, SPI2).
* @param [in]	:   IRQ: specifies the interrupt to be enabled, must be set based on @ref SPI_IRQ_DEFINE.
* @param [in]	:   p_IRQ_callback: pointer to the callback function to be executed.
* @return_value :   none.
* Note          :   In case of interrupt from the MODF or OVR flag you need to clear the flag manually.======================================================================================================================
*/
void MCAL_SPI_Interrupt_EN(volatile SPI_Typedef * SPIx, uint8 IRQ, void (* p_IRQ_callback)(void));

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Interrupt_Disable
* @brief		:   Disable a specific interrupt
* @param [in]	:   SPI: specifies the SPI instance, can be (SPI1, SPI2).
* @param [in]	:   IRQ: specifies the interrupt to be disabled, must be set based on @ref SPI_IRQ_DEFINE.
* @return_value :   none.
* Note			:   This function won't disable the SPI instance interrupt in NVIC you have to manually disable it.
======================================================================================================================
*/
void MCAL_SPI_Interrupt_Disable(volatile SPI_Typedef * SPIx, uint8 IRQ);
#endif /* MCAL_SPI_STM32F103X8_SPI_H_ */
