/*
 * TWI_config.h
 *
 *  Created on: Mar 30, 2024
 *      Author: ad
 */

#ifndef MCAL_TWI_TWI_CONFIG_H_
#define MCAL_TWI_TWI_CONFIG_H_

/********************** Include  Section **********************/
#include "TWI_priv.h"
/**************************************************************/

// Options: TWI_MASTER_MODE - TWI_SLAVE_MODE
#define TWI_MODE_M_or_S					TWI_MASTER_MODE


// For a 16 MHz clock frequency
#define F_CPU 							8000000UL


 // TWI SCL speed: 400 kHz
#define TWI_SPEED_SPECIFIER				400000


// Node address in the TWI network
// Don't use:
//				(0000 000 - reserved for general call)
//				(1111 xxx - all these address reserved for future purpose)
#define TWI_NODE_ADDR					4



// Options: TWI_PRESCALER_1, TWI_PRESCALER_4, TWI_PRESCALER_16, TWI_PRESCALER_64
// Prescaler affects the division factor for SCL frequency calculation
#define TWI_PRESCALER_SELECTOR			TWI_PRESCALER_1


// ACK Configuration for received data
// Options: TWI_ACK_ENABLE, TWI_ACK_DISABLE
// Enabling ACK allows the device to acknowledge received data
#define TWI_ACK_CONFIG                TWI_ACK_ENABLE


// General Call Enable (GCE) Configuration
// Options: TWI_GCE_ENABLE, TWI_GCE_DISABLE
// Enabling GCE allows the device to respond to general call addressing
#define TWI_GCE_CONFIG				  TWI_GCE_ENABLE




#endif /* MCAL_TWI_TWI_CONFIG_H_ */
