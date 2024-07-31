/*
 * EEPROM_priv.h
 *
 *  Created on: May 28, 2024
 *      Author: ad
 */

#ifndef HAL_EEPROM_EEPROM_PRIV_H_
#define HAL_EEPROM_EEPROM_PRIV_H_





#define EEPROM_NM24C04				1
#define EEPROM_NM24C04F				2
#define EEPROM_NM24C05				3
#define EEPROM_NM24C05F				4
#define EEPROM_NM24C08				5
#define EEPROM_NM24C08F				6
#define EEPROM_NM24C09				7
#define EEPROM_NM24C09F				8








#define EEPROM_GROUND				0
#define EEPROM_VCC					1


#define EEPROM_pinNOTCONNECTED		9


#endif /* HAL_EEPROM_EEPROM_PRIV_H_ */



/*
 * [[ EEPROM exist in proteus ]]
 *
 *	1. NM24C04					[]
 *	2. NM24C04F					[]
 *	3. NM24C05					[]
 *	4. NM24C05F					[]
 * 	1. NM24C08	100khz	8k		[x]
 * 	2. NM24C08F	400khz	8k		[x]
 * 	3. NM24C09					[!]
 * 	4. NM24C09F 				[!]
 *
 */
