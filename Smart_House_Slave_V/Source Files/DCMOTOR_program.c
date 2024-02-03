/*
 * DCMOTOR_program.c
 *
 *  Created on: Aug 11, 2023
 *      Author: Islam Shaaban
 */
#include "STD_TYPES.h"
#include "common_macros.h"

/*MCAL*/
#include "MDIO_interface.h"
#include "util/delay.h"
#include "DCMOTOR_interface.h"
#include "DCMOTOR_config.h"



void DCMOTOR_voidCWRotate(){
	MDIO_ErrorS_SetPinValue(DCMOTOR_PORT,DCMOTOR_PIN1,DIO_HIGH );
//	_delay_ms(1000);
}
void DCMOTOR_voidStop(){
	MDIO_ErrorS_SetPinValue(DCMOTOR_PORT,DCMOTOR_PIN1,DIO_LOW );

}





