/*
 * App.h
 *
 *  Created on: Aug 27, 2023
 *      Author: SOFT ZONE
 */

#ifndef APP_H_
#define APP_H_
//#define DEBUGG

#define READY        0xCC
#define FINISHED     0xCD

#define CHECK_REG_ADD         0x15
#define FIRST_TIME            0xFF
#define DONE_REG              0x00

#define MAX_DIGITS_PASS       4
#define MAX_NUMBER_TRIALS     3

#define PASS_ADRESS_LOC      {{0x00,0x01,0x02,0x03},\
		                      {0x04,0x05,0x06,0x07},\
		                      {0x08,0x09,0x0A,0x0B}}


typedef enum{
	FAILED,SUCCESS
}Error_Status;
#endif /* APP_H_ */
