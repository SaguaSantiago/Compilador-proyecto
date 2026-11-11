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
add %r10, %r11
mov %r11, -16(%rbp)
mov -16(%rbp), %r11
mov %r11, -8(%rbp)
instruccion no procesada: 19
ret 
instruccion no procesada: 17
main:
enter $(8 * 4), $0
instruccion no procesada: 18
mov $4, -24(%rbp)
add %r10, %r11
mov %r11, -32(%rbp)
mov -32(%rbp), %r11
mov %r11, -24(%rbp)
L1:
instruccion no procesada: 6
instruccion no procesada: 6
call prueba
mov %eax, -40(%rbp)
cmp %r10, %r11
mov $0, %r11
mov $1, %r10
cmovl %r10, %r11
mov %r11, -48(%rbp)
instruccion no procesada: 16
instruccion no procesada: 19
jmp L1
L2:
ret 
