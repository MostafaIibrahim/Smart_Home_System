/*
 * m_spi_program.c
 *
 *  Created on: Aug 17, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"
#include "mdio_interface.h"
#include "m_spi_registers.h"
#include "m_spi_private.h"
#include "m_spi_config.h"
#include "m_spi_interface.h"

static void (*g_pf)(void) = NULL_PTR ;
/*
 * Description:
 *  Function to Initialize Master by:
 *   Setting SS, MOSI,and SCK as output pin and MISO as input
 *   Enable Master bit
 *   Select SCK frequency
 *   Enable SPI
 */

void M_SPI_initMaster(SPI_ConfigType *config_master)
{
	MDIO_voidSetPinDirection(SPI_PORT_ID, SPI_SS_PIN, DIO_OUTPUT);
	MDIO_voidSetPinDirection(SPI_PORT_ID, SPI_MOSI_PIN, DIO_OUTPUT);
	MDIO_voidSetPinDirection(SPI_PORT_ID, SPI_SCK_PIN, DIO_OUTPUT);
	MDIO_voidSetPinDirection(SPI_PORT_ID,SPI_MISO_PIN, DIO_INPUT);
	/* Enable SPI pin and Initiate master  */
	SPCR = (1<<SPCR_SPE) | (1<<SPCR_MSTR);

	SET_BIT(SPCR,SPCR_DORD);
	/* Configure sampling edge */
	SPCR |= ((config_master->clk_polarity)<<3) | ((config_master->clk_phase)<<2);
	/* Configure clock rate */
	SPCR = SPCR | ((config_master->clk_rate) & 0x03);
	SPSR = SPSR | (((config_master->clk_rate) & 0x04)>>2);
}
/*
 * Description:
 *  Function to Initialize Slave by:
 *   Select MISO pin as output and rest pins input.
 *   Enable SPI.
 *   Setup clock polarity and phase same as master
 */
void M_SPI_initSlave(SPI_ConfigType *config_slave)
{
	MDIO_voidSetPinDirection(SPI_PORT_ID,SPI_MISO_PIN, DIO_OUTPUT);
	MDIO_voidSetPinDirection(SPI_PORT_ID, SPI_SS_PIN, DIO_INPUT);
	MDIO_voidSetPinDirection(SPI_PORT_ID, SPI_MOSI_PIN, DIO_INPUT);
	MDIO_voidSetPinDirection(SPI_PORT_ID, SPI_SCK_PIN, DIO_INPUT);
	/* Enable SPI pin */
	SPCR |= (1<<SPCR_SPE);

	SET_BIT(SPCR,SPCR_DORD);
	/* Configure sampling edge */
	SPCR |= ((config_slave->clk_polarity)<<3) | ((config_slave->clk_phase)<<2);
	SPSR &= ~(1<<SPSR_SPI2X);
#ifdef INTERRUPT
	SET_BIT(SPCR,SPCR_SPIE);
#endif

}
/*
 * Description:
 *  Function to send and receive data.
 */
u8 M_SPI_sendReceiveByte(u8 data)
{
	/* Send data */
	SPDR = data;
	/* Polling on SPI interrupt flag until finish sending */
	while(BIT_IS_CLEAR(SPSR,SPSR_SPIF)){}
	/* Read received data and clear interrupt flag */
	return SPDR;
}
#ifdef INTERRUPT
u8 M_SPI_returnDataInterrupt(void){
	return SPDR;
}
#endif
/*
 * Description:
 *
 */
void M_SPI_sendString(u8 *string)
{
	u8 received_data = 0;
	while (*string != '\0')
	{
		received_data = M_SPI_sendReceiveByte(*string);
		string++;
	}
}
/*
 * Description:
 *
 */
void M_SPI_receiveString(char *string)
{
	s8 i = -1;
	do{
		i++;
		string[i] = M_SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}while(string[i] != '#');
	string[i] = '\0';
}

void SPI_voidSetCallBack(void(*a_ptr)(void)){
	g_pf = a_ptr;
}
void __vector_12(void)       __attribute__((signal));

void __vector_12(void){
	if(g_pf != NULL_PTR ){
		(*g_pf)();
	}
}


