/*
 * adc_interface.h
 *
 *  Created on: Aug 9, 2023
 *      Author: SOFT ZONE
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_MAXIMUM_VALUE    1023  /* Equals for 10 bits */
#define ADC_REF_VOLT_VALUE   5

#define ADC_CHANNEL0         0
#define ADC_CHANNEL1         1
#define ADC_CHANNEL2         2
#define ADC_CHANNEL3         3
#define ADC_CHANNEL4         4
#define ADC_CHANNEL5         5
#define ADC_CHANNEL6         6
#define ADC_CHANNEL7         7

#ifndef   ATON
/**********************************************************************************************
 *                                 User define types                                          *
 **********************************************************************************************/
typedef enum{
	NO_SCALER,PRESCALER_2,PRESCALER_4,PRESCALER_8,PRESCALER_16,PRESCALER_32,\
	PRESCALER_64,PRESCALER_128
}ADC_Prescaler;

typedef enum{
	AREF , AVCC , INTERNAL_AREF=3
}ADC_Ref;

typedef enum{
	free_running_mode,analog_comparator,external_interrupt_request0,timer0_compare,\
	timer0_overflow,timer1_compare,timer1_overflow,timer1_capture_event
}ADC_Triggermode;
typedef struct
{
	ADC_Triggermode trigger_mode;
	ADC_Ref reference;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

void MADC_voidInit(ADC_ConfigType *config_ptr);
#endif
#ifdef ATON
void MADC_voidInit();
#endif
u16  MADC_u16ReadChannel(u8 channel);

#endif /* ADC_INTERFACE_H_ */
