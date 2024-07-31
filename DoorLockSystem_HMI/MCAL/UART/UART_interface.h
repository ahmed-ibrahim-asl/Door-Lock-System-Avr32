/*
 * UART_interface.h
 *
 *  Created on: Mar 14, 2024
 *      Author: ad
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_


/********************* Functions  Prototype *********************/
void UART_vidInit(uint16 copy_u8UART_BaudRate);

ErrorStatus_t UART_enuSendChar(uint8_t copy_u8Data);
ErrorStatus_t UART_enuSendString(uint8_t* copy_pu8Data);


ErrorStatus_t UART_enuRecieveChar(uint8_t* copy_pu8Data);
ErrorStatus_t UART_enuRecieveString(uint8_t* copy_pu8Data);
/****************************************************************/


//static void UART_UBRR_VALUE(UART_BAUD_RATE);


void UART_setBaudRate(uint16 copy_u8UART_BaudRate);

#endif /* MCAL_UART_UART_INTERFACE_H_ */
