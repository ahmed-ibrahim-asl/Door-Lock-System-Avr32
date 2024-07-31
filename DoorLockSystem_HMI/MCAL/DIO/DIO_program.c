/*
 * DIO_program.c
 *
 *  Created on: Dec 29, 2023
 *      Author: ad
*/

/*************** Include Section Start ********************/
#include "helper_embedded_libraries/micro_config.h"
#include "DIO_priv.h"
#include "DIO_config.h"
#include "DIO_interface.h"
/**********************************************************/



///********************************** Module intialization **********************************/
ErrorStatus_t DIO_enuInit(void)
{
    ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;

	/***************** Group A *****************/
	DDRA = CONC(DIO_u8PA0_DIR, DIO_u8PA1_DIR,
				DIO_u8PA2_DIR, DIO_u8PA3_DIR,
				DIO_u8PA4_DIR, DIO_u8PA5_DIR,
				DIO_u8PA6_DIR, DIO_u8PA7_DIR);

	PORTA = CONC(DIO_u8PA0_VALUE, DIO_u8PA1_VALUE,
				DIO_u8PA2_VALUE, DIO_u8PA3_VALUE,
				DIO_u8PA4_VALUE, DIO_u8PA5_VALUE,
				DIO_u8PA6_VALUE, DIO_u8PA7_VALUE);
	/******************************************/


	/***************** Group B *****************/
	DDRB = CONC(DIO_u8PB0_DIR, DIO_u8PB1_DIR,
				DIO_u8PB2_DIR, DIO_u8PB3_DIR,
				DIO_u8PB4_DIR, DIO_u8PB5_DIR,
				DIO_u8PB6_DIR, DIO_u8PB7_DIR);

	PORTB = CONC(DIO_u8PB0_VALUE, DIO_u8PB1_VALUE,
				DIO_u8PB2_VALUE, DIO_u8PB3_VALUE,
				DIO_u8PB4_VALUE, DIO_u8PB5_VALUE,
				DIO_u8PB6_VALUE, DIO_u8PB7_VALUE);
	/******************************************/


	/***************** Group C *****************/
	DDRC = CONC(DIO_u8PC0_DIR, DIO_u8PC1_DIR,
				DIO_u8PC2_DIR, DIO_u8PC3_DIR,
				DIO_u8PC4_DIR, DIO_u8PC5_DIR,
				DIO_u8PC6_DIR, DIO_u8PC7_DIR);

	PORTC = CONC(DIO_u8PC0_VALUE, DIO_u8PC1_VALUE,
				DIO_u8PC2_VALUE, DIO_u8PC3_VALUE,
				DIO_u8PC4_VALUE, DIO_u8PC5_VALUE,
				DIO_u8PC6_VALUE, DIO_u8PC7_VALUE);
	/******************************************/


	/***************** Group D *****************/
	DDRD = CONC(DIO_u8PD0_DIR, DIO_u8PD1_DIR,
				DIO_u8PD2_DIR, DIO_u8PD3_DIR,
				DIO_u8PD4_DIR, DIO_u8PD5_DIR,
				DIO_u8PD6_DIR, DIO_u8PD7_DIR);

	PORTD = CONC(DIO_u8PD0_VALUE, DIO_u8PD1_VALUE,
				DIO_u8PD2_VALUE, DIO_u8PD3_VALUE,
				DIO_u8PD4_VALUE, DIO_u8PD5_VALUE,
				DIO_u8PD6_VALUE, DIO_u8PD7_VALUE);
	/******************************************/
	
	//! (Now we either check if values are set or not ) 


    return Local_enu_ErrorState;
}




