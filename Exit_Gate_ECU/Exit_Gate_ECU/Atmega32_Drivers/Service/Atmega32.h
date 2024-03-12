/*
**************************************************************************************************************************
* brief     : MCU Device Header for the Atmega32.
* Author    : Hossam Eid
* Created on: 9/11/2023
**************************************************************************************************************************
* Description: This file contains the memory map for the MCU with each peripheral base address and registers and 
* instances of each peripheral
* note: This header file is intended for use with the Atmega32 MCU series, but may be adapted for use with other 
* compatible processors.
**************************************************************************************************************************
*/

#ifndef ATMEGA32_H_
#define ATMEGA32_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Bit_Math.h"
#include "Platform_Types.h"

/*
*===============================================
*                   Includes
*===============================================
*/
#ifndef F_CPU
#define F_CPU    8000000u
#endif

/*================================================================*/
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define DATA_ADDRESS_SPACE          0x00
#define PERIPHERAL_MEMORY_BASE      0x20
#define SRAM_MEMORY_BASE            0x60

/*
*===============================================
*  Base addresses for data bus registers
*===============================================
*/

/*---------------------------GPIO-----------------------------*/
#define GPIOA_BASE      (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x19)
#define GPIOB_BASE      (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x16)
#define GPIOC_BASE      (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x13)
#define GPIOD_BASE      (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x10)

/*---------------------------SPI-----------------------------*/
#define SPI_BASE        (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x0D)

/*---------------------------Timer0-----------------------------*/
#define Timer0_BASE     (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x32)

/*---------------------------Timer2-----------------------------*/
#define Timer2_BASE     (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x22)

/*---------------------------ADC-----------------------------*/
#define ADC_BASE        (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x04)

/*---------------------------USART-----------------------------*/
#define USART_BASE      (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x09)

/*================================================================
*-*-*-*-*-*-*-*-*-*-*-*-
  System registers:
*-*-*-*-*-*-*-*-*-*-*-*-
*/
#define SREG    *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x3F))  /*The AVR Status Register*/
#define SPH     *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x3E))  /*Stack Pointer High Register*/
#define SPL     *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x3D))  /*Stack Pointer Low Register*/
#define SFIOR   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x30))  /*Special Function IO Register*/

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers:
//-*-*-*-*-*-*-*-*-*-*-*-

typedef struct{
    vuint8_t PIN;                   /*Port Input Pins Register*/
    vuint8_t DDR;                   /*Port Data Direction Register*/
    vuint8_t PORT;                  /*Port Data Register*/
}GPIO_typedef;

typedef struct{
    vuint8_t UBRRL;                   /*USART Baud-Rate Low Register*/
    vuint8_t UCSRB;                   /*USART Control & Statys Register B*/
    vuint8_t UCSRA;                   /*USART Control & Statys Register A*/
    vuint8_t UDR;                     /*USART I/O Data Register*/
}USART_typedef;


typedef struct{
    vuint8_t SPCR;                  /*SPI Control Register*/
    vuint8_t SPSR;                  /*SPI Status Register*/
    vuint8_t SPDR;                  /*SPI Data Register*/
}SPI_typedef;

typedef struct{
    vuint8_t TCNT0;                 /*Timer0 count Register*/
    vuint8_t TCCR0;                 /*Timer0 Control Register*/
    vuint64_t  :  64;               /*Reserved space*/
    vuint8_t OCR0;                  /*Timer0 output compare Register*/
}Timer0_typedef;

typedef struct{
    vuint8_t ASSR;                  /*Timer2 Asynchronous Status Register*/
    vuint8_t OCR2;                  /*Timer2 output compare Register*/
    vuint8_t TCNT2;                 /*Timer2 count Register*/
    vuint8_t TCCR2;                 /*Timer2 Control Register*/
}Timer2_typedef;

typedef struct{
    vuint8_t  ADCL;                 /*ADC Data Register Low*/
    vuint8_t  ADCH;                 /*ADC Data Register High*/
    vuint8_t  ADCSRA;               /*ADC Control and Status Register A*/
    vuint8_t  ADMUX;                /*ADC Multiplexer Selection Register*/
}ADC_typedef;


