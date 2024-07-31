/*
 * EEPROM_config.h
 *
 *  Created on: May 28, 2024
 *      Author: ad
 */

#ifndef HAL_EEPROM_EEPROM_CONFIG_H_
#define HAL_EEPROM_EEPROM_CONFIG_H_


/********************** Include  Section **********************/
#include "EEPROM_priv.h"
/**************************************************************/


//! Notice you have to make sure you set TWI speed right
//EEPROM_NM24C04, EEPROM_NM24C04F, EEPROM_NM24C05, EEPROM_NM24C05F, EEPROM_NM24C08,
//EEPROM_NM24C08F, EEPROM_NM24C09, EEPROM_NM24C09F,
#define EEPROM_TYPE 		EEPROM_NM24C08F




#endif /* HAL_EEPROM_EEPROM_CONFIG_H_ */



/***
 *
 * [[ Supported eeprom ]]
 *
 *	1. NM24C04					[x]
 *	2. NM24C04F	400khz			[x]
 *	3. NM24C05					[x]
 *	4. NM24C05F	400khz			[x]
 * 	1. NM24C08	100khz	8k		[x]
 * 	2. NM24C08F	400khz	8k		[x]
 * 	3. NM24C09					[x]
 * 	4. NM24C09F 				[x]
 *
 */


/**
 *	[The difference between (NM24C08/F	- NM24C09/F	]
 *
 *	NM24C08/F:
 *		-Allows up to 8 devices on same bus using A0, A1 and A2 pins
 *		-A0, A1, A2 these pins is what allows us to have 8 devices on the bus
 *
 *
 *	NM24C09/F:
 *		-Supports up to 2 devices on the same bus using A2 pin.
 *		-has detecated pin for write protection,
 *			-WP=High: this prevent any write operations to the upper half of the memory
 *			-WP=Low:  this allow write operation for the entire memory
 *
 */
