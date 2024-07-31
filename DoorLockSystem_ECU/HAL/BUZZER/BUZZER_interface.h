/*
 * BUZZER_interface.h
 *
 *  Created on: Jul 29, 2024
 *      Author: ad
 */

#ifndef HAL_BUZZER_BUZZER_INTERFACE_H_
#define HAL_BUZZER_BUZZER_INTERFACE_H_


#include "../../MCAL/DIO/helper_embedded_libraries/micro_config.h"

typedef struct{
	uint8_t PortID;
	uint8_t	PinID;
}Buzzer_t;


///********************* Functions  Prototype *********************/
void Buzzer_voidInit(Buzzer_t *Copy_Buzzer);

void Buzzeer_voidON(Buzzer_t *Copy_Buzzer);

void Buzzeer_voidOFF(Buzzer_t *Copy_Buzzer);

void Buzzer_voidTOGGLE(Buzzer_t *Copy_Buzzer);
///****************************************************************/
//


#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
