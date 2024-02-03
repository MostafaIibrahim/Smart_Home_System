/*
 * m_uart_interface.h
 *
 *  Created on: Aug 16, 2023
 *      Author: SOFT ZONE
 */

#ifndef M_UART_INTERFACE_H_
#define M_UART_INTERFACE_H_
//#define RX_INTERRUPT
/********************************************************************************************
 *                               User Define type declaration                               *
 ********************************************************************************************/
typedef enum{
	DISABLED,ENABLE_EVEN=2,ENABLE_ODD
}UART_ParityMode;

typedef enum{
	ONE_BIT,TWO_BIT
}UART_StopBit;

typedef enum{
	FIVE_BIT,SIX_BIT,SEVEN_BIT,EIGHT_BIT,NINE_BIT=7
}UART_CharacterSize;

typedef struct{
	UART_ParityMode     parity;
	UART_StopBit        stop_bit;
	UART_CharacterSize  char_size;
	u32                 baud_rate;
}UART_ConfigType;
void  M_UART_voidInit(UART_ConfigType *config_type);
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void M_UART_sendByte(const u8 byte);
/*
 * Description :
 * Functional responsible for receive byte to another UART device.
 */
u8 M_UART_receiveByte(void);
/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void M_UART_sendString(const u8 *str);
/*
 * Description:
 *
 */
void M_UART_receiveString(u8 *str);
u8 M_UART_u8RxcFlagState(void);
u8 MUART_u8ReturnValReceived(void);
#ifdef RX_INTERRUPT
void M_UART_RxSetCallBack(void(*p2f)(void));
#endif
#endif /* M_UART_INTERFACE_H_ */
