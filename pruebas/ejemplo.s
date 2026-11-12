section .bss

  global: resd 1 
  global1: resd 1 

section .data

section .text

instruccion no procesada: 17

prueba:
enter $(8 * 2), $0

instruccion no procesada: 18

mov $1, [global1]

mov $3, %r10
mov [global1], %r11
add %r10, %r11
mov %r11, -16(%rbp)

mov -16(%rbp), %r11
mov %r11, -8(%rbp)

mov [global1], %r10
mov %r10, %rax

leave 
ret 

instruccion no procesada: 17

main:
enter $(8 * 4), $0

instruccion no procesada: 18

mov $4, -16(%rbp)

mov -16(%rbp), %r10
mov $1, %r11
add %r10, %r11
mov %r11, -24(%rbp)

mov -24(%rbp), %r11
mov %r11, -16(%rbp)

mov -16(%rbp), %r10
mov %r10, %rax

L1:

mov -16(%rbp), %r10
mov %r10, %rdi
mov $4, %r10
mov %r10, %rsi
call prueba
mov %eax, -24(%rbp)

mov -24(%rbp), %r10
mov $2, %r11
cmp %r10, %r11
mov $0, %r11
mov $1, %r10
cmovl %r10, %r11
mov %r11, -32(%rbp)

;IF_FALSE
mov -32(%rbp), %r11
mov $0, %r10
cmp %r11, %r10
je L2

mov -16(%rbp), %r10
mov %r10, %rax

jmp L1

L2:

leave 
ret 

