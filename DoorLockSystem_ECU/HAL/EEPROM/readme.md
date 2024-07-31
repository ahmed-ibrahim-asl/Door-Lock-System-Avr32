
# EEPROM HAL Driver for AVR32

## Overview

This repository contains an implementation of a HAL driver for controlling EEPROM devices using an AVR32 microcontroller. The driver supports initialization, reading, and writing operations for different types of EEPROMs.

## Features

| Feature         | Description                                        |
|-----------------|----------------------------------------------------|
| Initialization  | Initializes the EEPROM and sets up the TWI interface.|
| Write Data      | Writes data to a specified address in the EEPROM.  |
| Read Data       | Reads data from a specified address in the EEPROM. |

## File Structure

- `EEPROM_config.h`: Configuration file defining the EEPROM type and other settings.
- `EEPROM_interface.h`: Header file with function declarations and data structures.
- `EEPROM_priv.h`: Private header file containing internal macros and definitions.
- `EEPROM_program.c`: Source file implementing the functions declared in the interface header.

## Getting Started

### Prerequisites

To use this driver, you will need:
- AVR32 microcontroller (e.g., ATmega32)
- Supported EEPROM device (e.g., NM24C08F)
- AVR development environment (e.g., Atmel Studio)

### Installation

1. Clone this repository to your local machine.
   ```sh
   git clone https://github.com/ahmed-ibrahim-asl/Avr32_Driver.git
   ```
2. Include the `HAL/EEPROM` directory in your project.

### Configuration

Edit the `EEPROM_config.h` file to match your hardware setup and select the EEPROM type.

Example configuration for NM24C08F:
```c
#define EEPROM_TYPE        EEPROM_NM24C08F
```

### Usage

1. **Initialization:**
   ```c
   EEPROM_enuInit();
   ```

2. **Writing Data:**
   ```c
   EEPROM_Input_t eepromInstance;
   eepromInstance.address = 0x00;
   eepromInstance.data = 'A';
   eepromInstance.A0 = 0;
   eepromInstance.A1 = 0;
   eepromInstance.A2 = 0;
   EEPROM_enuWriteData(&eepromInstance);
   ```

3. **Reading Data:**
   ```c
   EEPROM_Input_t eepromInstance;
   eepromInstance.address = 0x00;
   eepromInstance.A0 = 0;
   eepromInstance.A1 = 0;
   eepromInstance.A2 = 0;
   EEPROM_enuReadData(&eepromInstance);
   uint8_t data = eepromInstance.data;
   ```

### Example

Here's an example of using the EEPROM driver in a main program:

```c
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/EEPROM/EEPROM_interface.h"
#include <util/delay.h>

int main() {
    EEPROM_enuInit();
    EEPROM_Input_t EEPROM_1;

    EEPROM_1.A0 = 0;
    EEPROM_1.A1 = 0;
    EEPROM_1.A2 = 0;
    EEPROM_1.address = 0x00;
    EEPROM_1.data = 'Z';

    EEPROM_enuWriteData(&EEPROM_1);
    _delay_ms(10);

    EEPROM_enuReadData(&EEPROM_1);

    DDRA = EEPROM_1.data;

    while (1) {
        // Infinite loop
    }

    return 0;
}
```

## Additional Notes

These notes will help you understand the EEPROM driver and its implementation:

- **EEPROM Types:** The driver supports various types of EEPROMs. Configure the `EEPROM_TYPE` macro in `EEPROM_config.h` to select the correct type.
- **TWI Interface:** Ensure that the TWI (I2C) interface is correctly initialized and configured for communication with the EEPROM.
- **Addressing:** Different EEPROM types use different addressing schemes. The driver handles these differences internally based on the selected `EEPROM_TYPE`.
- **Write Protection (NM24C09/F):** This EEPROM type includes a write protection feature. The WP pin can be used to protect the upper half of the memory from write operations.

### EEPROM Scanning Process

The EEPROM scanning process involves the following steps:

1. **Initialization:** The TWI interface is initialized to set up communication with the EEPROM.
2. **Setting EEPROM Address:** The correct EEPROM address is determined based on the `EEPROM_TYPE` and the A0, A1, A2 pin configurations.
3. **Writing Data:** Data is written to the EEPROM by sending the start condition, EEPROM address, memory address, and data.
4. **Reading Data:** Data is read from the EEPROM by sending the start condition, EEPROM address, memory address, repeated start condition, and reading the data.

### Explanation of `EEPROM_enuGetPressedKey` Function

The `EEPROM_enuWriteData` and `EEPROM_enuReadData` functions are responsible for writing and reading data to/from the EEPROM. Here is a step-by-step explanation of how they work:

1. **Initialization:** The TWI interface is initialized using the `TWI_enuInit` function.
2. **Setting EEPROM Address:** The EEPROM address is set based on the `EEPROM_TYPE` and the A0, A1, A2 pin configurations.
3. **Writing Data:** The `EEPROM_enuWriteData` function sends the start condition, EEPROM address, memory address, and data to write to the EEPROM.
4. **Reading Data:** The `EEPROM_enuReadData` function sends the start condition, EEPROM address, memory address, repeated start condition, and reads the data from the EEPROM.
