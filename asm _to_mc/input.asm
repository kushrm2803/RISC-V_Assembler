beq x0 x0 do
.data
a : .word 0xDEADBEEF,14,0b11010111
b : .byte 10,0x81,0b11111111
c : .half 0x55,20,0b11000001 
#d : .dword 0x77,90,0b111111111
e : .asciiz "My name is Slim Shady"
.text
label1:
add x10 x10 x10 
and x0 x0 x0 
srl x0 x0 x23
do:
jal x1 label1
label2: and x0 x0 x0 
srl x0 x0 x23
addi x1 x0 3996
andi x12 x12 -12345
ld x12 0(x13)
lh x12 0b101110101(x12)
sb x8 32(x7)
sw x6 -4(x5)
jalr x1,x0,0
label3: jalr x1,x0,0b101101
auipc x1,0b10101010301010
auipc x10,-0xAABC
label4: lui x10,-3244
auipc x10,0xAAFG
auipc x10,124378
addi x1 x0 234G
label5: sh x11 0A(x6)

addi x1 x3 5 7
add x3 x2 x4 x5
sb x1 8(x2) 4
ld  x2 5(x4) 9
lui x2 12333 7
auipc 5 76784 x6
addi x1 x2 6 x5
jal x1 label1 3
bge x1 x2 label2 x6

add x2 x3 4
addi x2 x5 x6
lw x4 x6(x5)
lui 2 5
blt x5 5 label3