/*
 * m_uart_registers.h
 *
 *  Created on: Aug 16, 2023
 *      Author: SOFT ZONE
 */

#ifndef M_UART_REGISTERS_H_
#define M_UART_REGISTERS_H_

/* UART Control and status register A */
#define UCSRA 				*((volatile u8*)0x2B)
#define UCSRA_MPCM                    0
#define UCSRA_U2X                     1
#define UCSRA_PE                      2
#define UCSRA_DOR                     3
#define UCSRA_FE                      4
#define UCSRA_UDRE                    5
#define UCSRA_TXC                     6
#define UCSRA_RXC                     7

/* UART Control and status register B*/
#define UCSRB 				*((volatile u8*)0x2A)
#define UCSRB_TXB8                    0
#define UCSRB_RXB8                    1
#define UCSRB_UCSZ2                   2
#define UCSRB_TXEN                    3
#define UCSRB_RXEN                    4
#define UCSRB_UDRIE                   5
#define UCSRB_TXCIE                   6
#define UCSRB_RXCIE                   7

/*UART Control and status register C*/
#define UCSRC 				*((volatile u8*)0x40)
#define UCSRC_UCPOL                   0
#define UCSRC_UCSZ0                   1
#define UCSRC_UCSZ1                   2
#define UCSRC_USBS                    3
#define UCSRC_UPM0                    4
#define UCSRC_UPM1                    5
#define UCSRC_UMSEL                   6
#define UCSRC_URSEL                   7
/*UART I/O register*/
#define UDR 				*((volatile u8*)0x2C)

/*UART BAUDRATE registers*/
#define UBRRL 				*((volatile u8*)0x29)
#define UBRRH 				*((volatile u8*)0x40)



#endif /* M_UART_REGISTERS_H_ */
