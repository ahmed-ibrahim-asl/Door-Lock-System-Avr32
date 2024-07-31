/*
 * uart_config.h
 *
 *  Created on: Mar 14, 2024
 *      Author: ad
 */

#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_

/*********************** Include  Section ***********************/
#include "UART_priv.h"
/****************************************************************/

// Options: UART_ASYNCMODE or UART_SYNCMODE
#define UART_SYNC_ASYNC_SELECT				UART_ASYNCMODE

#if(UART_SYNC_ASYNC_SELECT == UART_ASYNCMODE)
	// Options: UART_NORMAL_SPEED or UART_DOUBLE_SPEED
	#define UART_SPEED_MODE						UART_NORMAL_SPEED
#endif


// MPCM: Multi-Processor Communication Mode
// Options: UART_SINGLE_MODE or UART_MULTI_MODE
#define UART_MPCM_OPERATION						UART_SINGLE_MODE


// Options: UART_DATA_9bit, UART_DATA_8bit, UART_DATA_7bit,
//			UART_DATA_6bit, UART_DATA_5bit
#define UART_DATA_BIT						    UART_DATA_8bit


// Options: UART_STOP_2bit, UART_STOP_1bit
#define UART_STOP_BIT							UART_STOP_1bit


// Options: UART_PARITY_DISABLE, UART_PARITY_ODD
//			UART_PARITY_EVEN
#define UART_PARITY_MODE						UART_PARITY_ODD


// Options: UART_TxRising_RxFalling, UART_TxFalling_RxRising
#define UART_CLOCK_POLARITY						UART_TxRising_RxFalling




//! baud rate

// NOTICE: 16000000 -> 16MHZ
#define UART_MC_OSC_FREQ					8000000UL







#endif /* MCAL_UART_UART_CONFIG_H_ */
