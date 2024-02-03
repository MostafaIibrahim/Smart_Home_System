/*
 * adc_program.c
 *
 *  Created on: Aug 9, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"

#include "adc_interface.h"
#include "adc_register.h"
#include "adc_private.h"
#include "adc_config.h"

void MADC_voidInit(ADC_ConfigType *config_ptr){
#ifdef ATON
	/* Select Vref */
	CLEAR_BIT(ADMUX , ADMUX_RESFS1);
	SET_BIT(ADMUX , ADMUX_RESFS0);
	/* SELECT RIGHT ADJUST */
	CLEAR_BIT(ADMUX,ADMUX_MUX0);

	/* Enable ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

	/* Select prescaler */
	SET_BIT(ADCSRA,ADCSRA_ADPS0);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	CLEAR_BIT(ADCSRA,ADCSRA_ADPS2);
#endif
	/*
	 * ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = ((config_ptr->reference)<<6);
	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADCSRA_ADEN) | (config_ptr->prescaler);
	/* Auto trigger mode selection */
	SFIOR |= ((config_ptr->trigger_mode)<<5);

}
u16  MADC_u16ReadChannel(u8 channel){

	/* To select Channel */
	ADMUX = (ADMUX & 0xE0) | (channel & 0x07) ;
	/* Start conversion by setting bit in ADSC */
	SET_BIT(ADCSRA,ADCSRA_ADSC);
	/* Wait until finishing the conversion by polling on it */
	while(BIT_IS_CLEAR(ADCSRA,ADCSRA_ADIF));
	/* Clear Interrupt flag */
	SET_BIT(ADCSRA,ADCSRA_ADIF);
	/* Return digital signal in ADC register */
	return ADC_DATA_REG;

}

