/*
**************************************************************************************************************************
* file		 : stm32f103x6_EXTI.h
* brief     : This file contains functions to setup the EXTI peripheral.
* Author    : Hossam Eid
* Created on: Sep 8, 2023
**************************************************************************************************************************
* note: This module is intended for use with the STM32F103xx microcontroller series, but may be adapted for use with
* other compatible processors.
**************************************************************************************************************************
*/

#ifndef MCAL_EXTI_STM32F103X6_EXTI_H_
#define MCAL_EXTI_STM32F103X6_EXTI_H_

/*
*===============================================
*                   Includes
*===============================================
*/

#include "stm32f103x6.h"
#include "Platform_Types.h"
#include "GPIO/stm32f103x6_GPIO.h"
#include "AFIO/stm32f103x6_AFIO.h"
#include "NVIC/stm32f103x6_NVIC.h"

/**************************************************************************************************************************
*===============================================
* User type definitions (structures)
*===============================================
*/

typedef struct
{
    uint8   EXTI_lineNumber;            /*Specifies the EXTI line number must be a val of @ref EXTI_LINE_DEFINE*/
    GPIO_t* GPIO_PORT;                  /*The GPIO port to be used with this external interrupt*/
    uint8   GPIO_pinNumber;             /*The GPIO pin number to be used with this external interrupt*/
    uint8   AFIO_Port_config;           /*The used port ID in the AFIO module*/  
    uint8   EXTI_IVT_index;             /*The index of this interrupt in the vector table*/  
}EXTI_PinConfig_t;


typedef struct
{
    EXTI_PinConfig_t    PinConfig;              /*Choose the pin to be used with this external interrupt
                                                this must be a value of @ref EXTI_GPIOx_PINy*/
    
    uint8               EXTI_Trigger_Mode;      /*Choose the interrupt trigger Mode 
                                                ,must be a value of @ref EXTI_TRIGGER_MODE*/ 

    uint8               EXTI_En;                 /*Enable or Disable the EXTI @ref EXTI_STATUS*/

    uint8               EXTI_Priority;           /*Set the priority of the interrupt @ref NVIC_PRIORITY_DEFINE*/

    void (* P_callback_func)(void);              /*pointer to the function to be executed when the interrupt triggers*/
}EXTI_config_t;

/**************************************************************************************************************************
*===============================================
*         Macros Configuration References
*===============================================
*/

/*----------------@ref EXTI_LINE_DEFINE-----------------*/
#define EXTI_LINE_0           0 
#define EXTI_LINE_1           1 
#define EXTI_LINE_2           2 
#define EXTI_LINE_3           3 
#define EXTI_LINE_4           4 
#define EXTI_LINE_5           5 
#define EXTI_LINE_6           6 
#define EXTI_LINE_7           7 
#define EXTI_LINE_8           8 
#define EXTI_LINE_9           9
#define EXTI_LINE_10          10
#define EXTI_LINE_11          11
#define EXTI_LINE_12          12
#define EXTI_LINE_13          13 
#define EXTI_LINE_14          14 
#define EXTI_LINE_15          15 

/*----------------@ref EXTI_TRIGGER_MODE-----------------*/
#define EXTI_TRIGGER_RISING_EDGE            0
#define EXTI_TRIGGER_FALLING_EDGE           1
#define EXTI_TRIGGER_BOTH_EDGES             2

/*---------------- @ref EXTI_STATUS -----------------*/
#define EXTI_DISABLE    0
#define EXTI_ENABLE     1
/*--------------------------------------------@ref EXTI_GPIOx_PINy--------------------------------------------------*/

/*
    Note: LQFP48 package has PORT(A, B) ,part of PORT(C,D) and PORTE isn't used
*/

