/*
 * hlcd_interface.h
 *
 *  Created on: Aug 3, 2023
 *      Author: SOFT ZONE
 */

#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_

#define RIGHT   6
#define LEFT    5

void HLCD_voidInit(void);
void HLCD_voidSendCommand(u8 Copy_u8command);
void HLCD_voidDisplayCharacter(u8 Copy_u8data);
void HLCD_displayString(const char *string);
void HLCD_moveCursor(u8 row , u8 column);
void HLCD_displayStringRowColumn(u8 row,u8 column,const u8 *string);
void HLCD_displayStringRowColumnDirection(/*u8 row,u8 column,*/const u8 *string,u8 direction);
void HLCD_intgerToString(int number);
void HLCD_clearScrean();


#endif /* HLCD_INTERFACE_H_ */