#define WDTCR   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x21))  /*Watchdog Timer Control Register*/

/*-------------------------Timers shared Registers---------------------------*/
#define TIMSK   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x39))  /*Timer Interrupts Mask Register*/
#define TIFR    *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x38))  /*Timer Interrupts Flag Register*/

#define MCUCSR  *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x34))  /*The MCU Control and Status Register 
                                                                          provides information on which reset source
                                                                          caused an MCU Reset*/

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

/*----------------GPIO-----------------------*/
#define GPIOA   ((GPIO_typedef *)(GPIOA_BASE))
#define GPIOB   ((GPIO_typedef *)(GPIOB_BASE))
#define GPIOC   ((GPIO_typedef *)(GPIOC_BASE))
#define GPIOD   ((GPIO_typedef *)(GPIOD_BASE))

/*----------------SPI-----------------------*/
#define SPI     ((SPI_typedef *)(SPI_BASE))

/*----------------Timer0-----------------------*/
#define TIMER0  ((Timer0_typedef *)(Timer0_BASE))

/*----------------Timer0-----------------------*/
#define TIMER2  ((Timer2_typedef *)(Timer2_BASE))

/*----------------ADC-----------------------*/
#define ADC     ((ADC_typedef *)(ADC_BASE))

/*-----------------USART------------------------*/
#define USART   ((volatile USART_typedef *)(USART_BASE))

#define USART_UBRRH   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x20))  /*USART Baud Rate Register High*/
#define USART_UCSRC   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x20))  /*USART control/status Register C*/

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define G_INTERRUPT_ENABLE      SREG |= (1 << 7);
#define G_INTERRUPT_DISABLE     SREG &= ~(1 << 7);


/**************************************************************************************************************************
*===============================================
*                 Bit Defenitions
*===============================================
*/
/*---------------------SFIOR------------------------*/
#define SFIOR_ADTS0_POS           5
#define SFIOR_ADTS0_MASK          (1 << SFIOR_ADTS0_POS)
#define SFIOR_ADTS1_POS           6
#define SFIOR_ADTS1_MASK          (1 << SFIOR_ADTS1_POS)
#define SFIOR_ADTS2_POS           7
#define SFIOR_ADTS2_MASK          (1 << SFIOR_ADTS2_POS)
#define SFIOR_ADTS_MASK           (SFIOR_ADTS0_MASK | SFIOR_ADTS1_MASK | SFIOR_ADTS2_MASK)

/*---------------------WDT------------------------*/

#define WDTCR_WDP0_POS              0
#define WDTCR_WDP0_MASK             (1 << WDTCR_WDP0_POS)
#define WDTCR_WDP1_POS              1
#define WDTCR_WDP1_MASK             (1 << WDTCR_WDP1_POS)
#define WDTCR_WDP2_POS              2
#define WDTCR_WDP2_MASK             (1 << WDTCR_WDP2_POS)
#define WDTCR_WDP_MASK              (WDTCR_WDP0_MASK | WDTCR_WDP1_MASK | WDTCR_WDP2_MASK) /*!< Watchdog prescaler*/

#define WDTCR_WDE_POS               3                         /*!< Watchdog Enable*/
#define WDTCR_WDE_MASK              (1 << WDTCR_WDE_POS)

#define WDTCR_WDTOE_POS             4                         /*!< Watchdog turn-off enable*/   
#define WDTCR_WDTOE_MASK            (1 << WDTCR_WDTOE_POS)


/*---------------------Timer0------------------------*/

/** @defgroup TCCR0
  * @{
  */
