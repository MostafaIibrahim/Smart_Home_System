/*
 * HLED_program.c
 *
 *  Created on: Sep 2, 2023
 *      Author: SOFT ZONE
 */
#include "STD_TYPES.h"
#include "common_macros.h"
#include "MDIO_interface.h"
#include "HLED_config.h"
#include "HLED_interface.h"

void  HLED_voidDisplayLdr(u8 num){
	MDIO_ErrorS_SetPortValue(LED_PORT,num);
}

