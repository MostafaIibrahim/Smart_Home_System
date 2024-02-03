################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App.c \
../EEPROM_program.c \
../H_KEYPAD_program.c \
../MTWI_program.c \
../M_TIMER_program.c \
../adc_program.c \
../hlcd_program.c \
../hldr_program.c \
../lm035_program.c \
../m_spi_program.c \
../m_uart_program.c \
../mdio_program.c \
../mgie_program.c 

OBJS += \
./App.o \
./EEPROM_program.o \
./H_KEYPAD_program.o \
./MTWI_program.o \
./M_TIMER_program.o \
./adc_program.o \
./hlcd_program.o \
./hldr_program.o \
./lm035_program.o \
./m_spi_program.o \
./m_uart_program.o \
./mdio_program.o \
./mgie_program.o 

C_DEPS += \
./App.d \
./EEPROM_program.d \
./H_KEYPAD_program.d \
./MTWI_program.d \
./M_TIMER_program.d \
./adc_program.d \
./hlcd_program.d \
./hldr_program.d \
./lm035_program.d \
./m_spi_program.d \
./m_uart_program.d \
./mdio_program.d \
./mgie_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