#define TIMER0_TCCR_CS0_POS         0
#define TIMER0_TCCR_CS0_MASK        (1 << TIMER0_TCCR_CS0_POS)
#define TIMER0_TCCR_CS1_POS         1
#define TIMER0_TCCR_CS1_MASK        (1 << TIMER0_TCCR_CS1_POS)
#define TIMER0_TCCR_CS2_POS         2
#define TIMER0_TCCR_CS2_MASK        (1 << TIMER0_TCCR_CS2_POS)
#define TIMER0_TCCR_CS_MASK         (TIMER0_TCCR_CS0_MASK | TIMER0_TCCR_CS1_MASK | TIMER0_TCCR_CS2_MASK)
#define TIMER0_TCCR_WGM0_POS        6
#define TIMER0_TCCR_WGM0_MASK       (1 << TIMER0_TCCR_WGM0_POS)
#define TIMER0_TCCR_WGM1_POS        3
#define TIMER0_TCCR_WGM1_MASK       (1 << TIMER0_TCCR_WGM1_POS)
#define TIMER0_TCCR_WGM_MASK        (TIMER0_TCCR_WGM0_MASK | TIMER0_TCCR_WGM1_MASK)
#define TIMER0_TCCR_COM0_POS        4
#define TIMER0_TCCR_COM0_MASK       (1 << TIMER0_TCCR_COM0_POS)
#define TIMER0_TCCR_COM1_POS        5
#define TIMER0_TCCR_COM1_MASK       (1 << TIMER0_TCCR_COM1_POS)
#define TIMER0_TCCR_COM_MASK        (TIMER0_TCCR_COM0_MASK | TIMER0_TCCR_COM1_MASK)
/**
  * @}
  */

/*---------------------Timer2------------------------*/

/** @defgroup TCCR0
  * @{
  */
#define TIMER2_TCCR_CS0_POS         0
#define TIMER2_TCCR_CS0_MASK        (1 << TIMER2_TCCR_CS0_POS)
#define TIMER2_TCCR_CS1_POS         1
#define TIMER2_TCCR_CS1_MASK        (1 << TIMER2_TCCR_CS1_POS)
#define TIMER2_TCCR_CS2_POS         2
#define TIMER2_TCCR_CS2_MASK        (1 << TIMER2_TCCR_CS2_POS)
#define TIMER2_TCCR_CS_MASK         (TIMER2_TCCR_CS0_MASK | TIMER2_TCCR_CS1_MASK | TIMER2_TCCR_CS2_MASK)
#define TIMER2_TCCR_WGM0_POS        6
#define TIMER2_TCCR_WGM0_MASK       (1 << TIMER2_TCCR_WGM0_POS)
#define TIMER2_TCCR_WGM1_POS        3
#define TIMER2_TCCR_WGM1_MASK       (1 << TIMER2_TCCR_WGM1_POS)
#define TIMER2_TCCR_WGM_MASK        (TIMER2_TCCR_WGM0_MASK | TIMER2_TCCR_WGM1_MASK)
#define TIMER2_TCCR_COM0_POS        4
#define TIMER2_TCCR_COM0_MASK       (1 << TIMER2_TCCR_COM0_POS)
#define TIMER2_TCCR_COM1_POS        5
#define TIMER2_TCCR_COM1_MASK       (1 << TIMER2_TCCR_COM1_POS)
#define TIMER2_TCCR_COM_MASK        (TIMER2_TCCR_COM0_MASK | TIMER2_TCCR_COM1_MASK)
/**
  * @}
  */

/** @defgroup TIMSK
  * @{
  */
 
#define TIMER0_TIMSK_TOIE0_POS         0
#define TIMER0_TIMSK_TOIE0_MASK        (1 << TIMER0_TIMSK_TOIE0_POS)
#define TIMER0_TIMSK_OCIE0_POS         1
#define TIMER0_TIMSK_OCIE0_MASK        (1 << TIMER0_TIMSK_OCIE0_POS)

#define TIMER2_TIMSK_TOIE2_POS         6
#define TIMER2_TIMSK_TOIE2_MASK        (1 << TIMER2_TIMSK_TOIE2_POS)
#define TIMER2_TIMSK_OCIE2_POS         7
#define TIMER2_TIMSK_OCIE2_MASK        (1 << TIMER2_TIMSK_OCIE2_POS)

/**
  * @}
  */

/** @defgroup TIFR
  * @{
  */

#define TIMER0_TIFR_TOV0_POS          0
#define TIMER0_TIFR_TOV0_MASK         (1 << TIMER0_TIFR_TOV0_POS)
#define TIMER0_TIFR_OCF0_POS          1
#define TIMER0_TIFR_OCF0_MASK         (1 << TIMER0_TIFR_OCF0_POS)

