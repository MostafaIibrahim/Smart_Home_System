/*
 * m_spi_registers.h
 *
 *  Created on: Aug 17, 2023
 *      Author: SOFT ZONE
 */

#ifndef M_SPI_REGISTERS_H_
#define M_SPI_REGISTERS_H_

#define SPCR              *((volatile u8*)0x2D)
#define SPCR_SPR0                   0
#define SPCR_SPR1                   1
#define SPCR_CPHA                   2
#define SPCR_CPOL                   3
#define SPCR_MSTR                   4
#define SPCR_DORD                   5
#define SPCR_SPE                    6
#define SPCR_SPIE                   7


#define SPDR              *((volatile u8*)0x2F)     /*SPI Data Register*/
#define SPDR_MSB                    7
#define SPDR_LSB                    0

#define SPSR              *((volatile u8*)0x2E)     /*SPI Status Register*/
#define SPSR_SPIF                   7                         /*SPI Interrupt Flag*/
#define SPSR_WCOL                   6
#define SPSR_SPI2X                  0                         /*Prescaler bit 2*/

#endif /* M_SPI_REGISTERS_H_ */
