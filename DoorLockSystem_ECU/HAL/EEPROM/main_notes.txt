/******************** Include Section Start ********************/
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/EEPROM/EEPROM_interface.h"
#include <util/delay.h>
/****************************************************************/

int main() {


	EEPROM_enuInit();
    EEPROM_Input_t EEPROM_1;


    EEPROM_1.A0 = 0;
    EEPROM_1.A1 = 0;
    EEPROM_1.A2 = 0;
    EEPROM_1.address = 0x00;
    EEPROM_1.data = 'Z';

    EEPROM_enuWriteData(&EEPROM_1);
    _delay_ms(10);

    EEPROM_enuReadData(&EEPROM_1);

    DDRA = EEPROM_1.data;

    while (1) {
        // Infinite loop
    }

    return 0;
}