#define TIMER2_TIFR_TOV2_POS          6
#define TIMER2_TIFR_TOV2_MASK         (1 << TIMER2_TIFR_TOV2_POS)
#define TIMER2_TIFR_OCF2_POS          7
#define TIMER2_TIFR_OCF2_MASK         (1 << TIMER2_TIFR_OCF2_POS)

/**
  * @}
  */

/*---------------------ADC------------------------*/

/** @defgroup ADMUX
  * @{
  */

#define ADC_ADMUX_MUX0_POS             0
#define ADC_ADMUX_MUX0_MASK            (1 << ADC_ADMUX_MUX0_POS)
#define ADC_ADMUX_MUX1_POS             1
#define ADC_ADMUX_MUX1_MASK            (1 << ADC_ADMUX_MUX1_POS)
#define ADC_ADMUX_MUX2_POS             2
#define ADC_ADMUX_MUX2_MASK            (1 << ADC_ADMUX_MUX2_POS)
#define ADC_ADMUX_MUX3_POS             3
#define ADC_ADMUX_MUX3_MASK            (1 << ADC_ADMUX_MUX3_POS)
#define ADC_ADMUX_MUX4_POS             4
#define ADC_ADMUX_MUX4_MASK            (1 << ADC_ADMUX_MUX4_POS)
#define ADC_ADMUX_MUX_MASK             (ADC_ADMUX_MUX0_MASK | ADC_ADMUX_MUX1_MASK | ADC_ADMUX_MUX2_MASK | \
                                        ADC_ADMUX_MUX3_MASK | ADC_ADMUX_MUX4_MASK)
#define ADC_ADMUX_ADLAR_POS            5
#define ADC_ADMUX_ADLAR_MASK           (1 << ADC_ADMUX_ADLAR_POS)
#define ADC_ADMUX_REFS0_POS            6
#define ADC_ADMUX_REFS0_MASK           (1 << ADC_ADMUX_REFS0_POS)
#define ADC_ADMUX_REFS1_POS            7
#define ADC_ADMUX_REFS1_MASK           (1 << ADC_ADMUX_REFS1_POS)
#define ADC_ADMUX_REFS_MASK            (ADC_ADMUX_REFS0_MASK | ADC_ADMUX_REFS1_MASK)

/**
  * @}
  */

/** @defgroup ADCSRA
  * @{
  */

#define ADC_ADCSRA_ADPS0_POS             0
#define ADC_ADCSRA_ADPS0_MASK            (1 << ADC_ADCSRA_ADPS0_POS)
#define ADC_ADCSRA_ADPS1_POS             1
#define ADC_ADCSRA_ADPS1_MASK            (1 << ADC_ADCSRA_ADPS1_POS)
#define ADC_ADCSRA_ADPS2_POS             2
#define ADC_ADCSRA_ADPS2_MASK            (1 << ADC_ADCSRA_ADPS2_POS)
#define ADC_ADCSRA_ADPS_MASK             (ADC_ADCSRA_ADPS0_MASK | ADC_ADCSRA_ADPS1_MASK | ADC_ADCSRA_ADPS2_MASK)
#define ADC_ADCSRA_ADIE_POS              3
#define ADC_ADCSRA_ADIE_MASK             (1 << ADC_ADCSRA_ADIE_POS)
#define ADC_ADCSRA_ADIF_POS              4
#define ADC_ADCSRA_ADIF_MASK             (1 << ADC_ADCSRA_ADIF_POS)
#define ADC_ADCSRA_ADATE_POS             5
#define ADC_ADCSRA_ADATE_MASK            (1 << ADC_ADCSRA_ADATE_POS)
#define ADC_ADCSRA_ADSC_POS              6
#define ADC_ADCSRA_ADSC_MASK             (1 << ADC_ADCSRA_ADSC_POS)
#define ADC_ADCSRA_ADEN_POS              7
#define ADC_ADCSRA_ADEN_MASK             (1 << ADC_ADCSRA_ADEN_POS)


/**
  * @}
  */


/*---------------------USART------------------------*/

