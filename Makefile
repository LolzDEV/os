# BUILD
CC=riscv64-unknown-linux-gnu-gcc
CFLAGS=-Wall -Wextra -pedantic -Wextra -O0 -g -std=c11 -mcmodel=medany
CFLAGS+=-static -ffreestanding -nostdlib -fno-exceptions
CFLAGS+=-march=rv64gc -mabi=lp64
INCLUDES=
LINKER_SCRIPT=-Tsrc/kernel.ld
TYPE=debug
SOURCES_C=$(wildcard src/*.c)
SOURCES_ASM=$(wildcard src/*.S)
LIB=-lgcc
BUILD=build
OUT=kernel.elf

# EMULATION
QEMU=qemu-system-riscv64
MACH=virt
CPU=rv64
CPUS=4
MEM=128M
DRIVE=hdd.dsk

all:
	$(CC) $(CFLAGS) $(LINKER_SCRIPT) $(INCLUDES) -o $(BUILD)/$(OUT) $(SOURCES_ASM) $(SOURCES_C) $(LIBS) $(LIB)

run: all
	$(QEMU) -machine $(MACH) -cpu $(CPU) -smp $(CPUS) -m $(MEM) -monitor stdio -bios none -kernel $(BUILD)/$(OUT) -drive if=none,format=raw,file=$(DRIVE),id=foo -device virtio-blk-device,scsi=off,drive=foo

.PHONY: clean
clean:
	rm -f $(BUILD)/*
