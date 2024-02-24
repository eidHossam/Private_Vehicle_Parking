/*
**************************************************************************************************************************
* brief     : MCU Device Header for the stm32f103x6.
* Author    : Hossam Eid
* Created on: 26 Feb 2022
**************************************************************************************************************************
* Description: This file contains the memory map for the MCU
* with each peripheral base address and registers and instances of each peripheral
* note: This header file is intended for use with the STM32F103xx MCU series,
* but may be adapted for use with other compatible processors.
**************************************************************************************************************************
*/

#ifndef STM32F103X6_H_
#define STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------
#include "Bit_Math.h"
#include "Platform_Types.h"

/*================================================================*/
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE                             	0x08000000UL
#define SYSTEM_MEMORY_BASE                            	0x08000000UL
#define SRAM_MEMORY_BASE                              	0x20000000UL
#define PERIPHERAL_MEMORY_BASE                        	0x20000000UL
/*
*===============================================
*  	Cortex-M3 base addresses
*===============================================
*/
#define CORTEX_M3_INTERNAL_PERIPHERALS_MEMORY_BASE    	0xE0000000UL
#define NVIC_BASE										(CORTEX_M3_INTERNAL_PERIPHERALS_MEMORY_BASE + 0xE100)

/*================================================================*/
//--------------------------------------
//Base addresses for AHB BUS Peripherals
//--------------------------------------
#define RCC_BASE 		0x40021000ul

//--------------------------------------
//Base addresses for APB1 BUS Peripherals
//--------------------------------------

/*----------USART-----------------*/
#define USART2_BASE 	0x40004400ul
#define USART3_BASE 	0x40004800ul

/*----------SPI-----------------*/
#define SPI2_BASE 		0x40003800ul


/*----------I2C-----------------*/
#define I2C1_BASE 		0x40005400ul
#define I2C2_BASE 		0x40005800ul


//--------------------------------------
//Base addresses for APB2 BUS Peripherals
//--------------------------------------

/*----------GPIO-------------------
Note: LQFP48 package has PORT(A, B)
,part of PORT(C,D) and PORTE isn't
used*/
#define GPIOA_BASE 		0x40010800ul
#define GPIOB_BASE 		0x40010C00ul
#define GPIOC_BASE 		0x40011000ul
#define GPIOD_BASE 		0x40011400ul
#define GPIOE_BASE 		0x40011800ul

/*----------AFIO-----------------*/
#define AFIO_BASE 		0x40010000ul

/*----------EXTI-----------------*/
#define EXTI_BASE 		0x40010400ul

/*----------USART-----------------*/
#define USART1_BASE 	0x40013800ul

/*----------SPI-----------------*/
#define SPI1_BASE 		0x40013000ul

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*-

/*----------RCC registers-----------------*/
typedef struct{
	vuint32_t CR;           /*Clock control register*/
	vuint32_t CFGR;         /*Clock configuration register*/
	vuint32_t CIR;          /*Clock interrupt register*/
	vuint32_t APB2RSTR;     /*APB2 peripheral reset register*/
	vuint32_t APB1RSTR;     /*APB1 peripheral reset register*/
	vuint32_t AHBENR;       /*AHB Peripheral Clock enable register*/
	vuint32_t APB2ENR;      /*APB2 Peripheral Clock enable register*/
	vuint32_t APB1ENR;      /*APB1 Peripheral Clock enable register*/
	vuint32_t BDCR;         /*Backup domain control register*/
	vuint32_t CSR;          /*Control/status register*/
	vuint32_t AHBSTR;       /*AHB peripheral clock reset register*/
	vuint32_t CFGR2;        /*Clock configuration register2*/
}RCC_t;

/*----------NVIC registers-----------------*/
#define NVIC_ISER_BASE       ((volatile uint32 *)(NVIC_BASE + 0x000))	/*Interrupt set-enable registers base*/
#define NVIC_ISER0          *((volatile uint32 *)(NVIC_BASE + 0x000))	/*Interrupt[0 : 31] set-enable register*/
#define NVIC_ISER1          *((volatile uint32 *)(NVIC_BASE + 0x004))	/*Interrupt[32 : 63] set-enable register*/
#define NVIC_ISER2          *((volatile uint32 *)(NVIC_BASE + 0x008))	/*Interrupt[64 : 80] set-enable register*/


