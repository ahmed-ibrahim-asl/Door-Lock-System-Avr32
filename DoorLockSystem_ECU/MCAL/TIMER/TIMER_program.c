/*
 * TIMER_program.c
 *
 *  Created on: Apr 7, 2024
 *      Author: ad
 */




/******************************************* Include  Section *******************************************/
#include "../DIO/helper_embedded_libraries/micro_config.h"
#include "../DIO/DIO_interface.h"
#include "TIMER_config.h"
#include "TIMER_priv.h"
#include "TIMER_interface.h"
#include "../GIE/GIE_interface.h"
#include "../EXTI/EXTI_interface.h"
#include <avr/interrupt.h>
/********************************************************************************************************/





/******************************** Timer Tick Counters and ISR Handlers ********************************/

// Global tick count targets for each timer
static uint32_t TIMER0_TARGET_NTICKS;  // Target ticks for TIMER0
static uint32_t TIMER1_TARGET_NTICKS;  // Target ticks for TIMER1
static uint32_t TIMER2_TARGET_NTICKS;  // Target ticks for TIMER2


// Define counters for each timer to track the number of overflows
static uint32_t TIMER0_CURRENT_NTICKS = 0;  // Current overflow count for TIMER0
static uint32_t TIMER1_CURRENT_NTICKS = 0;  // Current overflow count for TIMER1
static uint32_t TIMER2_CURRENT_NTICKS = 0;  // Current overflow count for TIMER2
//

// Array of function pointers for Timer ISR callbacks
static void (*TIMERS_ISR_Functions[3])(void) = {NULL, NULL, NULL};


/*******************************************************************************************************/



/****************************************** TIMER0 FUNCTIONS ******************************************/
void TIMER0_voidInit(void){


	/*
	 * 1. Set Timter Mode (Normal - PWM phase correct - Fast PWM)
	 * 	  	For CTC MODE:
	 * 	  		- set compare output mode (toggle - clear - set)
	 *
	 * 2. set clock
	 *
	 * 3. Enable Interrupt (Compre Match Interrupt - OverFlow Interrupt)
	 *
	 * */

	/** Active global interrupt **/
	GIE_enuEnable();

	/**1. Set Timer Mode **/
	#if(TIMER0_MODE_SELECT == TIMER_MODE_NORMALovf)
		SET_BIT(TCCR0_REG, TCCR0_WGM01);
		SET_BIT(TCCR0_REG, TCCR0_WGM00);

	#elif(TIMER0_MODE_SELECT == TIMER_MODE_CTC)
		CLR_BIT(TCCR0_REG, TCCR0_WGM00);
		SET_BIT(TCCR0_REG, TCCR0_WGM01);

		/** Set compare output mode **/

		#if(TIMER0_OC0_OUTPUT_STATE == TIMER0_OC0_OUTPUT_ENABLE)
		DIO_enuSetPinDirection(TIMER_OC0_PORT, TIMER_OC0_PIN, DIO_u8OUTPUT);

			#if(TIMER_OC0_OUTPUT_MODE == TIMER_SET_OC0)
				SET_BIT(TCCR0_REG, TCCR0_COM00);
				SET_BIT(TCCR0_REG, TCCR0_COM01);

			#elif(TIMER_OC0_OUTPUT_MODE == TIMER_CLR_OC0)
				CLR_BIT(TCCR0_REG, TCCR0_COM00);
				SET_BIT(TCCR0_REG, TCCR0_COM01);

			#elif(TIMER_OC0_OUTPUT_MODE == TIMER_TOGGLE_OC0)
				SET_BIT(TCCR0_REG, TCCR0_COM00);
				CLR_BIT(TCCR0_REG, TCCR0_COM01);


			#elif(TIMER_OC0_OUTPUT_MODE == TIMER_NORMAL_OC0)
				CLR_BIT(TCCR0_REG, TCCR0_COM00);
				CLR_BIT(TCCR0_REG, TCCR0_COM01);
			#endif
		#endif


	#elif(TIMER0_MODE_SELECT == TIMER_MODE_FastPWM)
		SET_BIT(TCCR0_REG, TCCR0_WGM00);
		SET_BIT(TCCR0_REG, TCCR0_WGM01);

		#if(TIMER0_FastPwm_Type == TIMER_FastPwmType_Inverted)
			CLR_BIT(TCCR0_REG, TCCR0_COM00);
			SET_BIT(TCCR0_REG, TCCR0_COM01);

		#elif(TIMER0_FastPwm_Type == TIMER_FastPwmType_NonInverted)
			SET_BIT(TCCR0_REG, TCCR0_COM00);
			SET_BIT(TCCR0_REG, TCCR0_COM01);

		#endif

		// By default, OC0 pin is default output pin for Timer0's PWM signal
		DIO_enuSetPinDirection(TIMER_OC0_PORT, TIMER_OC0_PIN, DIO_u8OUTPUT);

	#elif(TIMER0_MODE_SELECT == TIMER_MODE_PWMphasecorrect)
		SET_BIT(TCCR0_REG, TCCR0_WGM00);
		CLR_BIT(TCCR0_REG, TCCR0_WGM01);

		#if(TIMER0_PhaseCorrect_Type == TIMER_PhaseCorrect_Inverted)
			SET_BIT(TCCR0_REG, TCCR0_COM01);
			CLR_BIT(TCCR0_REG, TCCR0_COM00);


		#elif(TIMER0_PhaseCorrect_Type == TIMER_PhaseCorrect_NonInverted)
			SET_BIT(TCCR0_REG, TCCR0_COM01);
			SET_BIT(TCCR0_REG, TCCR0_COM00);


		#endif

		// By default, OC0 pin is default output pin for Timer0's PWM signal
		DIO_enuSetPinDirection(TIMER_OC0_PORT, TIMER_OC0_PIN, DIO_u8OUTPUT);


	#endif



	/**2. Set Prescaller clock **/
	#if(TIMER0_CLK_PRE_SELECT == TIMER_PRES_01)
		SET_BIT(TCCR0_REG, TCCR0_CS00);
		CLR_BIT(TCCR0_REG, TCCR0_CS01);
		CLR_BIT(TCCR0_REG, TCCR0_CS02);

	#elif(TIMER0_CLK_PRE_SELECT == TIMER_PRES_08)
		CLR_BIT(TCCR0_REG, TCCR0_CS00);
		SET_BIT(TCCR0_REG, TCCR0_CS01);
		CLR_BIT(TCCR0_REG, TCCR0_CS02);

	#elif(TIMER0_CLK_PRE_SELECT == TIMER_PRES_64)
		SET_BIT(TCCR0_REG, TCCR0_CS00);
		SET_BIT(TCCR0_REG, TCCR0_CS01);
		CLR_BIT(TCCR0_REG, TCCR0_CS02);

	#elif(TIMER0_CLK_PRE_SELECT == TIMER_PRES_256)
		CLR_BIT(TCCR0_REG, TCCR0_CS00);
		CLR_BIT(TCCR0_REG, TCCR0_CS01);
		SET_BIT(TCCR0_REG, TCCR0_CS02);

	#elif(TIMER0_CLK_PRE_SELECT == TIMER_PRES_1024)
		SET_BIT(TCCR0_REG, TCCR0_CS00);
		CLR_BIT(TCCR0_REG, TCCR0_CS01);
		SET_BIT(TCCR0_REG, TCCR0_CS02);
	#endif
}

