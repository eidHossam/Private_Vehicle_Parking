/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the SPI module.
* Author    : Hossam Eid
* Created on: 9/29/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the SPI driver.
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32_SPI.h"

/**************************************************************************************************************************
===============================================
*  				Private Macros and defines
*===============================================
*/
#define SPCR_SPE_SET        0x40
#define SPCR_SPE_RESET      ~(0x40)
#define SPSR_SPIF           0x80

/*SPI ports and pins configuration--------------------------------------*/
#define SPI_DIR_PORT		GPIOB->DDR

#define SPI_SS_PIN			GPIO_PIN4
#define SPI_MOSI_PIN		GPIO_PIN5
#define SPI_MISO_PIN		GPIO_PIN6
#define SPI_SCK_PIN			GPIO_PIN7
/**************************************************************************************************************************
===============================================
*  				Global variables
*===============================================
*/
static void (* p_IRQ_callback_SPI)(void);
/**************************************************************************************************************************
===============================================
*  				Local functions
*===============================================
*/

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_GPIO_Set_Pins
* @brief		:   Initialization of the SPI peripheral pins
* @param [in]	:   SPix: specifies the SPI instance to be initialized can be (SPI1, SPI2).
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
static void MCAL_SPI_GPIO_Set_Pins(uint8_t SPI_Mode)
{
    GPIO_Pin_Config_t Pinconfig;
    
    if(SPI_Mode == SPI_MODE_MASTER)
    {
        /* Set MOSI, SS and SCK output, all others input */
        Pinconfig.pinNumber = SPI_MOSI_PIN; 
        Pinconfig.pinMode = GPIO_MODE_OUTPUT;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        Pinconfig.pinNumber = SPI_SCK_PIN; 
        Pinconfig.pinMode = GPIO_MODE_OUTPUT;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        Pinconfig.pinNumber = SPI_SS_PIN; 
        Pinconfig.pinMode = GPIO_MODE_OUTPUT;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        Pinconfig.pinNumber = SPI_SCK_PIN; 
        Pinconfig.pinMode = GPIO_MODE_OUTPUT;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        Pinconfig.pinNumber = SPI_MISO_PIN; 
        Pinconfig.pinMode = GPIO_MODE_INPUT_FLOATING;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        MCAL_GPIO_WritePin(GPIOB, GPIO_PIN4, GPIO_PIN_HIGH);
    }else{
        /* Set MISO output, all others input */
        Pinconfig.pinNumber = SPI_MOSI_PIN; 
        Pinconfig.pinMode = GPIO_MODE_OUTPUT;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        Pinconfig.pinNumber = SPI_SCK_PIN; 
        Pinconfig.pinMode = GPIO_MODE_INPUT_FLOATING;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        Pinconfig.pinNumber = SPI_SS_PIN; 
        Pinconfig.pinMode = GPIO_MODE_INPUT_FLOATING;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        Pinconfig.pinNumber = SPI_SCK_PIN; 
        Pinconfig.pinMode = GPIO_MODE_INPUT_FLOATING;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);

        Pinconfig.pinNumber = SPI_MISO_PIN; 
        Pinconfig.pinMode = GPIO_MODE_OUTPUT;  
        MCAL_GPIO_Init(GPIOB, &Pinconfig);
    }

}
/**************************************************************************************************************************
*===============================================
*  			APIs functions definitions
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
void MCAL_SPI_Init(SPI_Config_t* config)
{
    /*Reset the control register to its original state*/
    SPI->SPCR = 0;

    /*Set the control parameters:*/
    /* Set MSTR bit according to SPI_Mode*/
    /* Set LSBFirst bit according to SPI_FIRST_BIT_DEFINE value */
    /* Set BR bits according to SPI_BAUD_RATE_PRESCALER_DEFINE value */
    /* Set CPOL bit according to SPI_IDLE_DEFINE value */
    /* Set CPHA bit according to SPI_SAMPLE_DEFINE_EDGE value */
    /* Set SPIE bit according to SPI_IRQ_EN value*/
    SPI->SPCR |= (config->SPI_Mode | config->SPI_DataOrder | config->SPI_BaudRate | 
                  config->SPI_CPOL | config->SPI_CPHA | config->SPI_IRQ_EN); 

    /* Set SPI2X according to SPI_2XSPEED_DEFINE value*/
    SPI->SPSR |= ((SPI->SPSR & ~(SPI_2XSPEED_ENABLE)) | config->SPI_DoubleSpeed_EN); 

    /*Enable global interrupts*/
    if(config->SPI_IRQ_EN == SPI_IRQ_ENABLE)
    {
       G_INTERRUPT_ENABLE; 
       p_IRQ_callback_SPI = config->SPI_IRQHandler;
    }

    /*Set the GPIO Pins*/
    MCAL_SPI_GPIO_Set_Pins(config->SPI_Mode);

    /*Enable SPI*/
    SPI->SPCR |= SPCR_SPE_SET;
}

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
void MCAL_SPI_Reset()
{
    SPI->SPCR = 0;
    SPI->SPSR = 0;
}

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
void MCAL_SPI_SendData(uint8_t* pTxBuffer, enum Polling_mechanism polling)
{
    SPI->SPDR = *(pTxBuffer);
    
    /*Wait for transmission complete*/
    if(polling == PollingEnable)
    {
        /*Loop as long as the SPIF flag is zero*/
        while(!(SPI->SPSR & SPSR_SPIF));
    }
    
}

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
void MCAL_SPI_ReceiveData(uint8_t* pRxBuffer, enum Polling_mechanism polling)
{
    /* Wait for reception complete */
    if(polling == PollingEnable)
    {
        /*Loop as long as the SPIF flag is zero*/
        while(!(SPI->SPSR & SPSR_SPIF));
    }

    /* Return Data Register */
    *(pRxBuffer) = SPI->SPDR;
}

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
void MCAL_SPI_ExchangeData(uint8_t* pBuffer)
{
    SPI->SPDR = *(pBuffer);

    
    /*Loop as long as the SPIF flag is zero*/
    while(!(SPI->SPSR & SPSR_SPIF));
    
     
    /* Return Data Register */
    *(pBuffer) = SPI->SPDR;
}

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Enable
* @brief		:   Enable the SPI peripheral.
======================================================================================================================
*/
void MCAL_SPI_Enable()
{
    SPI->SPCR |= SPCR_SPE_SET;
}

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Disable
* @brief		:   Disable the SPI peripheral.
======================================================================================================================
*/
void MCAL_SPI_Disable()
{
    SPI->SPCR &= SPCR_SPE_RESET;
}

/**************************************************************************************************************************
===============================================
*               SPI ISR functions
*===============================================
*/

void __vector_12 (void) __attribute__((signal));
void __vector_12 (void){

  	p_IRQ_callback_SPI();
}

