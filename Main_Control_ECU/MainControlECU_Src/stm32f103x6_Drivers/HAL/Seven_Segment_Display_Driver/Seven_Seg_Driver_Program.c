/**
 * @file Seven_Seg_Driver_Program.c
 * 
 * @brief this file implements the APIs of the 7 segment display driver.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Seven_Seg_Driver_Interface.h"

/** @defgroup Global_Variables
  * @{
  */
static uint8 Glob_u8DisplayedNumber = 0;
/**
  * @}
  */

/**************************************************************************************************************************
===============================================
*           APIs Definitions
*===============================================
*/

/**
 * @brief This function initializes the binary coded seven segment display.
 * 
 */
void HAL_SevenSeg_Init(void)
{
    GPIO_Pin_Config_t cfg;
    cfg.pinMode = GPIO_MODE_GP_OUTPUT_PP_2MHZ;

    cfg.pinNumber = SEVEN_SEGMEN_A_PIN;
    MCAL_GPIO_Init(SEVEN_SEGMEN_A_PORT, &cfg);
    
    cfg.pinNumber = SEVEN_SEGMEN_B_PIN;
    MCAL_GPIO_Init(SEVEN_SEGMEN_B_PORT, &cfg);
    
    cfg.pinNumber = SEVEN_SEGMEN_C_PIN;
    MCAL_GPIO_Init(SEVEN_SEGMEN_C_PORT, &cfg);
    
    cfg.pinNumber = SEVEN_SEGMEN_D_PIN;
    MCAL_GPIO_Init(SEVEN_SEGMEN_D_PORT, &cfg);
}

/**
 * @brief This function displays a given number onto the display.
 * 
 * @param copy_Number : Number to be displayed must be between 0 and 9.
 */
void HAL_SevenSeg_DisplayNumber(uint8 copy_Number)
{
    MCAL_GPIO_WritePin(SEVEN_SEGMEN_A_PORT, SEVEN_SEGMEN_A_PIN, READ_BIT(copy_Number, 3));
    MCAL_GPIO_WritePin(SEVEN_SEGMEN_B_PORT, SEVEN_SEGMEN_B_PIN, READ_BIT(copy_Number, 2));
    MCAL_GPIO_WritePin(SEVEN_SEGMEN_C_PORT, SEVEN_SEGMEN_C_PIN, READ_BIT(copy_Number, 1));
    MCAL_GPIO_WritePin(SEVEN_SEGMEN_D_PORT, SEVEN_SEGMEN_D_PIN, READ_BIT(copy_Number, 0));

    Glob_u8DisplayedNumber = copy_Number;
}

/**
 * @brief This function increments the number displayed on the display by one.
 * 
 */
void HAL_SevenSeg_Increment()
{
    if(Glob_u8DisplayedNumber < 9)
    {
        Glob_u8DisplayedNumber++;
        
        HAL_SevenSeg_DisplayNumber(Glob_u8DisplayedNumber);
    }

}

/**
 * @brief This function decrements the number displayed on the display by one.
 * 
 */
void HAL_SevenSeg_Decrement()
{
    if(Glob_u8DisplayedNumber > 0)
    {
        Glob_u8DisplayedNumber--;
        
        HAL_SevenSeg_DisplayNumber(Glob_u8DisplayedNumber);
    }

}