#define NVIC_ICER_BASE       ((volatile uint32 *)(NVIC_BASE + 0x080))	/*Interrupt clear-enable registers base*/
#define NVIC_ICER0          *((volatile uint32 *)(NVIC_BASE + 0x080))	/*Interrupt[0 : 31]  clear-enable register*/
#define NVIC_ICER1          *((volatile uint32 *)(NVIC_BASE + 0x084))	/*Interrupt[32 : 63] clear-enable register*/
#define NVIC_ICER2          *((volatile uint32 *)(NVIC_BASE + 0x088))	/*Interrupt[64 : 80] clear-enable register*/

#define NVIC_ISPR_BASE		 ((volatile uint32 *)(NVIC_BASE + 0x100))	/*Interrupt set-pending registers base*/
#define NVIC_ISPR0			*((volatile uint32 *)(NVIC_BASE + 0x100))	/*Interrupt[0 : 31]  set-pending register*/
#define NVIC_ISPR1			*((volatile uint32 *)(NVIC_BASE + 0x104))	/*Interrupt[32 : 63] set-pending register*/
#define NVIC_ISPR2			*((volatile uint32 *)(NVIC_BASE + 0x108))	/*Interrupt[64 : 80] set-pending register*/

#define NVIC_ICPR_BASE		 ((volatile uint32 *)(NVIC_BASE + 0x180))	/*Interrupt clear-pending registers base*/
#define NVIC_ICPR0			*((volatile uint32 *)(NVIC_BASE + 0x180))	/*Interrupt[0 : 31]  clear-pending register*/
#define NVIC_ICPR1			*((volatile uint32 *)(NVIC_BASE + 0x184))	/*Interrupt[32 : 63] clear-pending register*/
#define NVIC_ICPR2			*((volatile uint32 *)(NVIC_BASE + 0x188))	/*Interrupt[64 : 80] clear-pending register*/

#define NVIC_IABR_BASE		 ((volatile uint32 *)(NVIC_BASE + 0x200))	/*Interrupt active bit registers base*/
#define NVIC_IABR0			*((volatile uint32 *)(NVIC_BASE + 0x200))	/*Interrupt[0 : 31]  active bit register*/
#define NVIC_IABR1			*((volatile uint32 *)(NVIC_BASE + 0x204))	/*Interrupt[32 : 63] active bit register*/
#define NVIC_IABR2			*((volatile uint32 *)(NVIC_BASE + 0x208))	/*Interrupt[64 : 80] active bit register*/

#define NVIC_IPR_BASE		 ((volatile uint32 *)(NVIC_BASE + 0x300))	/*Interrupt set-priority registers base*/
#define NVIC_IPR0			*((volatile uint32 *)(NVIC_BASE + 0x300))	/*Interrupt[0  : 3 ] set-priority register*/
#define NVIC_IPR1			*((volatile uint32 *)(NVIC_BASE + 0x304))	/*Interrupt[4  : 7 ] set-priority register*/	
#define NVIC_IPR2			*((volatile uint32 *)(NVIC_BASE + 0x308))	/*Interrupt[8  : 11] set-priority register*/
#define NVIC_IPR3			*((volatile uint32 *)(NVIC_BASE + 0x30C))	/*Interrupt[12 : 15] set-priority register*/
#define NVIC_IPR4			*((volatile uint32 *)(NVIC_BASE + 0x310))	/*Interrupt[16 : 19] set-priority register*/
#define NVIC_IPR5			*((volatile uint32 *)(NVIC_BASE + 0x314))	/*Interrupt[20 : 23] set-priority register*/
#define NVIC_IPR6			*((volatile uint32 *)(NVIC_BASE + 0x318))	/*Interrupt[24 : 27] set-priority register*/
#define NVIC_IPR7			*((volatile uint32 *)(NVIC_BASE + 0x31C))	/*Interrupt[28 : 31] set-priority register*/
#define NVIC_IPR8			*((volatile uint32 *)(NVIC_BASE + 0x320))	/*Interrupt[32 : 35] set-priority register*/
#define NVIC_IPR9			*((volatile uint32 *)(NVIC_BASE + 0x324))	/*Interrupt[36 : 39] set-priority register*/
#define NVIC_IPR10			*((volatile uint32 *)(NVIC_BASE + 0x328))	/*Interrupt[40 : 43] set-priority register*/
#define NVIC_IPR11			*((volatile uint32 *)(NVIC_BASE + 0x32C))	/*Interrupt[44 : 47] set-priority register*/
#define NVIC_IPR12			*((volatile uint32 *)(NVIC_BASE + 0x330))	/*Interrupt[48 : 51] set-priority register*/
#define NVIC_IPR13			*((volatile uint32 *)(NVIC_BASE + 0x334))	/*Interrupt[52 : 55] set-priority register*/
#define NVIC_IPR14			*((volatile uint32 *)(NVIC_BASE + 0x338))	/*Interrupt[56 : 59] set-priority register*/
#define NVIC_IPR15			*((volatile uint32 *)(NVIC_BASE + 0x33C))	/*Interrupt[60 : 63] set-priority register*/
#define NVIC_IPR16			*((volatile uint32 *)(NVIC_BASE + 0x340))	/*Interrupt[64 : 67] set-priority register*/
#define NVIC_IPR17			*((volatile uint32 *)(NVIC_BASE + 0x344))	/*Interrupt[68 : 71] set-priority register*/
#define NVIC_IPR18			*((volatile uint32 *)(NVIC_BASE + 0x348))	/*Interrupt[72 : 75] set-priority register*/
#define NVIC_IPR19			*((volatile uint32 *)(NVIC_BASE + 0x34C))	/*Interrupt[76 : 79] set-priority register*/
#define NVIC_IPR20			*((volatile uint32 *)(NVIC_BASE + 0x350))	/*Interrupt[80] 	 set-priority register*/

