# Atmega32 Timer0 Driver

## Introduction

This module contains functions for configuring and controlling the Timer0 module on the Atmega32 microcontroller.

## Description

The Atmega32 Timer0 driver facilitates precise timing and event generation capabilities within embedded systems leveraging the Atmega32 microcontroller platform. Timer0, an 8-bit timer/counter unit, plays a pivotal role in timekeeping, event scheduling, and pulse generation applications, offering versatile functionality tailored to diverse system requirements.

## Features

- **Timer0 Initialization**: Initialize Timer0 with specified configuration parameters.
- **Timer0 Start/Stop**: Start or stop Timer0 operation.
- **Get/Set Compare Value**: Retrieve or modify the value of the output compare register.
- **Get/Set Counter Value**: Retrieve or modify the value of the counter register.
- **Get/Set Overflow Value**: Retrieve or modify the number of overflow events.
- **Interrupt Callbacks**: Set callbacks for overflow and compare match interrupts.
- **Busy Wait Delay**: Functions for busy wait delays in milliseconds and microseconds.

## Getting Started

### Prerequisites

- Atmega32 microcontroller
- Compatible Integrated Development Environment (IDE) such as Atmel Studio or MPLAB X IDE
- Basic knowledge of C programming and microcontroller peripherals

### Installation

1. Clone this repository or download the source code.
2. Include the header and source files (`Atmega32_Timer0.h` and `Atmega32_Timer0.c`) in your project.

## Usage

1. **Timer0 Initialization**: Initialize Timer0 using `MCAL_TIMER0_Init()` with configuration parameters in the `sTIMER0_Config_t` structure.

    ```c
    sTIMER0_Config_t config;
    // Set configuration parameters
    MCAL_TIMER0_Init(&config);
    ```

2. **Timer0 Start/Stop**: Start or stop Timer0 using `MCAL_TIMER0_Start()` and `MCAL_TIMER0_Stop()`.

    ```c
    MCAL_TIMER0_Start();
    ```

3. **Get/Set Compare Value**: Get or set the value of the output compare register using `MCAL_TIMER0_GetCompare()` and `MCAL_TIMER0_SetCompare()`.

    ```c
    uint8_t compareVal;
    MCAL_TIMER0_GetCompare(&compareVal);
    ```

4. **Get/Set Counter Value**: Get or set the value of the counter register using `MCAL_TIMER0_GetCounter()` and `MCAL_TIMER0_SetCounter()`.

    ```c
    uint8_t counterVal;
    MCAL_TIMER0_GetCounter(&counterVal);
    ```

5. **Get/Set Overflow Value**: Get or set the number of overflow events using `MCAL_TIMER0_GetOverflow()` and `MCAL_TIMER0_SetOverflow()`.

    ```c
    uint32_t overflowVal;
    MCAL_TIMER0_GetOverflow(&overflowVal);
    ```

6. **Interrupt Callbacks**: Set callbacks for overflow and compare match interrupts using `MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT()` and `MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT()`.

    ```c
    void overflow_callback() {
        // Overflow interrupt handler
    }
    MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT(overflow_callback);
    ```

7. **Busy Wait Delay**: Use `MCAL_TIMER0_BusyWaitDelayms()` and `MCAL_TIMER0_BusyWaitDelayus()` for busy wait delays in milliseconds and microseconds respectively.

    ```c
    MCAL_TIMER0_BusyWaitDelayms(1000); // Delay for 1000 milliseconds
    ```

8. **Single Interval Delay**: Utilize `MCAL_TIMER0_SingleIntervalDelayms()` to create a delay without halting the CPU, using interrupts.

    ```c
    void delay_complete_callback() {
        // Delay complete callback handler
    }

    int main(void) {
        // Initialize Timer0 configuration struct
        sTIMER0_Config_t timer_config;
        timer_config.TIMER0_CLK_SRC = TIMER0_Prescale_64;
        timer_config.TIMER0_Mode = TIMER0_CTC_Mode;
        timer_config.TIMER0_COM = TIMER0_COM_Disconnected;
        timer_config.TIMER0_OCIE = TIMER0_TOCI_Enable;
        timer_config.TIMER0_OIE = TIMER0_TOI_Enable;

        // Initialize Timer0
        MCAL_TIMER0_Init(&timer_config);

        // Set callback for delay completion
        MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(delay_complete_callback);

        // Enable global interrupts
        sei();

        // Perform a single interval delay of 1000 milliseconds
        MCAL_TIMER0_SingleIntervalDelayms(1000, delay_complete_callback);

        while (1) {
            // Main application code
        }

        return 0;
    }
    ```

    In this usage example, the `MCAL_TIMER0_SingleIntervalDelayms()` function is employed to create a delay of 1000 milliseconds without halting the CPU. An overflow interrupt handler can be specified with `delay_complete_callback` to execute code when the delay completes.
