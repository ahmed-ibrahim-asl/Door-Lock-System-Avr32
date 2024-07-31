 /* main.c
 *
 *  Created on: Jul 29, 2024
 *      Author: ad
 */

/*********** Include  Section ***********/
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "HAL/LCD/LCD_HAL_interface.h"
#include "HAL/KEYPAD/keypad_HAL_interface.h"

#include <util/delay.h>
void Handle_keyInput(uint8_t Copy_u8dataType);

/****************************/

uint8_t Tx_Buffer[5] = {0};
uint8_t Rx_buffer = 0;
uint8_t Global_u8IsLoggedIn = 0;

int main() {
    UART_vidInit(9600);
    LCD_enuInit();

    keypad_enuInit();



	// Telling ECU: Hey, I Am awake
	UART_enuSendChar('S');
	while (1) {
        UART_enuRecieveChar(&Rx_buffer);

        switch(Rx_buffer){
        	case 'Y':
        		LCD_enuClearDisplay();
        		LCD_u8SetPosXY(0, 0);

        		LCD_u8SendString("Enter Password: ");
        		LCD_u8SetPosXY(0, 2);
        		// handle keyInput
        		Handle_keyInput('L');

        	break;
        	case 'N':
        		LCD_u8SendString("Set New Password: ");
        		LCD_u8SetPosXY(0, 2);
        		// handle keyInput
        		Handle_keyInput('C');
        		LCD_enuClearDisplay();

        	break;
        	case 'W':
				LCD_enuClearDisplay();
				LCD_u8SendString("Wrong enter Pass: ");
				LCD_u8SetPosXY(0, 2);

				Handle_keyInput('L');

    		break;
        	case 'R':
        		LCD_enuClearDisplay();
        		LCD_u8SetPosXY(0, 0);
        		Global_u8IsLoggedIn = 1;

        	break;
        	case 'X':
        		Global_u8IsLoggedIn = 0;
        		Rx_buffer = 'Y';
        }




        if(Global_u8IsLoggedIn){
        	/*
        	 *
        	 *
        	 * */
        	LCD_enuClearDisplay();
			LCD_u8SendString("ON: 1 | OFF: 0 ");
			LCD_u8SetPosXY(0, 2);
			Handle_keyInput('R');


        }








    }


    return 0;
}


void Handle_keyInput(uint8_t Copy_u8dataType) {
    uint8_t keyStatus = 0;
    uint8_t padPressedValue = 0;
    uint8_t Local_u8TxIndex = 0;

    while (1) {
        keyStatus = keypad_enuGetPressedKey(&padPressedValue);

        if (keyStatus == 0 && padPressedValue != 0) {
            if (padPressedValue != 'K') {
                switch (Copy_u8dataType) {
                    case 'L':
                    case 'C':
                        if (Local_u8TxIndex < 5) {
                            LCD_enuSendData(padPressedValue);
                            Tx_Buffer[Local_u8TxIndex++] = padPressedValue;
                        }
                        break;


                    case 'R':
                        if (Local_u8TxIndex < 1) {

                        	if(padPressedValue == '7'){
                        		UART_enuSendChar('X');
                        		return;
                        	}

                        	if(padPressedValue == '1' || padPressedValue == '0'){
								LCD_enuSendData(padPressedValue);
								Tx_Buffer[Local_u8TxIndex++] = padPressedValue;
                        	}

                        }
                        break;
                }
            } else {
                Tx_Buffer[Local_u8TxIndex] = '\0';
                UART_enuSendChar(Copy_u8dataType);
                UART_enuSendString(Tx_Buffer);
                memset(Tx_Buffer, 0, sizeof(Tx_Buffer));
                Local_u8TxIndex = 0;
                break;
            }
        }

        while (keyStatus == 0 && padPressedValue != 0) {
            keyStatus = keypad_enuGetPressedKey(&padPressedValue);
        }
    }
}






