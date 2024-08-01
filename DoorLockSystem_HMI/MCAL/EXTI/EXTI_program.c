/*
 * EXTI_program.c
 *
 *  Created on: Jan 15, 2024
 *      Author: ad
 *
 * 	Special thing in this driver is "Linking type" configuration
 * 	is implemented.
 */





/*************** Include Section Start ********************/
#include "../DIO/helper_embedded_libraries/micro_config.h"
#include "EXTI_interface.h"
#include "EXTI_priv.h"
#include "EXTI_config.h"

#include <avr/interrupt.h>
/**********************************************************/

//void (*Copy_pfunAppFun[NUM_INT])(void) = {NULL, NULL, NULL};

static void (*EXTI_pfunISRFun[NUM_INT])(void) = {NULL, NULL, NULL};



ErrorStatus_t EXTI_enuInit(EXTI* Copy_pu8GroupConfig){

	ErrorStatus_t Local_enuErrorStatus = ERROR_STATUS_FAILURE;


	if(Copy_pu8GroupConfig == NULL){

		return Local_enuErrorStatus;
	}


	else{


		/**************** INT0 Configuration ****************/
		if(Copy_pu8GroupConfig[INT_NO_0].Int_State == EXTI_ENABLED){

			SET_BIT(GICR, INT0_switch);

			switch(Copy_pu8GroupConfig[INT_NO_0].Sence_Level){


				case EXTI_LOW_LEVEL:

					CLR_BIT(MCUCR, ISC00);
					CLR_BIT(MCUCR, ISC01);

					break;

				case EXTI_ANY_lOGICALCHANGE:

					SET_BIT(MCUCR, ISC00);
					CLR_BIT(MCUCR, ISC01);

					break;


				case EXTI_FALLING_EDGE:

					CLR_BIT(MCUCR, ISC00);
					SET_BIT(MCUCR, ISC01);

					break;

				case EXTI_RISING_EDGE:

					SET_BIT(MCUCR, ISC00);
					SET_BIT(MCUCR, ISC01);

					break;
			}


		}
		else if (Copy_pu8GroupConfig[INT_NO_0].Int_State == EXTI_DISABLED){

			CLR_BIT(GICR, INT0_switch);

		}
		/***************************************************/


		/**************** INT1 Configuration ****************/
		if(Copy_pu8GroupConfig[INT_NO_1].Int_State == EXTI_ENABLED){

			SET_BIT(GICR, INT1_switch);


			switch(Copy_pu8GroupConfig[INT_NO_1].Sence_Level){

				case EXTI_LOW_LEVEL:

					CLR_BIT(MCUCR, ISC10);
					CLR_BIT(MCUCR, ISC11);

					break;


				case EXTI_ANY_lOGICALCHANGE:

					SET_BIT(MCUCR, ISC10);
					CLR_BIT(MCUCR, ISC11);

					break;


				case EXTI_FALLING_EDGE:

					CLR_BIT(MCUCR, ISC10);
					SET_BIT(MCUCR, ISC11);

					break;

				case EXTI_RISING_EDGE:


					SET_BIT(MCUCR, ISC10);
					SET_BIT(MCUCR, ISC11);

					break;
			}


		}
		else if (Copy_pu8GroupConfig[INT_NO_1].Int_State == EXTI_DISABLED){

			CLR_BIT(GICR, INT1_switch);
		}
		/***************************************************/


		/**************** INT2 Configuration ****************/
		if(Copy_pu8GroupConfig[INT_NO_2].Int_State == EXTI_ENABLED){

			SET_BIT(GICR, INT2_switch);

			switch(Copy_pu8GroupConfig[INT_NO_2].Sence_Level){

				case EXTI_FALLING_EDGE:

					CLR_BIT(MCUCSR, ISC2);
					break;

				case EXTI_RISING_EDGE:

					SET_BIT(MCUCSR, ISC2);
					break;
			}


		}
		else if (Copy_pu8GroupConfig[INT_NO_2].Int_State == EXTI_DISABLED){

			CLR_BIT(GICR, INT2_switch);

		}
		/***************************************************/





		Local_enuErrorStatus = ERROR_STATUS_OK;
	}

	return Local_enuErrorStatus;
}

ErrorStatus_t EXTI_enuEnableInterrupt(uint8_t Copy_u8IntNumber){

	ErrorStatus_t Local_enuErrorStatus = ERROR_STATUS_FAILURE;


		switch(Copy_u8IntNumber){
			case INT_NO_0:

				SET_BIT(GICR, INT0_switch);
				break;

			case INT_NO_1:

				SET_BIT(GICR, INT1_switch);
				break;

			case INT_NO_2:

				SET_BIT(GICR, INT2_switch);
		}

		Local_enuErrorStatus = ERROR_STATUS_OK;


	return Local_enuErrorStatus;
}

