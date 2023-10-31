#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Makefile to compile and/or link a simple project into the desired platform.
#
# Use: 
#     	make build PLATFORM=[HOST/MSP432]
#		make compile-all PLATFORM=[HOST/MSP432]
#		make clean
#
#***********PLATFORM MUST BE DECLARED AND SET WHEN RUNNING THE BUILD/COMPILE-ALL COMMAND
#
# Build Targets:
#      Provided the desired Platform, the respective files can be generated out of the c-program implementation files:
# 					- Preprocessed files [*.i]
# 					- Assembly files [*.asm]
# 					- Object files [*.o]
#
# Platform Overrides:
#      The supported platforms are the local host device and the MSP432 device.
#
#------------------------------------------------------------------------------
include sources.mk

# Platform Overrides
PLATFORM = HOST
VERBOSE = false
COURSE1 = false

# Final output file name
TARGET = c1mf

# Compiler Flags and Defines
CFLAGS =\
	-Wall	\
	-Werror	\
	-g		\
	-O0		\
	-std=c99	\
	-D$(PLATFORM)

ifeq ($(VERBOSE), defined)
	CFLAGS += -DVERBOSE
endif
ifeq ($(COURSE1), true)
	CFLAGS += -DCOURSE1
endif

CPPFLAGs = -E

ifeq ($(PLATFORM), HOST)
	CC = gcc
	LD = ld
	LDFLAGS = -Wl,-Map=$(TARGET).map
	OBJDUMP = objdump
	SIZE = size
else 
	ifeq ($(PLATFORM), MSP432)
	CC =  arm-none-eabi-gcc
	LD = arm-none-eabi-ld
	LINKER_FILE = ./msp432p401r.lds
	LDFLAGS = -Wl,-Map=$(TARGET).map -T $(LINKER_FILE)
	CPU = cortex-m4
	ARCH = armv7e-m
	SPECS = nosys.specs
	FPU = fpv4-sp-d16
	ARMSFLAGS = -march=$(ARCH) -mthumb -mfloat-abi=hard -mfpu=$(FPU) --specs=$(SPECS)
	OBJDUMP = arm-none-eabi-objdump
	SIZE = arm-none-eabi-size
	CFLAGS += $(ARMSFLAGS)
else
$(error ****Unsoported Platform, please check*****)
endif
endif


OBJS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)

################ Commands section ###################

# Preprocessed file generation from c-source file
%.i: %.c 
	$(CC) $(INCLUDES) $(CPPFLAGs) $< $(CFLAGS) -o $@

# Object file generation from c-source file
%.o : %.c
	$(CC) $(INCLUDES) -c $< $(CFLAGS) -o $@

# Dependency file generation from c-source file
%.d: %.c
	$(CC) $(INCLUDES) -M $< $(CFLAGS) -o $@

# Assembly file generation from c-source file
%.asm: %.c
	$(CC) $(INCLUDES) -S $< $(CFLAGS) -o $@

# Assembly file from final output executable
$(TARGET).asm: $(TARGET).out
	$(OBJDUMP) -d $< >> $@

# Compile all out of specified PLATFORM
.PHONY: compile-all
compile-all: $(OBJS)
	@echo  "\nCompiling all for $(PLATFORM)\n"
	$(CC) $(INCLUDES) $(OBJS) -c $(CFLAGS) -o $(TARGET).o

# Build out of specified PLATFORM
.PHONY: build
build: $(TARGET).out $(TARGET).asm

$(TARGET).out: $(OBJS) $(DEPS)
	@echo  "\nBuilding and build report for $(PLATFORM)\n"
	$(CC) $(OBJS) $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o $@
# $(SIZE) $(TARGET).out

# Clean all generated files from directory
.PHONY: clean
clean:
	rm -f $(TARGET).out *.asm *map	&& 		\
	cd src 							&& 		\
	rm -f  *.o *.d					&&		\
	clear