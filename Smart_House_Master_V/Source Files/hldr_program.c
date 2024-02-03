/*
 * hldr_program.c
 *
 *  Created on: Aug 17, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"
#include "hldr_config.h"
#include "hldr_interface.h"
#include "adc_interface.h"


u8 HLDR_u16GetSensorRead(){
    u8 result = 0 ;
	u16 adc_value;

	adc_value = MADC_u16ReadChannel(LDR_CHANNEL_ID);
//	adc_value = 0;

	result = (u8)((( (u32) (adc_value-MIN_ADC_REG) * (MAX_AVR_REG - MIN_AVR_REG) ) / (MAX_ADC_REG - MIN_ADC_REG) ) + MIN_AVR_REG);
//result = ( (u8) ((u32) 90 * adc_value )/1024);
	return result;
}