void TIMER0_voidStart(void){
		#if(TIMER0_MODE_SELECT == TIMER_MODE_NORMALovf)
			SET_BIT(TIMSK_REG, TIMSK_TOIE0);

		#elif(TIMER0_MODE_SELECT == TIMER_MODE_CTC)
			SET_BIT(TIMSK_REG, TIMSK_OCIE0);

		#endif
}

void TIMER0_voidStop(void){
		#if(TIMER0_MODE_SELECT == TIMER_MODE_NORMALovf)
			CLR_BIT(TIMSK_REG, TIMSK_TOIE0);

		#elif(TIMER0_MODE_SELECT == TIMER_MODE_CTC)
			CLR_BIT(TIMSK_REG, TIMSK_OCIE0);

		#endif
}

uint8_t TIMER0_voidScheduleTask( void (*TaskCallback)(void), float64 copy_f64RequiredTime_inSeconds){

	uint32_t Local_u32PrescalerValue = 0;

	switch(TCCR0_REG & 0x07){
		case 0x01: Local_u32PrescalerValue = 1; break;
		case 0x02: Local_u32PrescalerValue = 8; break;
		case 0x03: Local_u32PrescalerValue = 64; break;
		case 0x04: Local_u32PrescalerValue = 256; break;
		case 0x05: Local_u32PrescalerValue = 1024; break;
	}

	float64 Local_f64Totalticks = (copy_f64RequiredTime_inSeconds * F_CPU)/Local_u32PrescalerValue;

	#if(TIMER0_MODE_SELECT == TIMER_MODE_NORMALovf)




		/**
		 *  fmod - function similar to modulus operator but designed to work
		 *  with floating point numbers, not just integers. it computes the
		 *  remainder of the diviion of one floating-point number by another.
		 * */

		if( (fmod(Local_f64Totalticks, 1.00) == 0.0)  &&  fmod(Local_f64Totalticks, 256.0) == 0.0){
			TIMER0_TARGET_NTICKS = (uint32_t)(Local_f64Totalticks/256);
		}else{
			// It's floating Number, setting preload value

			TCNT0_REG = 256 - (uint32_t)(fmod(Local_f64Totalticks, 256.0));

			TIMER0_TARGET_NTICKS = (uint32_t)ceil(Local_f64Totalticks/256);
		}




	#elif(TIMER0_MODE_SELECT == TIMER_MODE_CTC)


		if(Local_f64Totalticks > 255){
			OCR0_REG = 255;
	        TIMER0_TARGET_NTICKS = ceil((double)Local_f64Totalticks / 255.0); // How many times timer should reach 255

		}else{
			OCR0_REG = Local_f64Totalticks-1;
			TIMER0_TARGET_NTICKS  = 1;
		}

	#endif


		TIMERS_ISR_Functions[0] = TaskCallback;
		TIMER0_voidStart();
	return 0;
}

