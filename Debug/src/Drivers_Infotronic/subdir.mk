################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers_Infotronic/DR_7Seg_Expansion3.c \
../src/Drivers_Infotronic/DR_Antirebote_Digital.c \
../src/Drivers_Infotronic/DR_EntradaDigital.c \
../src/Drivers_Infotronic/DR_LCD.c \
../src/Drivers_Infotronic/DR_Rgb.c \
../src/Drivers_Infotronic/DR_Segmento.c \
../src/Drivers_Infotronic/DR_Teclado.c \
../src/Drivers_Infotronic/DR_Teclado_Expansion3.c 

OBJS += \
./src/Drivers_Infotronic/DR_7Seg_Expansion3.o \
./src/Drivers_Infotronic/DR_Antirebote_Digital.o \
./src/Drivers_Infotronic/DR_EntradaDigital.o \
./src/Drivers_Infotronic/DR_LCD.o \
./src/Drivers_Infotronic/DR_Rgb.o \
./src/Drivers_Infotronic/DR_Segmento.o \
./src/Drivers_Infotronic/DR_Teclado.o \
./src/Drivers_Infotronic/DR_Teclado_Expansion3.o 

C_DEPS += \
./src/Drivers_Infotronic/DR_7Seg_Expansion3.d \
./src/Drivers_Infotronic/DR_Antirebote_Digital.d \
./src/Drivers_Infotronic/DR_EntradaDigital.d \
./src/Drivers_Infotronic/DR_LCD.d \
./src/Drivers_Infotronic/DR_Rgb.d \
./src/Drivers_Infotronic/DR_Segmento.d \
./src/Drivers_Infotronic/DR_Teclado.d \
./src/Drivers_Infotronic/DR_Teclado_Expansion3.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers_Infotronic/%.o: ../src/Drivers_Infotronic/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Aplicacion" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Drivers_Infotronic" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Drivers_LPC1769" -I"C:\Users\Alka\Documents\LPCXpresso_7.7.2_379\workspace\TPO_v22_0_entrada\src\Primitivas" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


