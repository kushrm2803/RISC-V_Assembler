# RISC-V Assembler

This is a simple RISC-V assembler program based on Venus that converts RISC-V assembly language (.asm) into machine language (.mc) format. The program supports both .text and .data sections. The support for pseudo instructions and floating-point operations is not included.

## Supported Instructions

The program supports the following RISC-V 32-bit ISA instructions:

### R Format
- add
- and
- or
- sll
- slt
- sra
- srl
- sub
- xor
- mul
- div
- rem

### I Format
- addi
- andi
- ori
- lb
- ld
- lh
- lw
- jalr

### S Format
- sb
- sw
- sd
- sh

### SB Format
- beq
- bne
- bge
- blt

### U Format
- auipc
- lui

### UJ Format
- jal

## Assembler Directives

The program also supports the following assembler directives:

- .text
- .data
- .byte
- .half
- .word
- .dword
- .asciz

## Usage

To run the program, follow these steps:

1. **Input File**: Create an input assembly file (e.g., `input.asm`) containing your RISC-V assembly instructions. Each instruction should be on a single line.

2. **Command Line**: Compile and execute the C++ program from the command line. Provide the input assembly file as an argument along with ./a.exe or ./a.out.

3. **Output**: The program will create a separate file named `input.mc`, which contains the parsed assembly language instructions converted into machine language in hexadecimal form.

## Example

Here's an example of an input assembly file (`input.asm`):

```assembly
.text
addi x1 x0 10
addi x2 x1 20
#This is a comment
sw x2 0(x1)
.data
a : .byte 1,2,3
b : .half 2
c : .word 0xA2,45
d : .dword 4
e : .asciiz "Hello, World!"
```

Running the program with this input:

```machine code
0x 0x00A00093
0x4 0x01408113
0x8 0x0020A023


------------------------DATA--------------------------
0x10000000 01
0x10000001 02
0x10000002 03
0x10000003 02
0x10000004 00
0x10000005 A2
0x10000006 00
0x10000007 00
0x10000008 00
0x10000009 2D
0x1000000A 00
0x1000000B 00
0x1000000C 00
0x1000000D 04
0x1000000E 00
0x1000000F 00
0x10000010 00
0x10000011 00
0x10000012 00
0x10000013 00
0x10000014 00
0x10000015 48
0x10000016 65
0x10000017 6C
0x10000018 6C
0x10000019 6F
0x1000001A 20
0x1000001B 57
0x1000001C 6F
0x1000001D 72
0x1000001E 6C
0x1000001F 64
0x10000020 21
0x10000021 00
```

Will generate an output file (`input.mc`) containing the machine language code.

## Contributors

- [Dhruv Gupta](https://github.com/dhruvgupta2112) - Roll No: 2022CSB1079
- [Kush Mahajan](https://github.com/kushrm2803) - Roll No: 2022CSB1089
- [Nishant Patil](https://github.com/Nishant984) - Roll No: 2022CSB1097

