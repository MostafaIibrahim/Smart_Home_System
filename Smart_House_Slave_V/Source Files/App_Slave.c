/*
 * main.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Amr-a
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MDIO_interface.h"
#include "MDIO_registers.h"
#include "m_spi_interface.h"
#include "H7SEG_interface.h"
#include "stepmotor_interface.h"
#include "DCMOTOR_interface.h"
#include "HLED_interface.h"
#include "m_timer_config.h"
#include "servo_interface.h"
#include "mgie_interface.h"
#include "m_timer_interface.h"
#include <util/delay.h>
#define READY        0xCC
#define FINISHED     0xCD
u8 g_flag = 0 ;
u8 Read_Spi = 0 ;
void ISR_SPI(void);
int main (){

	u8 STEPPER_CwFlag = 0 ;
	u16 Number_Iteration , MAX_Iteration =  270/FULL_STEP  ;
	SPI_ConfigType SPI_config = {RISING, LEADING_EDGE, F_CPU_64A};
	SPI_voidSetCallBack(ISR_SPI);
	Port_voidInit();
	SERVO_voidInit();
	M_SPI_initSlave(&SPI_config);
	MGIE_voidEnable();

	while(1){
		switch (Read_Spi){
		case '1':
			SERVO_voidEnable(MAX_180_ANGEL);
			break;
		case '2':
			SERVO_voidEnable(MIN_ZERO_ANGEL);
			break;
		case '3':
			DCMOTOR_voidCWRotate();
			break;
		case '4':
			DCMOTOR_voidStop();
			break;
		case '5':
			STEPPER_CwFlag = 1 ;
			break;
		case '6':
			STEPPER_CwFlag = 2 ;
			break;
		case 0 :
			break;
		default:

			H7SEG_voidDisplayNumber(Read_Spi);

			HLED_voidDisplayLdr(Read_Spi);

			break;
		}
		Read_Spi = 0 ;
		if(Number_Iteration < MAX_Iteration){
			if(STEPPER_CwFlag == 1){
				Number_Iteration++;
				STEPMOTOR_oneStepRotation();
			}
			else if(STEPPER_CwFlag == 2){
				Number_Iteration++;
				STEPMOTOR_oneStepRotationACW();
			}
		}
		else{
			Number_Iteration = 0 ;
			STEPPER_CwFlag = 0 ;
		}
	}
}
void ISR_SPI(void){
	Read_Spi = M_SPI_returnDataInterrupt();
}
