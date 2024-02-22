################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers_LPC1769/DR_Adc.c \
../src/Drivers_LPC1769/DR_EINT.c \
../src/Drivers_LPC1769/DR_PLL.c \
../src/Drivers_LPC1769/DR_Pwm.c \
../src/Drivers_LPC1769/DR_RTC.c \
../src/Drivers_LPC1769/DR_SysTick.c \
../src/Drivers_LPC1769/DR_Timer.c \
../src/Drivers_LPC1769/DR_gpio.c \
../src/Drivers_LPC1769/DR_pinsel.c \
../src/Drivers_LPC1769/DR_uart.c 

OBJS += \
./src/Drivers_LPC1769/DR_Adc.o \
./src/Drivers_LPC1769/DR_EINT.o \
./src/Drivers_LPC1769/DR_PLL.o \
./src/Drivers_LPC1769/DR_Pwm.o \
./src/Drivers_LPC1769/DR_RTC.o \
./src/Drivers_LPC1769/DR_SysTick.o \
./src/Drivers_LPC1769/DR_Timer.o \
./src/Drivers_LPC1769/DR_gpio.o \
./src/Drivers_LPC1769/DR_pinsel.o \
./src/Drivers_LPC1769/DR_uart.o 

C_DEPS += \
./src/Drivers_LPC1769/DR_Adc.d \
./src/Drivers_LPC1769/DR_EINT.d \
./src/Drivers_LPC1769/DR_PLL.d \
./src/Drivers_LPC1769/DR_Pwm.d \
./src/Drivers_LPC1769/DR_RTC.d \
./src/Drivers_LPC1769/DR_SysTick.d \
./src/Drivers_LPC1769/DR_Timer.d \
./src/Drivers_LPC1769/DR_gpio.d \
./src/Drivers_LPC1769/DR_pinsel.d \
./src/Drivers_LPC1769/DR_uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers_LPC1769/%.o: ../src/Drivers_LPC1769/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Aplicacion" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Drivers_Infotronic" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Drivers_LPC1769" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Primitivas" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


