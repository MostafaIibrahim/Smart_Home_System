/*
 * hlcd_interface.c
 *
 *  Created on: Aug 3, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"
#include <stdlib.h>

#include <util/delay.h>
#include "mdio_interface.h"
#include "hlcd_config.h"
#include "hlcd_interface.h"
#include "hlcd_private.h"



void HLCD_voidInit(void){
	//u8 command = 0x
	_delay_ms(40);
#if LCD_DATA_BITS_MODE == 8
	/* Send command Function set */
	HLCD_voidSendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#elif LCD_DATA_BITS_MODE == 4
	HLCD_voidSendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1); /* LCD 2 lines 4 bit mode */
	HLCD_voidSendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	HLCD_voidSendCommand(LCD_TWO_LINES_FOUR_BITS_MODE); /* 4 bits + 2 Lines + 5x7 mode command */
#endif
	/* Send Command to display ON/OFF control */
	HLCD_voidSendCommand(DISPLAY_CURSOR_OFF_COMMAND);
	/* Send command to Clear screen */
	HLCD_voidSendCommand(CLEAR_COMMAND);
}

void HLCD_voidSendCommand(u8 Copy_u8command){
	/* Clr RS to send command */
	MDIO_errorStateSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_LOW);
	/* Clr RW to write */
	//MDIO_errorStateSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_LOW);
#if LCD_DATA_BITS_MODE == 8
	/* Send Data */
	MDIO_errorStateSetPortValue(LCD_PORT_DATA,Copy_u8command);
#elif LCD_DATA_BITS_MODE == 4
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB4_PIN,GET_BIT(Copy_u8command,4));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB5_PIN,GET_BIT(Copy_u8command,5));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB6_PIN,GET_BIT(Copy_u8command,6));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB7_PIN,GET_BIT(Copy_u8command,7));
	/* Set EN to make LND Micro read Copy_u8command */
	MDIO_errorStateSetPinValue(LCD_ENABLE_PORT,LCD_ENABLE_PIN,DIO_HIGH);
	_delay_ms(2);
	MDIO_errorStateSetPinValue(LCD_ENABLE_PORT,LCD_ENABLE_PIN,DIO_LOW);

	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB4_PIN,GET_BIT(Copy_u8command,0));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB5_PIN,GET_BIT(Copy_u8command,1));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB6_PIN,GET_BIT(Copy_u8command,2));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB7_PIN,GET_BIT(Copy_u8command,3));
#endif
	/* Set EN to make LND Micro read command */
	MDIO_errorStateSetPinValue(LCD_ENABLE_PORT,LCD_ENABLE_PIN,DIO_HIGH);
	_delay_ms(2);
	MDIO_errorStateSetPinValue(LCD_ENABLE_PORT,LCD_ENABLE_PIN,DIO_LOW);
}

void HLCD_voidDisplayCharacter(u8 Copy_u8data){
	/* SET RS to send data */
	MDIO_errorStateSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_HIGH);
	_delay_ms(1);
	/* Clr RW to write */
	//MDIO_errorStateSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_LOW);
	//_delay_ms(1);
#if LCD_DATA_BITS_MODE == 8
	/* Send Data */
	MDIO_errorStateSetPortValue(LCD_PORT_DATA,Copy_u8data);
#elif LCD_DATA_BITS_MODE == 4
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB4_PIN,GET_BIT(Copy_u8data,4));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB5_PIN,GET_BIT(Copy_u8data,5));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB6_PIN,GET_BIT(Copy_u8data,6));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB7_PIN,GET_BIT(Copy_u8data,7));
	_delay_ms(1);
	/* Set EN to make LND Micro read Copy_u8data */
	MDIO_errorStateSetPinValue(LCD_ENABLE_PORT,LCD_ENABLE_PIN,DIO_HIGH);
	_delay_ms(2);
	MDIO_errorStateSetPinValue(LCD_ENABLE_PORT,LCD_ENABLE_PIN,DIO_LOW);

	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB4_PIN,GET_BIT(Copy_u8data,0));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB5_PIN,GET_BIT(Copy_u8data,1));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB6_PIN,GET_BIT(Copy_u8data,2));
	MDIO_errorStateSetPinValue(LCD_PORT_DATA,LCD_DB7_PIN,GET_BIT(Copy_u8data,3));
#endif
	_delay_ms(1);
	/* Set EN to make LND Micro read data */
	MDIO_errorStateSetPinValue(LCD_ENABLE_PORT,LCD_ENABLE_PIN,DIO_HIGH);
	_delay_ms(2);
	MDIO_errorStateSetPinValue(LCD_ENABLE_PORT,LCD_ENABLE_PIN,DIO_LOW);
}
void HLCD_displayString(const char *string){
	while((*string) != '\0'){
		HLCD_voidDisplayCharacter(*string);
		string++;
	}
}
void HLCD_moveCursor(u8 row , u8 column){
	u8 adressresult;
	switch(row)
	{
	case 0: adressresult = column;
	break;
	case 1: adressresult = column + 0x40;
	break;
	case 2: adressresult = column + 0x10;
	break;
	case 3: adressresult = column + 0x50;
	}
	HLCD_voidSendCommand(adressresult | LCD_CURSOR_TO_BEGIN);
}
void HLCD_displayStringRowColumn(u8 row,u8 column,const u8 *string){
	HLCD_moveCursor(row,column);
	HLCD_displayString(string);
}
void HLCD_displayStringRowColumnDirection(/*u8 row,u8 column,*/const u8 *string,u8 direction){
	//HLCD_moveCursor(row,column);
	if(direction == RIGHT){
		HLCD_voidSendCommand(LCD_SHIFT_CURSOR_RIGHT);
	}
	else if(direction == LEFT){
		HLCD_voidSendCommand(LCD_SHIFT_CURSOR_LEFT);
	}
	HLCD_displayString(string);
}
void HLCD_intgerToString(int number){
	u8 buff[16];
	itoa(number,buff,10);
	HLCD_displayString(buff);
}
void HLCD_clearScrean(){
	HLCD_voidSendCommand(CLEAR_COMMAND);
}