/*-------------------------------------EXTI line 0------------------------------------------------*/
#define EXTI_GPIOA_PIN0          (EXTI_PinConfig_t){EXTI_LINE_0, GPIOA, GPIO_PIN0, AFIO_PORTA, NVIC_EXTI0_IVT_INDEX}
#define EXTI_GPIOB_PIN0          (EXTI_PinConfig_t){EXTI_LINE_0, GPIOB, GPIO_PIN0, AFIO_PORTB, NVIC_EXTI0_IVT_INDEX}
#define EXTI_GPIOC_PIN0          (EXTI_PinConfig_t){EXTI_LINE_0, GPIOC, GPIO_PIN0, AFIO_PORTC, NVIC_EXTI0_IVT_INDEX}
#define EXTI_GPIOD_PIN0          (EXTI_PinConfig_t){EXTI_LINE_0, GPIOD, GPIO_PIN0, AFIO_PORTD, NVIC_EXTI0_IVT_INDEX}
#define EXTI_GPIOE_PIN0          (EXTI_PinConfig_t){EXTI_LINE_0, GPIOE, GPIO_PIN0, AFIO_PORTE, NVIC_EXTI0_IVT_INDEX}

/*-------------------------------------EXTI line 1------------------------------------------------*/
#define EXTI_GPIOA_PIN1          (EXTI_PinConfig_t){EXTI_LINE_1, GPIOA, GPIO_PIN1, AFIO_PORTA, NVIC_EXTI1_IVT_INDEX}
#define EXTI_GPIOB_PIN1          (EXTI_PinConfig_t){EXTI_LINE_1, GPIOB, GPIO_PIN1, AFIO_PORTB, NVIC_EXTI1_IVT_INDEX}
#define EXTI_GPIOC_PIN1          (EXTI_PinConfig_t){EXTI_LINE_1, GPIOC, GPIO_PIN1, AFIO_PORTC, NVIC_EXTI1_IVT_INDEX}
#define EXTI_GPIOD_PIN1          (EXTI_PinConfig_t){EXTI_LINE_1, GPIOD, GPIO_PIN1, AFIO_PORTD, NVIC_EXTI1_IVT_INDEX}
#define EXTI_GPIOE_PIN1          (EXTI_PinConfig_t){EXTI_LINE_1, GPIOE, GPIO_PIN1, AFIO_PORTE, NVIC_EXTI1_IVT_INDEX}

/*-------------------------------------EXTI line 2------------------------------------------------*/
#define EXTI_GPIOA_PIN2          (EXTI_PinConfig_t){EXTI_LINE_2, GPIOA, GPIO_PIN2, AFIO_PORTA, NVIC_EXTI2_IVT_INDEX}
#define EXTI_GPIOB_PIN2          (EXTI_PinConfig_t){EXTI_LINE_2, GPIOB, GPIO_PIN2, AFIO_PORTB, NVIC_EXTI2_IVT_INDEX}
#define EXTI_GPIOC_PIN2          (EXTI_PinConfig_t){EXTI_LINE_2, GPIOC, GPIO_PIN2, AFIO_PORTC, NVIC_EXTI2_IVT_INDEX}
#define EXTI_GPIOD_PIN2          (EXTI_PinConfig_t){EXTI_LINE_2, GPIOD, GPIO_PIN2, AFIO_PORTD, NVIC_EXTI2_IVT_INDEX}
#define EXTI_GPIOE_PIN2          (EXTI_PinConfig_t){EXTI_LINE_2, GPIOE, GPIO_PIN2, AFIO_PORTE, NVIC_EXTI2_IVT_INDEX}

/*-------------------------------------EXTI line 3------------------------------------------------*/
#define EXTI_GPIOA_PIN3          (EXTI_PinConfig_t){EXTI_LINE_3, GPIOA, GPIO_PIN3, AFIO_PORTA, NVIC_EXTI3_IVT_INDEX}
#define EXTI_GPIOB_PIN3          (EXTI_PinConfig_t){EXTI_LINE_3, GPIOB, GPIO_PIN3, AFIO_PORTB, NVIC_EXTI3_IVT_INDEX}
#define EXTI_GPIOC_PIN3          (EXTI_PinConfig_t){EXTI_LINE_3, GPIOC, GPIO_PIN3, AFIO_PORTC, NVIC_EXTI3_IVT_INDEX}
#define EXTI_GPIOD_PIN3          (EXTI_PinConfig_t){EXTI_LINE_3, GPIOD, GPIO_PIN3, AFIO_PORTD, NVIC_EXTI3_IVT_INDEX}
#define EXTI_GPIOE_PIN3          (EXTI_PinConfig_t){EXTI_LINE_3, GPIOE, GPIO_PIN3, AFIO_PORTE, NVIC_EXTI3_IVT_INDEX}

