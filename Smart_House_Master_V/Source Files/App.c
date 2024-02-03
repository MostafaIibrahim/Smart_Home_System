/*
 * App.c
 *
 *  Created on: Aug 26, 2023
 *      Author: SOFT ZONE
 */
#include "STD_Types.h"
#include "common_macros.h"
#include "App.h"
#include "mdio_interface.h"

#include "hlcd_interface.h"
#include "H_KEYPAD_interface.h"

#include "EEPROM_interface.h"
#include "MTWI_interface.h"

#include <util/delay.h>
#include "m_spi_interface.h"
#include "m_uart_interface.h"

#include "adc_interface.h"
#include "hldr_interface.h"
#include "lm035_interface.h"
#include "mgie_interface.h"
#include "m_timer_interface.h"

/* *****************************************************************************************
 *                                   Global Variables                                      *
 *******************************************************************************************/

u8 g_password[MAX_DIGITS_PASS]={0};
u8 address_pass [3][MAX_DIGITS_PASS]= PASS_ADRESS_LOC;
u8 g_registerionFlag =0 ;
u8 g_test_pass[4]={2};
volatile u8 g_timer = 0;
u8 SendChar_Spi = 0 ;
/* *****************************************************************************************
 *                                    Prototypes                                           *
 *******************************************************************************************/
void initFuncs(void);
void welcome_message(void);
void addnNew_User(void);
void Change_pass(void);
Error_Status Enter_Password(void);
void Open_System(void);
void ISR_TIMER(void);
//void ISR_UART(void);
/* *****************************************************************************************
 *                                   Main Function                                         *
 *******************************************************************************************/
int main(){
	u8 key = NO_KEY;

	initFuncs();

	welcome_message();
	//	EEPROM_voidWrite(CHECK_REG_ADD,0xFF);
	//	_delay_ms(15);

	EEPROM_voidRead(CHECK_REG_ADD,&g_registerionFlag);

	while(1){
		if(g_registerionFlag){
			addnNew_User();
			/*
			 * CHANGE FLAGE STATE & WRITE ON EEPROM
			 **/
			g_registerionFlag  = DONE_REG;
			EEPROM_voidWrite(CHECK_REG_ADD,DONE_REG);
		}
		else{
			HLCD_clearScrean();
			HLCD_displayString("1-Change pass");
			HLCD_moveCursor(1,0);
			HLCD_displayString("2-Add User  3-..");

			do{
				key = H_KeyPad_u8GetKey();
			}while(key == NO_KEY);

			if(key == 3){
				HLCD_clearScrean();
				HLCD_displayString("4-Open System");
				HLCD_moveCursor(1,0);
				HLCD_displayString("5-Previous");
				do{
					key = H_KeyPad_u8GetKey();
				}while(key == NO_KEY);
			}

			switch (key){
			case 1:
				//Change Password
				if( Enter_Password() ){
					Change_pass();
				}
				else{
					HLCD_clearScrean();
					HLCD_displayString("You are Blocked");
					_delay_ms(1000);
				}
				break;

			case 2 :
				//Add user
				if( Enter_Password() ){
					addnNew_User();
				}
				else{
					HLCD_clearScrean();
					HLCD_displayString("You are Blocked");
					_delay_ms(1000);
				}

				break;
			case 4 :
				if(Enter_Password()){
					Open_System();
				}
				else{
					HLCD_clearScrean();
					HLCD_displayString("You are Blocked");
					_delay_ms(1000);
				}
				break;
			case 5 :
				//prev menue

				break;
			default:
				HLCD_clearScrean();
				HLCD_displayString("Wrong Input");
				//delay
				_delay_ms(300);
			}
		}
	}
}
/* *****************************************************************************************
 *                                    Funcs Definition                                     *
 *******************************************************************************************/
void initFuncs(void){
	/* Declare pins configs */
	SPI_ConfigType  config_spi   = {RISING,LEADING_EDGE,F_CPU_64A};
	ADC_ConfigType  config_adc   = {free_running_mode,AVCC,PRESCALER_16};
	UART_ConfigType config_uart  = {DISABLED,ONE_BIT,EIGHT_BIT,9600};
	TIMER0_Config   config_timer = {TIMER0_NORMAL_MODE,NO_CLK,6};

	Port_voidInit();
	HLCD_voidInit();
	MTWI_voidInit();
	MADC_voidInit(&config_adc);
	M_SPI_initMaster(&config_spi);
	M_UART_voidInit(&config_uart);
	M_TIMER0_voidInit(&config_timer);
	M_TIMER0_voidSetCallBack(ISR_TIMER);
	MGIE_voidEnable();
}
void welcome_message(void){
	HLCD_displayString(" Welcome Smart ");
	// Delay
	_delay_ms(100);
	HLCD_moveCursor(1,5);
	HLCD_displayString("Home");
	//Delay
	_delay_ms(100);
	HLCD_clearScrean();
}
void addnNew_User(void){
	u8 key = NO_KEY , confirm_pass[MAX_DIGITS_PASS] = {0} , i ;
	Error_Status state = SUCCESS;

	do{
		/*
		 * ENTER PASSWORD FOR FIRST TIME
		 */
		HLCD_clearScrean();
		HLCD_displayString("Enter Password: ");
		HLCD_moveCursor(1,0);

		for( i = 0 ; i < MAX_DIGITS_PASS ; i++){
			do{
				key = H_KeyPad_u8GetKey();
			}while(key == NO_KEY);
			g_password[i] = key;
			HLCD_intgerToString(g_password[i]);
		}

		HLCD_clearScrean();
		HLCD_displayString("Renter Password:");
		HLCD_moveCursor(1,0);
		for( i = 0 ; i < MAX_DIGITS_PASS ; i++){
			do{
				key = H_KeyPad_u8GetKey();
			}while(key == NO_KEY);
			confirm_pass[i] = key;
			HLCD_intgerToString(key);
		}

		for(i = 0 ; i < MAX_DIGITS_PASS ; i++){
			if(confirm_pass[i] != g_password[i]){
				state = FAILED;
				break;
			}else{
				state = SUCCESS;
			}
		}
	}while(state == FAILED);
	/*
	 *STORE PASSWORD AT EEPROM
	 */
	for(u8 i = 0 ; i < MAX_DIGITS_PASS ; i++){
		EEPROM_voidWrite(address_pass[0][i],g_password[i]);
		_delay_ms(20);
	}

	HLCD_clearScrean();
	for(u8 i = 0 ; i < MAX_DIGITS_PASS ; i++){
		EEPROM_voidRead(address_pass[0][i],&g_test_pass[i]);
		HLCD_intgerToString(g_test_pass[i]);
		_delay_ms(200);
	}
	//until here all done ass required but still wrong pass in EEPROM
	//I need to check on the value at add

}

