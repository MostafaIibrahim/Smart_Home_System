/*
 * H_KEYPAD_config.h
 *
 *  Created on: Aug 5, 2023
 *      Author: Asem
 */

#ifndef H_KEYPAD_CONFIG_H_
#define H_KEYPAD_CONFIG_H_

#define KEYPAD_ROW_PORT		DIO_PORTD
#define KEYPAD_COL_PORT		DIO_PORTA


#define KEYPAD_R0	    DIO_PIN4
#define KEYPAD_R1	    DIO_PIN5
#define KEYPAD_R2    	DIO_PIN6
#define KEYPAD_R3	    DIO_PIN7

#define KEYPAD_C0		DIO_PIN7
#define KEYPAD_C1	    DIO_PIN6
#define KEYPAD_C2	    DIO_PIN5
#define KEYPAD_C3	    DIO_PIN4

#define COL_SIZE		4
#define ROW_SIZE 		4

#define KEYPAD_TYPE	   {{ 7, 8 , 9 , '/'},{ 4 , 5 , 6 ,'*'},{ 1 , 2 , 3 ,'-'},{'#', 0 ,'=','+'}}

#endif /* H_KEYPAD_CONFIG_H_ */
