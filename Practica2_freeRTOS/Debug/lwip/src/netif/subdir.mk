################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/netif/ethernet.c \
../lwip/src/netif/lowpan6.c \
../lwip/src/netif/slipif.c 

OBJS += \
./lwip/src/netif/ethernet.o \
./lwip/src/netif/lowpan6.o \
./lwip/src/netif/slipif.o 

C_DEPS += \
./lwip/src/netif/ethernet.d \
./lwip/src/netif/lowpan6.d \
./lwip/src/netif/slipif.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/netif/%.o: ../lwip/src/netif/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DPRINTF_FLOAT_ENABLE=0 -DFRDM_K64F -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DCR_INTEGER_PRINTF -DFREEDOM -DPRINTF_ADVANCED_ENABLE=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_FREE_RTOS -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -I"C:\Projects_2\Practica2_freeRTOS\board" -I"C:\Projects_2\Practica2_freeRTOS\source" -I"C:\Projects_2\Practica2_freeRTOS" -I"C:\Projects_2\Practica2_freeRTOS\drivers" -I"C:\Projects_2\Practica2_freeRTOS\CMSIS" -I"C:\Projects_2\Practica2_freeRTOS\utilities" -I"C:\Projects_2\Practica2_freeRTOS\startup" -I"C:\Projects_2\Practica2_freeRTOS\lwip\contrib\apps\tcpecho" -I"C:\Projects_2\Practica2_freeRTOS\lwip\port\arch" -I"C:\Projects_2\Practica2_freeRTOS\lwip\port" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\lwip\priv" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\lwip\prot" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\lwip" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\netif\ppp\polarssl" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\netif\ppp" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\netif" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\posix\sys" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include\posix" -I"C:\Projects_2\Practica2_freeRTOS\freertos\include" -I"C:\Projects_2\Practica2_freeRTOS\freertos\portable" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src" -I"C:\Projects_2\Practica2_freeRTOS\lwip\src\include" -I"C:\Projects_2\Practica2_freeRTOS\lwip\contrib\apps" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


