#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/TIMER/TIMER_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "HAL/EEPROM/EEPROM_interface.h"
#include "HAL/BUZZER/BUZZER_interface.h"
#include "HAL/LCD/LCD_HAL_interface.h"
#include <util/delay.h>
#include <string.h>

uint8_t System_PasswordChecker(EEPROM_Input_t eepromInstance, uint8_t startAddress, uint8_t flag, uint8_t* pu8dataBuffer, uint8_t dataLength);

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

        switch (Rx_Buffer[0]) {
            case 'S':
                if (EEPROM_SearchForFlag(EEPROM_MAIN, 'X', 0x00, 5)) {
                    UART_enuSendChar('E');
                } else {
                    UART_enuSendChar('N');
                }
                break;
            case 'C':
                UART_enuRecieveString(Rx_Buffer);
                EEPROM_WriteDataSequence(&EEPROM_MAIN, Rx_Buffer, 5, 'X', 0x00);
                UART_enuSendChar('Y');
                break;
            case 'L':
                UART_enuRecieveString(Rx_Buffer);
                if (System_PasswordChecker(EEPROM_MAIN, 0x00, 'X', Rx_Buffer, 5) && u8NO_LoginAtempts != 0) {
                    UART_enuSendChar('R');
                } else if (u8NO_LoginAtempts == 0) {
                    LCD_enuClearDisplay();
                    LCD_u8SendString("LOCKED");
                    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN2, DIO_u8HIGH);
                    _delay_ms(4000);
                    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN2, DIO_u8LOW);
                    LCD_enuClearDisplay();
                    UART_enuSendChar('L');
                    u8NO_LoginAtempts = 3;
                } else {
                    UART_enuSendChar('W');
                    u8NO_LoginAtempts--;
                }
                break;
            case 'R':
                UART_enuRecieveString(Rx_Buffer);
                LCD_u8SendString((char*)Rx_Buffer);
                if (Rx_Buffer[0] == '0' && Rx_Buffer[1] == '0') {
                    UART_enuSendChar('L');
                } else if (Rx_Buffer[0] == '1') {
                    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN3, DIO_u8HIGH);
                    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN4, DIO_u8LOW);
                    UART_enuSendChar('R');
                } else if (Rx_Buffer[0] == '0') {
                    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN3, DIO_u8LOW);
                    DIO_enuSetPinValue(DIO_u8PortB, DIO_u8PIN4, DIO_u8HIGH);
                    UART_enuSendChar('R');
                }
                break;
        }

        memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
    }

    return 0;
}

uint8_t System_PasswordChecker(EEPROM_Input_t eepromInstance, uint8_t startAddress, uint8_t flag, uint8_t* pu8dataBuffer, uint8_t dataLength) {
    eepromInstance.address = startAddress;
    for (uint8_t Local_u8Index = 0; Local_u8Index < dataLength; Local_u8Index++) {
        EEPROM_enuReadData(&eepromInstance);
        if (eepromInstance.data != pu8dataBuffer[Local_u8Index]) {
            return 0;
        }
        eepromInstance.address++;
    }
    return 1;
}
