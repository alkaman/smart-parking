################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Primitivas/PR_7Seg_Expansion3.c \
../src/Primitivas/PR_7seg.c \
../src/Primitivas/PR_EntradaDigital.c \
../src/Primitivas/PR_LCD.c \
../src/Primitivas/PR_Pwm.c \
../src/Primitivas/PR_Rgb.c \
../src/Primitivas/PR_Sensores.c \
../src/Primitivas/PR_Teclado.c \
../src/Primitivas/PR_Teclado_Expansion3.c \
../src/Primitivas/PR_Temperatura.c \
../src/Primitivas/PR_Timer.c 

OBJS += \
./src/Primitivas/PR_7Seg_Expansion3.o \
./src/Primitivas/PR_7seg.o \
./src/Primitivas/PR_EntradaDigital.o \
./src/Primitivas/PR_LCD.o \
./src/Primitivas/PR_Pwm.o \
./src/Primitivas/PR_Rgb.o \
./src/Primitivas/PR_Sensores.o \
./src/Primitivas/PR_Teclado.o \
./src/Primitivas/PR_Teclado_Expansion3.o \
./src/Primitivas/PR_Temperatura.o \
./src/Primitivas/PR_Timer.o 

C_DEPS += \
./src/Primitivas/PR_7Seg_Expansion3.d \
./src/Primitivas/PR_7seg.d \
./src/Primitivas/PR_EntradaDigital.d \
./src/Primitivas/PR_LCD.d \
./src/Primitivas/PR_Pwm.d \
./src/Primitivas/PR_Rgb.d \
./src/Primitivas/PR_Sensores.d \
./src/Primitivas/PR_Teclado.d \
./src/Primitivas/PR_Teclado_Expansion3.d \
./src/Primitivas/PR_Temperatura.d \
./src/Primitivas/PR_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/Primitivas/%.o: ../src/Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_salida\src\Aplicacion" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_salida\src\Drivers_Infotronic" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_salida\src\Drivers_LPC1769" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_salida\src\Primitivas" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


