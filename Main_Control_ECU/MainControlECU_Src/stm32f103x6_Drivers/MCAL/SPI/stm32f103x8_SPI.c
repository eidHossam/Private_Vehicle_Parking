/*
**************************************************************************************************************************
* file		: stm32f103x8_SPI.c
* brief     : Header file for the SPI peripheral Driver. 
* Author    : Hossam Eid
* Created on: Sep 26, 2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the SPI driver.**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/
#include "stm32f103x8_SPI.h"

/**************************************************************************************************************************
===============================================
*  				Private Macros and defines
*===============================================
*/
#define SPI_CR1_SPE_SET     (((uint16)0x0040))
#define SPI_SR_TXE          (((uint16)0x0002))
#define SPI_SR_RXNE         (((uint16)0x0001))
#define SPI_SR_BSY          (((uint16)0x0080))
#define SPI_SR_OVR          (((uint16)0x0040))
#define SPI_SR_MODF         (((uint16)0x0020))

#define SPI1_INDEX          0
#define SPI2_INDEX          1

/**************************************************************************************************************************
===============================================
*  				Global variables
*===============================================
*/
static SPI_Config_t SPI_Config[2];
static void (* p_IRQ_callback_SPI1[3])(void);
static void (* p_IRQ_callback_SPI2[3])(void);

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
static void MCAL_SPI_GPIO_Set_Pins(volatile SPI_Typedef * SPIx)
{
    uint8 index, SCK_pin, MOSI_Pin, MISO_Pin, SS_Pin;
    volatile GPIO_t* GPIOx;
    GPIO_Pin_Config_t GPIO_Config;
    if(SPIx == SPI1)
    {
        index = SPI1_INDEX;
        
        /** @defgroup SPI1 Pin Configuration
        * @{
        *       SPI1_NSS    : PA4
        *       SPI1_SCK    : PA5
        *       SPI1_MISO   : PA6
        *       SPI1_MOSI   : PA7
        * @}
        */

       SS_Pin   = GPIO_PIN4;
       SCK_pin  = GPIO_PIN5; 
       MISO_Pin = GPIO_PIN6; 
       MOSI_Pin = GPIO_PIN7; 

       GPIOx = GPIOA;
    }else
    {
        index = SPI2_INDEX;
        
        /** @defgroup SPI2 Pin Configuration
        * @{
        *       SPI2_NSS    : PB12
        *       SPI2_SCK    : PB13
        *       SPI2_MISO   : PB14
        *       SPI2_MOSI   : PB15
        * @}
        */
       SS_Pin   = GPIO_PIN12;
       SCK_pin  = GPIO_PIN13; 
       MISO_Pin = GPIO_PIN14; 
       MOSI_Pin = GPIO_PIN15; 

       GPIOx = GPIOB;
    }

    if(SPI_Config[index].SPI_Mode == SPI_MODE_MASTER)
    {
        /*SPIx_SCK: Master ====> Alternate function push-pull*/
        GPIO_Config.pinNumber = SCK_pin;
        GPIO_Config.pinMode = GPIO_MODE_AF_OUTPUT_PP_10MHZ;
        MCAL_GPIO_Init(GPIOx, &GPIO_Config);

        /*SPIx_MOSI: Full duplex/master ===> Alternate function push-pull,
        Simplex bidirectional data wire / master Alternate function push-pull*/
        GPIO_Config.pinNumber = MOSI_Pin;
        GPIO_Config.pinMode = GPIO_MODE_AF_OUTPUT_PP_10MHZ;
        MCAL_GPIO_Init(GPIOx, &GPIO_Config);

        /*SPIx_MISO: Full duplex/master ===> Input floating / Input pull-up
        Simplex bidirectional data wire/master ===> Not used. Can be used as a GPIO*/
        if(SPI_Config[index].SPI_Direction == SPI_DIRECTION_2LINES_FULL_DUPLEX ||
           SPI_Config[index].SPI_Direction == SPI_DIRECTION_2LINES_RX_ONLY)
        {
            GPIO_Config.pinNumber = MISO_Pin;
            GPIO_Config.pinMode = GPIO_MODE_INPUT_FLOATING;
            MCAL_GPIO_Init(GPIOx, &GPIO_Config);
        }

        /*SPIx_NSS: Hardware master/slave ===> Input floating/ Input pull-up / Input pull-down*/
        if(SPI_Config[index].SPI_NSS_Managment == SPI_NSS_HW_INPUT)
        {
            GPIO_Config.pinNumber = SS_Pin;
            GPIO_Config.pinMode = GPIO_MODE_INPUT_FLOATING;
            MCAL_GPIO_Init(GPIOx, &GPIO_Config);
        }
        /*SPIx_NSS: Hardware master/ NSS output enabled ===>  Alternate function push-pull*/
        else if(SPI_Config[index].SPI_NSS_Managment == SPI_NSS_HW_OUTPUT)
        {
            GPIO_Config.pinNumber = SS_Pin;
            GPIO_Config.pinMode = GPIO_MODE_AF_OUTPUT_PP_10MHZ;
            MCAL_GPIO_Init(GPIOx, &GPIO_Config);
        }

    }else
    {
        /*SPIx_SCK: Slave ====> Input floating*/
        GPIO_Config.pinNumber = SCK_pin;
        GPIO_Config.pinMode = GPIO_MODE_INPUT_FLOATING;
        MCAL_GPIO_Init(GPIOx, &GPIO_Config);

        /*SPIx_MOSI: Full duplex/slave ====> Input floating / Input pull-up
        Simplex bidirectional data wire/ slave Not used. Can be used as a GPIO*/
        if(SPI_Config[index].SPI_Direction == SPI_DIRECTION_2LINES_FULL_DUPLEX ||
           SPI_Config[index].SPI_Direction == SPI_DIRECTION_2LINES_RX_ONLY)
        {
            GPIO_Config.pinNumber = MOSI_Pin;
            GPIO_Config.pinMode = GPIO_MODE_INPUT_FLOATING;
            MCAL_GPIO_Init(GPIOx, &GPIO_Config);
        }

        /*SPIx_MISO: Full duplex/slave (point to point) ===> Alternate function push-pull
        Simplex bidirectional data wire/slave(point to point) ===> Alternate function push-pull*/
        if(SPI_Config[index].SPI_Direction == SPI_DIRECTION_2LINES_FULL_DUPLEX ||
           SPI_Config[index].SPI_Direction == SPI_DIRECTION_1LINE_TX)
        {
            GPIO_Config.pinNumber = MISO_Pin;
            GPIO_Config.pinMode = GPIO_MODE_AF_OUTPUT_PP_10MHZ;
            MCAL_GPIO_Init(GPIOx, &GPIO_Config);
        }  

        /*Todo:
        SPIx_MISO: Full duplex/slave (multi-slave) ===> Alternate function open drain
        Simplex bidirectional data wire/slave (multi-slave) ===> Alternate function open drain*/

        /*SPIx_NSS: Hardware master/slave ===> Input floating/ Input pull-up / Input pull-down*/
        if(SPI_Config[index].SPI_NSS_Managment == SPI_NSS_HW_INPUT)
        {
            GPIO_Config.pinNumber = SS_Pin;
            GPIO_Config.pinMode = GPIO_MODE_INPUT_FLOATING;
            MCAL_GPIO_Init(GPIOx, &GPIO_Config);
        }
    }

}