///********************************** Control Pin by Pin **********************************/
// 1. set pin as output or output
ErrorStatus_t DIO_enuSetPinDirection(
	uint8_t Copy_u8PortID,
	uint8_t Copy_u8PinID,
	uint8_t Copy_u8Direction){

	
	ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;


	if(Copy_u8PortID <= DIO_u8PortD && Copy_u8PinID <= DIO_u8PIN7 && Copy_u8Direction <= DIO_u8OUTPUT){

		switch(Copy_u8PortID){
			case DIO_u8PortA:
				
				if(Copy_u8Direction == DIO_u8OUTPUT){
					SET_BIT(DDRA, Copy_u8PinID);
				}else{
					
					/* setting pin as input */

					//! input pullup-float is not cacluated
					CLR_BIT(DDRA, Copy_u8PinID);
				}

			break;

			case DIO_u8PortB:
			
				if(Copy_u8Direction == DIO_u8OUTPUT){
					SET_BIT(DDRB, Copy_u8PinID);
				}else{
					
					/* setting pin as input */

					//! input pullup-float is not cacluated
					CLR_BIT(DDRB, Copy_u8PinID);
				}

			break;

			case DIO_u8PortC:

				if(Copy_u8Direction == DIO_u8OUTPUT){
					SET_BIT(DDRC, Copy_u8PinID);
				}else{
					
					/* setting pin as input */

					//! input pullup-float is not cacluated
					CLR_BIT(DDRC, Copy_u8PinID);
				}

			break;

			case DIO_u8PortD:
		
				if(Copy_u8Direction == DIO_u8OUTPUT){
					SET_BIT(DDRD, Copy_u8PinID);
				}else{
					
					/* setting pin as input */

					//! input pullup-float is not cacluated
					CLR_BIT(DDRD, Copy_u8PinID);
				}

		}

		Local_enu_ErrorState = ERROR_STATUS_OK;

	}else{
		// one of arguments are not valid
		return Local_enu_ErrorState;
	}
	
	return Local_enu_ErrorState;
   }


// 2. set value for pin as high or low 
ErrorStatus_t DIO_enuSetPinValue(
   uint8_t Copy_u8PortID,
   uint8_t Copy_u8PinID,
   uint8_t Copy_u8Value){


	ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;


	// DIO_u8PULLUP - 1
	if(Copy_u8PortID <= DIO_u8PortD && Copy_u8PinID <= DIO_u8PIN7 && Copy_u8Value <= DIO_u8PULLUP){
		
		switch (Copy_u8PortID){
		
			case DIO_u8PortA:
				if(Copy_u8Value){

					// if the value is set to HIGH
					SET_BIT(PORTA, Copy_u8PinID);
				}else{
					CLR_BIT(PORTA, Copy_u8PinID);
				}	

			break;
			
			case DIO_u8PortB:
				if(Copy_u8Value){

					// if the value is set to HIGH
					SET_BIT(PORTB, Copy_u8PinID);
				}else{
					CLR_BIT(PORTB, Copy_u8PinID);
				}	
			
			break;

			case DIO_u8PortC:
				if(Copy_u8Value){

					// if the value is set to HIGH
					SET_BIT(PORTC, Copy_u8PinID);
				}else{
					CLR_BIT(PORTC, Copy_u8PinID);
				}	

			break;
			case DIO_u8PortD:
				if(Copy_u8Value){

					// if the value is set to HIGH
					SET_BIT(PORTD, Copy_u8PinID);
				}else{
					CLR_BIT(PORTD, Copy_u8PinID);
				}
		}
		Local_enu_ErrorState = ERROR_STATUS_OK;

    }else{
		return Local_enu_ErrorState;
	}

	return Local_enu_ErrorState;
   }


// 3. read pin value 
ErrorStatus_t DIO_enuGetPinValue(
   uint8_t Copy_u8PortID,
   uint8_t Copy_u8PinID,
   uint8_t *Copy_pu8Value){

	ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;


	if(Copy_pu8Value == NULL){

		Local_enu_ErrorState = ERROR_STATUS_NULL_POINTER;
		return Local_enu_ErrorState;
	}


	else if(Copy_u8PortID <= DIO_u8PortD && Copy_u8PinID <= DIO_u8PIN7){

		switch(Copy_u8PortID){
			case DIO_u8PortA:
				*Copy_pu8Value = GET_BIT(PINA, Copy_u8PinID);
			break;

			case DIO_u8PortB:
				*Copy_pu8Value = GET_BIT(PINB, Copy_u8PinID);
			break;

			case DIO_u8PortC:
				*Copy_pu8Value = GET_BIT(PINC, Copy_u8PinID);
			break;
			
			case DIO_u8PortD:
				*Copy_pu8Value = GET_BIT(PIND, Copy_u8PinID);
		}
		Local_enu_ErrorState = ERROR_STATUS_OK;


	}else{
		return Local_enu_ErrorState;
	}

	return Local_enu_ErrorState;
   }