/*-------------------------------------EXTI line 4------------------------------------------------*/
#define EXTI_GPIOA_PIN4          (EXTI_PinConfig_t){EXTI_LINE_4, GPIOA, GPIO_PIN4, AFIO_PORTA, NVIC_EXTI4_IVT_INDEX}
#define EXTI_GPIOB_PIN4          (EXTI_PinConfig_t){EXTI_LINE_4, GPIOB, GPIO_PIN4, AFIO_PORTB, NVIC_EXTI4_IVT_INDEX}
#define EXTI_GPIOC_PIN4          (EXTI_PinConfig_t){EXTI_LINE_4, GPIOC, GPIO_PIN4, AFIO_PORTC, NVIC_EXTI4_IVT_INDEX}
#define EXTI_GPIOD_PIN4          (EXTI_PinConfig_t){EXTI_LINE_4, GPIOD, GPIO_PIN4, AFIO_PORTD, NVIC_EXTI4_IVT_INDEX}
#define EXTI_GPIOE_PIN4          (EXTI_PinConfig_t){EXTI_LINE_4, GPIOE, GPIO_PIN4, AFIO_PORTE, NVIC_EXTI4_IVT_INDEX}

/*-------------------------------------EXTI line 5------------------------------------------------*/
#define EXTI_GPIOA_PIN5          (EXTI_PinConfig_t){EXTI_LINE_5, GPIOA, GPIO_PIN5, AFIO_PORTA, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOB_PIN5          (EXTI_PinConfig_t){EXTI_LINE_5, GPIOB, GPIO_PIN5, AFIO_PORTB, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOC_PIN5          (EXTI_PinConfig_t){EXTI_LINE_5, GPIOC, GPIO_PIN5, AFIO_PORTC, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOD_PIN5          (EXTI_PinConfig_t){EXTI_LINE_5, GPIOD, GPIO_PIN5, AFIO_PORTD, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOE_PIN5          (EXTI_PinConfig_t){EXTI_LINE_5, GPIOE, GPIO_PIN5, AFIO_PORTE, NVIC_EXTI9_5_IVT_INDEX}

/*-------------------------------------EXTI line 6------------------------------------------------*/
#define EXTI_GPIOA_PIN6          (EXTI_PinConfig_t){EXTI_LINE_6, GPIOA, GPIO_PIN6, AFIO_PORTA, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOB_PIN6          (EXTI_PinConfig_t){EXTI_LINE_6, GPIOB, GPIO_PIN6, AFIO_PORTB, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOC_PIN6          (EXTI_PinConfig_t){EXTI_LINE_6, GPIOC, GPIO_PIN6, AFIO_PORTC, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOD_PIN6          (EXTI_PinConfig_t){EXTI_LINE_6, GPIOD, GPIO_PIN6, AFIO_PORTD, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOE_PIN6          (EXTI_PinConfig_t){EXTI_LINE_6, GPIOE, GPIO_PIN6, AFIO_PORTE, NVIC_EXTI9_5_IVT_INDEX}

/*-------------------------------------EXTI line 7------------------------------------------------*/
#define EXTI_GPIOA_PIN7          (EXTI_PinConfig_t){EXTI_LINE_7, GPIOA, GPIO_PIN7, AFIO_PORTA, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOB_PIN7          (EXTI_PinConfig_t){EXTI_LINE_7, GPIOB, GPIO_PIN7, AFIO_PORTB, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOC_PIN7          (EXTI_PinConfig_t){EXTI_LINE_7, GPIOC, GPIO_PIN7, AFIO_PORTC, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOD_PIN7          (EXTI_PinConfig_t){EXTI_LINE_7, GPIOD, GPIO_PIN7, AFIO_PORTD, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOE_PIN7          (EXTI_PinConfig_t){EXTI_LINE_7, GPIOE, GPIO_PIN7, AFIO_PORTE, NVIC_EXTI9_5_IVT_INDEX}