/**************************************************************************************************************************
*===============================================
*  			APIs functions definitions
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
void MCAL_SPI_Init(volatile SPI_Typedef* SPIx, SPI_Config_t* config)
{
    /*Activate the peripheral clock and save the config in a global variable to be used
        in other functions in the driver.*/
    if(SPIx == SPI1)
    {
        APB2_PERI_CLOCK_EN(APB2_SPI1);
        SPI_Config[SPI1_INDEX] = *config;
    }else{
        APB1_PERI_CLOCK_EN(APB1_SPI2);
        SPI_Config[SPI2_INDEX] = *config;
    }

    SPIx->CR1 = 0;  /*Reset the Register to its original state*/

    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
     master/salve mode, CPOL and CPHA */
    /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
    /* Set MSTR bit according to SPI_Mode*/
    /* Set LSBFirst bit according to SPI_BitOrder value */
    /* Set BR bits according to SPI_BR_Prescaler value */
    /* Set CPOL bit according to SPI_ClockPolarity value */
    /* Set CPHA bit according to SPI_ClockPhase value */

    SPIx->CR1 |= (config->SPI_Direction | config->SPI_Mode | config->SPI_BitOrder | 
                  config->SPI_DataSize | config->SPI_BR_Prescaler | config->SPI_ClockPolarity |
                  config->SPI_ClockPhase);

    /*Configure the NSS bit according to SPI_NSS_Managment*/
    if(config->SPI_NSS_Managment == SPI_NSS_SW_SET || config->SPI_NSS_Managment == SPI_NSS_SW_RESET)
    {
        SPIx->CR1 |= config->SPI_NSS_Managment;
    }else{
        SPIx->CR2 |= config->SPI_NSS_Managment;
    }
    
    /*Enable the SPI*/
    SPIx->CR1 |= SPI_CR1_SPE_SET;

    /*Set the GPIO pins for the SPI*/
    MCAL_SPI_GPIO_Set_Pins(SPIx);
}

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
void MCAL_SPI_Reset(volatile SPI_Typedef* SPIx)
{
     if(SPIx == SPI1)
    {
        APB2_PERI_RESET(APB2_SPI1);
    }else{
        APB1_PERI_RESET(APB1_SPI2);
    }
}

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
void MCAL_SPI_SendData(volatile SPI_Typedef* SPIx, uint16* pTxBuffer, enum Polling_mechanism polling)
{
    uint8 index;
    index = (SPIx == SPI1)? SPI1_INDEX : SPI2_INDEX;
    
    if(polling == PollingEnable)
    {
        /*Loop as long as the TXE flag is zero*/
        while(!(SPIx->SR & SPI_SR_TXE));
    }
    
    /*Send normally if you are in full duplex mode or half duplex transmit mode*/
    if(SPI_Config[index].SPI_Direction == SPI_DIRECTION_2LINES_FULL_DUPLEX || 
        SPI_Config[index].SPI_Direction == SPI_DIRECTION_1LINE_TX)
    {
        SPIx->DR = *pTxBuffer;
    }else 
    {

    }
    
}

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
void MCAL_SPI_ReceiveData(volatile SPI_Typedef* SPIx, uint16* pRxBuffer, enum Polling_mechanism polling)
{
    uint8 index;
    index = (SPIx == SPI1)? SPI1_INDEX : SPI2_INDEX;

    if(polling == PollingEnable)
    {
        /*Loop as long as the TXE flag is zero*/
        while(!(SPIx->SR & SPI_SR_RXNE));
    }

     /*Receive normally if you are in full duplex mode or half duplex receive mode*/
    if(SPI_Config[index].SPI_Direction == SPI_DIRECTION_2LINES_FULL_DUPLEX || 
        SPI_Config[index].SPI_Direction == SPI_DIRECTION_1LINE_RX ||
        SPI_Config[index].SPI_Direction == SPI_DIRECTION_2LINES_RX_ONLY)
    {
        *pRxBuffer = SPIx->DR;
    }else
    {
       
    }
}

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_ExchangeData
* @brief		:   Send and Receive data from the specified SPI channel.
* @param [in]	:   SPIx: specifies the SPI instance to be initialized can be (SPI1, SPI2).
* @param [in]	:   pBuffer: Pointer to the buffer holding data to be send.
* @param [out]	:   pBuffer: Pointer to the buffer to store the received data in.
* @return_value :   none.
* Note			:   This function works with polling mechanism.
======================================================================================================================
*/
void MCAL_SPI_ExchangeData(volatile SPI_Typedef* SPIx, uint16* pBuffer)
{
   
    /*Loop as long as the TXE flag is zero*/
    while(!(SPIx->SR & SPI_SR_TXE));
    

    SPIx->DR = *pBuffer;

    /*Loop as long as the TXE flag is zero*/
    while(!(SPIx->SR & SPI_SR_RXNE));
    

    *pBuffer = SPIx->DR;
}

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
void MCAL_SPI_WAIT_TC(USART_Typedef * SPIx)
{
    while(!(SPIx->SR & SPI_SR_BSY));
}

