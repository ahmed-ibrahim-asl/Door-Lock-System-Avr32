/*
 * LCD_HAL_priv.h
 *
 *  Created on: Jan 5, 2024
 *      Author: ad
 */

#ifndef HAL_LCD_HAL_PRIV_H_
#define HAL_LCD_HAL_PRIV_H_


///*************** Include Section Start ***************/
//#include "../MCAL/DIO/DIO_interface.h"
///*****************************************************/


/**************** Mode of Operation *****************/
#define FOUR_BIT 					      4
#define EIGHT_BIT 					   	  8
/****************************************************/


/****************** Delay Durations ******************/
// Values are obtained from DataSheet
// Names are named after the function before that time

#define POWER_ON_DELAY			  	35
#define FUNCTION_SET_DELAY			1
#define DISPLAY_ON_OFF_CONTROL		1
#define DISPLAY_CLEAR_DELAY			2
/****************************************************/


/****************************************************/


/**
  * NOTICE:
  * 	1. Here i am using macro as function to save time of context switching
  * 	   between multiple of functions withdrawback of increases size.
  *
  * 	2. ENABLE_PULSE - think of it as we were hitting send to LCD
  * */


#define SEND_ENABLE_PULSE() \
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8HIGH); \
	_delay_ms(2); 									 \
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8LOW); \
/****************************************************/

/****************** Commands  ******************/
#define CLEAR			0x01
#define RETURN_HOME		0x02
/**********************************************/




#define LCD_DATA_BIT_1				  0
#define LCD_DATA_BIT_2				  1
#define LCD_DATA_BIT_3				  2
#define LCD_DATA_BIT_4				  3

#define LCD_DATA_BIT_5				  4
#define LCD_DATA_BIT_6				  5
#define LCD_DATA_BIT_7				  6
#define LCD_DATA_BIT_8				  7







#endif /* HAL_LCD_HAL_PRIV_H_ */
