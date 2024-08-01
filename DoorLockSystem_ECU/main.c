/*
 * EEPROM_interface.h
 *
 *  Created on: May 28, 2024
 *      Author: ad
 */

// ECU
/*********** Include  Section ***********/

#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/TIMER/TIMER_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "HAL/EEPROM/EEPROM_interface.h"
#include "HAL/BUZZER/BUZZER_interface.h"
#include "HAL/LCD/LCD_HAL_interface.h"
#include <util/delay.h>
/****************************************/


uint8_t System_PasswordChecker(EEPROM_Input_t eepromInstance, uint8_t startAddress, uint8_t flag, uint8_t* pu8dataBuffer ,uint8_t dataLength);



uint8_t Rx_Buffer[5] = {0};

uint8_t u8NO_LoginAtempts = 2;
int main(void) {
    UART_vidInit(9600);
    LCD_enuInit();


    EEPROM_enuInit();
    EEPROM_Input_t EEPROM_MAIN;
    EEPROM_MAIN.A2 = 0;


    DIO_enuSetPinDirection(DIO_u8PortB, DIO_u8PIN3, DIO_u8OUTPUT);
    DIO_enuSetPinDirection(DIO_u8PortB, DIO_u8PIN4, DIO_u8OUTPUT);

    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN3, DIO_u8LOW);
    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN4, DIO_u8LOW);


    DIO_enuSetPinDirection(DIO_u8PortB, DIO_u8PIN2, DIO_u8OUTPUT);
    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN2, DIO_u8LOW);

    EEPROM_Format(&EEPROM_MAIN);

    while (1) {
        UART_enuRecieveChar(Rx_Buffer);


    	switch(Rx_Buffer[0]){
    		case 'S':
            /*
             * 'S' Mode:
             * 		-	HMI is awake,
             * 		-	HIM asks ECU do you have password stored
             *
             * 	if(there dataStored)
             * 		yes: sends -> 'Y'	(then HMI should login	'L')
             * 		No:	 sends -> 'N'	(then HMI should create password	'C')
             *
             * */


                if( EEPROM_SearchForFlag(EEPROM_MAIN, 'X', 0x00, 5) ){
                	//EEPROM is not EMPTY
                	UART_enuSendChar('E');

                }else{

                	UART_enuSendChar('N');

                }


            break;
    		case 'C':
    			UART_enuRecieveString(Rx_Buffer);

    			EEPROM_WriteDataSequence(&EEPROM_MAIN, Rx_Buffer, 5, 'X', 0x00);


            	UART_enuSendChar('L');

            break;
    		case 'L':
    			UART_enuRecieveString(Rx_Buffer);

    			// debug
    			LCD_u8SendString(Rx_Buffer);

				if(System_PasswordChecker(EEPROM_MAIN, 0x00, 'X', Rx_Buffer, 5) && u8NO_LoginAtempts != 0){
					///! system has Logged in		(R- Right)

					UART_enuSendChar('R');



				}else if(u8NO_LoginAtempts == 0){
					//! alarm and system Locked
					LCD_enuClearDisplay();
					LCD_u8SendString("LOCKED");
				    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN2, DIO_u8HIGH);

					_delay_ms(4000);
				    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN2, DIO_u8LOW);

					LCD_enuClearDisplay();

					UART_enuSendChar('L');
					u8NO_LoginAtempts = 3;
				}else{
					// (W - Wrong)
					UART_enuSendChar('W');
					u8NO_LoginAtempts--;

				}


    		break;
    		case 'R':
    			UART_enuRecieveString(Rx_Buffer);

    			LCD_u8SendString((char*)Rx_Buffer);

    			if(Rx_Buffer[0] == '0' && Rx_Buffer[1] == '0'){
    				UART_enuSendChar('L');

    			}else if(Rx_Buffer[0] == '1'){
    				// ON
    				DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN3, DIO_u8HIGH);
    				DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN4, DIO_u8LOW);

    				// TELL the HMI, data is received and i handle it you can send again
    				UART_enuSendChar('R');

    			}else if(Rx_Buffer[0] == '0'){
    				//OFF
    				DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN3, DIO_u8LOW);
    				DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN4, DIO_u8HIGH);

    				// TELL the HMI, data is received and i handle it you can send again
    				UART_enuSendChar('R');


    			}


    		break;
    	}

    }

    return 0;
}

uint8_t System_PasswordChecker(EEPROM_Input_t eepromInstance, uint8_t startAddress, uint8_t flag, uint8_t* pu8dataBuffer, uint8_t dataLength) {
    eepromInstance.address = startAddress;

    for (uint8_t Local_u8Index = 0; Local_u8Index < dataLength; Local_u8Index++) {

    	EEPROM_enuReadData(&eepromInstance);

        if (eepromInstance.data != pu8dataBuffer[Local_u8Index]) {
            return 0;  // Password mismatch
        }

        (eepromInstance.address)++;
    }

    return 1;  // Password match
}
