/*
 * uart_priv.h
 *
 *  Created on: Mar 12, 2024
 *      Author: ad
 */

#ifndef MCAL_UART_UART_PRIV_H_
#define MCAL_UART_UART_PRIV_H_

/*********************** Uart Registers ***********************/
#define UBRRH_REG	*((volatile uint8_t*) (0x40))
#define UBRRL_REG	*((volatile uint8_t*) (0x29))
#define UCSRC_REG	*((volatile uint8_t*) (0x40))

#define UDR_REG	    *((volatile uint8_t*) (0x2C))
#define UCSRA_REG	*((volatile uint8_t*) (0x2B))
#define UCSRB_REG	*((volatile uint8_t*) (0x2A))
/***************************************************************/


/************************* UCSRA Bits *************************/
#define UCSRA_MPCM							0
#define UCSRA_U2X							1
#define UCSRA_URDE							5
#define UCSRA_RXC							7
/**************************************************************/



/************************* UCSRB Bits *************************/
#define UCSRB_TXEN							3
#define UCSRB_RXEN							4
#define UCSRB_TXCIE							6
#define UCSRB_UCSZ2							2
/**************************************************************/



/************************* UCSRC Bits *************************/
#define UCSRC_UCPOL							0
#define UCSRC_UCSZ0							1
#define UCSRC_UCSZ1							2
#define UCSRC_USBS							3

#define UCSRC_UPM0							4
#define UCSRC_UPM1							5
#define UCSRC_UMSEL							6
#define UCSRC_URSEL							7

/**************************************************************/
#define UBRRH_URSEL							7





#define UART_SYNCMODE						1
#define UART_ASYNCMODE						2

#define UART_NORMAL_SPEED					3
#define UART_DOUBLE_SPEED					4

#define UART_SINGLE_MODE					5
#define UART_MULTI_MODE						6




#define UART_DATA_9bit						9
#define UART_DATA_8bit						8
#define UART_DATA_7bit						7
#define UART_DATA_6bit						6
#define UART_DATA_5bit						5


#define UART_STOP_1bit						1
#define UART_STOP_2bit						2


#define UART_PARITY_DISABLE					1
#define UART_PARITY_ODD						2
#define UART_PARITY_EVEN					3




#define UART_TxRising_RxFalling				0
#define UART_TxFalling_RxRising				1




#endif /* MCAL_UART_UART_PRIV_H_ */
