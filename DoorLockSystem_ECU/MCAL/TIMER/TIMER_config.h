/*
 * TIMER_config.h
 *
 *  Created on: Apr 7, 2024
 *      Author: ad
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_

#define F_CPU 1000000UL

/******************* Set  mode for TIMER Pins *******************/
#define TIMER_OC0_PORT			DIO_u8PortB
#define TIMER_OC0_PIN			DIO_u8PIN3


#define TIMER_OC1A_PORT			DIO_u8PortD
#define TIMER_OC1A_PIN			DIO_u8PIN5

#define TIMER_OC1B_PORT			DIO_u8PortD
#define TIMER_OC1B_PIN			DIO_u8PIN4

#define TIMER_OC2_PORT			DIO_u8PortD
#define TIMER_OC2_PIN			DIO_u8PIN7
/****************************************************************/

/************************ TIMER0  CONFIG ***********************/
// Options: TIMER_MODE_NORMALovf	or		TIMER_MODE_PWMphasecorrect
//			TIMER_MODE_FastPWM      or  	TIMER_MODE_CTC
#define TIMER0_MODE_SELECT				TIMER_MODE_FastPWM



// Options: TIMER0_OC0_OUTPUT_ENABLE or TIMER0_OC0_OUTPUT_DISABLE
#define TIMER0_OC0_OUTPUT_STATE			TIMER0_OC0_OUTPUT_ENABLE

#if(TIMER0_OC0_OUTPUT_STATE == TIMER0_OC0_OUTPUT_ENABLE)
	#if(TIMER0_MODE_SELECT == TIMER_MODE_CTC)
		// Options: TIMER_SET_OC0 or TIMER_CLR_OC0
		//			TIMER_TOGGLE_OC0 or TIMER_NORMAL_OC0
		#define TIMER_OC0_OUTPUT_MODE			TIMER_TOGGLE_OC0
	#endif
#endif

/*
 *PWM and other options
 *
 **/


#if(TIMER0_MODE_SELECT == TIMER_MODE_FastPWM)

	//TIMER_FastPwmType_Inverted, TIMER_FastPwmType_NonInverted
	#define TIMER0_FastPwm_Type			TIMER_FastPwmType_Inverted
#endif



#if(TIMER0_MODE_SELECT == TIMER_MODE_PWMphasecorrect)
	//TIMER_PhaseCorrect_Inverted, TIMER_PhaseCorrect_NonInverted
	#define TIMER0_PhaseCorrect_Type			TIMER_PhaseCorrect_NonInverted
#endif


// Options: TIMER_PRES_01  or TIMER_PRES_08
//			TIMER_PRES_64
// 			TIMER_PRES_256 or TIMER_PRES_1024
#define TIMER0_CLK_PRE_SELECT			TIMER_PRES_01
/***************************************************************/



/************************ TIMER1  CONFIG ***********************/
/**
 *Options:
 *
 * - TIMER_MODE_NORMALovf
 * - TIMER_MODE_CTC
 *
 * [[ Fast PWM ]]
 * - TIMER1_MODE_FastPWM_8bit
 * - TIMER1_MODE_FastPWM_9bit
 * - TIMER1_MODE_FastPWM_10bit
 * - TIMER1_MODE_FastPWM_16bit
 *
 * [[ Phase Correct ]]
 * - TIMER1_MODE_PWMphasecorrect_8bit
 * - TIMER1_MODE_PWMphasecorrect_9bit
 * - TIMER1_MODE_PWMphasecorrect_10bit
 * - TIMER1_MODE_PWMphasecorrect_16bit
 *
 * TIMER1_MODE_PhaseFreqCorrect
 *
 *
 * [NOTICE]
 * Phase Correct PWM:
 * 		Immediate duty cycle updates can cause frequency instability.
 *
 * Phase and Frequency Correct PWM:
 * 		Duty cycle updates at the end of the cycle ensure stable frequency and smooth transitions.
 *
 */
#define TIMER1_MODE_SELECT				 TIMER1_MODE_PhaseFreqCorrect


// Options: TIMER1_OC1_OUTPUT_ENABLE or TIMER1_OC1_OUTPUT_DISABLE
#define TIMER1_OC1A_OUTPUT_STATE		TIMER1_OC1_OUTPUT_ENABLE
#define TIMER1_OC1B_OUTPUT_STATE		TIMER1_OC1_OUTPUT_DISABLE


