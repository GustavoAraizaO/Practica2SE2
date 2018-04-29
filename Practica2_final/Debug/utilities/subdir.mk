################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c \
../utilities/fsl_io.c \
../utilities/fsl_log.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_debug_console.o \
./utilities/fsl_io.o \
./utilities/fsl_log.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_debug_console.d \
./utilities/fsl_io.d \
./utilities/fsl_log.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DPRINTF_FLOAT_ENABLE=0 -D__USE_CMSIS -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -DDEBUG -DSDK_OS_FREE_RTOS -DFSL_RTOS_FREE_RTOS -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -I"C:\Projects_2\Practica2\board" -I"C:\Projects_2\Practica2\source" -I"C:\Projects_2\Practica2" -I"C:\Projects_2\Practica2\freertos\include" -I"C:\Projects_2\Practica2\freertos\portable" -I"C:\Projects_2\Practica2\drivers" -I"C:\Projects_2\Practica2\CMSIS" -I"C:\Projects_2\Practica2\utilities" -I"C:\Projects_2\Practica2\lwip\port\arch" -I"C:\Projects_2\Practica2\lwip\port" -I"C:\Projects_2\Practica2\lwip\src\include\lwip\priv" -I"C:\Projects_2\Practica2\lwip\src\include\lwip\prot" -I"C:\Projects_2\Practica2\lwip\src\include\lwip" -I"C:\Projects_2\Practica2\lwip\src\include\netif\ppp\polarssl" -I"C:\Projects_2\Practica2\lwip\src\include\netif\ppp" -I"C:\Projects_2\Practica2\lwip\src\include\netif" -I"C:\Projects_2\Practica2\lwip\src\include\posix\sys" -I"C:\Projects_2\Practica2\lwip\src\include\posix" -I"C:\Projects_2\Practica2\startup" -I"C:\Projects_2\Practica2\lwip\template_application" -I"C:\Projects_2\Practica2\lwip\src" -I"C:\Projects_2\Practica2\lwip\src\include" -I"C:\Projects_2\Practica2\lwip\contrib\apps" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


