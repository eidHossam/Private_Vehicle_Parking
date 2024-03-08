/**
 * @file main.c
 * 
 * @brief this file implements the main functionality of the entrance gate ECU.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 07-03-2024
 * 
 * @version 1.0
 */
#define F_CPU  8000000UL
#include "Atmega32_Drivers/APP/APP.h"

int main(void)
{
    EntranceGate_ECU_APP_SETUP();

    while (1) 
    {
        EntranceGate_ECU_APP_Loop();
    }
}