void  TIMER0_voidSetPWM(uint8_t copy_u8DutyCycle){



	/*
	 *
	 * It's more recommened to pass an integer number to OCR0 register
	 * avoids reliance on floating point hardware support wich is absent in many
	 * avr micrcontrollersings using floating-point arithmetic can
	 * consume significantly more CPU cycles due to software emulation,
	 * leading to potential inaccuracies in time-sensitive applications such
	 * as PWM signal generation.
	 *
	 *
	 * Avr32 does has floating point operation
	 * **/


	OCR0_REG = (uint8_t)(((uint16_t)copy_u8DutyCycle * 256) / 100);
}





/******************************************************************************************************/


/****************************************** TIMER1 FUNCTIONS ******************************************/

void TIMER1_voidInit(void) {
	/**
	 * TODO:
	 *
	 */


	/** Active global interrupt **/
	GIE_enuEnable();

	/**1. Set Timer Mode **/
	#if(TIMER1_MODE_SELECT == TIMER_MODE_NORMALovf)
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM10);
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM12);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM13);

	#elif(TIMER1_MODE_SELECT == TIMER_MODE_CTC)
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM10);
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM11);
		SET_BIT(TCCR1B_REG, TCCR1B_WGM12);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM13);


		/** Set compare output mode **/
		#if(TIMER1_OC1_OUTPUT_STATE == TIMER1_OC1_OUTPUT_ENABLE)

			#if(TIMER1_OC1A_OUTPUT_STATE == TIMER1_OC1_OUTPUT_ENABLE)
				DIO_enuSetPinDirection(TIMER_OC1A_PORT, TIMER_OC1A_PIN, DIO_u8OUTPUT);
			#endif

			#if(TIMER1_OC1A_OUTPUT_STATE == TIMER1_OC1_OUTPUT_ENABLE)
				DIO_enuSetPinDirection(TIMER_OC1B_PORT, TIMER_OC1B_PIN, DIO_u8OUTPUT);
			#endif


			#if(TIMER_OC1A_OUTPUT_MODE   == TIMER_NORMAL_OC1A)
				CLR_BIT(TCCR1A_REG, TCCR1A_COM1A0);
				CLR_BIT(TCCR1A_REG, TCCR1A_COM1A1);

			#elif(TIMER_OC1A_OUTPUT_MODE == TIMER_SET_OC1A)
				SET_BIT(TCCR1A_REG, TCCR1A_COM1A0);
				SET_BIT(TCCR1A_REG, TCCR1A_COM1A1);

			#elif(TIMER_OC1A_OUTPUT_MODE == TIMER_CLR_OC1A)
				CLR_BIT(TCCR1A_REG, TCCR1A_COM1A0);
				SET_BIT(TCCR1A_REG, TCCR1A_COM1A1);

			#elif(TIMER_OC1A_OUTPUT_MODE == TIMER_TOGGLE_OC1A)
				SET_BIT(TCCR1A_REG, TCCR1A_COM1A0);
				CLR_BIT(TCCR1A_REG, TCCR1A_COM1A1);

			#endif



			#if(TIMER_OC1B_OUTPUT_MODE   == TIMER_NORMAL_OC1B)
				CLR_BIT(TCCR1A_REG, TCCR1A_COM1B0);
				CLR_BIT(TCCR1A_REG, TCCR1A_COM1B1);

			#elif(TIMER_OC1B_OUTPUT_MODE == TIMER_SET_OC1B)
				SET_BIT(TCCR1A_REG, TCCR1A_COM1B0);
				SET_BIT(TCCR1A_REG, TCCR1A_COM1B1);

			#elif(TIMER_OC1A_OUTPUT_MODE == TIMER_CLR_OC1A)
				CLR_BIT(TCCR1A_REG, TCCR1A_COM1B0);
				SET_BIT(TCCR1A_REG, TCCR1A_COM1B1);

			#elif(TIMER_OC1A_OUTPUT_MODE == TIMER_TOGGLE_OC1A)
				SET_BIT(TCCR1A_REG, TCCR1A_COM1B0);
				CLR_BIT(TCCR1A_REG, TCCR1A_COM1B1);

			#endif

		#endif
	#endif

