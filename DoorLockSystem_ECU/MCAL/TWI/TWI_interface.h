/*
 * TWI_interface.h
 *
 *  Created on: Mar 30, 2024
 *      Author: ad
 */

#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_

/********************** Include  Section **********************/
#include "TWI_priv.h"
#include "TWI_config.h"
/**************************************************************/



TWIStatus_t TWI_enuInit(void);

TWIStatus_t TWI_enuStartCondition(void);
TWIStatus_t TWI_enuRepeatStartCondition(void);

TWIStatus_t TWI_enuStopCondition(void);


TWIStatus_t TWI_enuSetSlaveOperation(
		uint8_t copy_u8SlaveAddress, uint8_t copy_u8Operation);

TWIStatus_t	TWI_enuWriteData(uint8_t copy_u8Data);


TWIStatus_t	TWI_enuReadData(uint8_t  *copy_pu8Data);

//!
ErrorStatus_t TWI_enuCheckMyAddress(void);

#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