/*
======================================================================================================================
* @Func_name	:   MCAL_SPI_Interrupt_EN
* @brief		:   Enable a specific interrupt and set its callback function.
* @param [in]	:   SPI: specifies the SPI instance, can be (SPI1, SPI2).
* @param [in]	:   IRQ: specifies the interrupt to be enabled, must be set based on @ref SPI_IRQ_DEFINE.
* @param [in]	:   p_IRQ_callback: pointer to the callback function to be executed.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_SPI_Interrupt_EN(volatile SPI_Typedef * SPIx, uint8 IRQ, void (* p_IRQ_callback)(void))
{
    if(SPIx == SPI1)
    {
        MCAL_NVIC_EnableIRQ(NVIC_SPI1_IVT_INDEX);
        p_IRQ_callback_SPI1[IRQ >> 6] = p_IRQ_callback;
    }else{
        MCAL_NVIC_EnableIRQ(NVIC_SPI2_IVT_INDEX);
        p_IRQ_callback_SPI2[IRQ >> 6] = p_IRQ_callback;
    }

    /*Enable the Interrupt in CR2*/
    SPIx->CR2 |= IRQ;
}

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
void MCAL_SPI_Interrupt_Disable(volatile SPI_Typedef * SPIx, uint8 IRQ)
{
    if(SPIx == SPI1)
    {
        MCAL_NVIC_EnableIRQ(NVIC_SPI1_IVT_INDEX);
    }else{
        MCAL_NVIC_EnableIRQ(NVIC_SPI2_IVT_INDEX);
    }

    /*Enable the Interrupt in CR2*/
    SPIx->CR2 &= ~(IRQ);
}