void Change_pass(void){
	u8 key = NO_KEY;
	u8 i = 0 ;

	HLCD_clearScrean();
	HLCD_displayString("Enter New Pass:");
	HLCD_moveCursor(1,0);

	do{
		do{
			key = H_KeyPad_u8GetKey();
		}while(key == NO_KEY);
		g_password[i] = key;
		HLCD_intgerToString(key);
		EEPROM_voidWrite(address_pass[0][i],key);
		i++;
	}while(i < MAX_DIGITS_PASS);
}

Error_Status Enter_Password(void){

	u8 key = NO_KEY , pass_iterator = 0 , trials_Flag = 0 , i = 0 ;
	Error_Status state = SUCCESS;
	u8 temp_pass[MAX_DIGITS_PASS]= {0};
	u8 EEPROM_pass[MAX_DIGITS_PASS]= {0};

	/*
	 * Read password form memory
	 * */
	do{
		EEPROM_voidRead(address_pass[0][i],&EEPROM_pass[i]);
		_delay_ms(15);
		i++;
	}while(i < MAX_DIGITS_PASS );

	do{
		HLCD_clearScrean();
		HLCD_displayString("Enter Password: ");
		HLCD_moveCursor(1,0);
		pass_iterator=0;
		trials_Flag++;
		/*
		 * Get password from user
		 */
		do{
			/*
			 * Scan from keypad
			 */
			do{
				key = H_KeyPad_u8GetKey();
			}while(key == NO_KEY);
			/*
			 * Store Number at array and display it at LCD
			 */
			temp_pass[pass_iterator] = key;
			HLCD_intgerToString(key);
			pass_iterator++;

		}while(pass_iterator < MAX_DIGITS_PASS);

		state = SUCCESS;

		for(pass_iterator = 0 ; pass_iterator < MAX_DIGITS_PASS ; pass_iterator++){

			if(temp_pass[pass_iterator] != EEPROM_pass[pass_iterator]){
				state = FAILED;
				break;
			}
		}

	}while( (trials_Flag <3 ) && (state == FAILED) );

	return state;
}

void Open_System(void){
	u8 key = NO_KEY ;
	HLCD_clearScrean();
	HLCD_displayString("System is Open");

	M_SPI_sendReceiveByte(READY);
	M_TIMER0_voidSelectPrescaler(PRESC_8);

	do{

		if(M_UART_u8RxcFlagState()){
			SendChar_Spi = MUART_u8ReturnValReceived();
			M_SPI_sendReceiveByte(SendChar_Spi);
		}

		key = H_KeyPad_u8GetKey();
	}while(key != '#');
	M_TIMER0_voidSelectPrescaler(NO_CLK);
}
void ISR_TIMER(void){
	M_TIMER0_voidSetPreLoad(6);
	g_timer++;
	if(g_timer == 100){
		SendChar_Spi = LM35_getTemperature();
		M_SPI_sendReceiveByte(SendChar_Spi);
	}else if(g_timer == 120){
		g_timer = 0 ;
		SendChar_Spi = HLDR_u16GetSensorRead();
	}
		M_SPI_sendReceiveByte(SendChar_Spi);
}

/*
 *
 *

		//		if(M_UART_u8RxcFlagState()){  //0
		//			SendChar_Spi = MUART_u8ReturnValReceived();
		//		}else{
		//		Sync_flag++;
		//		switch (Sync_flag){
		//		case 1 : SendChar_Spi = LM35_getTemperature();
		//		break;
		//		case 2 : SendChar_Spi = HLDR_u16GetSensorRead();
		//		M_SPI_sendReceiveByte(SendChar_Spi);
		//		Sync_flag = 0;
		//		break;
		//		}
		//		}
		/*if(g_BluetoothFlag){
			M_SPI_sendReceiveByte(g_BluetoothData);
			g_BluetoothFlag = 0;
		}
		else{
			Sync_flag++;
			if(Sync_flag == 1){
				SendChar_Spi = LM35_getTemperature();
			}
			else if(Sync_flag == 2){
				Sync_flag=0;
				SendChar_Spi = HLDR_u16GetSensorRead();
			}
		}*/
