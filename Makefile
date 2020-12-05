
CC = clang -target aarch64-none-elf
AS = aarch64-none-elf-as
LD = aarch64-none-elf-ld

CFLAGS = -Wall -Wextra -O2 -ffreestanding -nostdinc -nostdlib -c
LDFLAGS = -nostdlib -nostartfiles -T linkin.ld

.PHONY: clean all

all: kernel8.img

boot.o: kernel/boot.S
	$(AS) kernel/boot.S -o boot.o
	
kernel_main.o: kernel/kern_main.c
	$(CC) $(CFLAGS) kernel/kern_main.c -o kern_main.o

kernel8.img: kernel_main.o boot.o
	$(LD) $(LDFLAGS) boot.o kern_main.o -o kernel8.img
	
clean:
	rm -rf *.o kernel8.img