/*-------------------------------------EXTI line 8------------------------------------------------*/
#define EXTI_GPIOA_PIN8          (EXTI_PinConfig_t){EXTI_LINE_8, GPIOA, GPIO_PIN8, AFIO_PORTA, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOB_PIN8          (EXTI_PinConfig_t){EXTI_LINE_8, GPIOB, GPIO_PIN8, AFIO_PORTB, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOC_PIN8          (EXTI_PinConfig_t){EXTI_LINE_8, GPIOC, GPIO_PIN8, AFIO_PORTC, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOD_PIN8          (EXTI_PinConfig_t){EXTI_LINE_8, GPIOD, GPIO_PIN8, AFIO_PORTD, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOE_PIN8          (EXTI_PinConfig_t){EXTI_LINE_8, GPIOE, GPIO_PIN8, AFIO_PORTE, NVIC_EXTI9_5_IVT_INDEX}

/*-------------------------------------EXTI line 9------------------------------------------------*/
#define EXTI_GPIOA_PIN9          (EXTI_PinConfig_t){EXTI_LINE_9, GPIOA, GPIO_PIN9, AFIO_PORTA, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOB_PIN9          (EXTI_PinConfig_t){EXTI_LINE_9, GPIOB, GPIO_PIN9, AFIO_PORTB, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOC_PIN9          (EXTI_PinConfig_t){EXTI_LINE_9, GPIOC, GPIO_PIN9, AFIO_PORTC, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOD_PIN9          (EXTI_PinConfig_t){EXTI_LINE_9, GPIOD, GPIO_PIN9, AFIO_PORTD, NVIC_EXTI9_5_IVT_INDEX}
#define EXTI_GPIOE_PIN9          (EXTI_PinConfig_t){EXTI_LINE_9, GPIOE, GPIO_PIN9, AFIO_PORTE, NVIC_EXTI9_5_IVT_INDEX}

/*-------------------------------------EXTI line 10------------------------------------------------*/
#define EXTI_GPIOA_PIN10         (EXTI_PinConfig_t){EXTI_LINE_10, GPIOA, GPIO_PIN10, AFIO_PORTA, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOB_PIN10         (EXTI_PinConfig_t){EXTI_LINE_10, GPIOB, GPIO_PIN10, AFIO_PORTB, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOC_PIN10         (EXTI_PinConfig_t){EXTI_LINE_10, GPIOC, GPIO_PIN10, AFIO_PORTC, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOD_PIN10         (EXTI_PinConfig_t){EXTI_LINE_10, GPIOD, GPIO_PIN10, AFIO_PORTD, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOE_PIN10         (EXTI_PinConfig_t){EXTI_LINE_10, GPIOE, GPIO_PIN10, AFIO_PORTE, NVIC_EXTI15_10_IVT_INDEX}

/*-------------------------------------EXTI line 11------------------------------------------------*/
#define EXTI_GPIOA_PIN11         (EXTI_PinConfig_t){EXTI_LINE_11, GPIOA, GPIO_PIN11, AFIO_PORTA, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOB_PIN11         (EXTI_PinConfig_t){EXTI_LINE_11, GPIOB, GPIO_PIN11, AFIO_PORTB, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOC_PIN11         (EXTI_PinConfig_t){EXTI_LINE_11, GPIOC, GPIO_PIN11, AFIO_PORTC, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOD_PIN11         (EXTI_PinConfig_t){EXTI_LINE_11, GPIOD, GPIO_PIN11, AFIO_PORTD, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOE_PIN11         (EXTI_PinConfig_t){EXTI_LINE_11, GPIOE, GPIO_PIN11, AFIO_PORTE, NVIC_EXTI15_10_IVT_INDEX}

/*-------------------------------------EXTI line 12------------------------------------------------*/
#define EXTI_GPIOA_PIN12         (EXTI_PinConfig_t){EXTI_LINE_12, GPIOA, GPIO_PIN12, AFIO_PORTA, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOB_PIN12         (EXTI_PinConfig_t){EXTI_LINE_12, GPIOB, GPIO_PIN12, AFIO_PORTB, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOC_PIN12         (EXTI_PinConfig_t){EXTI_LINE_12, GPIOC, GPIO_PIN12, AFIO_PORTC, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOD_PIN12         (EXTI_PinConfig_t){EXTI_LINE_12, GPIOD, GPIO_PIN12, AFIO_PORTD, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOE_PIN12         (EXTI_PinConfig_t){EXTI_LINE_12, GPIOE, GPIO_PIN12, AFIO_PORTE, NVIC_EXTI15_10_IVT_INDEX}

