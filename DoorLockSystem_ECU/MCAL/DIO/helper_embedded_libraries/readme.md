# Helper Embedded Library for AVR32

## Overview

This repository contains a collection of helper libraries for AVR32 microcontrollers. These libraries provide essential functionalities for bit manipulation, error handling, microcontroller configurations, register definitions, and standard data types.

## Features

| Feature                    | Description                                                                 |
|----------------------------|-----------------------------------------------------------------------------|
| Bit Manipulation           | Provides macros for setting, clearing, toggling, and reading bits.          |
| Error Handling             | Defines standard error types for consistent error reporting.                |
| Microcontroller Configurations | Includes essential configurations and includes for AVR32.                    |
| Register Definitions       | Defines the register addresses for the AVR32 microcontroller ports.         |
| Standard Data Types        | Defines standard data types for consistency across the project.             |

## File Structure

- `bit_math.h`: Header file providing macros for bit manipulation.
- `error_types.h`: Header file defining error types used across the project.
- `micro_config.h`: Header file including essential configurations and includes.
- `register.h`: Header file defining the microcontroller register addresses.
- `std_types.h`: Header file defining standard data types.

## Getting Started

### Prerequisites

To use these libraries, you will need:
- AVR32 microcontroller (e.g., ATmega32)
- AVR development environment (e.g., Atmel Studio, Eclipse)
 