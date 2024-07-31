/*
 * EEPROM_interface.h
 *
 *  Created on: May 28, 2024
 *      Author: ad
 */


// HMI
#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_


/********************** Include  Section **********************/
#include "../../MCAL/DIO/helper_embedded_libraries/micro_config.h"
#include "../../MCAL/TWI/TWI_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_priv.h"
/**************************************************************/


typedef struct {
    uint8_t address;     // Address within the EEPROM
    uint8_t data;        // Data to be written or read


    #if(EEPROM_TYPE == EEPROM_NM24C04 || EEPROM_TYPE == EEPROM_NM24C04F || EEPROM_TYPE == EEPROM_NM24C05 || EEPROM_TYPE == EEPROM_NM24C05F)
        uint8_t A2: 1;
        uint8_t A1: 1;
        uint8_t A0: 1;
        uint8_t   : 5;   // Padding to make it 8 bits


    #elif(EEPROM_TYPE == EEPROM_NM24C08 || EEPROM_TYPE == EEPROM_NM24C08F)
        uint8_t A2: 1;
        uint8_t A1: 1;
        uint8_t A0: 1;
        uint8_t   : 5;   // Padding to make it 8 bits


     #elif(EEPROM_TYPE == EEPROM_NM24C09 || EEPROM_TYPE == EEPROM_NM24C09F)
        uint8_t A2: 1;
        uint8_t   : 7;   // Padding to make it 8 bits
    #endif
} EEPROM_Input_t;




ErrorStatus_t EEPROM_enuInit(void);

//ErrorStatus_t EEPROM_enuWriteData(uint16 copy_u16Address, uint8_t copy_u8Data);


ErrorStatus_t EEPROM_enuWriteData(EEPROM_Input_t* eepromInstance);


ErrorStatus_t EEPROM_enuReadData(EEPROM_Input_t* eepromInstance);



void EEPROM_WriteDataSequence(EEPROM_Input_t* eepromInstance, const uint8_t *dataBuffer, uint8_t dataLength, uint8_t flag, uint8_t startAddress);

uint8_t EEPROM_SearchForFlag(EEPROM_Input_t eepromInstance, uint8_t flag, uint8_t startAddress, uint8_t dataLength);

void EEPROM_Format(EEPROM_Input_t* eepromInstance);


#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
