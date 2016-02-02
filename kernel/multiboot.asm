[BITS 32]

FLAGS equ 0
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot

align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
