/*
 * DIO_priv.h
 *
 *  Created on: Dec 29, 2023
 *      Author: ad
 */

#ifndef DIO_DIO_PRIV_H_
#define DIO_DIO_PRIV_H_

/********** PORTs_Groups **********/
#define DIO_u8PortA    0
#define DIO_u8PortB    1
#define DIO_u8PortC    2   
#define DIO_u8PortD    3
/*********************************/


/********** PIN_pins **********/
#define DIO_u8PIN0    0
#define DIO_u8PIN1    1
#define DIO_u8PIN2    2
#define DIO_u8PIN3    3
#define DIO_u8PIN4    4
#define DIO_u8PIN5    5
#define DIO_u8PIN6    6
#define DIO_u8PIN7    7
/******************************/


/********** Status (in/out) **********/
//! add description to explain where it cames from (0, 1)
#define DIO_u8OUTPUT 	1
#define DIO_u8INPUT 	0 
/************************************/


/********** input(PULLup/ float) **********/
#define DIO_u8FLOAT             0
#define DIO_u8PULLUP            1

/*
    FLOAT: means that it depends on external circuit
    configuration

    PULLUP: think of it as we setting pin to be internally 
    pull up
*/
/******************************************/



/********** Levels (high/low) **********/
#define DIO_u8HIGH  1
#define DIO_u8LOW   0
/**************************************/


// instead of dealing with pins pin by bin this can help dealing
// with entire port without directly making direct request to MCAL
#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)			0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)				CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
                                      

#endif /* DIO_DIO_PRIV_H_ */
