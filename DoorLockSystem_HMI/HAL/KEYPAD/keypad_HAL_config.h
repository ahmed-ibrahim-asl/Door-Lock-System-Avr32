/*
 * keypad_HAL_config.h
 *
 *  Created on: Jan 13, 2024
 *      Author: ad
 */

#ifndef HAL_KEYPAD_KEYPAD_HAL_CONFIG_H_
#define HAL_KEYPAD_KEYPAD_HAL_CONFIG_H_


#define KEYPAD_COL_NUM	4
#define KEYPAD_ROW_NUM	4



#if(KEYPAD_COL_NUM == 4 && KEYPAD_ROW_NUM == 4)

/********************** Keypad Rows **********************/
#define KEYPAD_ROW1_PIN		DIO_u8PIN0
#define KEYPAD_ROW1_PORT	DIO_u8PortA

#define KEYPAD_ROW2_PIN		DIO_u8PIN1
#define KEYPAD_ROW2_PORT	DIO_u8PortA

#define KEYPAD_ROW3_PIN		DIO_u8PIN2
#define KEYPAD_ROW3_PORT	DIO_u8PortA

#define KEYPAD_ROW4_PIN		DIO_u8PIN3
#define KEYPAD_ROW4_PORT	DIO_u8PortA
/********************************************************/

/********************** Keypad col **********************/
#define KEYPAD_COL1_PIN		DIO_u8PIN4
#define KEYPAD_COL1_PORT	DIO_u8PortA

#define KEYPAD_COL2_PIN		DIO_u8PIN5
#define KEYPAD_COL2_PORT	DIO_u8PortA

#define KEYPAD_COL3_PIN		DIO_u8PIN6
#define KEYPAD_COL3_PORT	DIO_u8PortA

#define KEYPAD_COL4_PIN		DIO_u8PIN7
#define KEYPAD_COL4_PORT	DIO_u8PortA
/********************************************************/

/******** Keypad Values ********/
#define KEYPAD_u8ROW0_COL0	'7'
#define KEYPAD_u8ROW0_COL1	'8'
#define KEYPAD_u8ROW0_COL2	'9'
#define KEYPAD_u8ROW0_COL3	'/'

#define KEYPAD_u8ROW1_COL0	'4'
#define KEYPAD_u8ROW1_COL1	'5'
#define KEYPAD_u8ROW1_COL2	'6'
#define KEYPAD_u8ROW1_COL3	'X'

#define KEYPAD_u8ROW2_COL0	'1'
#define KEYPAD_u8ROW2_COL1	'2'
#define KEYPAD_u8ROW2_COL2	'3'
#define KEYPAD_u8ROW2_COL3	'-'

#define KEYPAD_u8ROW3_COL0	'K'
#define KEYPAD_u8ROW3_COL1	'0'
#define KEYPAD_u8ROW3_COL2	'='
#define KEYPAD_u8ROW3_COL3	'+'

/********************************/
#endif







#endif /* HAL_KEYPAD_KEYPAD_HAL_CONFIG_H_ */
