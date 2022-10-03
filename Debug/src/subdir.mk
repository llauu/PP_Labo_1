################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PP_Lautaro_Monserrat.c \
../src/mylib.c \
../src/perfilAdmin.c \
../src/perfilColeccionista.c 

C_DEPS += \
./src/PP_Lautaro_Monserrat.d \
./src/mylib.d \
./src/perfilAdmin.d \
./src/perfilColeccionista.d 

OBJS += \
./src/PP_Lautaro_Monserrat.o \
./src/mylib.o \
./src/perfilAdmin.o \
./src/perfilColeccionista.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/PP_Lautaro_Monserrat.d ./src/PP_Lautaro_Monserrat.o ./src/mylib.d ./src/mylib.o ./src/perfilAdmin.d ./src/perfilAdmin.o ./src/perfilColeccionista.d ./src/perfilColeccionista.o

.PHONY: clean-src

