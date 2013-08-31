CC=arm-linux-gnueabi-gcc

CFLAGS=-ansi -pedantic -Wall -Wextra -march=armv6 -msoft-float -fPIC -mapcs-frame
LDFLAGS=-nostdlib -N -Ttext=0x10000

kernel.elf: bootstrap.o kernel.o main.o supervisor.o

run: kernel.elf
	qemu-system-arm -M versatilepb -cpu arm1176 -nographic -kernel kernel.elf

.PHONY: clean

clean:
	$(RM) *.elf *.o

.SUFFIXES: .s .o .elf

.s.o:
	$(CC) $(CFLAGS) -o $@ -c $^

.o.elf:
	$(CC) $(LDFLAGS) -o $@ $^ -lgcc -lc
