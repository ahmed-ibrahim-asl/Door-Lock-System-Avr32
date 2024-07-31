/*
 * uart_program.c
 *
 *  Created on: Mar 12, 2024
 *      Author: ad
 */
/********************************* Include  Section *********************************/
#include "../DIO/helper_embedded_libraries/micro_config.h"
#include "UART_interface.h"
#include "UART_priv.h"
#include "UART_config.h"
/************************************************************************************/


void UART_vidInit(uint16 copy_u8UART_BaudRate){


	/********************** Setting  Baud Rate **********************/
	UART_setBaudRate(copy_u8UART_BaudRate);
	/***************************************************************/
    SET_BIT(UCSRC_REG, UCSRC_URSEL);


	#if(UART_SYNC_ASYNC_SELECT == UART_ASYNCMODE)

		CLR_BIT(UCSRC_REG, UCSRC_UMSEL);

		#if(UART_SPEED_MODE == UART_NORMAL_SPEED)
			CLR_BIT(UCSRA_REG, UCSRA_U2X);

		#elif(UART_SPEED_MODE == UART_DOUBLE_SPEED)
			SET_BIT(UCSRA_REG, UCSRA_U2X);

		#endif


	#elif(UART_SYNC_ASYNC_SELECT == UART_SYNCMODE)
			SET_BIT(UCSRC_REG, UCSRC_UMSEL);
	#endif


	#if(UART_MPCM_OPERATION == UART_SINGLE_MODE)
			CLR_BIT(UCSRA_REG, UCSRA_MPCM);

	#elif(UART_MPCM_OPERATION == UART_MULTI_MODE)
			SET_BIT(UCSRA_REG, UCSRA_MPCM);
	#endif


	// Receiver Enable
	SET_BIT(UCSRB_REG, UCSRB_RXEN);

	// Transmitter Enable
	SET_BIT(UCSRB_REG, UCSRB_TXEN);


	/********************* Setting No Data Bits *********************/


    #if(UART_DATA_BIT == UART_DATA_9bit)

		SET_BIT(UCSRC_REG, UCSRC_UCSZ0);
		SET_BIT(UCSRC_REG, UCSRC_UCSZ1);
		SET_BIT(UCSRB_REG, UCSRB_UCSZ2);

	#elif(UART_DATA_BIT == UART_DATA_8bit)

		SET_BIT(UCSRC_REG, UCSRC_UCSZ0);
		SET_BIT(UCSRC_REG, UCSRC_UCSZ1);
		CLR_BIT(UCSRB_REG, UCSRB_UCSZ2);

	#elif(UART_DATA_BIT == UART_DATA_7bit)

		CLR_BIT(UCSRC_REG, UCSRC_UCSZ0);
		SET_BIT(UCSRC_REG, UCSRC_UCSZ1);
		CLR_BIT(UCSRB_REG, UCSRB_UCSZ2);

	#elif(UART_DATA_BIT == UART_DATA_6bit)

		SET_BIT(UCSRC_REG, UCSRC_UCSZ0);
		CLR_BIT(UCSRC_REG, UCSRC_UCSZ1);
		CLR_BIT(UCSRB_REG, UCSRB_UCSZ2);

	#elif(UART_DATA_BIT == UART_DATA_5bit)

		CLR_BIT(UCSRC_REG, UCSRC_UCSZ0);
		CLR_BIT(UCSRC_REG, UCSRC_UCSZ1);
		CLR_BIT(UCSRB_REG, UCSRB_UCSZ2);

	#endif
	/****************************************************************/


	/********************* Setting No Stop Bits *********************/
	#if(UART_STOP_BIT == UART_STOP_1bit)

		CLR_BIT(UCSRC_REG, UCSRC_USBS);
	#elif(UART_STOP_BIT == UART_STOP_2bit)

		SET_BIT(UCSRC_REG, UCSRC_USBS);
	#endif


	/****************************************************************/


	/********************* Setting  Parity Mode *********************/
	#if(UART_PARITY_MODE == UART_PARITY_DISABLE)

		CLR_BIT(UCSRC_REG, UCSRC_UPM0);
		CLR_BIT(UCSRC_REG, UCSRC_UPM1);

	#elif(UART_PARITY_MODE == UART_PARITY_EVEN)

		CLR_BIT(UCSRC_REG, UCSRC_UPM0);
		SET_BIT(UCSRC_REG, UCSRC_UPM1);

	#elif(UART_PARITY_MODE == UART_PARITY_ODD)

		SET_BIT(UCSRC_REG, UCSRC_UPM1);
		SET_BIT(UCSRC_REG, UCSRC_UPM0);

	#endif
	/****************************************************************/


	/*********************** Clock Polarity ***********************/
	#if(UART_SYNC_ASYNC_SELECT == UART_SYNCMODE)
		#if(UART_CLOCK_POLARITY == UART_TxFalling_RxRising)
			SET_BIT(UCSRC_REG, UCSRC_UCPOL);

		#elif(UART_CLOCK_POLARITY == UART_TxRising_RxFalling)
			CLR_BIT(UCSRC_REG, UCSRC_UCPOL);
		#endif

	#endif
	/**************************************************************/




}


