################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_salida\src\Aplicacion" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_salida\src\Drivers_Infotronic" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_salida\src\Drivers_LPC1769" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_salida\src\Primitivas" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


