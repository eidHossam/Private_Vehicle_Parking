################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include stm32f103x6_Drivers/MCAL/SYSTICK/subdir.mk
-include stm32f103x6_Drivers/MCAL/SPI/subdir.mk
-include stm32f103x6_Drivers/MCAL/RCC/subdir.mk
-include stm32f103x6_Drivers/MCAL/NVIC/subdir.mk
-include stm32f103x6_Drivers/MCAL/GPIO/subdir.mk
-include stm32f103x6_Drivers/MCAL/EXTI/subdir.mk
-include stm32f103x6_Drivers/MCAL/AFIO/subdir.mk
-include stm32f103x6_Drivers/LIB/FIFO_Buffer_Driver/subdir.mk
-include stm32f103x6_Drivers/HAL/LCD_Driver/subdir.mk
-include stm32f103x6_Drivers/HAL/Keypad_Driver/subdir.mk
-include stm32f103x6_Drivers/APP/Gates_Communication/subdir.mk
-include stm32f103x6_Drivers/APP/Admin_Interface/subdir.mk
-include stm32f103x6_Drivers/APP/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MainControlECU.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MainControlECU.list \

OBJCOPY_HEX += \
MainControlECU.hex \

OBJCOPY_BIN += \
MainControlECU.bin \


# All Target
all: MainControlECU.elf secondary-outputs

# Tool invocations
MainControlECU.elf: $(OBJS) $(USER_OBJS) D:\Learn-In-Depth\Private_Vechicle_Parking\Main_Control_ECU\MainControlECU_Src\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "MainControlECU.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Learn-In-Depth\Private_Vechicle_Parking\Main_Control_ECU\MainControlECU_Src\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MainControlECU.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MainControlECU.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MainControlECU.list"
	@echo 'Finished building: $@'
	@echo ' '

MainControlECU.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "MainControlECU.hex"
	@echo 'Finished building: $@'
	@echo ' '

MainControlECU.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "MainControlECU.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
