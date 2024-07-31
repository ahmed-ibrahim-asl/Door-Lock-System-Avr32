
# Keypad HAL Driver for AVR32

## Overview

This repository contains an implementation of a HAL driver for controlling a 4x4 keypad matrix using an AVR32 microcontroller. The driver supports initialization of the keypad, reading pressed keys, and provides functionality for interfacing with the keypad.

## Features

| Feature            | Description                                        |
|--------------------|----------------------------------------------------|
| Initialization     | Sets up the keypad pins and initializes the keypad.|
| Get Pressed Key    | Reads the pressed key from the keypad matrix.      |

## File Structure

- `keypad_HAL_config.h`: Configuration file defining the number of rows and columns, pin configurations, and key values.
- `keypad_HAL_interface.h`: Header file with function declarations.
- `keypad_HAL_priv.h`: Private header file containing internal macros and definitions.
- `keypad_HAL_program.c`: Source file implementing the functions declared in the interface header.

## Getting Started

### Prerequisites

To use this driver, you will need:
- AVR32 microcontroller (e.g., ATmega32)
- 4x4 keypad matrix
- AVR development environment (e.g., Atmel Studio)

### Installation

1. Clone this repository to your local machine.
   ```sh
   git clone https://github.com/ahmed-ibrahim-asl/Avr32_Driver.git
   ```
2. Include the `HAL/KEYPAD` directory in your project.

### Configuration

Edit the `keypad_HAL_config.h` file to match your hardware setup. Define the number of rows and columns, and configure the pin assignments.

Example configuration for a 4x4 keypad:
```c
#define KEYPAD_COL_NUM  4
#define KEYPAD_ROW_NUM  4

/********************** Keypad Rows **********************/
#define KEYPAD_ROW1_PIN DIO_u8PIN4
#define KEYPAD_ROW1_PORT DIO_u8PortB
#define KEYPAD_ROW2_PIN DIO_u8PIN5
#define KEYPAD_ROW2_PORT DIO_u8PortB
#define KEYPAD_ROW3_PIN DIO_u8PIN6
#define KEYPAD_ROW3_PORT DIO_u8PortB
#define KEYPAD_ROW4_PIN DIO_u8PIN7
#define KEYPAD_ROW4_PORT DIO_u8PortB

/********************** Keypad Columns **********************/
#define KEYPAD_COL1_PIN DIO_u8PIN0
#define KEYPAD_COL1_PORT DIO_u8PortD
#define KEYPAD_COL2_PIN DIO_u8PIN1
#define KEYPAD_COL2_PORT DIO_u8PortD
#define KEYPAD_COL3_PIN DIO_u8PIN4
#define KEYPAD_COL3_PORT DIO_u8PortD
#define KEYPAD_COL4_PIN DIO_u8PIN5
#define KEYPAD_COL4_PORT DIO_u8PortD

/******** Keypad Values ********/
#define KEYPAD_u8ROW0_COL0 '7'
#define KEYPAD_u8ROW0_COL1 '8'
#define KEYPAD_u8ROW0_COL2 '9'
#define KEYPAD_u8ROW0_COL3 '/'

#define KEYPAD_u8ROW1_COL0 '4'
#define KEYPAD_u8ROW1_COL1 '5'
#define KEYPAD_u8ROW1_COL2 '6'
#define KEYPAD_u8ROW1_COL3 'X'

#define KEYPAD_u8ROW2_COL0 '1'
#define KEYPAD_u8ROW2_COL1 '2'
#define KEYPAD_u8ROW2_COL2 '3'
#define KEYPAD_u8ROW2_COL3 '-'

#define KEYPAD_u8ROW3_COL0 'K'
#define KEYPAD_u8ROW3_COL1 '0'
#define KEYPAD_u8ROW3_COL2 '='
#define KEYPAD_u8ROW3_COL3 '+'
```

### Usage

1. **Initialization:**
   ```c
   keypad_enuInit();
   ```