/** @defgroup UCSRA
  * @{
  */
#define USART_UCSRA_RXC_POS               7
#define USART_UCSRA_RXC_MASK              (1 << USART_UCSRA_RXC_POS)

#define USART_UCSRA_TXC_POS               6
#define USART_UCSRA_TXC_MASK              (1 << USART_UCSRA_TXC_POS)

#define USART_UCSRA_UDRE_POS              5
#define USART_UCSRA_UDRE_MASK             (1 << USART_UCSRA_UDRE_POS)

#define USART_UCSRA_FE_POS                4
#define USART_UCSRA_FE_MASK               (1 << USART_UCSRA_FE_POS)

#define USART_UCSRA_DOR_POS               3
#define USART_UCSRA_DOR_MASK              (1 << USART_UCSRA_DOR_POS)

#define USART_UCSRA_PE_POS                2
#define USART_UCSRA_PE_MASK               (1 << USART_UCSRA_PE_POS)

#define USART_UCSRA_U2X_POS               1
#define USART_UCSRA_U2X_MASK              (1 << USART_UCSRA_U2X_POS)

/**
  * @}
  */

/** @defgroup UCSRB
  * @{
  */
#define USART_UCSRB_RXCIE_POS                 7
#define USART_UCSRB_RXCIE_MASK                (1 << USART_UCSRB_RXCIE_POS)

#define USART_UCSRB_TXCIE_POS                 6
#define USART_UCSRB_TXCIE_MASK                (1 << USART_UCSRB_TXCIE_POS)

#define USART_UCSRB_UDREIE_POS                5
#define USART_UCSRB_UDREIE_MASK               (1 << USART_UCSRB_UDREIE_POS)

#define USART_UCSRB_RXEN_POS                  4
#define USART_UCSRB_RXEN_MASK                 (1 << USART_UCSRB_RXEN_POS)

#define USART_UCSRB_TXEN_POS                  3
#define USART_UCSRB_TXEN_MASK                 (1 << USART_UCSRB_TXEN_POS)

#define USART_UCSRB_UCSZ2_POS                 2
#define USART_UCSRB_UCSZ2_MASK                (1 << USART_UCSRB_UCSZ2_POS)

#define USART_UCSRB_RXB8_POS                  1
#define USART_UCSRB_RXB8_MASK                 (1 << USART_UCSRB_RXB8_POS)

#define USART_UCSRB_TXB8_POS                  0
#define USART_UCSRB_TXB8_MASK                 (1 << USART_UCSRB_TXB8_POS)

/**
  * @}
  */

/** @defgroup   UCSRC
  * @{
  */
#define USART_UCSRC_URSEL_POS           7
#define USART_UCSRC_URSEL_MASK          (1 << USART_UCSRC_URSEL_POS)

#define USART_UCSRC_UMSEL_POS           6
#define USART_UCSRC_UMSEL_MASK          (1 << USART_UCSRC_URSEL_POS)

#define USART_UCSRC_UPM1_POS            5
#define USART_UCSRC_UPM1_MASK           (1 << USART_UCSRC_UPM1_POS)
#define USART_UCSRC_UPM0_POS            4
#define USART_UCSRC_UPM0_MASK           (1 << USART_UCSRC_UPM0_POS)
#define USART_UCSRC_UPM_MASK            (USART_UCSRC_UPM1_MASK | USART_UCSRC_UPM0_MASK)

#define USART_UCSRC_USBS_POS            3
#define USART_UCSRC_USBS_MASK           (1 << USART_UCSRC_USBS_POS)

#define USART_UCSRC_UCSZ1_POS            2
#define USART_UCSRC_UCSZ1_MASK           (1 << USART_UCSRC_UCSZ1_POS)
#define USART_UCSRC_UCSZ0_POS            1
#define USART_UCSRC_UCSZ0_MASK           (1 << USART_UCSRC_UCSZ0_POS)
#define USART_UCSRC_UCSZ_MASK            (USART_UCSRC_UCSZ1_MASK | USART_UCSRC_UCSZ0_MASK)
/**
  * @}
  */

#endif /* ATMEGA32_H_ */