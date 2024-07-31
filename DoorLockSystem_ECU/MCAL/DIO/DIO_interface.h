/*
 * DIO_interface.h
 *
 *  Created on: Dec 29, 2023
 *      Author: ad
*/

#ifndef DIO_DIO_INTERFACE_H_
#define DIO_DIO_INTERFACE_H_

/*************** Include Section Start ********************/
#include "helper_embedded_libraries/micro_config.h"
#include "DIO_config.h"
#include "DIO_priv.h"
/**********************************************************/


// golden rule: any driver you do has to have function that start the driver
ErrorStatus_t DIO_enuInit(void);


// PortID - is it A, B, C, D ordered from (0->3)
// PinID  - refers to pin Number (0->7)


/********************************** Control Pin by Pin **********************************/
ErrorStatus_t DIO_enuSetPinDirection(
    uint8_t Copy_u8PortID,
    uint8_t Copy_u8PinID,
    uint8_t Copy_u8Direction);

ErrorStatus_t DIO_enuSetPinValue(
    uint8_t Copy_u8PortID,
    uint8_t Copy_u8PinID,
    uint8_t Copy_u8Value);

ErrorStatus_t DIO_enuGetPinValue(
    uint8_t Copy_u8PortID,
    uint8_t Copy_u8PinID,
    uint8_t *Copy_pu8Value);

ErrorStatus_t DIO_enuTogglePinValue(uint8_t Copy_u8PortID, uint8_t Copy_u8PinID);
/****************************************************************************************/


/********************************** Control Entire Port **********************************/
ErrorStatus_t DIO_enuSetPortDirection(uint8_t Copy_u8PortID, uint8_t Copy_u8Direction);
ErrorStatus_t DIO_enuGetPortValue    (uint8_t Copy_u8PortID, uint8_t *Copy_pu8Value);
ErrorStatus_t DIO_enuSetPortValue    (uint8_t Copy_u8PortID, uint8_t Copy_u8Value);
/*****************************************************************************************/

#endif /* DIO_DIO_INTERFACE_H_ */
