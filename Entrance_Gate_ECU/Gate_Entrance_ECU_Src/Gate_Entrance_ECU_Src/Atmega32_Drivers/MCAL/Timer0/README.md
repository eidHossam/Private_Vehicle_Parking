# Atmega32 Timer0 Driver

## Introduction

This module contains functions for configuring and controlling the Timer0 module on the Atmega32 microcontroller.

## Description

The Atmega32 Timer0 driver facilitates precise timing and event generation capabilities within embedded systems leveraging the Atmega32 microcontroller platform. Timer0, an 8-bit timer/counter unit, plays a pivotal role in timekeeping, event scheduling, and pulse generation applications, offering versatile functionality tailored to diverse system requirements.

## Features

- **Timer0 Initialization**: Initialize Timer0 with specified configuration parameters.
- **Timer0 Start/Stop**: Start or stop the Timer0 peripheral.
- **Get/Set Compare Value**: Get or set the value of the output compare register.
- **Get/Set Counter Value**: Get or set the value of the counter register.
- **Get/Set Overflow Value**: Get or set the number of overflow events.
- **Interrupt Callbacks**: Set callbacks for overflow and compare match interrupts.

## Getting Started

### Prerequisites

- Atmega32 microcontroller
- Compatible Integrated Development Environment (IDE) such as Atmel Studio or MPLAB X IDE
- Basic knowledge of C programming and microcontroller peripherals

### Installation

1. Clone this repository or download the source code.
2. Include the header and source files (`Atmega32_Timer0.h` and `Atmega32_Timer0.c`) in your project.

## Usage

1. **Timer0 Initialization**: Initialize Timer0 using `MCAL_TIMER0_Init()` with configuration parameters in the `sTimer0_Config_t` structure.

    ```c
    sTimer0_Config_t config;
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
# Timer0 Example

This example demonstrates how to use the Timer0 driver to blink an LED connected to a GPIO pin.

## Code Example

```c
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Atmega32_Timer0.h"

#define LED_PIN     PB0

// Define callback functions for Timer0 interrupts
void overflow_callback() {
    // Overflow interrupt handler
}

void compare_match_callback() {
    // Compare match interrupt handler
}

int main(void) {
    // Initialize Timer0 configuration struct
    sTimer0_Config_t timer_config;
    timer_config.Timer_CLK_SRC = Timer_CLK_SRC_CPU_1024;
    timer_config.Timer_Mode = Timer_Mode_Normal;
    timer_config.Timer_COM = Timer_COM_Disconnected;
    timer_config.Timer_OIE = Timer_TOI_Enable;
    timer_config.Timer_OCIE = Timer_TOCI_Disable;

    // Initialize Timer0
    MCAL_TIMER0_Init(&timer_config);

    // Set callbacks for Timer0 interrupts
    MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT(overflow_callback);
    MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(compare_match_callback);

    // Set LED pin as output
    DDRB |= (1 << LED_PIN);

    // Enable global interrupts
    sei();

    while (1) {
        // Toggle LED every 500 ms
        _delay_ms(500);
        PORTB ^= (1 << LED_PIN);
    }

    return 0;
}
```

In this example, the Timer0 module is initialized with a prescaler value of 1024 and configured in normal mode. The overflow interrupt is enabled, while the compare match interrupt is disabled. Two callback functions, `overflow_callback` and `compare_match_callback`, are defined to handle Timer0 overflow and compare match interrupts, respectively. The main function initializes Timer0, sets the LED pin as an output, enables global interrupts, and toggles the LED pin every 500 milliseconds.
