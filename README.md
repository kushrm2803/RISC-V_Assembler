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
e : .asciz "Hello, World!"
```

Running the program with this input:

Will generate an output file (`input.mc`) containing the machine language code.

## Contributors

- [Dhruv Gupta](https://github.com/dhruvgupta2112) - Roll No: 2022CSB1079
- [Kush Mahajan](https://github.com/kushrm2803) - Roll No: 2022CSB1089
- [Nishant Patil](https://github.com/Nishant984) - Roll No: 2022CSB1097