ErrorStatus_t UART_enuSendChar(uint8_t copy_u8Data){
	ErrorStatus_t Local_enuErrrorState = ERROR_STATUS_FAILURE;


	// Wait until transmit buffer is empty
	while(GET_BIT(UCSRA_REG, UCSRA_URDE) == 0);

	UDR_REG = copy_u8Data;


	Local_enuErrrorState = ERROR_STATUS_OK;
	return Local_enuErrrorState;
}


ErrorStatus_t UART_enuSendString(uint8_t* copy_pu8Data){
	ErrorStatus_t Local_enuErrrorState = ERROR_STATUS_FAILURE;

	if(copy_pu8Data == NULL){
		return Local_enuErrrorState;
	}

	else{

		while(*copy_pu8Data != '\0'){
			UART_enuSendChar(*copy_pu8Data);
			copy_pu8Data++;
		}
		UART_enuSendChar('\0');
	}

	Local_enuErrrorState = ERROR_STATUS_OK;
	return Local_enuErrrorState;
}

ErrorStatus_t UART_enuRecieveChar(uint8_t* copy_pu8Data){


	ErrorStatus_t Local_enuErrrorState = ERROR_STATUS_FAILURE;

	if(copy_pu8Data == NULL){
		return Local_enuErrrorState;
	}

	else{

		// Receive Complete
		while(GET_BIT(UCSRA_REG, UCSRA_RXC) == 0);

		*copy_pu8Data = UDR_REG;
	}

	Local_enuErrrorState = ERROR_STATUS_OK;
	return Local_enuErrrorState;
}



ErrorStatus_t UART_enuRecieveString(uint8_t* copy_pu8Data) {
    if (copy_pu8Data == NULL) {
        return ERROR_STATUS_FAILURE;
    }

    uint8_t receivedChar;
    while (1) {
        // Receive a character from UART
        UART_enuRecieveChar(&receivedChar);

        // Store the received character in the buffer
        *copy_pu8Data = receivedChar;

        // Check if the received character is the null terminator
        if (receivedChar == '\0') {
            break; // Exit the loop if end of string is detected
        }

        // Move to the next position in the buffer
        copy_pu8Data++;
    }

    // Null-terminate the string
    *copy_pu8Data = '\0';

    return ERROR_STATUS_OK;
}

//!
void UART_setBaudRate(uint16 copy_u8UART_BaudRate){
    unsigned int copy_u16Temp = 0;


    #if (UART_SYNC_ASYNC_SELECT == UART_ASYNCMODE)
        #if (UART_SPEED_MODE == UART_NORMAL_SPEED)


    			copy_u16Temp = ((UART_MC_OSC_FREQ / (16UL*copy_u8UART_BaudRate) ) - 1);


        #elif (UART_SPEED_MODE == UART_DOUBLE_SPEED)
    			copy_u16Temp = ((UART_MC_OSC_FREQ / (8UL*copy_u8UART_BaudRate) ) - 1);

        #endif


    #elif (UART_SYNC_ASYNC_SELECT == UART_SYNCMODE)

    			copy_u16Temp = ((UART_MC_OSC_FREQ / (2UL*copy_u8UART_BaudRate) ) - 1);
    #endif


    CLR_BIT(UCSRC_REG, UCSRC_URSEL);

    UBRRH_REG = (uint8_t)(copy_u16Temp >> 8);
    UBRRL_REG = (uint8_t)copy_u16Temp;
}
