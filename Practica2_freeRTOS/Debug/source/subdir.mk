################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/lwip_tcpecho_freertos.c \
../source/semihost_hardfault.c 

OBJS += \
./source/lwip_tcpecho_freertos.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/lwip_tcpecho_freertos.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DPRINTF_FLOAT_ENABLE=0 -DFRDM_K64F -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DCR_INTEGER_PRINTF -DFREEDOM -DPRINTF_ADVANCED_ENABLE=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_FREE_RTOS -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -I"C:\Projects_2\Practica2_freeRTOS\board" -I"C:\Projects_2\Practica2_freeRTOS\source" -I"C:\Projects_2\Practica2_freeRTOS" -I"C:\Projects_2\Practica2_freeRTOS\drivers" -I"C:\Projects_2\Practica2_freeRTOS\CMSIS" -I"C:\Projects_2\Practica2_freeRTOS\utilities" -I"C:\Projects_2\Practica2_freeRTOS\startup" -I"C:\Projects_2\Practica2_freeRTOS\lwip\contrib\apps\tcpecho" -I"C:\Projects_2\Practica2_freeRTOS\lwip\port\arch" -I"C:\Projects_2\Practica2_freeRTOS\lwip\port" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\lwip\priv" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\lwip\prot" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\lwip" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\netif\ppp\polarssl" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\netif\ppp" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\netif" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\posix\sys" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\posix" -I"C:\Projects_2\Practica2_freeRTOS\freertos\include" -I"C:\Projects_2\Practica2_freeRTOS\freertos\portable" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include" -I"C:\Projects_2\Practica2_freeRTOS\lwip\contrib\apps" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


