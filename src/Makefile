MSP430PATH = /usr/local/msp430
MSP430MCU = msp430g2553
GCCVERSION = $(shell ls $(MSP430PATH)/lib/gcc/msp430-elf | head -n1)

CC = $(MSP430PATH)/bin/msp430-elf-gcc
CFLAGS = -Os -nostdlib -std=c++17 -ffunction-sections -fdata-sections -mmcu=$(MSP430MCU)

CXX = $(MSP430PATH)/bin/msp430-elf-g++
CXXFLAGS = $(CFLAGS)

AR = $(MSP430PATH)/bin/msp430-elf-ar

LD = $(MSP430PATH)/bin/msp430-elf-ld
LDFLAGS = -L $(MSP430PATH)/msp430-elf/lib/430 \
	-L $(MSP430PATH)/lib/gcc/msp430-elf/$(GCCVERSION)/430 \
	-T $(MSP430MCU).ld -l:crt0.o -lgcc

objects = \
	digital-io.o \
	timer.o \
	usci-spi.o \
	watchdog.o

libmdlmsp430.a: $(objects)
	$(AR) rvs $@ $^

digital-io.o:

timer.o:

usci-spi.o:

watchdog.o:

.PHONY: clean

clean:
	$(RM) *.o libmdlmsp430.a
