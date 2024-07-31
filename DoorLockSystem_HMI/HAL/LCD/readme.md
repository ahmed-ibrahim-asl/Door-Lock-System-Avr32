
# LCD HAL Driver for AVR32

## Overview

This repository contains an implementation of a HAL driver for controlling an LMB162A LCD module using an AVR32 microcontroller. The driver supports both 4-bit and 8-bit communication modes.

## Features

| Feature                     | Description                                 |
|-----------------------------|---------------------------------------------|
| Initialization              | Initializes the LCD in 4-bit or 8-bit mode. |
| Send Data                   | Sends data to the LCD.                      |
| Send Command                | Sends commands to the LCD.                  |
| Display Strings             | Displays strings on the LCD.                |
| Clear Display               | Clears the display.                         |
| Set Cursor Position         | Sets the cursor position on the LCD.        |
| Custom Character Storage    | Stores custom characters in CGRAM.          |
| Custom Character Display    | Displays custom characters from CGRAM.      |
| Integer to String Conversion| Converts integers to strings on the LCD.    |

## File Structure

- `LCD_HAL_config.h`: Configuration for operation modes, control pins, and data pins.
- `LCD_HAL_interface.h`: Function declarations.
- `LCD_HAL_priv.h`: Internal macros and definitions.
- `LCD_HAL_program.c`: Function implementations.
- `main_notes.txt`: Example usage.

## Getting Started

### Prerequisites

- AVR32 microcontroller (e.g., ATmega32)
- LMB162A LCD module
- AVR development environment (e.g., Atmel Studio, eclipse)

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/ahmed-ibrahim-asl/Avr32_Driver.git
   ```
2. Include the `HAL/LCD` directory in your project.

### Configuration

Edit `LCD_HAL_config.h` to match your hardware setup.

Example for 4-bit mode:
```c
#define LCD_MODE                FOUR_BIT

#define RS_PORT                 DIO_u8PortA
#define RS_PIN                  DIO_u8PIN0
#define RW_PORT                 DIO_u8PortA
#define RW_PIN                  DIO_u8PIN1
#define EN_PORT                 DIO_u8PortA
#define EN_PIN                  DIO_u8PIN2

#define LCD_DATA_PORT           DIO_u8PortB
#define DB7_PORT                DIO_u8PortB
#define DB7_PIN                 DIO_u8PIN3
#define DB6_PORT                DIO_u8PortB
#define DB6_PIN                 DIO_u8PIN2
#define DB5_PORT                DIO_u8PortB
#define DB5_PIN                 DIO_u8PIN1
#define DB4_PORT                DIO_u8PortB
#define DB4_PIN                 DIO_u8PIN0
```

### Usage

1. **Initialization:**
   ```c
   LCD_enuInit();
   ```

2. **Sending Data:**
   ```c
   LCD_enuSendData('A');
   ```

3. **Sending Commands:**
   ```c
   LCD_enuSendCommand(0x01); // Clear display command
   ```

4. **Displaying Strings:**
   ```c
   LCD_u8SendString("Hello, World!");
   ```

5. **Setting Cursor Position:**
   ```c
   LCD_u8SetPosXY(0, 1); // Set cursor to the beginning of the second line
   ```

6. **Custom Characters:**
   ```c
   uint8_t customChar[8] = {0x00, 0x0A, 0x0A, 0x0A, 0x11, 0x0E, 0x00, 0x00};
   LCD_u8StoreCustomChar(customChar, 0);
   LCD_u8DisplayCustomChar(0, 0, 0);
   ```

### Example

```c
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/LCD/LCD_HAL_interface.h"
#include <util/delay.h>

int main() {
    LCD_enuInit();
    LCD_u8SendString("Welcome");
    LCD_u8SetPosXY(0, 1);
    LCD_u8SendString("AVR32 LCD Driver");
    while (1) {
        // Loop forever
    }
    return 0;
}
```

### Additional Notes

These notes will help you understand the datasheet and the module more effectively:

- **Control Pins:** 
  - RS (Register Select): Selects the Instruction Register when low and the Data Register when high.
  - RW (Read/Write): Selects read mode when high and write mode when low.
  - EN (Enable): Latches data on the falling edge.

- **Data Pins:** 
  - For 4-bit mode, use DB4 to DB7.
  - For 8-bit mode, use DB0 to DB7.

- **Initialization Sequence:** 
  - Follow the initialization sequence as per the datasheet to ensure the proper setup of the LCD.

- **Custom Characters:** 
  - Use CGRAM to store custom characters, which enhances the display capabilities. CGRAM allows for the creation of up to 8 custom characters.

- **Timing:** 
  - Accurate timing is critical. Use appropriate delays to match the LCD's requirements.

- **Memory Types:**
  - **CGROM:** Character Generator ROM contains pre-defined character patterns.
  - **CGRAM:** Character Generator RAM allows you to define custom characters.
  - **DDRAM:** Display Data RAM holds the characters currently displayed on the screen.

- **Initialization by Internal Reset Circuit:**
  - **Display Clear:** Clears the display and resets the cursor.
  - **Function Set:** Configures the data length, number of display lines, and font type.
    - `DL`: Data Length (0 = 4-bit mode, 1 = 8-bit mode)
    - `N`: Number of display lines (0 = 1 line, 1 = 2 lines)
    - `F`: Font type (0 = 5x7 dots, 1 = 5x10 dots)
  - **Display ON/OFF Control:** Controls the display, cursor, and blinking.
    - `D`: Display (0 = OFF, 1 = ON)
    - `C`: Cursor (0 = OFF, 1 = ON)
    - `B`: Blinking (0 = OFF, 1 = ON)
  - **Entry Mode Set:** Sets the cursor move direction and specifies display shift.
    - `I/D`: Increment/Decrement (1 = Increment, 0 = Decrement)
    - `S`: Shift (0 = No shift, 1 = Shift display)

By following these guidelines and notes, you can ensure proper configuration and operation of your LCD module.
