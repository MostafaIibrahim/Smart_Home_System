/*
 * SERVO_program.c
 *
 *  Created on: Aug 16, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"

#include "m_timer_interface.h"
#include "servo_interface.h"
#include <util/delay.h>


void SERVO_voidInit(void){
	M_TIMER1_voidInit(TOP_FPWM_ICR1,FAST_PWM_NON_INV,DIV_8);
	M_TIMER1_voidSetTopValue(20000,TOP_FPWM_ICR1);
}
void SERVO_voidEnable(u16 duty_cycle){
		M_TIMER1_voidSetDutyCycle(duty_cycle);
//		_delay_ms(2);
}




