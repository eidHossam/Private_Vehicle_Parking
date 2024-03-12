################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32f103x6_Drivers/HAL/Seven_Segment_Display_Driver/Seven_Seg_Driver_Program.c 

OBJS += \
./stm32f103x6_Drivers/HAL/Seven_Segment_Display_Driver/Seven_Seg_Driver_Program.o 

C_DEPS += \
./stm32f103x6_Drivers/HAL/Seven_Segment_Display_Driver/Seven_Seg_Driver_Program.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f103x6_Drivers/HAL/Seven_Segment_Display_Driver/Seven_Seg_Driver_Program.o: ../stm32f103x6_Drivers/HAL/Seven_Segment_Display_Driver/Seven_Seg_Driver_Program.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Learn-In-Depth/Private_Vechicle_Parking/Main_Control_ECU/MainControlECU_Src/stm32f103x6_Drivers/APP" -I"D:/Learn-In-Depth/Private_Vechicle_Parking/Main_Control_ECU/MainControlECU_Src/stm32f103x6_Drivers/HAL" -I"D:/Learn-In-Depth/Private_Vechicle_Parking/Main_Control_ECU/MainControlECU_Src/stm32f103x6_Drivers/MCAL" -I"D:/Learn-In-Depth/Private_Vechicle_Parking/Main_Control_ECU/MainControlECU_Src/stm32f103x6_Drivers/LIB" -I"D:/Learn-In-Depth/Private_Vechicle_Parking/Main_Control_ECU/MainControlECU_Src/stm32f103x6_Drivers/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32f103x6_Drivers/HAL/Seven_Segment_Display_Driver/Seven_Seg_Driver_Program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

