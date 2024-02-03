# Smart_Home_System
The aim of this project is to control your home remotely by controlling different systems such as :- Light system - Fans - Garage door - Home door
#Overiew
Controlling different systems is done by Master Microcontroller ATmega32. This is master will be responsible of any input data in the system.
-Master MCU will ask the user to choose one of 3 modes:
			1- Open SmartSystem
			2- Change Password
			3- Add User
	1- Open SmartSystem:
		1 - Master MCU will ask you about your User ID and password?
			case 1: Wrong ID >> master mcu will ask you about a valid ID
			case 2: Your password is true>> Now you can control any electronic device in your home via your smart phone
			case 3: Your password is wrong>> Master mcu will ask you to enter your password again for more 3 times if ur password still wrong, Master mcu return you to the main menu.
		
		
		2 - MCU2 work as Slave and it controls the following behaviors:
			1 - if temperature is bigger than 35C fan will work
			2 - Based on Ambiant light (data came from LDR sensor) your home light will turns on 
			3 - if user pressed on button '1' send via Bluetooth >> the door will open (Servo motor will move to angle 180)
			4 - if user pressed on button '2' send via Bluetooth >> the door will close (Servo motor will move back to angle 0)
			5 - if user pressed on button '3' send via Bluetooth >> fan will work (Dc Motor will run)
			6 - if user pressed on button '4' send via Bluetooth >> fan will stop (Dc Motor will stop)
			7 - if user pressed on button '5' send via Bluetooth >> garage door will open  (Stepper motor will move to reach 270 degree)
			8 - if user pressed on button '6' send via Bluetooth >> garage door will close (Stepper motor will move back to its previous position)
			9 - if user say "open light"      send via Bluetooth >> the light turns On  (8 LEDS should be On) 
			10- if user say "close light"     send via Bluetooth >> the light turns Off (8 LEDS should be Off)  
			
		Note:
			1 - Master MCU will send all data to Slave MCU via SPI protocol.
			2 - Your password should be reserved in a non-volatile memory (External EEPROM)
			3 - Temperature degree should displayed on 2 SevenSegment
			4 - you should not use the _delay_ms function, you should use Timer to make delay 
			
	2- Change Password:
		Master mcu will ask you to enter the User ID then User previous password
		case 1: Wrong ID >> master mcu will ask you about a valid ID
		case 2: if previous password is True >> Master mcu will ask you to enter your New Password
		case 3: if previous password is wrong >> Master mcu will ask you to enter your password again for more one time if ur password still wrong, Master mcu return you to the main menu.
	3- Add User:
		1 - Master mcu will ask you to enter User ID
		2 - Master mcu will ask you to enter User Password
		3 - Master mcu will ask you to confirm your password
			case 1: if your confirmation password is True >> Master mcu will return back to main menu
			case 2: if your confirmation password is wrong >> Master mcu will print Wrong password and return back to main menu 
#Componants
1- Atmega32 microcontroller 	QTY>2
2- LCD 16X2						QTY>1
3- KeyPad 4x4					QTY>1
4- LM35 temp. sensor			QTY>1
5- HC-05|06 Bluetooth module	QTY>1
6- LDR sensor					QTY>1
7- External EEPROM				QTY>1
8- Limited Servo Motor			QTY>1
9- DC Motor						QTY>1
10-Stepper Motor				QTY>1
11-LED							QTY>8
12-Seven-Segment Display		QTY>2		
