/***************************************************/
/********************	Auther	: Mostafa 		********/
/********************	Layer 	:  H7SEG	********/
/********************	Module	:  7sement	********/
/********************	Version : 1.00		********/
/********************	Date	:  3/8/2023	********/
/***************************************************/
/***************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO_interface.h"
#include "util/delay.h"
#include "H7SEG_interface.h"
#include "H7SEG_private.h"
#include "H7SEG_config.h"

u8 MapNum[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};

void H7SEG_voidDisplayNumber(u8 num){
	u8 First_digit , Second_digit;
	num &= 0x7F;

	First_digit =  MapNum[num%10];
	Second_digit = MapNum[num/10] | 0x80;
//	for(u8 i = 0 ; i < 100 ; i++){

		MDIO_ErrorS_SetPinValue(SEVEN_SEG_SEC_ENABLE_PORT,SEVEN_SEG_SEC_ENABLE_PIN,DIO_LOW);
		MDIO_ErrorS_SetPinValue(SEVEN_SEG_FIRST_ENABLE_PORT,SEVEN_SEG_FIRST_ENABLE_PIN,DIO_HIGH);
		MDIO_ErrorS_SetPortValue(SEVEN_SEG_DATA_PORT,First_digit);
		_delay_ms(2);
		MDIO_ErrorS_SetPinValue(SEVEN_SEG_SEC_ENABLE_PORT,SEVEN_SEG_SEC_ENABLE_PIN,DIO_HIGH);
		MDIO_ErrorS_SetPinValue(SEVEN_SEG_FIRST_ENABLE_PORT,SEVEN_SEG_FIRST_ENABLE_PIN,DIO_LOW);
		MDIO_ErrorS_SetPortValue(SEVEN_SEG_DATA_PORT,Second_digit);
		_delay_ms(2);
}
