/*
 * GIE_program.c
 *
 *  Created on: Jan 15, 2024
 *  Author: ad
 *
 *
 *  Description: This module handles the global interrupt
 *  functionality. It provides interfaces,
 *  enable and disable global interrupt
 *
 */

/*************** Include Section Start ********************/
#include "../DIO/helper_embedded_libraries/micro_config.h"
#include "GIE_interface.h"
#include "GIE_priv.h"
/**********************************************************/

//ErrorStatus_t GIE_enuInit(void);

ErrorStatus_t GIE_enuEnable(void){
	ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;


	if( ((SREG >> I_BIT)&&1) == BIT_OFF ){

		SREG |= (1 << I_BIT);
		Local_enu_ErrorState = ERROR_STATUS_OK;
	}


	return Local_enu_ErrorState;
}


ErrorStatus_t GIE_enuDisable(void){
	ErrorStatus_t Local_enu_ErrorState = ERROR_STATUS_FAILURE;


	if( ((SREG >> I_BIT)&&1) == BIT_ON){

		SREG &= ~(1 << I_BIT);
		Local_enu_ErrorState = ERROR_STATUS_OK;
	}


	return Local_enu_ErrorState;
}


