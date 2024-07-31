/*
 * keypad_HAL_interface.h
 *
 *  Created on: Jan 13, 2024
 *      Author: ad
 */

#ifndef HAL_KEYPAD_KEYPAD_HAL_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_HAL_INTERFACE_H_


ErrorStatus_t keypad_enuInit(void);

ErrorStatus_t keypad_enuGetPressedKey(uint8_t* Copy_pu8KeyValue);


#endif /* HAL_KEYPAD_KEYPAD_HAL_INTERFACE_H_ */
