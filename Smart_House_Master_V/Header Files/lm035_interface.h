/*
 * lm035_interface.h
 *
 *  Created on: Aug 10, 2023
 *      Author: SOFT ZONE
 */

#ifndef LM035_INTERFACE_H_
#define LM035_INTERFACE_H_

/**********************************************************************************************
 *                                 Static configuration                                       *
 **********************************************************************************************/
#define SENSOR_CHANNEL_ID       0
#define LM35_VOLT_MAX_VALUE     1.5
#define LM35_TEMP_MAX_VALUE     150

/**********************************************************************************************
 *                                 Functions Prototypes                                       *
 **********************************************************************************************/
/*
 * Description:
 * Function responsible for calculate the temperature from the ADC digital value.
 */
u8 LM35_getTemperature(void);
#endif /* LM035_INTERFACE_H_ */