#define NVIC_STIR			*((volatile uint32 *)(0xE000EF00 + 0xE00))	/*Software trigger interrupt register*/

/*----------GPIO registers-----------------*/
typedef struct{
	vuint32_t CRL;          /*Control register for bits (0 to 7)*/
	vuint32_t CRH;          /*Control register for bits (8 to 15)*/
	vuint32_t IDR;          /*Input data register*/
	vuint32_t ODR;          /*Output data register*/
	vuint32_t BSRR;         /*Bit set/reset register*/
	vuint32_t BRR;          /*Bit reset register*/
	vuint32_t LCKR;         /*Bit configuration lock register*/
}GPIO_t;


/*----------AFIO registers-----------------*/
typedef struct{
	vuint32_t EVCR;          	/*Event control register*/
	vuint32_t MAPR;          	/*AF remap and debug I/O configuration register 1*/
	vuint32_t EXTICR[4];       	/*External interrupt configuration registers*/
	vuint32_t :    32;       	/*Reserved space*/
	vuint32_t MAPR2;         	/*AF remap and debug I/O configuration register 2*/
}AFIO_t;

/*----------EXTI registers-----------------*/
typedef struct{
	vuint32_t IMR;				/*Interrupt mask register (Enable, Disable)*/
	vuint32_t EMR;				/*Event mask register (Enable, Disable)*/
	vuint32_t RTSR;				/*Rising trigger selection register*/
	vuint32_t FTSR;				/*Falling trigger selection register*/
	vuint32_t SWIER;			/*Software interrupt event register*/
	vuint32_t PR;				/*Pending register*/
}EXTI_t;

/*----------USART registers-----------------*/
typedef struct{
	vuint32_t SR;            	/*USART status Register*/
	vuint32_t DR;            	/*USART I/O data Register*/
	vuint32_t BRR;            	/*USART baud-rate Register*/
	vuint32_t CR1;            	/*USART control Register 1*/
	vuint32_t CR2;            	/*USART control Register 2*/
	vuint32_t CR3;            	/*USART control Register 3*/
	vuint32_t GTPR;            	/*USART gaurd time & prescaler Register*/
}USART_Typedef;

/*----------SPI registers-----------------*/
typedef struct{
	vuint32_t CR1;            		/*SPI Control Register 1*/
	vuint32_t CR2;            		/*SPI Control Register 2*/
	vuint32_t SR;            		/*SPI Status Register*/
	vuint32_t DR;            		/*SPI I/O Data Register 1*/
	vuint32_t CRCPR;            	/*SPI CRC polynomial Register */
	vuint32_t RXCRCR;            	/*SPI RX CRC Register*/
	vuint32_t TXCRCR;            	/*SPI TX CRC Register*/
	vuint32_t I2SCFGR;            	/*SPI_I2S configuration Register*/
	vuint32_t I2SPR;            	/*SPI_I2S prescaler Register*/
}SPI_Typedef;

