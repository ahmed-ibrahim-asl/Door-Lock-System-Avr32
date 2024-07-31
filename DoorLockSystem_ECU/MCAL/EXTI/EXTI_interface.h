/*
 * EXTI_interface.h
 *
 *  Created on: Jan 15, 2024
 *      Author: ad
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/*************** Include Section Start ********************/
#include "../DIO/helper_embedded_libraries/micro_config.h"
#include "EXTI_config.h"
#include "EXTI_priv.h"
/**********************************************************/



//ErrorStatus_t EXTI_enuInit(EXTI* Copy_pu8GroupConfig)
ErrorStatus_t EXTI_enuInit(EXTI* Copy_pu8GroupConfig);

ErrorStatus_t EXTI_enuEnableInterrupt(uint8_t Copy_u8IntNumber);
ErrorStatus_t EXTI_enuDisableInterrupt(uint8_t Copy_u8IntNumber);


ErrorStatus_t EXTI_enuSetSenseLevel(uint8_t Copy_u8IntNumber,  uint8_t Copy_u8SenseLevel);


ErrorStatus_t EXTI_enuSetCallBack(void(*Copy_pfunAppFun)(void), uint8_t Copy_u8IntNumber);






#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