2. **Getting Pressed Key:**
   ```c
   uint8_t pressedKey;
   if (keypad_enuGetPressedKey(&pressedKey) == ERROR_STATUS_OK) {
       // Use the pressed key
   }
   ```

### Example

Here's an example of using the keypad driver in a main program:

```c
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/KEYPAD/keypad_HAL_interface.h"
#include <util/delay.h>

int main() {
    uint8_t key;
    keypad_enuInit();
    while (1) {
        if (keypad_enuGetPressedKey(&key) == ERROR_STATUS_OK) {
            // Use the pressed key (e.g., send it to an LCD)
        }
        _delay_ms(200);  // Debounce delay
    }
    return 0;
}
```

## Additional Notes

These notes will help you understand the keypad driver and its implementation:

- **Control Pins:** Configure the row pins as outputs and the column pins as inputs with internal pull-up resistors.
- **Row and Column Scanning:** The driver sets each row low one by one and reads the columns to detect a pressed key.
- **Debouncing:** Use a delay to debounce the keypad to avoid multiple detections of a single key press.
- **Key Mapping:** The keypad values are defined in `keypad_HAL_config.h` and mapped to their corresponding row and column.

### Keypad Scanning Process

The keypad scanning process involves setting one row low at a time and reading all the columns to check for a pressed key. Here's a detailed explanation:

1. **Set one row low at a time:** The driver sets each row pin low one by one while keeping the others high. This is done to isolate each row during the scanning process.
2. **Check which column reads low:** For each row that is set low, the driver checks all the column pins. If any column pin reads low, it indicates that the key at the intersection of the current row and the column is pressed.
3. **Map the row-column pair to the corresponding key value:** Once a pressed key is detected, the driver maps the row-column pair to the corresponding key value using a predefined key mapping table. This table is defined in `keypad_HAL_config.h`.

This scanning process ensures that the driver can detect which key is pressed on the keypad by systematically checking each row and column.

### Explanation of `keypad_enuGetPressedKey` Function

The `keypad_enuGetPressedKey` function is responsible for detecting which key is pressed on the keypad. Here is a step-by-step explanation of how it works:

1. **Input Validation:** The function first checks if the pointer to store the pressed key value (`Copy_pu8KeyValue`) is `NULL`. If it is `NULL`, the function returns an error status.
2. **Row and Column Scanning:** The function iterates over each row and sets it low one by one. For each row that is set low, the function iterates over each column and reads its value.
3. **Key Detection:** If a column pin reads low (indicating a pressed key), the function retrieves the corresponding key value from the predefined key mapping table (`keypadOutput`) and stores it in the provided pointer (`Copy_pu8KeyValue`).
4. **Debouncing:** The function waits until the key is released (the column pin reads high again) to avoid multiple detections of a single key press.
5. **Return Status:** The function returns a success status if a key is detected, otherwise it continues scanning.

```c
ErrorStatus_t keypad_enuGetPressedKey(uint8_t* Copy_pu8KeyValue) {
    if (Copy_pu8KeyValue == NULL) {
        return ERROR_STATUS_FAILURE;
    }

    for (uint8_t row = 0; row < KEYPAD_ROW_NUM; row++) {
        LCD_vidSetRowPattern(row);

        for (uint8_t col = 0; col < KEYPAD_COL_NUM; col++) {
            uint8_t keyStatus;
            DIO_enuGetPinValue(Local_u8Columns_ArrayPORT[col], Local_u8Columns_ArrayPIN[col], &keyStatus);

            if (keyStatus == KEY_PRESSED) {
                *Copy_pu8KeyValue = keypadOutput[(KEYPAD_ROW_NUM * row) + col];

                while (keyStatus == KEY_PRESSED) {
                    DIO_enuGetPinValue(Local_u8Columns_ArrayPORT[col], Local_u8Columns_ArrayPIN[col], &keyStatus);
                }

                return ERROR_STATUS_OK;
            }
        }
    }

    return ERROR_STATUS_FAILURE;
}
```
