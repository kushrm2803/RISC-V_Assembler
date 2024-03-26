# RISC-V Assembler

This is a simple RISC-V assembler program based on Venus that converts RISC-V assembly language (.asm) into machine language (.mc) format. The program supports both .text and .data sections.(The support for pseudo instructions and floating-point operations is not included).Additionally, it includes a basic branch predictor implementation to evaluate the accuracy of various branch prediction methods.

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

## Supported Branch Prediction Methods
- Always Taken
- Always Not Taken
- 1-bit Branch Predictor
- 2-bit Branch Predictor

## Usage

To run asm_to_mc program, follow these steps:

1. **Input File**: Create an input assembly file (e.g., `input.asm`) containing your RISC-V assembly instructions. Each instruction should be on a single line.

2. **Command Line**: Compile and execute the C++ program from the command line. Provide the input assembly file as an argument along with ./a.exe or ./a.out.

3. **Output**: The program will create a separate file named `input.mc`, which contains the parsed assembly language instructions converted into machine language in hexadecimal form.

To run branch_prediction program, follow these steps:

1. **Input File**: Create an input assembly file (e.g., `input.asm`) containing your TRACE of RISC-V assembly instructions. Each instruction should be on a single line.

2. **Command Line**: Compile and execute the C++ program from the command line. Provide the input assembly file as an argument along with ./a.exe or ./a.out.

3. **Output**: The program will create 3 separate files named `input_OutputBTB.txt`, `input_OutputHT.txt`,`input_OuputAccuracy.txt` which contains Branch Target Buffer, History Table, Accuracy of 4 methods respectively.

## Example for asm_to_mc

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

## Example for branch_prediction
```assembly
core   0: 0x8000c81c (0x00150513) addi    a0, a0, 1
core   0: 0x8000c820 (0xfff5c703) lbu     a4, -1(a1)
core   0: 0x8000c824 (0x00078863) beqz    a5, pc + 16
core   0: 0x8000c828 (0xfee786e3) beq     a5, a4, pc - 20
core   0: 0x8000c814 (0x00054783) lbu     a5, 0(a0)
core   0: 0x8000c818 (0x00158593) addi    a1, a1, 1
core   0: 0x8000c81c (0x00150513) addi    a0, a0, 1
core   0: 0x8000c820 (0xfff5c703) lbu     a4, -1(a1)
core   0: 0x8000c824 (0x00078863) beqz    a5, pc + 16
core   0: 0x8000c828 (0xfee786e3) beq     a5, a4, pc - 20
core   0: 0x8000c82c (0x40e78533) sub     a0, a5, a4
core   0: 0x8000c830 (0x00008067) ret
core   0: 0x80005b98 (0x02051663) bnez    a0, pc + 44
core   0: 0x80005bc4 (0x003c0c13) addi    s8, s8, 3
core   0: 0x80005bc8 (0x41fc5793) srai    a5, s8, 31
core   0: 0x80005bcc (0x0037f793) andi    a5, a5, 3
core   0: 0x80005bd0 (0x018787b3) add     a5, a5, s8
core   0: 0x80005bd4 (0x004b2703) lw      a4, 4(s6)
```
Running the program with this input will generate Three files:

input_OutputBTB.txt
```.txt

-----------------------BRANCH TARGET BUFFER-----------------------

Current PC: 0x8000c824 Target PC: 0x8000c834 MISS
Current PC: 0x8000c828 Target PC: 0x8000c814 HIT
Current PC: 0x8000c824 Target PC: 0x8000c834 MISS
Current PC: 0x8000c828 Target PC: 0x8000c814 MISS
Current PC: 0x80005b98 Target PC: 0x80005bc4 HIT

-------------------------------------------------------------------

```

input_OutputHT.txt
```.txt


-----------------------HISTORY TABLE-------------------------------

0x8000c824
Predictions of One Bit Predictor => NT|NT|
Predictions of Two Bit Predictor => NT|NT|
Actual Result => NT|NT|
-------------------------------------------------------------------
0x8000c828
Predictions of One Bit Predictor => NT|T|
Predictions of Two Bit Predictor => NT|T|
Actual Result => T|NT|
-------------------------------------------------------------------
0x80005b98
Predictions of One Bit Predictor => NT|
Predictions of Two Bit Predictor => NT|
Actual Result => T|
-------------------------------------------------------------------

```
inputAccuracy.txt
```.txt


------------------------------ACCURACY-------------------------------------

Total Prediction of 1-bit Branch Predictor -> 40%
Total Prediction of 2-bit Branch Predictor -> 40%
Accuracy of branch predictor By Always Taken -> 40%
Accuracy of branch predictor By Always Not Taken -> 60%


-------------------------------------------------------------------

```

## Contributors

- [Dhruv Gupta](https://github.com/dhruvgupta2112) - Roll No: 2022CSB1079
- [Kush Mahajan](https://github.com/kushrm2803) - Roll No: 2022CSB1089
- [Nishant Patil](https://github.com/Nishant984) - Roll No: 2022CSB1097