/**************************************************************************************************************************
===============================================
*               SPI ISR functions
*===============================================
*/

void SPI1_IRQHandler(void)
{
    if((SPI1->CR2 & SPI_IRQ_ERRIE) && ((SPI1->SR & SPI_SR_OVR) || (SPI1->SR & SPI_SR_MODF)))
    {
        p_IRQ_callback_SPI1[SPI_IRQ_ERRIE >> 6]();
    }

    if((SPI1->CR2 & SPI_IRQ_RXNEIE) && (SPI1->SR & SPI_SR_RXNE))
    {
        p_IRQ_callback_SPI1[SPI_IRQ_RXNEIE >> 6]();
    }
    
    if((SPI1->CR2 & SPI_IRQ_TXEIE) && (SPI1->SR & SPI_SR_TXE))
    {
        p_IRQ_callback_SPI1[SPI_IRQ_TXEIE >> 6]();
    }
}

void SPI2_IRQHandler(void)
{
    if((SPI2->CR2 & SPI_IRQ_ERRIE) && ((SPI2->SR & SPI_SR_OVR) || (SPI2->SR & SPI_SR_MODF)))
    {
        p_IRQ_callback_SPI2[SPI_IRQ_ERRIE >> 6]();
    }

    if((SPI2->CR2 & SPI_IRQ_RXNEIE) && (SPI2->SR & SPI_SR_RXNE))
    {
        p_IRQ_callback_SPI2[SPI_IRQ_RXNEIE >> 6]();
    }
    
    if((SPI2->CR2 & SPI_IRQ_TXEIE) && (SPI2->SR & SPI_SR_TXE))
    {
        p_IRQ_callback_SPI2[SPI_IRQ_TXEIE >> 6]();
    }
}
