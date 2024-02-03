/*
 * hlcd_private.h
 *
 *  Created on: Aug 3, 2023
 *      Author: SOFT ZONE
 */

#ifndef HLCD_CONFIG_H_
#define HLCD_CONFIG_H_

#define LCD_DATA_BITS_MODE      4

#if ((LCD_DATA_BITS_MODE != 8) && (LCD_DATA_BITS_MODE != 4))
#error "Number of Data bits should be equal 4 or 8"
#endif

/* Configure RS port and pin */
#define LCD_RS_PORT                        DIO_PORTC
#define LCD_RS_PIN                         DIO_PIN2

//#define LCD_RW_PORT                        DIO_PORTC
//#define LCD_RW_PIN                         DIO_PIN2
/* Configure ENABLE port and pin */
#define LCD_ENABLE_PORT                    DIO_PORTC
#define LCD_ENABLE_PIN                     DIO_PIN3

#define LCD_PORT_DATA                      DIO_PORTC

#if (LCD_DATA_BITS_MODE == 4)
/* Pins of data bus */
#define LCD_DB4_PIN                     DIO_PIN4
#define LCD_DB5_PIN                     DIO_PIN5
#define LCD_DB6_PIN                     DIO_PIN6
#define LCD_DB7_PIN                     DIO_PIN7
#endif

#endif /* HLCD_CONFIG_H_ */
