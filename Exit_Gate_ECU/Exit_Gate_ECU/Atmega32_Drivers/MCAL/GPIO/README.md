# Atmega32 GPIO Driver

This project provides a comprehensive General-Purpose Input/Output (GPIO) driver for the Atmega32 microcontroller. The driver is designed to facilitate easy and efficient use of GPIO functionality, allowing users to configure and control GPIO pins for a wide range of applications.

## Features

- **Pin Initialization**: Configure GPIO pins as input, output, or alternate function modes with customizable configurations including pull-up/pull-down resistors.
- **Pin Read/Write**: Read the status of GPIO pins or an entire port, and write values to pins or an entire port with simple API calls.
- **Pin Toggling**: Easily toggle the state of GPIO pins.
- **Pin Locking**: Lock the configuration of GPIO pins to prevent unintended changes.

## Getting Started

### Prerequisites

- Atmega32 microcontroller
- Compatible Integrated Development Environment (IDE) such as Atmel Studio or MPLAB X IDE
- Basic knowledge of C programming and microcontroller peripherals

### Installation

1. Clone this repository or download the source code.
2. Include the header and source files (`Atmega32_GPIO.h` and `Atmega32_GPIO.c`) in your project.

### Usage

1. **GPIO Initialization**: Configure GPIO pins using `MCAL_GPIO_Init()` by specifying the GPIO port and a configuration structure (`GPIO_Pin_Config_t`).

    ```c
    GPIO_Pin_Config_t pinConfig;
    pinConfig.pinNumber = GPIO_PIN_1;
    pinConfig.pinMode = GPIO_MODE_OUTPUT_PP;
    MCAL_GPIO_Init(&GPIOA, &pinConfig);
    ```

2. **Reading and Writing**: Use `MCAL_GPIO_ReadPin()` and `MCAL_GPIO_WritePin()` for pin manipulation.

    ```c
    // Write to a pin
    MCAL_GPIO_WritePin(&GPIOA, GPIO_PIN_1, GPIO_PIN_STATUS_HIGH);
    
    // Read from a pin
    uint8_t pinStatus = MCAL_GPIO_ReadPin(&GPIOA, GPIO_PIN_1);
    ```

3. **Toggling Pins**: Toggle the state of a GPIO pin with `MCAL_GPIO_TogglePin()`.

    ```c
    MCAL_GPIO_TogglePin(&GPIOA, GPIO_PIN_1);
    ```

4. **Locking Configuration**: Prevent accidental changes to a pin's configuration using `MCAL_GPIO_LockPin()`.

    ```c
    MCAL_GPIO_LockPin(&GPIOA, GPIO_PIN_1);
    ```

## Example

An example application toggling an LED based on a button press:

```c
int main(void)
{
    GPIO_Pin_Config_t ledConfig;
    ledConfig.pinNumber = GPIO_PIN_1;
    ledConfig.pinMode = GPIO_MODE_OUTPUT_PP;
    MCAL_GPIO_Init(&GPIOA, &ledConfig);
    
    GPIO_Pin_Config_t buttonConfig;
    buttonConfig.pinNumber = GPIO_PIN_2;
    buttonConfig.pinMode = GPIO_MODE_INPUT_PULLUP;
    MCAL_GPIO_Init(&GPIOA, &buttonConfig);
    
    while(1)
    {
        if(MCAL_GPIO_ReadPin(&GPIOA, GPIO_PIN_2) == GPIO_PIN_STATUS_LOW)
        {
            MCAL_GPIO_TogglePin(&GPIOA, GPIO_PIN_1);
            while(MCAL_GPIO_ReadPin(&GPIOA, GPIO_PIN_2) == GPIO_PIN_STATUS_LOW);
        }
    }
}
