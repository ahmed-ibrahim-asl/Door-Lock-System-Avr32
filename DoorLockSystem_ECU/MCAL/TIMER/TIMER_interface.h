/*
 * TIMER_interface.h
 *
 *  Created on: Apr 7, 2024
 *      Author: ad
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

/****************************************** TIMER0 INTERFACE ******************************************/
void TIMER0_voidInit(void);
void TIMER0_voidStart(void);
void TIMER0_voidStop(void);
void TIMER0_voidSetPWM(uint8_t copy_u8DutyCycle);

void TIMER0_voidOutputPWM(uint8_t Copy_u8DutyCycle, uint8_t Copy_u8PortID, uint8_t Copy_u8PinID);
uint8_t TIMER0_voidScheduleTask( void (*TaskCallback)(void), float64 copy_f64RequiredTime_inSeconds);
/******************************************************************************************************/



/****************************************** TIMER1 INTERFACE ******************************************/
void TIMER1_voidInit(void);
void TIMER1_voidStart(void);
void TIMER1_voidStop(void);

// Function for setting PWM in non-16bit modes
void TIMER1_voidSetPWM(uint8_t duty_cycle_percent);

// Function for setting PWM in 16bit modes with frequency control
void TIMER1_voidSetPWM_16bit(uint8_t duty_cycle_percent, uint32_t frequency);


uint8_t TIMER1_voidScheduleTask( void (*TaskCallback)(void), float64 copy_f64RequiredTime_inSeconds);
/******************************************************************************************************/



/****************************************** TIMER2 INTERFACE ******************************************/
void TIMER2_voidInit(void);
void TIMER2_voidStart(void);
void TIMER2_voidStop(void);
void TIMER2_voidSetPWM(uint8_t copy_u8DutyCycle);


uint8_t TIMER2_voidScheduleTask( void (*TaskCallback)(void), float64 copy_f64RequiredTime_inSeconds);
/******************************************************************************************************/



/****************************************** WATCH DOG TIMER INTERFACE ******************************************/
void TIMER_voidWDTSleep(uint8_t copy_u8WdtPeriod);
void TIMER_voidWDTEnable (void);
void TIMER_voidWDTDisable(void);
#define WDT_voidRestart() 												asm("WDR")
/******************************************************************************************************/


/******************** Watchdog Timer Control *********************/
#define WDTCSR_WDP0                     0
#define WDTCSR_WDP1                     1
#define WDTCSR_WDP2                     2
#define WDTCSR_WDE                      3
#define WDTCSR_WDCE                     4
#define WDTCSR_WDP3                     5
#define WDTCSR_WDIE                     6
#define WDTCSR_WDIF                     7

// Watchdog Timer Prescaler Values
#define WDT_PRESCALER_16MS              0x00
#define WDT_PRESCALER_32MS              0x01
#define WDT_PRESCALER_64MS              0x02
#define WDT_PRESCALER_125MS             0x03
#define WDT_PRESCALER_250MS             0x04
#define WDT_PRESCALER_500MS             0x05
#define WDT_PRESCALER_1S                0x06
#define WDT_PRESCALER_2S                0x07
#define WDT_PRESCALER_4S                0x08
#define WDT_PRESCALER_8S                0x09
/*****************************************************************/



#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