// 4. if it (1) change it to (0) and vice versa
ErrorStatus_t DIO_enuTogglePinValue(uint8_t Copy_u8PortID, uint8_t Copy_u8PinID){

	ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;


	if(Copy_u8PortID <= DIO_u8PortD && Copy_u8PinID <= DIO_u8PIN7){

		switch(Copy_u8PortID){
			case DIO_u8PortA:
				TOG_BIT(PORTA, Copy_u8PinID);
			break;

			case DIO_u8PortB:
				TOG_BIT(PORTB, Copy_u8PinID);
			break;

			case DIO_u8PortC:
				TOG_BIT(PORTC, Copy_u8PinID);
			break;
			
			case DIO_u8PortD:
				TOG_BIT(PORTD, Copy_u8PinID);
		}

		Local_enu_ErrorState = ERROR_STATUS_OK;

	}else{

		return Local_enu_ErrorState;
	}


	return Local_enu_ErrorState;
}

///****************************************************************************************/


///********************************** Control Entire Port **********************************/
// 1. set entire port as OUTPUT
ErrorStatus_t DIO_enuSetPortDirection(uint8_t Copy_u8PortID, uint8_t Copy_u8Direction){

	ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;

	if(Copy_u8PortID <= DIO_u8PortD && Copy_u8Direction <= DIO_u8OUTPUT){

		switch (Copy_u8PortID){

			case DIO_u8PortA:
				if(Copy_u8Direction == DIO_u8OUTPUT){
					DDRA = 0xFF;
				}else{

					// set them as Input
					DDRA = 0x00;
				}
			break;

			case DIO_u8PortB:
				if(Copy_u8Direction == DIO_u8OUTPUT){
					DDRB = 0xFF;
				}else{

					// set them as Input
					DDRB = 0x00;
				}				

			break;

			case DIO_u8PortC:
				if(Copy_u8Direction == DIO_u8OUTPUT){
					DDRC = 0xFF;
				}else{

					// set them as Input
					DDRC = 0x00;
				}
			break;

			case DIO_u8PortD:
				if(Copy_u8Direction == DIO_u8OUTPUT){
					DDRD = 0xFF;
				}else{

					// set them as Input
					DDRD = 0x00;
				}
			break;	
		}
		Local_enu_ErrorState = ERROR_STATUS_OK;

	}else{
		return Local_enu_ErrorState;
	}


	return Local_enu_ErrorState;
}


//! why ??? would you read entire port ?!
//ErrorStatus_t DIO_enuGetPortValue    (uint8_t Copy_u8PortID, uint8_t *Copy_pu8Value);


ErrorStatus_t DIO_enuSetPortValue(uint8_t Copy_u8PortID, uint8_t Copy_u8Value){
	ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;

	if(Copy_u8PortID <= DIO_u8PortD && Copy_u8Value <= DIO_u8PULLUP){
		
		switch (Copy_u8PortID){
			case DIO_u8PortA:
				if(Copy_u8Value){
					PORTA = 0xFF;
				}else{
					PORTA = 0x00;
				}
			break;

			case DIO_u8PortB:
				if(Copy_u8Value){
					PORTB = 0xFF;
				}else{
					PORTB = 0x00;
				}
			break;

			
			case DIO_u8PortC:
				if(Copy_u8Value){
					PORTC = 0xFF;
				}else{
					PORTC = 0x00;
				}
			break;
	
			case DIO_u8PortD:
				if(Copy_u8Value){
					PORTD = 0xFF;
				}else{
					PORTD = 0x00;
				}
			break;
		}

		Local_enu_ErrorState = ERROR_STATUS_OK;
	}else{
		return Local_enu_ErrorState;
	}


	return Local_enu_ErrorState;
}
///*****************************************************************************************/
