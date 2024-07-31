# DIO Driver for AVR32

## Overview

This repository contains the implementation of a DIO (Digital Input/Output) driver for AVR32 microcontrollers. The driver supports initialization of the DIO module, setting pin directions, setting pin values, getting pin values, and toggling pin values. Additionally, it provides functionalities for controlling entire ports.

## Features

| Feature                    | Description                                                                 |
|----------------------------|-----------------------------------------------------------------------------|
| Pin Initialization         | Initializes the DIO module by configuring the direction and initial values of pins. |
| Set Pin Direction          | Sets the direction of a specific pin as input or output.                    |
| Set Pin Value              | Sets the value of a specific pin as high or low.                            |
| Get Pin Value              | Reads the current value of a specific pin.                                  |
| Toggle Pin Value           | Toggles the value of a specific pin.                                        |
| Set Port Direction         | Sets the direction of an entire port as input or output.                    |
| Set Port Value             | Sets the value of an entire port as high or low.                            |

## File Structure

- `DIO_config.h`: Header file for configuring the directions and initial values of pins.
- `DIO_interface.h`: Header file with function declarations for the DIO driver.
- `DIO_priv.h`: Private header file containing internal macros and definitions.
- `DIO_program.c`: Source file implementing the functions declared in the interface header.
- `DIO_register.h`: Header file defining the microcontroller register addresses.

## Getting Started

### Prerequisites

To use this driver, you will need:
- AVR32 microcontroller (e.g., ATmega32)
- AVR development environment (e.g., Atmel Studio, Eclipse)

### Installation

1. Clone this repository to your local machine.
   ```sh
   git clone https://github.com/ahmed-ibrahim-asl/Avr32_Driver.git
   ```
2. Include the `DIO` directory in your project.

### Usage

1. **Initialization:**

   ```c
   DIO_enuInit();
   ```

2. **Setting Pin Direction:**

   ```c
   DIO_enuSetPinDirection(DIO_u8PortA, DIO_u8PIN0, DIO_u8OUTPUT);
   ```

3. **Setting Pin Value:**

   ```c
   DIO_enuSetPinValue(DIO_u8PortA, DIO_u8PIN0, DIO_u8HIGH);
   ```

4. **Getting Pin Value:**

   ```c
   uint8_t pinValue;
   DIO_enuGetPinValue(DIO_u8PortA, DIO_u8PIN0, &pinValue);
   ```

5. **Toggling Pin Value:**

   ```c
   DIO_enuTogglePinValue(DIO_u8PortA, DIO_u8PIN0);
   ```

### Example

Here's an example of using the DIO driver in a main program:

   ```c
   #include "DIO_interface.h"
   #include <util/delay.h>

   int main() {
       DIO_enuInit();
       while (1) {
           DIO_enuTogglePinValue(DIO_u8PortA, DIO_u8PIN0);
           _delay_ms(500);
       }
       return 0;
   }
   ```

## Additional Notes

These notes will help you understand the DIO driver and its implementation:

- **Control Pins Individually:** You can set the direction and value of individual pins using the provided functions.
- **Control Entire Ports:** You can set the direction and value of entire ports if needed.
- **Configuration File:** Use `DIO_config.h` to configure the initial directions and values of the pins.
- **Error Handling:** The driver functions return error status codes to indicate the success or failure of operations.