ErrorStatus_t EXTI_enuDisableInterrupt(uint8_t Copy_u8IntNumber){

	ErrorStatus_t Local_enuErrorStatus = ERROR_STATUS_FAILURE;

	if(Copy_u8IntNumber > INT_NO_2){
		return Local_enuErrorStatus;
	}

	else{

		switch(Copy_u8IntNumber){
		case INT_NO_0:

			
			GICR &= ~(1<<INT0_switch);
			break;

		case INT_NO_1:

			GICR &= ~(1<<INT1_switch);
			break;

		case INT_NO_2:

			GICR &= ~(1<<INT2_switch);
		}

		Local_enuErrorStatus = ERROR_STATUS_OK;
	}

	return Local_enuErrorStatus;
}


ErrorStatus_t EXTI_enuSetSenseLevel(uint8_t Copy_u8IntNumber,  uint8_t Copy_u8SenseLevel){

	ErrorStatus_t Local_enuErrorStatus = ERROR_STATUS_FAILURE;


	if( (Copy_u8IntNumber > INT_NO_2) || Copy_u8SenseLevel > EXTI_RISING_EDGE){

		return Local_enuErrorStatus;
	}

	else{

		switch(Copy_u8IntNumber){
		case INT_NO_0:

			/**************** INT0 Sense_LEVEL ****************/
			switch(Copy_u8SenseLevel){
				case EXTI_ANY_lOGICALCHANGE:

					MCUCR |=  (1 << ISC00);
					MCUCR &= ~(1 << ISC01);

					break;

				case EXTI_LOW_LEVEL:

					MCUCR &= ~(1 << ISC00);
					MCUCR &= ~(1 << ISC01);

					break;

				case EXTI_FALLING_EDGE:

					MCUCR &= ~(1 << ISC00);
					MCUCR |=  (1 << ISC01);

					break;

				case EXTI_RISING_EDGE:

					MCUCR |=  (1 << ISC00);
					MCUCR |=  (1 << ISC01);

					break;
			}

			break;
			/**************************************************/

		case INT_NO_1:

			/**************** 1 Sense_LEVEL ****************/
			switch(Copy_u8SenseLevel){
			case EXTI_ANY_lOGICALCHANGE:

				MCUCR |=   (1 << ISC10);
				MCUCR &=  ~(1 << ISC11);

				break;

			case EXTI_LOW_LEVEL:

				MCUCR &=  ~(1 << ISC10);
				MCUCR &=  ~(1 << ISC11);

				break;

			case EXTI_FALLING_EDGE:

				MCUCR &=  ~(1 << ISC10);
				MCUCR |=   (1 << ISC11);

				break;

			case EXTI_RISING_EDGE:

				MCUCR |=  (1 << ISC10);
				MCUCR |=  (1 << ISC11);

				break;
			}

			break;
			/**************************************************/



		case INT_NO_2:

			/**************** INT2 Sense_LEVEL ****************/
			switch(Copy_u8SenseLevel){

				case EXTI_FALLING_EDGE:
					MCUCSR &= ~(1 << ISC2);

					break;

				case EXTI_RISING_EDGE:

					MCUCSR |= (1 << ISC2);

					break;
			}

			/**************************************************/
		}


		Local_enuErrorStatus = ERROR_STATUS_OK;
	}


	return Local_enuErrorStatus;
}


ErrorStatus_t EXTI_enuSetCallBack( void (*Copy_pfunAppFun)(void), uint8_t Copy_u8IntNumber){

	ErrorStatus_t Local_enuErrorStatus = ERROR_STATUS_FAILURE;


	if( (Copy_pfunAppFun == NULL ) ){


		Local_enuErrorStatus = ERROR_STATUS_NULL_POINTER;
		return Local_enuErrorStatus;
	}

	else if(Copy_u8IntNumber > INT_NO_2){

		Local_enuErrorStatus = ERROR_OUT_OF_RANGE;
		return Local_enuErrorStatus;
	}

	else{
		EXTI_pfunISRFun[Copy_u8IntNumber] = Copy_pfunAppFun;
	}


	Local_enuErrorStatus = ERROR_STATUS_OK;
	return Local_enuErrorStatus;
}


ISR(INT0_vect){

		if(EXTI_pfunISRFun[INT_NO_0] != NULL){
			EXTI_pfunISRFun[INT_NO_0]();
		}
}




ISR(INT1_vect){

		if(EXTI_pfunISRFun[INT_NO_1] != NULL){
			EXTI_pfunISRFun[INT_NO_1]();
		}
}



ISR(INT2_vect){

		if(EXTI_pfunISRFun[INT_NO_2] != NULL){
			EXTI_pfunISRFun[INT_NO_2]();
		}
}









