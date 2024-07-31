/*
 * keypad_program.c
 *
 *  Created on: Jan 13, 2024
 *      Author: ad
 */


///*************** Include Section Start ********************/
#include "../../MCAL/DIO/DIO_interface.h"
#include "keypad_HAL_priv.h"
#include "keypad_HAL_config.h"
#include "keypad_HAL_interface.h"
///**********************************************************/


ErrorStatus_t keypad_enuInit(void){

	ErrorStatus_t Local_enuErrrorState = ERROR_STATUS_FAILURE;

	/************************ !Rows Pins! ************************/
	 DIO_enuSetPinDirection(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, DIO_u8OUTPUT);
	 DIO_enuSetPinDirection(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, DIO_u8OUTPUT);
	 DIO_enuSetPinDirection(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, DIO_u8OUTPUT);
	 DIO_enuSetPinDirection(KEYPAD_ROW4_PORT, KEYPAD_ROW4_PIN, DIO_u8OUTPUT);

	 DIO_enuSetPinValue(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, DIO_u8HIGH);
	 DIO_enuSetPinValue(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, DIO_u8HIGH);
	 DIO_enuSetPinValue(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, DIO_u8HIGH);
	 DIO_enuSetPinValue(KEYPAD_ROW4_PORT, KEYPAD_ROW4_PIN, DIO_u8HIGH);
	/****************************************************************/


	/************************* !Columns Pins! **************************/
	 DIO_enuSetPinDirection(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, DIO_u8INPUT);
	 DIO_enuSetPinDirection(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, DIO_u8INPUT);
	 DIO_enuSetPinDirection(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN, DIO_u8INPUT);
	 DIO_enuSetPinDirection(KEYPAD_COL4_PORT, KEYPAD_COL4_PIN, DIO_u8INPUT);

	// To activate internal input-pull resistor we set corresponding
	// pin to high
	 DIO_enuSetPinValue(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, DIO_u8HIGH);
	 DIO_enuSetPinValue(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, DIO_u8HIGH);
	 DIO_enuSetPinValue(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN, DIO_u8HIGH);
	 DIO_enuSetPinValue(KEYPAD_COL4_PORT, KEYPAD_COL4_PIN, DIO_u8HIGH);

	/****************************************************************/


	Local_enuErrrorState = ERROR_STATUS_OK;
	return Local_enuErrrorState;
}

static void LCD_vidSetRowPattern(uint8_t Copy_u8Row){

	uint8_t Local_u8RowIterator = 0;



	uint8_t Local_u8RowsArrayPORT[KEYPAD_ROW_NUM] = {
			KEYPAD_ROW1_PORT, KEYPAD_ROW2_PORT,
			KEYPAD_ROW3_PORT, KEYPAD_ROW4_PORT};

	uint8_t Local_u8RowsArrayPIN[KEYPAD_ROW_NUM] = {
			KEYPAD_ROW1_PIN, KEYPAD_ROW2_PIN,
			KEYPAD_ROW3_PIN, KEYPAD_ROW4_PIN
	};

	for(Local_u8RowIterator = 0; Local_u8RowIterator< KEYPAD_ROW_NUM; Local_u8RowIterator++){

		if(Local_u8RowIterator == Copy_u8Row){

			DIO_enuSetPinValue(
					Local_u8RowsArrayPORT[Local_u8RowIterator],
					Local_u8RowsArrayPIN[Local_u8RowIterator],
					DIO_u8LOW);
		}

		else{
			DIO_enuSetPinValue(
					Local_u8RowsArrayPORT[Local_u8RowIterator],
					Local_u8RowsArrayPIN[Local_u8RowIterator],
					DIO_u8HIGH);
		}
	}


}

ErrorStatus_t keypad_enuGetPressedKey(uint8_t* Copy_pu8KeyValue){
	ErrorStatus_t Local_enuErrrorState = ERROR_STATUS_FAILURE;


	if(Copy_pu8KeyValue == NULL){
		return Local_enuErrrorState;
	}

	else{

		uint8_t Local_u8KeyStatus = 1;
		uint8_t Local_u8RowIterator = 0;
		uint8_t Local_u8COLIterator = 0;

		uint8_t Local_u8Columns_ArrayPORT[KEYPAD_ROW_NUM] = {
				KEYPAD_COL1_PORT, KEYPAD_COL2_PORT,
				KEYPAD_COL3_PORT, KEYPAD_COL4_PORT};

		uint8_t Local_u8Columns_ArrayPIN[KEYPAD_ROW_NUM] = {
				KEYPAD_COL1_PIN, KEYPAD_COL2_PIN,
				KEYPAD_COL3_PIN, KEYPAD_COL4_PIN
		};

		for( Local_u8RowIterator = 0; Local_u8RowIterator <  KEYPAD_ROW_NUM; Local_u8RowIterator++){

			LCD_vidSetRowPattern(Local_u8RowIterator);


			for( Local_u8COLIterator = 0; (Local_u8COLIterator <  KEYPAD_COL_NUM); Local_u8COLIterator++){

				DIO_enuGetPinValue(
						Local_u8Columns_ArrayPORT[Local_u8COLIterator],
						Local_u8Columns_ArrayPIN[Local_u8COLIterator],
						&Local_u8KeyStatus);



			     if(Local_u8KeyStatus == KEY_PRESSED) {


			    	 *Copy_pu8KeyValue = keypadOutput[(KEYPAD_ROW_NUM * Local_u8RowIterator) + Local_u8COLIterator];



			    	 while(Local_u8KeyStatus == KEY_PRESSED){
			    			DIO_enuGetPinValue(
			    							Local_u8Columns_ArrayPORT[Local_u8COLIterator],
			    							Local_u8Columns_ArrayPIN[Local_u8COLIterator],
			    							&Local_u8KeyStatus);
			    	 }


			    	 Local_enuErrrorState = ERROR_STATUS_OK;
			    	 return Local_enuErrrorState;
			      }
			}

		}
	}
	return Local_enuErrrorState;
}