/*----------I2C registers-----------------*/
typedef struct{
	vuint32_t CR1;            		/*I2C Control Register 1*/
	vuint32_t CR2;            		/*I2C Control Register 2*/
	vuint32_t OAR1;            		/*I2C Slave Address Register 1*/
	vuint32_t OAR2;            		/*I2C Slave Address Register 2*/
	vuint32_t DR;            		/*I2C I/O Data Register */
	vuint32_t SR1;            		/*I2C Status Register 1*/
	vuint32_t SR2;            		/*I2C Status Register 2*/
	vuint32_t CCR;            		/*I2C Clock Control Register*/
	vuint32_t TRISE;            	/*I2C Clock Rise Time Register*/
}I2C_Typedef;

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

/*----------RCC-----------------*/
#define RCC          ((volatile RCC_t *)(RCC_BASE))

/*----------GPIO-------------------
Note: LQFP48 package has PORT(A, B)
,part of PORT(C,D) and PORTE isn't
used*/
#define GPIOA        ((volatile GPIO_t *)(GPIOA_BASE))
#define GPIOB        ((volatile GPIO_t *)(GPIOB_BASE))
#define GPIOC        ((volatile GPIO_t *)(GPIOC_BASE))
#define GPIOD        ((volatile GPIO_t *)(GPIOD_BASE))
#define GPIOE        ((volatile GPIO_t *)(GPIOE_BASE))

/*----------------------AFIO---------------------------*/
#define AFIO        ((volatile AFIO_t *)(AFIO_BASE))

/*---------------------EXTI---------------------------*/
#define EXTI 		((volatile EXTI_t *)(EXTI_BASE))

/*---------------------USART---------------------------*/
#define USART1 		((volatile USART_Typedef *)(USART1_BASE))
#define USART2 		((volatile USART_Typedef *)(USART2_BASE))
#define USART3 		((volatile USART_Typedef *)(USART3_BASE))

/*---------------------SPI---------------------------*/
#define SPI1		((volatile SPI_Typedef*)(SPI1_BASE))
#define SPI2		((volatile SPI_Typedef*)(SPI2_BASE))

/*---------------------I2C---------------------------*/
#define I2C1		((volatile I2C_Typedef*)(I2C1_BASE))
#define I2C2		((volatile I2C_Typedef*)(I2C2_BASE))

/*================================================================*/
//Delete this part after making RCC driver
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable/reset Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define APB2_PERI_CLOCK_EN(periID) (SET_BIT(RCC->APB2ENR, periID))  /*PeriID must be a value of @ref APB2_ID*/

#define APB2_PERI_RESET(periID) (SET_BIT(RCC->APB2RSTR, periID)); \
                                (CLEAR_BIT(RCC->APB2RSTR, periID)) /*PeriID must be a value of @ref APB2_ID*/

#define APB1_PERI_CLOCK_EN(periID) (SET_BIT(RCC->APB1ENR, periID))  /*PeriID must be a value of @ref APB1_ID*/

#define APB1_PERI_RESET(periID) (SET_BIT(RCC->APB1RSTR, periID)); \
                                (CLEAR_BIT(RCC->APB1RSTR, periID)) /*PeriID must be a value of @ref APB1_ID*/


/*================================================================*/
//---------------------------------
//Macros Configuration References
//---------------------------------
/*================================================================*/

/*@ref APB1_ID-------------*/
#define APB1_SPI2		14
#define APB1_USART2		17
#define APB1_USART3		18
#define APB1_I2C1		21
#define APB1_I2C2		22

/*@ref APB2_ID-------------*/
#define APB2_AFIO 		0
#define APB2_IOPA 		2
#define APB2_IOPB 		3
#define APB2_IOPC 		4
#define APB2_IOPD 		5
#define APB2_IOPE 		6
#define APB2_SPI1 		12
#define APB2_USART1 	14
/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

/********************************************************/
/********************************************************/
/********************************************************/
/*******************  Bit definition  ********************/
/********************************************************/
/********************************************************/



/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */
/*================================================================*/


/**************************************************************************************************************************
*===============================================
* User type definitions 
*===============================================
*/

typedef enum{Disable = 0, Enable = 1}FunctionalState;

#endif /* STM32F103X6_H_ */
