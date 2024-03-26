core    0:    0x00000000    (0x10000a97)      auipc x21 65536
  core    0:    0x00000004    (0x000a8a93)    addi x21 x21 0
  core    0:    0x00000008    (0xfff00613)    addi x12 x0 -1
  core    0:    0x0000000c    (0x10000697)    auipc x13 65536
  core    0:    0x00000010    (0x0086a683)    lw x13 8(x13)
  core    0:    0x00000014    (0x00000713)    addi x14 x0 0
  core    0:    0x00000018    (0x00160613)    addi x12 x12 1
  core    0:    0x0000001c    (0x04d60463)    beq x12 x13 pc + 72
  core    0:    0x00000020    (0x00000713)    addi x14 x0 0
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000050    (0x008000ef)    jal x1 8
  core    0:    0x00000058    (0x00bb2023)    sw x11 0(x22)
  core    0:    0x0000005c    (0x00aba023)    sw x10 0(x23)
  core    0:    0x00000060    (0x00008067)    jalr x0 x1 0
  core    0:    0x00000054    (0xfc0008e3)    beq x0 x0 pc - 48
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000050    (0x008000ef)    jal x1 8
  core    0:    0x00000058    (0x00bb2023)    sw x11 0(x22)
  core    0:    0x0000005c    (0x00aba023)    sw x10 0(x23)
  core    0:    0x00000060    (0x00008067)    jalr x0 x1 0
  core    0:    0x00000054    (0xfc0008e3)    beq x0 x0 pc - 48
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x00000018    (0x00160613)    addi x12 x12 1
  core    0:    0x0000001c    (0x04d60463)    beq x12 x13 pc + 72
  core    0:    0x00000020    (0x00000713)    addi x14 x0 0
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000050    (0x008000ef)    jal x1 8
  core    0:    0x00000058    (0x00bb2023)    sw x11 0(x22)
  core    0:    0x0000005c    (0x00aba023)    sw x10 0(x23)
  core    0:    0x00000060    (0x00008067)    jalr x0 x1 0
  core    0:    0x00000054    (0xfc0008e3)    beq x0 x0 pc - 48
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x00000018    (0x00160613)    addi x12 x12 1
  core    0:    0x0000001c    (0x04d60463)    beq x12 x13 pc + 72
  core    0:    0x00000020    (0x00000713)    addi x14 x0 0
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000050    (0x008000ef)    jal x1 8
  core    0:    0x00000058    (0x00bb2023)    sw x11 0(x22)
  core    0:    0x0000005c    (0x00aba023)    sw x10 0(x23)
  core    0:    0x00000060    (0x00008067)    jalr x0 x1 0
  core    0:    0x00000054    (0xfc0008e3)    beq x0 x0 pc - 48
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x00000018    (0x00160613)    addi x12 x12 1
  core    0:    0x0000001c    (0x04d60463)    beq x12 x13 pc + 72
  core    0:    0x00000020    (0x00000713)    addi x14 x0 0
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x00000018    (0x00160613)    addi x12 x12 1
  core    0:    0x0000001c    (0x04d60463)    beq x12 x13 pc + 72
  core    0:    0x00000020    (0x00000713)    addi x14 x0 0
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x0000002c    (0x00070293)    addi x5 x14 0
  core    0:    0x00000030    (0xfff70313)    addi x6 x14 -1
  core    0:    0x00000034    (0x00229293)    slli x5 x5 2
  core    0:    0x00000038    (0x005a8b33)    add x22 x21 x5
  core    0:    0x0000003c    (0x00231313)    slli x6 x6 2
  core    0:    0x00000040    (0x006a8bb3)    add x23 x21 x6
  core    0:    0x00000044    (0x000b2503)    lw x10 0(x22)
  core    0:    0x00000048    (0x000ba583)    lw x11 0(x23)
  core    0:    0x0000004c    (0xfcb55ce3)    bge x10 x11 pc - 40
  core    0:    0x00000024    (0x00170713)    addi x14 x14 1
  core    0:    0x00000028    (0xfee688e3)    beq x13 x14 pc - 16
  core    0:    0x00000018    (0x00160613)    addi x12 x12 1
  core    0:    0x0000001c    (0x04d60463)    beq x12 x13 pc + 72
  core    0:    0x00000064    (0x10000297)    auipc x5 65536
  core    0:    0x00000068    (0xf9c2a283)    lw x5 -100(x5)
  core    0:    0x0000006c    (0x004aa303)    lw x6 4(x21)
  core    0:    0x00000070    (0x008aa383)    lw x7 8(x21)
  core    0:    0x00000074    (0x00caa403)    lw x8 12(x21)
  core    0:    0x00000078    (0x010aa483)    lw x9 16(x21)