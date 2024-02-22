################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Aplicacion/Infotronic_garage.c \
../src/Aplicacion/Inicializacion.c \
../src/Aplicacion/maquina_estados.c 

OBJS += \
./src/Aplicacion/Infotronic_garage.o \
./src/Aplicacion/Inicializacion.o \
./src/Aplicacion/maquina_estados.o 

C_DEPS += \
./src/Aplicacion/Infotronic_garage.d \
./src/Aplicacion/Inicializacion.d \
./src/Aplicacion/maquina_estados.d 


# Each subdirectory must supply rules for building sources it contributes
src/Aplicacion/%.o: ../src/Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Aplicacion" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Drivers_Infotronic" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Drivers_LPC1769" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Primitivas" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


