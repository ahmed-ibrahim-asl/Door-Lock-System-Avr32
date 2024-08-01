/*
 * EXTI_config.c
 *
 *  Created on: Jan 15, 2024
 *      Author: ad
 */


/*************** Include Section Start ********************/
#include "EXTI_priv.h"
#include "EXTI_config.h"
/**********************************************************/



/*
 * [OPTIONS]
 *
 * 1. EXTI_DISABLED | EXTI_ENABLED
 *
 * 2. EXTI_ANY_lOGICALCHANGE | EXTI_LOW_LEVEL
 *    EXTI_FALLING_EDGE      | EXTI_RISING_EDGE
 *
 *
 * For INT2 only
 *
 * */




EXTI EXTI_GroupConfig[NUM_INT] = {
	{EXTI_ENABLED, EXTI_RISING_EDGE},	//INT0
	{EXTI_DISABLED, EXTI_DISABLED},	//INT1
	{EXTI_DISABLED, EXTI_DISABLED}	//INT2
};