/************************							************************/

	#if(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_8bit)
		SET_BIT(TCCR1A_REG, TCCR1A_WGM10);
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM11);

		SET_BIT(TCCR1B_REG, TCCR1B_WGM12);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM13);


	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_9bit)
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM10);
		SET_BIT(TCCR1A_REG, TCCR1A_WGM11);

		SET_BIT(TCCR1B_REG, TCCR1B_WGM12);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM13);

	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_10bit)
		SET_BIT(TCCR1A_REG, TCCR1A_WGM10);
		SET_BIT(TCCR1A_REG, TCCR1A_WGM11);

		SET_BIT(TCCR1B_REG, TCCR1B_WGM12);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM13);

	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_16bit)
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM10);
		SET_BIT(TCCR1A_REG, TCCR1A_WGM11);

		SET_BIT(TCCR1B_REG, TCCR1B_WGM12);
		SET_BIT(TCCR1B_REG, TCCR1B_WGM13);


	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_8bit)
		SET_BIT(TCCR1A_REG, TCCR1A_WGM10);
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM11);

		CLR_BIT(TCCR1B_REG, TCCR1B_WGM12);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM13);


	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_9bit)
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM10);
		SET_BIT(TCCR1A_REG, TCCR1A_WGM11);

		CLR_BIT(TCCR1B_REG, TCCR1B_WGM12);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM13);


	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_10bit)
		SET_BIT(TCCR1A_REG, TCCR1A_WGM10);
		SET_BIT(TCCR1A_REG, TCCR1A_WGM11);

		CLR_BIT(TCCR1B_REG, TCCR1B_WGM12);
		CLR_BIT(TCCR1B_REG, TCCR1B_WGM13);


	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_16bit)
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM10);
		SET_BIT(TCCR1A_REG, TCCR1A_WGM11);

		CLR_BIT(TCCR1B_REG, TCCR1B_WGM12);
		SET_BIT(TCCR1B_REG, TCCR1B_WGM13);

	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_PhaseFreqCorrect)
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM10);
		CLR_BIT(TCCR1A_REG, TCCR1A_WGM11);

		CLR_BIT(TCCR1B_REG, TCCR1B_WGM12);
		SET_BIT(TCCR1B_REG, TCCR1B_WGM13);

		#endif

/************************			Inverted/ non-inverted/ normal / toggle		************************/
	#if(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_8bit || \
		TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_9bit || \
		TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_10bit || \
		TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_16bit)




		#if(TIMER1_FastPwm_Type_OC1A == TIMER_FastPwmType_Inverted)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1A0);
			SET_BIT(TCCR1A_REG, TCCR1A_COM1A1);

		#elif(TIMER1_FastPwm_Type_OC1A == TIMER_FastPwmType_NonInverted)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1A0);
			SET_BIT(TCCR1A_REG, TCCR1A_COM1A1);

		#elif(TIMER1_FastPwm_Type_OC1A == TIMER_FastPwmType_Normal)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1A0);
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1A1);
		#endif

		#if(TIMER1_FastPwm_Type_OC1B == TIMER_FastPwmType_Inverted)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1B0);
			SET_BIT(TCCR1A_REG, TCCR1A_COM1B1);

		#elif(TIMER1_FastPwm_Type_OC1B == TIMER_FastPwmType_NonInverted)
			SET_BIT(TCCR1A_REG, TCCR1A_COM1B0);
			SET_BIT(TCCR1A_REG, TCCR1A_COM1B1);


		#elif(TIMER1_FastPwm_Type_OC1B == TIMER_FastPwmType_Normal)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1B0);
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1B1);

		#endif



	#elif(TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_8bit || \
			TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_9bit || \
			TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_10bit || \
			TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_16bit || \
			TIMER1_MODE_SELECT == TIMER1_MODE_PhaseFreqCorrect)


		#if(TIMER1_PhaseCorrect_Type_OC1A == TIMER_PhaseCorrect_Inverted)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1A0);
			SET_BIT(TCCR1A_REG, TCCR1A_COM1A1);

		#elif(TIMER1_PhaseCorrect_Type_OC1A == TIMER_PhaseCorrect_NonInverted)
			SET_BIT(TCCR1A_REG, TCCR1A_COM1A0);
			SET_BIT(TCCR1A_REG, TCCR1A_COM1A1);

		#elif(TIMER1_PhaseCorrect_Type_OC1A == TIMER_PhaseCorrect_Normal)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1A0);
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1A1);
		#endif

		#if(TIMER1_PhaseCorrect_Type_OC1B == TIMER_PhaseCorrect_Inverted)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1B0);
			SET_BIT(TCCR1A_REG, TCCR1A_COM1B1);

		#elif(TIMER1_PhaseCorrect_Type_OC1B == TIMER_PhaseCorrect_NonInverted)
			SET_BIT(TCCR1A_REG, TCCR1A_COM1B0);
			SET_BIT(TCCR1A_REG, TCCR1A_COM1B1);


		#elif(TIMER1_PhaseCorrect_Type_OC1B == TIMER_PhaseCorrect_Normal)
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1B0);
			CLR_BIT(TCCR1A_REG, TCCR1A_COM1B1);

		#endif


	#endif




