################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App_Slave.c \
../DCMOTOR_program.c \
../H7SEG_program.c \
../HLED_program.c \
../MDIO_program.c \
../M_TIMER_program.c \
../SERVO_program.c \
../m_spi_program.c \
../mgie_program.c \
../stepmotor_program.c 

OBJS += \
./App_Slave.o \
./DCMOTOR_program.o \
./H7SEG_program.o \
./HLED_program.o \
./MDIO_program.o \
./M_TIMER_program.o \
./SERVO_program.o \
./m_spi_program.o \
./mgie_program.o \
./stepmotor_program.o 

C_DEPS += \
./App_Slave.d \
./DCMOTOR_program.d \
./H7SEG_program.d \
./HLED_program.d \
./MDIO_program.d \
./M_TIMER_program.d \
./SERVO_program.d \
./m_spi_program.d \
./mgie_program.d \
./stepmotor_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


