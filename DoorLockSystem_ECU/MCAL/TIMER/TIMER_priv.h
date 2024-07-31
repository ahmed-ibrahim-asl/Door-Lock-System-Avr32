/*
 * TIMER_priv.h
 *
 *  Created on: Apr 7, 2024
 *      Author: ad
 */

#ifndef MCAL_TIMER_TIMER_PRIV_H_
#define MCAL_TIMER_TIMER_PRIV_H_


/************************ TIMER Registers ************************/
#define TIFR_REG    				*((volatile uint8_t*) (0x58))
#define TIMSK_REG   				*((volatile uint8_t*) (0x59))


#define TCNT0_REG   				*((volatile uint8_t*) (0x52))
#define TCCR0_REG   				*((volatile uint8_t*) (0x53))


#define OCR0_REG					*((volatile uint8_t*) (0x5C))


#define TCNT2_REG					*((volatile uint8_t*) (0x44))
#define TCCR2_REG					*((volatile uint8_t*) (0x45))
#define OCR2_REG					*((volatile uint8_t*) (0x43))



#define TCCR1A_REG					*((volatile uint8_t*) (0x4F))
#define TCCR1B_REG					*((volatile uint8_t*) (0x4E))

#define TCNT1_REG					*((volatile uint16_t*)(0x4C))
#define OCR1A_REG					*((volatile uint16_t*)(0x4A))
#define OCR1B_REG					*((volatile uint16_t*)(0x48))
#define WDTCSR_REG 				    *((volatile uint8_t*) (0x41))

/*****************************************************************/


/************************** TCCR0 BITS ***************************/
#define TCCR0_CS00							0
#define TCCR0_CS01							1
#define TCCR0_CS02							2
#define TCCR0_WGM01							3
#define TCCR0_COM00							4
#define TCCR0_COM01							5
#define TCCR0_WGM00							6
#define TCCR0_FOC0							7
/*****************************************************************/



/*************************** TCCR1A BITS *************************/
#define TCCR1A_WGM10						0
#define TCCR1A_WGM11						1
#define TCCR1A_FOC1B						2
#define TCCR1A_FOC1A						3
#define TCCR1A_COM1B0						4
#define TCCR1A_COM1B1						5
#define TCCR1A_COM1A0						6
#define TCCR1A_COM1A1						7
/*****************************************************************/



/*************************** TCCR1B BITS *************************/
#define TCCR1B_CS10							0
#define TCCR1B_CS11							1
#define TCCR1B_CS12							2
#define TCCR1B_WGM12						3
#define TCCR1B_WGM13						4

#define TCCR1B_ICES1						6
#define TCCR1B_ICNC1						7
/*****************************************************************/



/*************************** TCCR2 BITS **************************/
#define TCCR2_CS20							0
#define TCCR2_CS21							1
#define TCCR2_CS22							2
#define TCCR2_WGM21							3
#define TCCR2_COM20							4
#define TCCR2_COM21							5
#define TCCR2_WGM20							6
#define TCCR2_FOC2							7
/*****************************************************************/



/************************** TIMSK BITS ***************************/
#define TIMSK_TOIE0							0
#define TIMSK_OCIE0							1
#define TIMSK_TOIE1							2
#define TIMSK_OCIE1B						3
#define TIMSK_OCIE1A						4
#define TIMSK_TICIE1						5
#define TIMSK_TOIE2							6
#define TIMSK_OCIE2							7
/*****************************************************************/





/************************ Timer Modes ****************************/
#define TIMER_MODE_NORMALovf               0
#define TIMER_MODE_PWMphasecorrect         1
#define TIMER_MODE_CTC                     2
#define TIMER_MODE_FastPWM                 3
/*****************************************************************/



/***************** Output Compare Modes for OC0 ******************/
#define TIMER_NORMAL_OC0                   4
#define TIMER_SET_OC0                      5
#define TIMER_CLR_OC0                      6
#define TIMER_TOGGLE_OC0                   7
/*****************************************************************/



/************************* Fast PWM Modes ************************/
#define TIMER_FastPwmType_Inverted         8
#define TIMER_FastPwmType_NonInverted      9
/*****************************************************************/



/******************** Phase Correct PWM Modes ********************/
#define TIMER_PhaseCorrect_Inverted        10
#define TIMER_PhaseCorrect_NonInverted     11
/*****************************************************************/



/*********************** Timer1 PWM Modes ************************/
#define TIMER1_MODE_FastPWM_8bit           12
#define TIMER1_MODE_FastPWM_9bit           13
#define TIMER1_MODE_FastPWM_10bit          14
#define TIMER1_MODE_FastPWM_16bit          15

#define TIMER1_MODE_PWMphasecorrect_8bit   16
#define TIMER1_MODE_PWMphasecorrect_9bit   17
#define TIMER1_MODE_PWMphasecorrect_10bit  18
#define TIMER1_MODE_PWMphasecorrect_16bit  19

#define TIMER1_MODE_PhaseFreqCorrect       20


#define TIMER1_OC1_OUTPUT_ENABLE		   21
#define TIMER1_OC1_OUTPUT_DISABLE		   22
/*****************************************************************/



/***************** Output Compare Modes for OC2 ******************/
#define TIMER_NORMAL_OC2                   23
#define TIMER_SET_OC2                      24
#define TIMER_CLR_OC2                      25
#define TIMER_TOGGLE_OC2                   26
/*****************************************************************/



/***************** Output Compare Modes for OC1A *****************/
#define TIMER_NORMAL_OC1A                  27
#define TIMER_SET_OC1A                     28
#define TIMER_CLR_OC1A                     29
#define TIMER_TOGGLE_OC1A                  30
/*****************************************************************/



/***************** Output Compare Modes for OC1B *****************/
#define TIMER_NORMAL_OC1B                  31
#define TIMER_SET_OC1B                     32
#define TIMER_CLR_OC1B                     33
#define TIMER_TOGGLE_OC1B                  34
/*****************************************************************/



/******************** Timer Prescaler Values *********************/
#define TIMER_PRES_01                      35
#define TIMER_PRES_08                      36
#define TIMER_PRES_32                      37
#define TIMER_PRES_64                      38
#define TIMER_PRES_128                     39
#define TIMER_PRES_256                     40
#define TIMER_PRES_1024                    41
/*****************************************************************/



/******************** Output Control States  *********************/
#define TIMER0_OC0_OUTPUT_ENABLE           42
#define TIMER0_OC0_OUTPUT_DISABLE          43

#define TIMER2_OC2_OUTPUT_ENABLE           44
#define TIMER2_OC2_OUTPUT_DISABLE          45
/*****************************************************************/

#endif /* MCAL_TIMER_TIMER_PRIV_H_ */