/***************************************************************************/
	/**2. Set Prescaller clock **/
	#if(TIMER1_CLK_PRE_SELECT == TIMER_PRES_01)
		SET_BIT(TCCR1B_REG, TCCR1B_CS10);
		CLR_BIT(TCCR1B_REG, TCCR1B_CS11);
		CLR_BIT(TCCR1B_REG, TCCR1B_CS12);

	#elif(TIMER1_CLK_PRE_SELECT == TIMER_PRES_08)
		CLR_BIT(TCCR1B_REG, TCCR1B_CS10);
		SET_BIT(TCCR1B_REG, TCCR1B_CS11);
		CLR_BIT(TCCR1B_REG, TCCR1B_CS12);

	#elif(TIMER1_CLK_PRE_SELECT == TIMER_PRES_64)
		SET_BIT(TCCR1B_REG, TCCR1B_CS10);
		SET_BIT(TCCR1B_REG, TCCR1B_CS11);
		CLR_BIT(TCCR1B_REG, TCCR1B_CS12);

	#elif(TIMER1_CLK_PRE_SELECT == TIMER_PRES_256)
		CLR_BIT(TCCR1B_REG, TCCR1B_CS10);
		CLR_BIT(TCCR1B_REG, TCCR1B_CS11);
		SET_BIT(TCCR1B_REG, TCCR1B_CS12);


	#elif(TIMER1_CLK_PRE_SELECT == TIMER_PRES_1024)
		SET_BIT(TCCR1B_REG, TCCR1B_CS10);
		CLR_BIT(TCCR1B_REG, TCCR1B_CS11);
		SET_BIT(TCCR1B_REG, TCCR1B_CS12);
	#endif
}


void TIMER1_voidStart(void) {
    #if(TIMER1_MODE_SELECT == TIMER_MODE_NORMALovf)
        SET_BIT(TIMSK_REG, TIMSK_TOIE1);

    #elif(TIMER1_MODE_SELECT == TIMER_MODE_CTC)
        SET_BIT(TIMSK_REG, TIMSK_OCIE1A);

    #elif(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_8bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_9bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_10bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_16bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_8bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_9bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_10bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_16bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PhaseFreqCorrect)
        SET_BIT(TIMSK_REG, TIMSK_OCIE1A);

    #endif
}


void TIMER1_voidStop(void) {
    #if(TIMER1_MODE_SELECT == TIMER_MODE_NORMALovf)
        CLR_BIT(TIMSK_REG, TIMSK_TOIE1);

    #elif(TIMER1_MODE_SELECT == TIMER_MODE_CTC)
        CLR_BIT(TIMSK_REG, TIMSK_OCIE1A);

    #elif(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_8bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_9bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_10bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_16bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_8bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_9bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_10bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_16bit || \
          TIMER1_MODE_SELECT == TIMER1_MODE_PhaseFreqCorrect)
        CLR_BIT(TIMSK_REG, TIMSK_OCIE1A);

    #endif
}

uint8_t TIMER1_voidScheduleTask(void (*TaskCallback)(void), float64 copy_f64RequiredTime_inSeconds) {
    uint32_t Local_u32PrescalerValue = 0;

    switch(TCCR1B & 0x07) {
        case 0x01: Local_u32PrescalerValue = 1; break;
        case 0x02: Local_u32PrescalerValue = 8; break;
        case 0x03: Local_u32PrescalerValue = 64; break;
        case 0x04: Local_u32PrescalerValue = 256; break;
        case 0x05: Local_u32PrescalerValue = 1024; break;
        default: return 1; // Invalid prescaler setting
    }

    float64 Local_f64Totalticks = (copy_f64RequiredTime_inSeconds * F_CPU) / Local_u32PrescalerValue;

    #if (TIMER1_MODE_SELECT == TIMER_MODE_NORMALovf)
        if (Local_f64Totalticks <= 65536.0) {
            TCNT1 = 65536 - (uint16_t)Local_f64Totalticks;
            TIMER1_TARGET_NTICKS = 1;
        } else {
            TCNT1 = 0;
            TIMER1_TARGET_NTICKS = (uint32_t)(Local_f64Totalticks / 65536.0);
        }
    #elif (TIMER1_MODE_SELECT == TIMER_MODE_CTC)
        if (Local_f64Totalticks <= 65535.0) {
            OCR1A = (uint16_t)Local_f64Totalticks;
            TIMER1_TARGET_NTICKS = 1;
        } else {
            OCR1A = 65535;
            TIMER1_TARGET_NTICKS = (uint32_t)(Local_f64Totalticks / 65535.0);
        }
    #endif

    TIMER1_CURRENT_NTICKS = 0;
    TIMERS_ISR_Functions[1] = TaskCallback;
    TIMER1_voidStart();
    return 0;
}


void TIMER1_voidSetPWM(uint8_t copy_u8DutyCycle) {

		uint16_t Local_u16TopValue = 0;

		#if(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_8bit || \
			TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_8bit)
			Local_u16TopValue = 0x00FF;   // 8-bit resolution

		#elif(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_9bit || \
			TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_9bit)
			Local_u16TopValue = 0x01FF;  // 9-bit resolution

		#elif(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_10bit || \
			TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_10bit)
			Local_u16TopValue = 0x03FF;  // 10-bit resolution


		#elif(TIMER1_MODE_SELECT == TIMER1_MODE_PhaseFreqCorrect)
			// Ensure ICR1 is already set correctly during initialization
			Local_u16TopValue = ICR1;  // ICR1 for Phase and Frequency Correct

		#endif

		OCR1A_REG = (uint16_t)(((uint32_t)copy_u8DutyCycle * Local_u16TopValue) / 100);

}

