/*
 * TWI_priv.h
 *
 *  Created on: Mar 30, 2024
 *      Author: ad
 */

#ifndef MCAL_TWI_TWI_PRIV_H_
#define MCAL_TWI_TWI_PRIV_H_



/*********************** TWI  Registers ***********************/
#define TWBR_REG	*((volatile uint8_t*) (0x20))
#define TWSR_REG	*((volatile uint8_t*) (0x21))
#define TWAR_REG	*((volatile uint8_t*) (0x22))
#define TWDR_REG	*((volatile uint8_t*) (0x23))

#define TWCR_REG	*((volatile uint8_t*) (0x56))
/**************************************************************/



/************************* TWCR  bits *************************/
#define TWCR_TWIE							0

#define TWCR_TWEN							2
#define TWCR_TWWC							3
#define TWCR_TWSTO							4
#define TWCR_TWSTA							5
#define TWCR_TWEA							6
#define TWCR_TWINT 							7
/**************************************************************/



/************************* TWAR  bits *************************/
#define TWAR_TWGCE							0
/**************************************************************/



/************************* TWI  Modes *************************/
#define TWI_WriteOperation					0
#define TWI_ReadOperation					1

#define TWI_MASTER_MODE						2
#define TWI_SLAVE_MODE						3
/**************************************************************/



/******************** TWI Prescaler Macros ********************/
#if   TWI_PRESCALER_SELECTOR == TWI_PRESCALER_1
    #define TWI_PRESCALER_VALUE     0x00
    #define TWI_PRESCALER_DIV       1

#elif TWI_PRESCALER_SELECTOR == TWI_PRESCALER_4
    #define TWI_PRESCALER_VALUE     0x01
    #define TWI_PRESCALER_DIV       4

#elif TWI_PRESCALER_SELECTOR == TWI_PRESCALER_16
    #define TWI_PRESCALER_VALUE     0x02
    #define TWI_PRESCALER_DIV       16

#elif TWI_PRESCALER_SELECTOR == TWI_PRESCALER_64
    #define TWI_PRESCALER_VALUE     0x03
    #define TWI_PRESCALER_DIV       64

#else
    #error "Invalid TWI Prescaler value"
#endif
/**************************************************************/



/*************** TWI Configuration Calculations ***************/
#define TWBR_VALUE 		(((F_CPU / TWI_SPEED_SPECIFIER) - 16) / (2 * TWI_PRESCALER_DIV))

#define TWI_SET_ADDR	(TWI_NODE_ADDR&0x7F) << 1
/**************************************************************/



/***************** TWI General Macros Control *****************/
#define TWI_ACK_ENABLE                		4
#define TWI_ACK_DISABLE						5

#define TWI_GCE_ENABLE						6
#define TWI_GCE_DISABLE						7
/**************************************************************/

#define TWI_START_SUCCESS_CODE				0x08

#define TWI_RSTART_SUCCESS_CODE				0x10


// 0x40 SLA+R has been transmitted, ack has been received
#define TWI_SLA_RD_ACK_TSUCCESS_CODE 		0x40

// 0x18 SLA+W has been transmitted, ack has been received
#define TWI_SLA_WR_ACK_TSUCCESS_CODE 		0x18

// 0x60 - SLA+W has been received, ACK has been returned
#define TWI_SLA_WR_ACK_RSUCCESS_CODE		0x60

// 0xA8 - SLA+R has been received, ACK has been returned
#define TWI_SLA_RD_ACK_RSUCCESS_CODE		0xA8

// 0x28 -(master) data byte has been transmitted ack has been received
#define TWI_M_TSUCCESS_CODE_withACK			0x28

// 0xB8	- (slave) data byte has been transmitted ack has been received
#define TWI_S_TSUCCESS_CODE_withACK			0xB8

// 0x50 - (master) data byte has been received ack has been returned
#define TWI_M_RSUCCESS_CODE_withAck			0x50

// 0x58 - (master) data byte has been received not ack has been returned
#define TWI_M_RSUCCESS_CODE_withoutAck		0x58

// 0x80 - (slave)  data has been received ack has been returned
#define TWI_S_RSUCCESS_CODE_withACK			0x80

// 0x88 - (slave)  data has been received not ack has been returned
#define TWI_S_RSUCCESS_CODE_withoutACK		0x88





/************************* TWI Status *************************/
typedef enum{
	TWI_STATUS_FAILURE,
	TWI_STATUS_OK

}TWIStatus_t;
/**************************************************************/








#endif /* MCAL_TWI_TWI_PRIV_H_ */