#if(TIMER1_OC1_OUTPUT_STATE == TIMER1_OC1_OUTPUT_ENABLE)
	#if(TIMER1_MODE_SELECT == TIMER_MODE_CTC)
		// Options: TIMER_SET_OC1A or TIMER_CLR_OC1A
		//			TIMER_TOGGLE_OC1A or TIMER_NORMAL_OC1A

		// Options: TIMER_SET_OC1B or TIMER_CLR_OC1B
		//			TIMER_TOGGLE_OC1B or TIMER_NORMAL_OC1B

		#define TIMER_OC1A_OUTPUT_MODE			TIMER_TOGGLE_OC1A
		#define	TIMER_OC1B_OUTPUT_MODE			TIMER_NORMAL_OC1B
	#endif
#endif



#if(TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_8bit || \
    TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_9bit || \
    TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_10bit || \
    TIMER1_MODE_SELECT == TIMER1_MODE_FastPWM_16bit)

	//TIMER_FastPwmType_Inverted, TIMER_FastPwmType_NonInverted, TIMER_FastPwmType_Normal

	#define TIMER1_FastPwm_Type_OC1A	TIMER_FastPwmType_NonInverted
	#define TIMER1_FastPwm_Type_OC1B	TIMER_FastPwmType_Normal
#endif



#if(TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_8bit || \
    TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_9bit || \
    TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_10bit || \
    TIMER1_MODE_SELECT == TIMER1_MODE_PWMphasecorrect_16bit || \
    TIMER1_MODE_SELECT == TIMER1_MODE_PhaseFreqCorrect)

	//TIMER_PhaseCorrect_Inverted, TIMER_PhaseCorrect_NonInverted, TIMER_PhaseCorrect_Normal

	#define TIMER1_PhaseCorrect_Type_OC1A	TIMER_PhaseCorrect_Inverted
	#define TIMER1_PhaseCorrect_Type_OC1B	TIMER_PhaseCorrect_Normal

#endif



// Options: TIMER_PRES_01  or TIMER_PRES_08
//			TIMER_PRES_64
// 			TIMER_PRES_256 or TIMER_PRES_1024
#define TIMER1_CLK_PRE_SELECT			TIMER_PRES_01
/***************************************************************/



/************************ TIMER2  CONFIG ***********************/
// Options: TIMER_MODE_NORMALovf	or		TIMER_MODE_PWMphasecorrect
//			TIMER_MODE_FastPWM      or  	TIMER_MODE_CTC
#define TIMER2_MODE_SELECT				TIMER_MODE_PWMphasecorrect


// Options: TIMER2_OC2_OUTPUT_ENABLE or TIMER2_OC2_OUTPUT_DISABLE
#define TIMER2_OC2_OUTPUT_STATE			TIMER2_OC2_OUTPUT_ENABLE

#if(TIMER2_OC2_OUTPUT_STATE == TIMER2_OC2_OUTPUT_ENABLE)

	#if(TIMER2_MODE_SELECT == TIMER_MODE_CTC)
		// Options: TIMER_SET_OC2 or TIMER_CLR_OC2
		//			TIMER_TOGGLE_OC2 or TIMER_NORMAL_OC2
		#define TIMER_OC2_OUTPUT_MODE			TIMER_TOGGLE_OC2
	#endif

#endif



#if(TIMER2_MODE_SELECT == TIMER_MODE_FastPWM)
	//TIMER_FastPwmType_Inverted, TIMER_FastPwmType_NonInverted
	#define TIMER2_FastPwm_Type			TIMER_FastPwmType_Inverted

#endif


#if(TIMER2_MODE_SELECT == TIMER_MODE_PWMphasecorrect)
	//TIMER_PhaseCorrect_Inverted, TIMER_PhaseCorrect_NonInverted
	#define TIMER2_PhaseCorrect_Type			TIMER_PhaseCorrect_Inverted
#endif

// Options: TIMER_PRES_01  or TIMER_PRES_08
//			TIMER_PRES_64
// 			TIMER_PRES_256 or TIMER_PRES_1024
#define TIMER2_CLK_PRE_SELECT			TIMER_PRES_01
/***************************************************************/





#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