void TIMER1_voidSetPWM_16bit(uint8_t copy_u8DutyCycle, uint32_t copy_u8Frequency){
	uint32_t Local_u32PrescalerValue = 0;
	switch (TCCR1B_REG & 0x07) {
		case 0x01: Local_u32PrescalerValue = 1; break;
		case 0x02: Local_u32PrescalerValue = 8; break;
		case 0x03: Local_u32PrescalerValue = 64; break;
		case 0x04: Local_u32PrescalerValue = 256; break;
		case 0x05: Local_u32PrescalerValue = 1024; break;
		default: Local_u32PrescalerValue = 8; // Default to prescaler 8
	}

	// Calculate TOP value based on desired frequency for Fast PWM or Phase and Frequency Correct PWM
	ICR1 = (F_CPU / (Local_u32PrescalerValue * copy_u8Frequency)) - 1;

	// Calculate OCR1A value based on desired duty cycle percentage
	OCR1A_REG = (uint16_t) (((uint32_t)copy_u8DutyCycle * ICR1) / 100);

}

/******************************************************************************************************/


/****************************************** TIMER2 FUNCTIONS ******************************************/
void TIMER2_voidInit(void){
	/**
	 * TODO:
	 *  1. Specify opearting mode (Normal - PWM - CTC - Fast PWM)
	 *
	 *  	Incase of choosing CTC Mode
	 *  	. CTC output mode (Toggle - Clear - Set )
	 *
	 *
	 *		Incase of choosing Fast PWM Mode
	 *		. modes(normal - reversed clear on compare match - set)
	 *
	 *
	 *		Incase of choosing Phase Correct PWM Mode
	 *		. modes(Normal - Reversed - clear on compare - set on compare)
	 *
	 *
	 *	2. Set Prescaler Value
	 *
	 *
	 *	3. ⚠{Asynchrounous is not addressed yet}
	 *
	 *	4. Turn Global Interrupt ON
	 *
	 * */


	/**************************** Set  mode for TIMER2 ****************************/
	#if(TIMER2_MODE_SELECT == TIMER_MODE_NORMALovf)
		CLR_BIT(TCCR2_REG, TCCR2_WGM20);
		CLR_BIT(TCCR2_REG, TCCR2_WGM21);

	#elif(TIMER2_MODE_SELECT == TIMER_MODE_CTC)

		CLR_BIT(TCCR2_REG, TCCR2_WGM20);
		SET_BIT(TCCR2_REG, TCCR2_WGM21);


		#if(TIMER2_OC2_OUTPUT_STATE == TIMER2_OC2_OUTPUT_ENABLE)
		DIO_enuSetPinDirection(TIMER_OC2_PORT, TIMER_OC2_PIN, DIO_u8OUTPUT);

			#if(TIMER_OC2_OUTPUT_MODE == TIMER_TOGGLE_OC2)
				SET_BIT(TCCR2_REG, TCCR2_COM20);
				CLR_BIT(TCCR2_REG, TCCR2_COM21);

			#elif(TIMER_OC2_OUTPUT_MODE == TIMER_SET_OC2)
				SET_BIT(TCCR2_REG, TCCR2_COM20);
				SET_BIT(TCCR2_REG, TCCR2_COM21);

			#elif(TIMER_OC2_OUTPUT_MODE == TIMER_CLR_OC2)
				CLR_BIT(TCCR2_REG, TCCR2_COM20);
				SET_BIT(TCCR2_REG, TCCR2_COM21);

			#elif(TIMER_OC2_OUTPUT_MODE == TIMER_NORMAL_OC2)
				CLR_BIT(TCCR2_REG, TCCR2_COM20);
				CLR_BIT(TCCR2_REG, TCCR2_COM21);

			#endif

		#endif

	#elif(TIMER2_MODE_SELECT == TIMER_MODE_FastPWM)
		SET_BIT(TCCR2_REG, TCCR2_WGM20);
		SET_BIT(TCCR2_REG, TCCR2_WGM21);

		#if(TIMER2_FastPwm_Type == TIMER_FastPwmType_Inverted)
			CLR_BIT(TCCR2_REG, TCCR2_COM20);
			SET_BIT(TCCR2_REG, TCCR2_COM21);
		#elif(TIMER2_FastPwm_Type == TIMER_FastPwmType_NonInverted)
			SET_BIT(TCCR2_REG, TCCR2_COM20);
			SET_BIT(TCCR2_REG, TCCR2_COM21);
		#endif
		DIO_enuSetPinDirection(TIMER_OC2_PORT, TIMER_OC2_PIN, DIO_u8OUTPUT);

	#elif(TIMER2_MODE_SELECT == TIMER_MODE_PWMphasecorrect)
		SET_BIT(TCCR2_REG, TCCR2_WGM20);
		CLR_BIT(TCCR2_REG, TCCR2_WGM21);

		#if(TIMER2_PhaseCorrect_Type == TIMER_PhaseCorrect_NonInverted)
			SET_BIT(TCCR2_REG, TCCR2_COM20);
			SET_BIT(TCCR2_REG, TCCR2_COM21);

		#elif(TIMER2_PhaseCorrect_Type == TIMER_PhaseCorrect_Inverted)
			CLR_BIT(TCCR2_REG, TCCR2_COM20);
			SET_BIT(TCCR2_REG, TCCR2_COM21);
		#endif

	#endif
	/******************************************************************************/

	/***************************** TIMER2  PRE SELECT *****************************/
	#if(TIMER2_CLK_PRE_SELECT == TIMER_PRES_01)
		SET_BIT(TCCR2_REG, TCCR2_CS20);
		CLR_BIT(TCCR2_REG, TCCR2_CS21);
		CLR_BIT(TCCR2_REG, TCCR2_CS22);

	#elif(TIMER2_CLK_PRE_SELECT == TIMER_PRES_08)
		CLR_BIT(TCCR2_REG, TCCR2_CS20);
		SET_BIT(TCCR2_REG, TCCR2_CS21);
		CLR_BIT(TCCR2_REG, TCCR2_CS22);

	#elif(TIMER2_CLK_PRE_SELECT == TIMER_PRES_32)
		SET_BIT(TCCR2_REG, TCCR2_CS20);
		SET_BIT(TCCR2_REG, TCCR2_CS21);
		CLR_BIT(TCCR2_REG, TCCR2_CS22);

	#elif(TIMER2_CLK_PRE_SELECT == TIMER_PRES_64)
		CLR_BIT(TCCR2_REG, TCCR2_CS20);
		CLR_BIT(TCCR2_REG, TCCR2_CS21);
		SET_BIT(TCCR2_REG, TCCR2_CS22);

	#elif(TIMER2_CLK_PRE_SELECT == TIMER_PRES_128)
		SET_BIT(TCCR2_REG, TCCR2_CS20);
		CLR_BIT(TCCR2_REG, TCCR2_CS21);
		SET_BIT(TCCR2_REG, TCCR2_CS22);

	#elif(TIMER2_CLK_PRE_SELECT == TIMER_PRES_256)
		CLR_BIT(TCCR2_REG, TCCR2_CS20);
		SET_BIT(TCCR2_REG, TCCR2_CS21);
		SET_BIT(TCCR2_REG, TCCR2_CS22);

	#elif(TIMER2_CLK_PRE_SELECT == TIMER_PRES_1024)
		SET_BIT(TCCR2_REG, TCCR2_CS20);
		SET_BIT(TCCR2_REG, TCCR2_CS21);
		SET_BIT(TCCR2_REG, TCCR2_CS22);
	#endif
	/******************************************************************************/


	// Turn Global Interrupt ON
	GIE_enuEnable();


}

