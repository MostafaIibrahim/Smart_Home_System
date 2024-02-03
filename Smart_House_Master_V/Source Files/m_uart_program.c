/*
 * m_uart_program.c
 *
 *  Created on: Aug 16, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"

#include "m_uart_registers.h"
#include "m_uart_interface.h"
#include "m_uart_private.h"
#include "m_uart_config.h"
#ifdef RX_INTERRUPT
static void (*g_pf)(void) = NULL_PTR ;
#endif
void  M_UART_voidInit(UART_ConfigType *config_type){
	u16 ubrr_value = 0;

	/* Set double transmission speed */
	UCSRA= (1<<UCSRA_U2X);
	/*
	 * 1- Enable receive and transmit.
	 * 2- choose Number of data bits per frame
	 */
	UCSRB = (1<<UCSRB_RXEN) | (1<<UCSRB_TXEN);
	UCSRB =  UCSRB | (config_type->char_size & 0x04);
#ifdef RX_INTERRUPT
	SET_BIT(UCSRB,UCSRB_RXCIE);
#endif
	/*
	 * 1-choose parity mode
	 * 2-choose stop bit for frame
	 * 3-choose number of data bits per frame
	 */
	UCSRC = (1<<UCSRC_URSEL) | (config_type->parity<<4) | (config_type->stop_bit<<3) | ((config_type->char_size & 0x03)<<1);
	/* Calculate the UBRR register value */
	ubrr_value = (u16)(((F_CPU / (config_type->baud_rate * 8UL))) - 1);
	/*
	 * Choose baud rate:
	 * First 8 bit of ubrr_value in UBRRL
	 * Last 4 bit of ubrr_value in UBRRH
	 */
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value>>8);
}
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void M_UART_sendByte(const u8 byte){
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UCSRA_UDRE));
	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = byte;
	/************************* Another Method *************************
	 * UDR = byte;
	 * while(BIT_IS_CLEAR(UCSRA,UCSRA_TXC)); // Wait until the transmission is complete TXC = 1
	 * SET_BIT(UCSRA,UCSRA_TXC)); // Clear the TXC flag
	 *******************************************************************/
}
/*
 * Description :
 * Functional responsible for receive byte to another UART device.
 */
u8 M_UART_receiveByte(void){
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UCSRA_RXC));
	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}
/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void M_UART_sendString(const u8 *str){
	while(*str != '\0')
	{
		M_UART_sendByte(*str);
		str++;
	}
}
/*
 * Description:
 *
 */
void M_UART_receiveString(u8 *str){
	s8 i = -1 ;
	/* Receive the whole string until the '#' */
	do{
		i++;
		str[i] = M_UART_receiveByte();
	}while(str[i] != '#');
	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}
u8 M_UART_u8RxcFlagState(void){
	return GET_BIT(UCSRA,UCSRA_RXC);
}
u8 MUART_u8ReturnValReceived(void){
	return UDR;
}
#ifdef RX_INTERRUPT

void M_UART_RxSetCallBack(void(*p2f)(void)){
	g_pf = p2f;
}


void __vector_13(void)       __attribute__((signal));

void __vector_13(void){
	if(g_pf != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_pf)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif
