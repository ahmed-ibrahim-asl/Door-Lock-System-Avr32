/*
 * keypad_HAL_priv.h
 *
 *  Created on: Jan 13, 2024
 *      Author: ad
 */

#ifndef HAL_KEYPAD_KEYPAD_HAL_PRIV_H_
#define HAL_KEYPAD_KEYPAD_HAL_PRIV_H_

#include "keypad_HAL_config.h"


/*
 * Notice: here i am assuming
 * we working with input-pull resistor configuration
 * **/
//#define KEYPAD_KEY_PRESSED	0
//#define KEYPAD_KEY_PRESSED	1



static void LCD_vidSetRowPattern(uint8_t Copy_u8Row);



#if(KEYPAD_COL_NUM == 4 && KEYPAD_ROW_NUM == 4)

static uint8_t keypadOutput[]={
		KEYPAD_u8ROW0_COL0, KEYPAD_u8ROW0_COL1, KEYPAD_u8ROW0_COL2, KEYPAD_u8ROW0_COL3,
		KEYPAD_u8ROW1_COL0, KEYPAD_u8ROW1_COL1, KEYPAD_u8ROW1_COL2, KEYPAD_u8ROW1_COL3,
		KEYPAD_u8ROW2_COL0, KEYPAD_u8ROW2_COL1, KEYPAD_u8ROW2_COL2, KEYPAD_u8ROW2_COL3,
		KEYPAD_u8ROW3_COL0, KEYPAD_u8ROW3_COL1, KEYPAD_u8ROW3_COL2, KEYPAD_u8ROW3_COL3
};


#define KEY_NOT_PRESSED 1
#define KEY_PRESSED		0






#endif

#endif /* HAL_KEYPAD_KEYPAD_HAL_PRIV_H_ */
