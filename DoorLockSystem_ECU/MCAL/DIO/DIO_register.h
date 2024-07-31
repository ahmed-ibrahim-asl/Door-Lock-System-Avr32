/*
 * DIO_register.h
 *
 *  Created on: Dec 29, 2023
 *      Author: ad
 */

#ifndef DIO_DIO_REGISTER_H_
#define DIO_DIO_REGISTER_H_


//! volatile - we get an error while working with init function in dio_prog.c
/******************* PORTA *******************/
#define DDRA  *((unsigned char*)  (0x3A))
#define PORTA *((unsigned char*)  (0x3B))
#define PINA  *((unsigned char*)  (0x39))
/*********************************************/


/******************* PORTB *******************/
#define DDRB  *((unsigned char*)  (0x37))
#define PORTB *((unsigned char*)  (0x38))
#define PINB  *((unsigned char*)  (0x36))
/*********************************************/


/******************* PORTC *******************/
#define DDRC  *((unsigned char*)  (0x34))
#define PORTC *((unsigned char*)  (0x35))
#define PINC  *((unsigned char*)  (0x33))
/*********************************************/


/******************* PORTD *******************/
#define DDRD  *((unsigned char*)   (0x31))
#define PORTD *((unsigned char*)   (0x32))
#define PIND  *((unsigned char*)   (0x30))
/*********************************************/








#endif /* DIO_DIO_REGISTER_H_ */
