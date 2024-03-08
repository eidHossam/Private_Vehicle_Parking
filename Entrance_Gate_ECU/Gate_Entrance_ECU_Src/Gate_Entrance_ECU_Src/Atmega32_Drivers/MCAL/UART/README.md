# Atmega32 UART Driver

This project provides a comprehensive Universal Asynchronous Receiver/Transmitter (UART) driver for the Atmega32 microcontroller. The driver is designed to facilitate easy and efficient use of UART functionality, allowing users to configure and control UART communication for various applications.

## Features

- **Initialization**: Initialize UART instance with configurable parameters such as baud rate, parity, stop bits, and word length.
- **Data Transmission**: Send data through the UART interface, supporting both polling and interrupt-driven mechanisms.
- **Data Reception**: Receive data from the UART interface, supporting both polling and interrupt-driven mechanisms.
- **String Transmission/Reception**: Send and receive strings through the UART interface.
- **Interrupt Management**: Enable/disable specific UART interrupts and set corresponding callback functions.

## Getting Started

### Prerequisites

- Atmega32 microcontroller
- Compatible Integrated Development Environment (IDE) such as Atmel Studio or MPLAB X IDE
- Basic knowledge of C programming and microcontroller peripherals

### Installation

1. Clone this repository or download the source code.
2. Include the header and source files (`Atmega32_UART.h` and `Atmega32_UART.c`) in your project.
3. Ensure the necessary configuration for UART operation, including clock settings.

### Usage

1. **UART Initialization**: Initialize the UART instance using `MCAL_UART_Init()` with the desired configuration parameters.

    ```c
    sUSART_config_t config;
    config.USART_baudRate = 9600;
    config.USART_wordLength = USART_8BitWord;
    // Set other configuration parameters
    MCAL_UART_Init(&config);
    ```

2. **Data Transmission**: Send data through the UART using `MCAL_UART_Send_Data()`.

    ```c
    uint16_t data = 0x41; // ASCII value of 'A'
    MCAL_UART_Send_Data(&data, USART_PollingEnabled);
    ```

3. **Data Reception**: Receive data from the UART using `MCAL_UART_Get_Data()`.

    ```c
    uint16_t receivedData;
    MCAL_UART_Get_Data(&receivedData, USART_PollingEnabled);
    ```

4. **String Transmission/Reception**: Send and receive strings through the UART using `MCAL_USART_Send_String()` and `MCAL_USART_Get_String()`.

    ```c
    uint8_t txString[] = "Hello, UART!";
    MCAL_USART_Send_String(txString);

    uint8_t rxBuffer[50];
    MCAL_USART_Get_String(rxBuffer, sizeof(rxBuffer));
    ```

5. **Interrupt Management**: Enable/disable specific UART interrupts using `MCAL_UART_Interrupt_EN()` and `MCAL_UART_Interrupt_Disable()`.

    ```c
    MCAL_UART_Interrupt_EN(USART_IRQ_RXC, RXC_Callback);
    MCAL_UART_Interrupt_EN(USART_IRQ_TXC, TXC_Callback);
    MCAL_UART_Interrupt_EN(USART_IRQ_UDRE, UDRE_Callback);
    ```

## Example

An example application sending and receiving data through UART:

```c
int main(void)
{
    sUSART_config_t config;
    config.USART_baudRate = 9600;
    config.USART_wordLength = USART_8BitWord;
    // Set other configuration parameters
    MCAL_UART_Init(&config);

    uint16_t txData = 0x41; // ASCII value of 'A'
    MCAL_UART_Send_Data(&txData, USART_PollingEnabled);

    uint16_t rxData;
    MCAL_UART_Get_Data(&rxData, USART_PollingEnabled);

    while(1);
}
