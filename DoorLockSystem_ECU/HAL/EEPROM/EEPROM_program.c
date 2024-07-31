/*
 * EEPROM_program.c
 *
 *  Created on: May 28, 2024
 *      Author: ad
 */


/********************** Include  Section **********************/
#include "../../MCAL/DIO/helper_embedded_libraries/micro_config.h"


#include "EEPROM_interface.h"
#include <util/delay.h>
/**************************************************************/



ErrorStatus_t EEPROM_enuInit(void){
	ErrorStatus_t Local_enuErrorState = TWI_enuInit();

	return Local_enuErrorState;
}


ErrorStatus_t EEPROM_enuWriteData(EEPROM_Input_t* eepromInstance) {
    ErrorStatus_t Local_enuErrorState = ERROR_STATUS_FAILURE;


	#if(EEPROM_TYPE == EEPROM_NM24C04 || EEPROM_TYPE == EEPROM_NM24C04F )

    	uint8_t	Local_u8Address = (0xA0) | (eepromInstance->A2 << 3) | (eepromInstance->A1 << 2) | (eepromInstance->A0);

	#elif(EEPROM_TYPE == EEPROM_NM24C05 || EEPROM_TYPE == EEPROM_NM24C05F )

    	uint8_t	Local_u8Address = (0xA0) | (eepromInstance->A2 << 3) | (eepromInstance->A1 << 2) | (eepromInstance->A0);

	#elif(EEPROM_TYPE == EEPROM_NM24C08 || EEPROM_TYPE == EEPROM_NM24C08F )

		uint8_t	Local_u8Address = (0xA0) | (eepromInstance->A2 << 2) | (eepromInstance->A1 << 1) | (eepromInstance->A0);

	#elif(EEPROM_TYPE == EEPROM_NM24C09 || EEPROM_TYPE == EEPROM_NM24C09F )

		uint8_t Local_u8Address = (0xA0) | (EEPROM_A2_STATE << 2);

	#else
		#error "Unsupported EEPROM type!"
	#endif


    // Send start condition
    if( TWI_enuStartCondition() == TWI_STATUS_OK){

		// Send EEPROM address with write operation
		TWI_enuWriteData(Local_u8Address | TWI_WriteOperation);

		// Send memory address within EEPROM
		TWI_enuWriteData(eepromInstance->address);

		// Write data to EEPROM
		TWI_enuWriteData(eepromInstance->data);

		// Send stop condition
		TWI_enuStopCondition();

    }

    // Small delay to ensure data is written
    _delay_ms(10);
    Local_enuErrorState = ERROR_STATUS_OK;
    return Local_enuErrorState;
}


ErrorStatus_t EEPROM_enuReadData(EEPROM_Input_t* eepromInstance) {
    ErrorStatus_t Local_enuErrorState = ERROR_STATUS_FAILURE;

    eepromInstance->data = 0;

	#if(EEPROM_TYPE == EEPROM_NM24C04 || EEPROM_TYPE == EEPROM_NM24C04F )

		uint8_t	Local_u8Address = (0xA0) | (eepromInstance->A2 << 3) | (eepromInstance->A1 << 2) | (eepromInstance->A0);

	#elif(EEPROM_TYPE == EEPROM_NM24C05 || EEPROM_TYPE == EEPROM_NM24C05F )

		uint8_t	Local_u8Address = (0xA0) | (eepromInstance->A2 << 3) | (eepromInstance->A1 << 2) | (eepromInstance->A0);

	#elif(EEPROM_TYPE == EEPROM_NM24C08 || EEPROM_TYPE == EEPROM_NM24C08F )

		uint8_t	Local_u8Address = (0xA0) | (eepromInstance->A2 << 2) | (eepromInstance->A1 << 1) | (eepromInstance->A0);

	#elif(EEPROM_TYPE == EEPROM_NM24C09 || EEPROM_TYPE == EEPROM_NM24C09F )

		uint8_t Local_u8Address = (0xA0) | (EEPROM_A2_STATE << 2);

	#else
		#error "Unsupported EEPROM type!"
	#endif


	#if( EEPROM_TYPE == EEPROM_NM24C09 || EEPROM_TYPE == EEPROM_NM24C09F )
		uint8_t Local_u8Address = (0xA0) | (EEPROM_A2_STATE << 2);
	#endif

	// Send start condition
    if( TWI_enuStartCondition() == TWI_STATUS_OK){

		// Send EEPROM address with write operation
		TWI_enuWriteData(Local_u8Address);

		// Send memory address within EEPROM
		TWI_enuWriteData(eepromInstance->address);

		// Send repeated start condition
		TWI_enuStartCondition();

		// Send EEPROM address with read operation
		TWI_enuWriteData(Local_u8Address | TWI_ReadOperation);

		// Read data from EEPROM
		TWI_enuReadData(&(eepromInstance->data));

		// Send stop condition
		TWI_enuStopCondition();

    }

    Local_enuErrorState = ERROR_STATUS_OK;
    return Local_enuErrorState;
}



void EEPROM_WriteDataSequence(EEPROM_Input_t* eepromInstance, const uint8_t *dataBuffer, uint8_t dataLength, uint8_t flag, uint8_t startAddress) {
    eepromInstance->address = startAddress;  // Set the EEPROM address to the specified start address

    for(uint8_t i = 0; i < dataLength; i++) {
        eepromInstance->data = dataBuffer[i];
        EEPROM_enuWriteData(eepromInstance);
        eepromInstance->address++;  // Move to the next address
    }

    eepromInstance->data = flag;  // Write the flag to indicate the end of the data
    EEPROM_enuWriteData(eepromInstance);
}

uint8_t EEPROM_SearchForFlag(EEPROM_Input_t eepromInstance, uint8_t flag, uint8_t startAddress, uint8_t dataLength){

    // Set address to start searching from
	eepromInstance.address = startAddress + dataLength;

    // Read the data at the address where the flag is expected
    EEPROM_enuReadData(&eepromInstance);

    // Check if the read data matches the flag
    if (eepromInstance.data == flag) {
        return 1;  // Flag found
    }

    return 0;  // Flag not found

}


void EEPROM_Format(EEPROM_Input_t* eepromInstance) {
    // Define the starting address and the end address
    uint16_t startAddress = 0x00; // Starting address of EEPROM
    uint16_t endAddress = 0xFF;   // Ending address of EEPROM (example)

    // Set the EEPROM address to the start address
    eepromInstance->address = startAddress;

    // Write the default value (e.g., 0x00) to each address in EEPROM
    for (uint16_t address = startAddress; address <= endAddress; address++) {
        eepromInstance->data = 0x00;  // Default value
        EEPROM_enuWriteData(eepromInstance);  // Write to EEPROM
        eepromInstance->address++;  // Move to the next address
    }
}
