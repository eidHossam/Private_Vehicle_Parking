# Atmega32 SPI Driver

This module provides functions for configuring and controlling the Serial Peripheral Interface (SPI) module on the Atmega32 microcontroller.

## Description

The SPI (Serial Peripheral Interface) is a synchronous serial communication interface used for short-distance communication primarily in embedded systems. It allows full-duplex communication between a master device and one or more slave devices over multiple data lines.

This file contains the function prototypes and definitions for the SPI driver, including initialization, data transmission, and configuration.

## Features

- **SPI Initialization**: Initialize the SPI peripheral with specified configuration parameters.
- **SPI Reset**: Reset the SPI peripheral to its original state.
- **Send Data**: Send data through SPI with optional polling mechanism.
- **Receive Data**: Receive data from the SPI channel with optional polling mechanism.
- **Exchange Data**: Send and receive data from the SPI channel with polling mechanism.
- **SPI Enable/Disable**: Enable or disable the SPI peripheral.
- **SPI Interrupt Control**: Control the SPI interrupt with options to enable or disable it.


## Getting Started

### Prerequisites

- Atmega32 microcontroller
- Compatible Integrated Development Environment (IDE) such as Atmel Studio or MPLAB X IDE
- Basic knowledge of C programming and microcontroller peripherals

### Installation

1. Clone this repository or download the source code.
2. Include the header and source files (`Atmega32_SPI.h` and `Atmega32_SPI.c`) in your project.

## Usage

1. **SPI Initialization**: Initialize the SPI peripheral using `MCAL_SPI_Init()` with configuration parameters in the `SPI_Config_t` structure.

    ```c
    SPI_Config_t config;
    // Set configuration parameters
    MCAL_SPI_Init(&config);
    ```

2. **Send Data**: Send data through SPI using `MCAL_SPI_SendData()` with optional polling mechanism.

    ```c
    uint8_t txData = 0x55;
    MCAL_SPI_SendData(&txData, PollingEnable);
    ```

3. **Receive Data**: Receive data from the SPI channel using `MCAL_SPI_ReceiveData()` with optional polling mechanism.

    ```c
    uint8_t rxData;
    MCAL_SPI_ReceiveData(&rxData, PollingEnable);
    ```

4. **Exchange Data**: Send and receive data from the SPI channel using `MCAL_SPI_ExchangeData()` with polling mechanism.

    ```c
    uint8_t data = 0x55;
    MCAL_SPI_ExchangeData(&data);
    ```

5. **SPI Enable/Disable**: Enable or disable the SPI peripheral using `MCAL_SPI_Enable()` and `MCAL_SPI_Disable()`.

    ```c
    MCAL_SPI_Enable();
    ```

## Example

An example application illustrating SPI communication with an external SPI device:

```c
#include <avr/io.h>
#include "Atmega32_SPI.h"

int main(void)
{
    // Initialize SPI configuration
    SPI_Config_t spiConfig;
    spiConfig.SPI_Mode = SPI_MODE_MASTER;
    spiConfig.SPI_DataOrder = SPI_FIRST_BIT_MSB;
    spiConfig.SPI_BaudRate = SPI_CLOCK_RATE_DIV_16;
    spiConfig.SPI_CPOL = SPI_IDLE_LOW;
    spiConfig.SPI_CPHA = SPI_SAMPLE_LEADING_EDGE;
    spiConfig.SPI_IRQ_EN = SPI_IRQ_DISABLE;
    spiConfig.SPI_DoubleSpeed_EN = SPI_2XSPEED_DISABLE;

    // Initialize SPI
    MCAL_SPI_Init(&spiConfig);

    // Send data through SPI
    uint8_t txData = 0x55;
    MCAL_SPI_SendData(&txData, PollingEnable);

    // Receive data from SPI
    uint8_t rxData;
    MCAL_SPI_ReceiveData(&rxData, PollingEnable);

    // Exchange data with SPI
    uint8_t data = 0x55;
    MCAL_SPI_ExchangeData(&data);

    // Enable SPI
    MCAL_SPI_Enable();

    while(1)
    {
        // Your application code here
    }
}
