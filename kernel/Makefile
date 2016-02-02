C_FILES := $(wildcard *.c)
ASM_FILES := $(wildcard *.asm)
OBJ_FILES := $(C_FILES:.c=.o) $(ASM_FILES:.asm=.o)

kernel.bin: $(OBJ_FILES)
	/usr/local/gcc-4.8.1-for-linux32/bin/i586-pc-linux-ld -T linker.ld -melf_i386 -o $@ $^

%.o: %.c
	/usr/local/gcc-4.8.1-for-linux32/bin/i586-pc-linux-gcc -std=c99 -ffreestanding -m32 -c -O0 -o $@ $<

%.o: %.asm
	nasm -f elf -o $@ $<

.PHONY: clean
clean:
	rm *.o kernel.bin