void TIMER2_voidStart(void){
	#if(TIMER2_MODE_SELECT == TIMER_MODE_NORMALovf)
		SET_BIT(TIMSK_REG, TIMSK_TOIE2);

	#elif(TIMER2_MODE_SELECT == TIMER_MODE_CTC)
		SET_BIT(TIMSK_REG, TIMSK_OCIE2);

	#endif
}

void TIMER2_voidStop(void){
	#if(TIMER2_MODE_SELECT == TIMER_MODE_NORMALovf)
		CLR_BIT(TIMSK_REG, TIMSK_TOIE2);

	#elif(TIMER2_MODE_SELECT == TIMER_MODE_CTC)
		CLR_BIT(TIMSK_REG, TIMSK_OCIE2);

	#endif
}

uint8_t TIMER2_voidScheduleTask( void (*TaskCallback)(void), float64 copy_f64RequiredTime_inSeconds){

	uint32_t Local_u32PrescalerValue = 0;

	switch(TCCR2 & 0x07){
		case 0x01: Local_u32PrescalerValue = 1; break;
		case 0x02: Local_u32PrescalerValue = 8; break;
		case 0x03: Local_u32PrescalerValue = 64; break;
		case 0x04: Local_u32PrescalerValue = 256; break;
		case 0x05: Local_u32PrescalerValue = 1024; break;
	}

	float64 Local_f64Totalticks = (copy_f64RequiredTime_inSeconds * F_CPU)/Local_u32PrescalerValue;

	#if(TIMER2_MODE_SELECT == TIMER_MODE_NORMALovf)




		/**
		 *  fmod - function similar to modulus operator but designed to work
		 *  with floating point numbers, not just integers. it computes the
		 *  remainder of the diviion of one floating-point number by another.
		 * */

		if( (fmod(Local_f64Totalticks, 1.00) == 0.0)  &&  fmod(Local_f64Totalticks, 256.0) == 0.0){
			TIMER2_TARGET_NTICKS = (uint32_t)(Local_f64Totalticks/256);
		}else{
			// It's floating Number, setting preload value

			TCNT2_REG = 256 - (uint32_t)(fmod(Local_f64Totalticks, 256.0));

			TIMER2_TARGET_NTICKS = (uint32_t)ceil(Local_f64Totalticks/256);
		}




	#elif(TIMER2_MODE_SELECT == TIMER_MODE_CTC)


		if(Local_f64Totalticks > 255){
			OCR2_REG = 255;
	        TIMER2_TARGET_NTICKS = ceil((double)Local_f64Totalticks / 255.0); // How many times timer should reach 255

		}else{
			OCR2_REG = Local_f64Totalticks-1;
			TIMER2_TARGET_NTICKS  = 1;
		}

	#endif


		TIMERS_ISR_Functions[2] = TaskCallback;
		TIMER2_voidStart();
	return 0;

}


