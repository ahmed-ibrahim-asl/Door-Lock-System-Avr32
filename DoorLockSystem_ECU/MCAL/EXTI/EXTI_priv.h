/*
 * EXTI_priv.h
 *
 *  Created on: Jan 15, 2024
 *      Author: ad
 */

#ifndef MCAL_EXTI_EXTI_PRIV_H_
#define MCAL_EXTI_EXTI_PRIV_H_

/**
 * Remeber Job of each Register:
 *
 *
 * MCUCCR - MCU Control Register
 * 	contains control bits for interrupt sense control and ....
 *
 *
 * MCUCSR - MCU Control and Status Register
 * 	I guess, it's same as previous but for only INT2 except
 * 	otherone which was for INT0 and INT1
 *
 *
 * GICR   - General Interrupt Control:
 * 	This Controls turnning on or off INT0, INT1, INT2
 *
 * */


/******************** General_Macros ********************/
#define MCUCR 	*((volatile uint8_t*) (0x55))
#define MCUCSR 	*((volatile uint8_t*) (0x54))
#define GIFR	*((volatile uint8_t*) (0x5A))
#define GICR    *((volatile uint8_t*) (0x5B))




#define NUM_INT						3

#define INT_NO_0					0
#define INT_NO_1					1
#define INT_NO_2					2

#define EXTI_DISABLED				0
#define EXTI_ENABLED				1


//On-Off Control Section
#define INT0_switch					6
#define INT1_switch					7
#define INT2_switch					5


#define ISC00						0
#define ISC01						1
#define ISC10						2
#define ISC11						3
#define ISC2						6
/******************************************************/


/******************** Sense Modes ********************/
#define EXTI_LOW_LEVEL				0
#define EXTI_ANY_lOGICALCHANGE		1
#define EXTI_FALLING_EDGE			2
#define EXTI_RISING_EDGE			3


//#define EXTI_INT2_Falling_Edge	0
//#define EXTI_INT2_Rising_Edge   	1
/*****************************************************/



#endif /* MCAL_EXTI_EXTI_PRIV_H_ */
