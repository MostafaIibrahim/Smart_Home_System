/*
 * hlcd_private.h
 *
 *  Created on: Aug 3, 2023
 *      Author: SOFT ZONE
 */

#ifndef HLCD_PRIVATE_H_
#define HLCD_PRIVATE_H_




#define LCD_TWO_LINES_EIGHT_BITS_MODE            0b00111100
#define LCD_TWO_LINES_FOUR_BITS_MODE             0b00101100
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1       0b00110011
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2       0b00110010

#define LCD_SHIFT_CURSOR_RIGHT                   0b00010100
#define LCD_SHIFT_CURSOR_LEFT                    0b00010000
#define LCD_CURSOR_TO_BEGIN                      0b10000000
#define DISPLAY_CURSOR_OFF_COMMAND               0b00001100
#define DISPLAY_CURSOR_ON_COMMAND                0b00001110

#define CLEAR_COMMAND                            0b00000001



#endif /* HLCD_PRIVATE_H_ */
