#ifndef BIT_MATH_H
#define BIT_MATH_H



/******************************* Macro-Like  Function *******************************/
// To make the bit on
#define SET_BIT(VAR, BIT)		VAR |= (1<<(BIT)) 

// To flip the bit
#define TOG_BIT(VAR, BIT)   	VAR ^= (1<<(BIT)) 

// To make the bit off
#define CLR_BIT(VAR, BIT)       VAR &= ~(1<<(BIT)) 

// We going to shift the bits to right to the first bit and AND it with one
#define GET_BIT(VAR, BIT)   	((VAR>>BIT) & 1) // to read from
/************************************************************************************/

#endif