void  TIMER2_voidSetPWM(uint8_t copy_u8DutyCycle){

	/*
	 *
	 * It's more recommened to pass an integer number to OCR0 register
	 * avoids reliance on floating point hardware support wich is absent in many
	 * avr micrcontrollersings using floating-point arithmetic can
	 * consume significantly more CPU cycles due to software emulation,
	 * leading to potential inaccuracies in time-sensitive applications such
	 * as PWM signal generation.
	 *
	 *
	 * Avr32 does has floating point operation
	 * **/


	OCR2_REG = (uint8_t)(((uint16_t)copy_u8DutyCycle * 256) / 100);
}
/*******************************************************************************************************/



/****************************************** WATCH DOG TIMER INTERFACE ******************************************/
void TIMER_voidWDTSleep(uint8_t copy_u8WdtPeriod){
    // Reset watchdog timer using macro
    WDT_voidRestart();

    // Start timed sequence
    WDTCSR_REG |= (1 << WDTCSR_WDCE) | (1 << WDTCSR_WDE);

    // Set watchdog timer prescaler and enable watchdog timer
    WDTCSR_REG = (1 << WDTCSR_WDE) | copy_u8WdtPeriod;

}

void TIMER_voidWDTEnable (void){
    // Reset watchdog timer using macro
    WDT_voidRestart();

    // Start timed sequence
    WDTCSR_REG |= (1 << WDTCSR_WDCE) | (1 << WDTCSR_WDE);

    // Enable watchdog timer with the previously set period
    SET_BIT(WDTCSR_REG, WDTCSR_WDE);

}


void TIMER_voidWDTDisable(void) {
    // Reset watchdog timer using macro
    WDT_voidRestart();

    // Start timed sequence
    WDTCSR_REG |= (1 << WDTCSR_WDCE) | (1 << WDTCSR_WDE);

    // Disable watchdog timer
    WDTCSR_REG = 0x00;
}
/******************************************************************************************************/





ISR(TIMER0_OVF_vect){

	TIMER0_CURRENT_NTICKS++;

	if(TIMER0_CURRENT_NTICKS >= TIMER0_TARGET_NTICKS){
		TIMER0_CURRENT_NTICKS = 0;
		TIMERS_ISR_Functions[0]();
	}


	//here we can specify whether we want to stop timer0 or keep repeat or anything
}

ISR(TIMER0_COMP_vect){

	TIMER0_CURRENT_NTICKS++;

	if(TIMER0_CURRENT_NTICKS >= TIMER0_TARGET_NTICKS){
		TIMER0_CURRENT_NTICKS = 0;
		TIMERS_ISR_Functions[0]();
	}


	//here we can specify whether we want to stop timer0 or keep repeat or anything
}

ISR(TIMER1_OVF_vect){

	TIMER1_CURRENT_NTICKS++;

	if(TIMER1_CURRENT_NTICKS >= TIMER1_TARGET_NTICKS){
		TIMER1_CURRENT_NTICKS = 0;
		TIMERS_ISR_Functions[1]();
	}


	//here we can specify whether we want to stop timer0 or keep repeat or anything
}

ISR(TIMER1_COMPA_vect){

	TIMER1_CURRENT_NTICKS++;

	if(TIMER1_CURRENT_NTICKS >= TIMER1_TARGET_NTICKS){
		TIMER1_CURRENT_NTICKS = 0;
		TIMERS_ISR_Functions[1]();
	}


	//here we can specify whether we want to stop timer0 or keep repeat or anything
}


ISR(TIMER2_OVF_vect){

	TIMER2_CURRENT_NTICKS++;

	if(TIMER2_CURRENT_NTICKS >= TIMER2_TARGET_NTICKS){
		TIMER2_CURRENT_NTICKS = 0;
		TIMERS_ISR_Functions[2]();
	}


	//here we can specify whether we want to stop timer 2 or keep repeat or anything
}

ISR(TIMER2_COMP_vect){

	TIMER2_CURRENT_NTICKS++;

	if(TIMER2_CURRENT_NTICKS >= TIMER2_TARGET_NTICKS){
		TIMER2_CURRENT_NTICKS = 0;
		TIMERS_ISR_Functions[2]();
	}


	//here we can specify whether we want to stop timer 2 or keep repeat or anything

}
