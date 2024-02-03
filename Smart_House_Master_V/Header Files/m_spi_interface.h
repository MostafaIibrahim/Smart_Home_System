/*
 * m_spi_interface.h
 *
 *  Created on: Aug 17, 2023
 *      Author: SOFT ZONE
 */

#ifndef M_SPI_INTERFACE_H_
#define M_SPI_INTERFACE_H_
/******************************************************************************************
 *                                  Static Configuration                                  *
 ******************************************************************************************/
#define SPI_PORT_ID           DIO_PORTB
#define SPI_SS_PIN            DIO_PIN4
#define SPI_MOSI_PIN          DIO_PIN5
#define SPI_MISO_PIN          DIO_PIN6
#define SPI_SCK_PIN           DIO_PIN7

/*
 * Default SPI data value used in case we need to receive a byte from the other device,
 * without need to send a data to it
 */
#define SPI_DEFAULT_DATA_VALUE 0xFF

/******************************************************************************************
 *                                   User Defined Types                                   *
 ******************************************************************************************/
typedef enum{
	RISING,FALLING
}SPI_ConfigClkPolarity;
typedef enum{
	LEADING_EDGE,TRAILING_EDGE
}SPI_ConfigClkPhase;
typedef enum{
	F_CPU_4,F_CPU_16,F_CPU_64,F_CPU_128,F_CPU_2,F_CPU_8,F_CPU_32,F_CPU_64A
}SPI_ConfigClkRate;
typedef struct{
	SPI_ConfigClkPolarity clk_polarity;
	SPI_ConfigClkPhase    clk_phase;
	SPI_ConfigClkRate     clk_rate;
}SPI_ConfigType;
/******************************************************************************************
 *                                   Functions Prototypes                                 *
 ******************************************************************************************/
/*
 * Description:
 *  Function to Initialize Master by:
 *   Setting direction of SS, MOSI,and SCK as output pin and MISO as input
 *   Enable Master bit
 *   Select SCK frequency
 *   Enable SPI
 */
void M_SPI_initMaster(SPI_ConfigType *);
/*
 * Description:
 *  Function to Initialize Slave by:
 *   Select MISO pin as output and rest pins input.
 *   Enable SPI.
 *   Setup clock polarity and phase same as master
 */
void M_SPI_initSlave(SPI_ConfigType *);
/*
 * Description:
 *  Function to send and receive data.
 */
u8 M_SPI_sendReceiveByte(u8 data);
/*
 * Description:
 *
 */
void M_SPI_sendString(u8 *string);
/*
 * Description:
 *
 */
void M_SPI_receiveString(u8 *string);



#endif /* M_SPI_INTERFACE_H_ */
