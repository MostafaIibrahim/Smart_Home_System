/*
 * H_KEYPAD_program.c
 *
 *  Created on: Aug 5, 2023
 *      Author: Asem
 */

#include "std_types.h"
#include "common_macros.h"
#include "MDIO_interface.h"
#include "H_KEYPAD_private.h"
#include "H_KEYPAD_config.h"
#include "H_KEYPAD_interface.h"
//static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);

u8 H_KeyPad_u8GetKey(void){
	u8 Local_u8PressedKey = NO_KEY;
	u8 col = 0;
	u8 row = 0;
	u8 KeyIsPressed = NOT_PRESSED;
	u8 flag = 0;


	u8 Col_array[COL_SIZE] = {KEYPAD_C0, KEYPAD_C1, KEYPAD_C2, KEYPAD_C3};
	u8 Row_array[ROW_SIZE] = {KEYPAD_R0, KEYPAD_R1, KEYPAD_R2, KEYPAD_R3};

	u8 Keypad_arr[ROW_SIZE][COL_SIZE] = KEYPAD_TYPE;

	for(col = 0; col <COL_SIZE ; col++){
		MDIO_errorStateSetPinValue(KEYPAD_COL_PORT ,Col_array[col],DIO_LOW);

		for(row =0 ;row<ROW_SIZE;row++){
			MDIO_errorStateGetPinValue(KEYPAD_ROW_PORT, Row_array[row], &KeyIsPressed);
			if(KeyIsPressed == PRESSED)
			{
				/* For busy wait to avoid bouncing */
				while(KeyIsPressed == PRESSED)
				{
					MDIO_errorStateGetPinValue(KEYPAD_ROW_PORT, Row_array[row], &KeyIsPressed);
				}
				Local_u8PressedKey = Keypad_arr[row][col];
				flag = 1;
				break;
			}
			else
			{

			}
		}
		MDIO_errorStateSetPinValue(KEYPAD_COL_PORT, Col_array[col], DIO_HIGH);									//set the keypad columns to be low
		if(flag)
		{
			break;
		}
		else{}
	}
	return Local_u8PressedKey;
}