/*-------------------------------------EXTI line 13------------------------------------------------*/
#define EXTI_GPIOA_PIN13         (EXTI_PinConfig_t){EXTI_LINE_13, GPIOA, GPIO_PIN13, AFIO_PORTA, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOB_PIN13         (EXTI_PinConfig_t){EXTI_LINE_13, GPIOB, GPIO_PIN13, AFIO_PORTB, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOC_PIN13         (EXTI_PinConfig_t){EXTI_LINE_13, GPIOC, GPIO_PIN13, AFIO_PORTC, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOD_PIN13         (EXTI_PinConfig_t){EXTI_LINE_13, GPIOD, GPIO_PIN13, AFIO_PORTD, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOE_PIN13         (EXTI_PinConfig_t){EXTI_LINE_13, GPIOE, GPIO_PIN13, AFIO_PORTE, NVIC_EXTI15_10_IVT_INDEX}

/*-------------------------------------EXTI line 14------------------------------------------------*/
#define EXTI_GPIOA_PIN14         (EXTI_PinConfig_t){EXTI_LINE_14, GPIOA, GPIO_PIN14, AFIO_PORTA, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOB_PIN14         (EXTI_PinConfig_t){EXTI_LINE_14, GPIOB, GPIO_PIN14, AFIO_PORTB, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOC_PIN14         (EXTI_PinConfig_t){EXTI_LINE_14, GPIOC, GPIO_PIN14, AFIO_PORTC, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOD_PIN14         (EXTI_PinConfig_t){EXTI_LINE_14, GPIOD, GPIO_PIN14, AFIO_PORTD, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOE_PIN14         (EXTI_PinConfig_t){EXTI_LINE_14, GPIOE, GPIO_PIN14, AFIO_PORTE, NVIC_EXTI15_10_IVT_INDEX}

/*-------------------------------------EXTI line 15------------------------------------------------*/
#define EXTI_GPIOA_PIN15         (EXTI_PinConfig_t){EXTI_LINE_15, GPIOA, GPIO_PIN15, AFIO_PORTA, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOB_PIN15         (EXTI_PinConfig_t){EXTI_LINE_15, GPIOB, GPIO_PIN15, AFIO_PORTB, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOC_PIN15         (EXTI_PinConfig_t){EXTI_LINE_15, GPIOC, GPIO_PIN15, AFIO_PORTC, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOD_PIN15         (EXTI_PinConfig_t){EXTI_LINE_15, GPIOD, GPIO_PIN15, AFIO_PORTD, NVIC_EXTI15_10_IVT_INDEX}
#define EXTI_GPIOE_PIN15         (EXTI_PinConfig_t){EXTI_LINE_15, GPIOE, GPIO_PIN15, AFIO_PORTE, NVIC_EXTI15_10_IVT_INDEX}


/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL EXTI DRIVER"
*===============================================
*/

/*
======================================================================================================================
* @Func_name	:   MCAL_EXTI_Enable
* @brief		:   This function enables the specified external interrupt with the specified options.
* @param [in]	:   EXTI_Config: External interrupt configuration
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_EXTI_Enable(EXTI_config_t* EXTI_Config);

/*
======================================================================================================================
* @Func_name	:   MCAL_EXTI_Update_Config
* @brief		:   This function updates the specified external interrupt configuration.
* @param [in]	:   EXTI_Config: External interrupt configuration
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_EXTI_Update_Config(EXTI_config_t* EXTI_Config);

/*
======================================================================================================================
* @Func_name	:   MCAL_EXTI_Disable
* @brief		:   Disable the specified MCAL external interrupt.
* @param [in]	:   EXTI_lineNumber: specifies the interrupt line number, must be value of @ref EXTI_LINE_DEFINE.
* @param [in]	:   EXTI_IVT_index: The index of the interrupt in the IVT, must be value of @ref NVIC_MODULE_IVT_INDEX.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_EXTI_Disable(uint8 EXTI_lineNumber, uint8 EXTI_IVT_index);

/*
======================================================================================================================
* @Func_name	:   MCAL_EXTI_Reset
* @brief		:   Reset the EXTI peripheral by resetting all its registers.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_EXTI_Reset();

#endif /* MCAL_EXTI_STM32F103X6_EXTI_H_ */
