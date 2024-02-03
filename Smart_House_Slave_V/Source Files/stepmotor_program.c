/*
 * stepmotor_program.c
 *
 *  Created on: Aug 7, 2023
 *      Author: SOFT ZONE
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "MDIO_interface.h"

#include "stepmotor_interface.h"
#include "stepmotor_config.h"
#include "stepmotor_private.h"

void STEPMOTOR_angleRotation(u16 angle){//270
	u16 max_iterator = (angle/FULL_STEP)+1;
	u16 iterator ;
	for(iterator = 0 ; iterator < max_iterator ; iterator++){
		STEPMOTOR_fistStep();
		STEPMOTOR_secondStep();
		STEPMOTOR_thirdStep();
		STEPMOTOR_fourthStep();
	}
}
void STEPMOTOR_oneStepRotationACW(void){//270
		STEPMOTOR_fourthStep();
		STEPMOTOR_thirdStep();
		STEPMOTOR_secondStep();
		STEPMOTOR_fistStep();
}
void STEPMOTOR_oneStepRotation(void){//270
		STEPMOTOR_fistStep();
		STEPMOTOR_secondStep();
		STEPMOTOR_thirdStep();
		STEPMOTOR_fourthStep();
}

void STEPMOTOR_Stop(void){
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,DIO_LOW);
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,DIO_LOW);
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,DIO_LOW);
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN4,DIO_LOW);
}
void STEPMOTOR_fistStep(){
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,DIO_HIGH);
	_delay_ms(2);
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN1,DIO_LOW);
}
void STEPMOTOR_secondStep(){
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,DIO_HIGH);
	_delay_ms(2);
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN2,DIO_LOW);
}
void STEPMOTOR_thirdStep(){
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,DIO_HIGH);
	_delay_ms(2);
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN3,DIO_LOW);
}
void STEPMOTOR_fourthStep(){
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN4,DIO_HIGH);
	_delay_ms(2);
	MDIO_ErrorS_SetPinValue(STEPPER_MOTOR_PORT,STEPPER_MOTOR_PIN4,DIO_LOW);
}

