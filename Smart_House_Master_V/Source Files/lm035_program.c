/*
 * lm035_program.c
 *
 *  Created on: Aug 10, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"
#include "adc_interface.h"
#include "lm035_interface.h"

/***********************************************************************************************
 *                                 Functions Definitions                                       *
 ***********************************************************************************************/
/*
 * Description:
 * Function responsible for calculate the temperature from the ADC digital value.
 */
u8 LM35_getTemperature()
{
	u16 adc_value = 0 ;

	u8 sensor_temp_map = 0 ;
	u8 sensor_temp = 0 ;

	adc_value = MADC_u16ReadChannel(SENSOR_CHANNEL_ID);
	sensor_temp_map = (u8)( ((u32) ADC_REF_VOLT_VALUE*adc_value * LM35_TEMP_MAX_VALUE ) / (LM35_VOLT_MAX_VALUE * ADC_MAXIMUM_VALUE) );

	sensor_temp = (u8) (((u32)(50 * sensor_temp_map)) / 255) ;
	return sensor_temp_map;
}



