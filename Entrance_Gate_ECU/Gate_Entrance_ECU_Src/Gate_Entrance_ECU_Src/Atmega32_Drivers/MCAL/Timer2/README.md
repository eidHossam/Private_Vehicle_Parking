# Atmega32 Timer2 Driver

## Introduction

This module contains functions for configuring and controlling the Timer2 module on the Atmega32 microcontroller.

## Description

The Atmega32 Timer2 driver provides essential functionalities to interact with Timer2, enabling precise timing and event generation capabilities in embedded systems utilizing the Atmega32 microcontroller platform.

## Features

- **Timer2 Initialization**: Initialize Timer2 with specified configuration parameters.
- **Timer2 Start/Stop**: Start or stop Timer2 operation.
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
2. Include the header and source files (`Atmega32_Timer2.h` and `Atmega32_Timer2.c`) in your project.

## Usage

1. **Timer2 Initialization**: Initialize Timer2 using `MCAL_TIMER2_Init()` with configuration parameters in the `sTIMER2_Config_t` structure.

    ```c
    sTIMER2_Config_t config;
    // Set configuration parameters
    MCAL_TIMER2_Init(&config);
    ```

2. **Timer2 Start/Stop**: Start or stop Timer2 using `MCAL_TIMER2_Start()` and `MCAL_TIMER2_Stop()`.

    ```c
    MCAL_TIMER2_Start();
    ```

3. **Get/Set Compare Value**: Get or set the value of the output compare register using `MCAL_TIMER2_GetCompare()` and `MCAL_TIMER2_SetCompare()`.

    ```c
    uint8_t compareVal;
    MCAL_TIMER2_GetCompare(&compareVal);
    ```

4. **Get/Set Counter Value**: Get or set the value of the counter register using `MCAL_TIMER2_GetCounter()` and `MCAL_TIMER2_SetCounter()`.

    ```c
    uint8_t counterVal;
    MCAL_TIMER2_GetCounter(&counterVal);
    ```

5. **Get/Set Overflow Value**: Get or set the number of overflow events using `MCAL_TIMER2_GetOverflow()` and `MCAL_TIMER2_SetOverflow()`.

    ```c
    uint32_t overflowVal;
    MCAL_TIMER2_GetOverflow(&overflowVal);
    ```

6. **Interrupt Callbacks**: Set callbacks for overflow and compare match interrupts using `MCAL_TIMER2_CALLBACK_Overflow_INTERRUPT()` and `MCAL_TIMER2_CALLBACK_CompareMatch_INTERRUPT()`.

    ```c
    void overflow_callback() {
        // Overflow interrupt handler
    }
    MCAL_TIMER2_CALLBACK_Overflow_INTERRUPT(overflow_callback);
    ```

7. **Busy Wait Delay**: Use `MCAL_TIMER2_BusyWaitDelayms()` and `MCAL_TIMER2_BusyWaitDelayus()` for busy wait delays in milliseconds and microseconds respectively.

    ```c
    MCAL_TIMER2_BusyWaitDelayms(1000); // Delay for 1000 milliseconds
    ```

## Timer2 Example

This example demonstrates how to use the Timer2 driver to blink an LED connected to a GPIO pin.

### Code Example

```c
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Atmega32_Timer2.h"

#define LED_PIN     PB0

// Define callback functions for Timer2 interrupts
void overflow_callback() {
    // Overflow interrupt handler
}

void compare_match_callback() {
    // Compare match interrupt handler
}

int main(void) {
    // Initialize Timer2 configuration struct
    sTIMER2_Config_t timer_config;
    timer_config.Timer2_CLK_SRC = Timer2_Prescale_64;
    timer_config.Timer2_Mode = Timer2_CTC_Mode;
    timer_config.Timer2_COM = Timer2_COM_Disconnected;
    timer_config.Timer2_OCIE = Timer2_TOCI_Disable;
    timer_config.Timer2_OIE = Timer2_TOI_Enable;

    // Initialize Timer2
    MCAL_TIMER2_Init(&timer_config);

    // Set callbacks for Timer2 interrupts
    MCAL_TIMER2_CALLBACK_Overflow_INTERRUPT(overflow_callback);
    MCAL_TIMER2_CALLBACK_CompareMatch_INTERRUPT(compare_match_callback);

    // Set LED pin as output
    DDRB |= (1 << LED_PIN);

    // Enable global interrupts
    sei();

    while (1) {
        // Toggle LED every 500 ms
        MCAL_TIMER2_BusyWaitDelayms(500);
        PORTB ^= (1 << LED_PIN);
    }

    return 0;
}
```

In this example, the Timer2 module is initialized with a prescaler value of 64 and configured in CTC mode. The overflow interrupt is enabled, while the compare match interrupt is disabled. Two callback functions, overflow_callback and compare_match_callback, are defined to handle Timer2 overflow and compare match interrupts, respectively. The main function initializes Timer2, sets the LED pin as an output, enables global interrupts, and toggles the LED pin every 500 milliseconds.
