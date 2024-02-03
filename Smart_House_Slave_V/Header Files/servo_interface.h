/*
 * servo_interface.h
 *
 *  Created on: Aug 16, 2023
 *      Author: SOFT ZONE
 */

#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

#define     MIN_ZERO_ANGEL          450
#define     MAX_180_ANGEL          2550

typedef enum{
	FAILED,SUCCESS
}SERVO_ErrorState;
void SERVO_voidInit(void);
void SERVO_voidEnable(u16 duty_cycle);

#endif /* SERVO_INTERFACE_H_ */
