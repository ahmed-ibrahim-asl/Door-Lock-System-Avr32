/*
 *   DIO_config.h
 *   Author: ad
 *   Created on: Dec 29, 2023
 *   GOAL: here you can configure pins of your MC 
 *
 *   ( output <0/1> // input<pullUp/float> )
 */

#ifndef DIO_DIO_CONFIG_H_
#define DIO_DIO_CONFIG_H_



/////////////////////////////////////////////////////
// Setting Directions of Pins 
// Input  ---- DIO_u8INPUT 
// Output ---- DIO_u8OUTPUT

/******************* PortA/DIR *******************/
#define DIO_u8PA0_DIR           DIO_u8OUTPUT
#define DIO_u8PA1_DIR           DIO_u8OUTPUT
#define DIO_u8PA2_DIR           DIO_u8OUTPUT
#define DIO_u8PA3_DIR           DIO_u8OUTPUT
#define DIO_u8PA4_DIR           DIO_u8INPUT
#define DIO_u8PA5_DIR           DIO_u8INPUT
#define DIO_u8PA6_DIR           DIO_u8INPUT
#define DIO_u8PA7_DIR           DIO_u8INPUT
/************************************************/

/******************* PortB/DIR *******************/
#define DIO_u8PB0_DIR           DIO_u8OUTPUT
#define DIO_u8PB1_DIR           DIO_u8OUTPUT
#define DIO_u8PB2_DIR           DIO_u8OUTPUT
#define DIO_u8PB3_DIR           DIO_u8OUTPUT
#define DIO_u8PB4_DIR           DIO_u8INPUT
#define DIO_u8PB5_DIR           DIO_u8INPUT
#define DIO_u8PB6_DIR           DIO_u8INPUT
#define DIO_u8PB7_DIR           DIO_u8INPUT
/************************************************/

/******************* PortC/DIR *******************/
#define DIO_u8PC0_DIR           DIO_u8OUTPUT
#define DIO_u8PC1_DIR           DIO_u8OUTPUT
#define DIO_u8PC2_DIR           DIO_u8OUTPUT
#define DIO_u8PC3_DIR           DIO_u8OUTPUT
#define DIO_u8PC4_DIR           DIO_u8INPUT
#define DIO_u8PC5_DIR           DIO_u8INPUT
#define DIO_u8PC6_DIR           DIO_u8INPUT
#define DIO_u8PC7_DIR           DIO_u8INPUT
/************************************************/

/******************* PortD/DIR *******************/
#define DIO_u8PD0_DIR           DIO_u8OUTPUT
#define DIO_u8PD1_DIR           DIO_u8OUTPUT
#define DIO_u8PD2_DIR           DIO_u8OUTPUT
#define DIO_u8PD3_DIR           DIO_u8OUTPUT
#define DIO_u8PD4_DIR           DIO_u8INPUT
#define DIO_u8PD5_DIR           DIO_u8INPUT
#define DIO_u8PD6_DIR           DIO_u8INPUT
#define DIO_u8PD7_DIR           DIO_u8INPUT
/************************************************/

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
// Setting intial value of each pin 
//if direction is Input --- DIO_u8FLOAT|DIO_u8PULLUP              
//if direction is output--- DIO_u8HIGH|DIO_u8LOW

/******************* PortA/value *******************/
#define DIO_u8PA0_VALUE         DIO_u8HIGH
#define DIO_u8PA1_VALUE         DIO_u8HIGH
#define DIO_u8PA2_VALUE         DIO_u8LOW
#define DIO_u8PA3_VALUE         DIO_u8LOW
#define DIO_u8PA4_VALUE         DIO_u8FLOAT
#define DIO_u8PA5_VALUE         DIO_u8FLOAT
#define DIO_u8PA6_VALUE         DIO_u8PULLUP
#define DIO_u8PA7_VALUE         DIO_u8PULLUP
/**************************************************/

/******************* PortB/value *******************/
#define DIO_u8PB0_VALUE         DIO_u8HIGH
#define DIO_u8PB1_VALUE         DIO_u8HIGH
#define DIO_u8PB2_VALUE         DIO_u8LOW
#define DIO_u8PB3_VALUE         DIO_u8LOW
#define DIO_u8PB4_VALUE         DIO_u8FLOAT
#define DIO_u8PB5_VALUE         DIO_u8FLOAT
#define DIO_u8PB6_VALUE         DIO_u8PULLUP
#define DIO_u8PB7_VALUE         DIO_u8PULLUP
/**************************************************/

/******************* PortC/value *******************/
#define DIO_u8PC0_VALUE         DIO_u8HIGH
#define DIO_u8PC1_VALUE         DIO_u8HIGH
#define DIO_u8PC2_VALUE         DIO_u8LOW
#define DIO_u8PC3_VALUE         DIO_u8LOW
#define DIO_u8PC4_VALUE         DIO_u8FLOAT
#define DIO_u8PC5_VALUE         DIO_u8FLOAT
#define DIO_u8PC6_VALUE         DIO_u8PULLUP
#define DIO_u8PC7_VALUE         DIO_u8PULLUP
/**************************************************/

/******************* PortD/value *******************/
#define DIO_u8PD0_VALUE         DIO_u8HIGH
#define DIO_u8PD1_VALUE         DIO_u8HIGH
#define DIO_u8PD2_VALUE         DIO_u8LOW
#define DIO_u8PD3_VALUE         DIO_u8LOW
#define DIO_u8PD4_VALUE         DIO_u8FLOAT
#define DIO_u8PD5_VALUE         DIO_u8FLOAT
#define DIO_u8PD6_VALUE         DIO_u8PULLUP
#define DIO_u8PD7_VALUE         DIO_u8PULLUP
/**************************************************/




#endif /* DIO_DIO_CONFIG_H_ */
