int volatile data_mem[100];

void riscv_ugp(){
int i,n=100;
for(i=0; i < n; i++)
data_mem[i] = i;
asm volatile(
"start_individual:addi x2, x2, -96;"
"sw x1,  0x5C(x2);"
"sw  x3, 0x00(x2);"
"sw  x4, 0x04(x2);"
"sw  x5, 0x08(x2);"
"sw  x6, 0x0c(x2);"
"sw  x7, 0x10(x2);"
"sw x10, 0x14(x2);"
"sw x11, 0x18(x2);"
"sw x12, 0x1c(x2);"
"sw x13, 0x20(x2);"
"sw x14, 0x24(x2);"
"sw x15, 0x28(x2);"
"sw x16, 0x2c(x2);"
"sw x17, 0x30(x2);"
"sw x28, 0x34(x2);"
"sw x29, 0x38(x2);"
"sw x30, 0x3c(x2);"
"sw x31, 0x40(x2);"
"csrr x28, 0x7C0;"
"csrr x29, 0x7C1;"
"csrr x30, 0x7C2;"
"sw x28, 0x44(x2);"
"sw x29, 0x48(x2);"
"sw x30, 0x4C(x2);"
"csrr x28, 0x7C4;"
"csrr x29, 0x7C5;"
"csrr x30, 0x7C6;"
"sw x28, 0x50(x2);"
"sw x29, 0x54(x2);"
"sw x30, 0x58(x2);"

"xori x24, x1, 0x3e;"

"sub x22, x15, x5;"

"mulh x10, x12, x22;"

"blt x23, x24, nEZY;"

"xor x8, x11, x26;"

"lw x14, 0x6(%[data_addr]);"

"mulh x12, x13, x11;"

"lw x3, 0x9(%[data_addr]);"

"srl x9, x12, x4;"

"ori x29, x22, 0x0e;"

"div x17, x23, x31;"

"lui x13, 0x84;"

"slli x15, x18, 0xa;"

"auipc x12, 0x95;"

"ori x15, x18, 0x56;"

"div x5, x3, x21;"

"bge x28, x22, nEYZ;"

"srai x4, x5, 0x3;"

"auipc x16, 0x05;"

"addi x22, x19, 0x3c;"

"div x28, x15, x1;"

"auipc x5, 0x56;"

"and x1, x18, x19;"

"sb x19, 0xe(%[data_addr]);"

"blt x10, x8, nEZE;"

"remu x18, x13, x3;"

"j nEY5;"

"jal x19, nE2C;"

"srai x9, x6, 0xc;"

"jal x11, nEZC;"

"lhu x21, 0x9(%[data_addr]);"

"and x24, x26, x11;"

"lbu x25, 0x5(%[data_addr]);"

"lb x22, 0xe(%[data_addr]);"

"divu x3, x13, x20;"

"mul x22, x6, x4;"

"remu x26, x11, x26;"

"sltu x4, x25, x19;"

"andi x23, x9, 0x12;"

"addi x17, x7, 0x57;"

"sltu x14, x15, x4;"

"auipc x10, 0xcb;"

"lui x13, 0x0e;"

"lui x3, 0x39;"

"srli x23, x9, 0xb;"

"mulhu x7, x3, x17;"

"srli x13, x17, 0xa;"

"lb x11, 0xb(%[data_addr]);"

"sb x26, 0xb(%[data_addr]);"

"slt x26, x26, x22;"

"auipc x23, 0x13;"

"jal x27, nE2S;"

"sll x18, x11, x27;"

"and x29, x10, x9;"

"slli x6, x25, 0x1;"

"or x1, x10, x23;"

"and x4, x13, x22;"

"xori x15, x18, 0x39;"

"lui x1, 0x54;"

"rem x29, x20, x25;"

"auipc x31, 0xb6;"

"lb x28, 0x9(%[data_addr]);"

"addi x24, x25, 0x49;"

"srl x17, x6, x18;"

"xor x31, x9, x7;"

"beq x27, x6, nE3T;"

"srai x19, x27, 0xc;"

"sb x19, 0x3(%[data_addr]);"

"lui x26, 0xa8;"

"lui x28, 0xa5;"

"or x20, x14, x29;"

"or x30, x4, x31;"

"add x15, x12, x5;"

"lui x5, 0x4f;"

"lw x26, 0xe(%[data_addr]);"

"lui x11, 0x19;"

"slti x26, x6, 0xb5;"

"mulh x24, x7, x16;"

"sltu x11, x22, x4;"

"mul x27, x12, x19;"

"lhu x30, 0x5(%[data_addr]);"

"divu x17, x22, x21;"

"lui x28, 0xd7;"

"sh x11, 0x5(%[data_addr]);"

"sltu x25, x19, x1;"

"lui x8, 0x8b;"

"bge x26, x14, nE2X;"

"auipc x25, 0x9d;"

"bgeu x18, x26, nEZO;"

"mulhsu x16, x29, x10;"

"auipc x1, 0xdd;"

"bgeu x1, x14, nEZV;"

"lbu x13, 0x5(%[data_addr]);"

"sub x23, x14, x12;"

"lui x1, 0xaf;"

"srai x7, x1, 0x7;"
"nEYZ: "
"lh x4, 0xc(%[data_addr]);"

"xor x28, x20, x27;"

"sw x3, 0x3(%[data_addr]);"

"sh x10, 0x2(%[data_addr]);"
"nEY5: "
"lb x1, 0xd(%[data_addr]);"

"bge x17, x12, nE3P;"

"lui x22, 0x97;"

"lui x5, 0xcb;"

"jal x26, nE3T;"
"nEZC: "
"auipc x19, 0xa0;"

"div x7, x30, x29;"
"nEZE: "
"srl x5, x10, x14;"

"bge x17, x8, nE2V;"

"auipc x23, 0x2e;"

"sh x12, 0x6(%[data_addr]);"

"slli x13, x5, 0x4;"

"sub x3, x19, x9;"

"lui x8, 0xfb;"

"j nE23;"

"lhu x21, 0xf(%[data_addr]);"

"sub x27, x13, x22;"
"nEZO: "
"lw x15, 0x3(%[data_addr]);"

"lw x15, 0xf(%[data_addr]);"

"slti x27, x22, 0x9b;"

"sra x14, x13, x25;"

"sra x13, x18, x19;"

"lui x29, 0x9d;"

"slli x27, x26, 0xf;"
"nEZV: "
"auipc x27, 0x75;"

"or x7, x27, x6;"

"sub x18, x7, x4;"
"nEZY: "
"slli x27, x5, 0x1;"

"srai x16, x24, 0x3;"

"ori x8, x8, 0x26;"

"addi x30, x8, 0x3c;"

"bltu x20, x6, nE2O;"

"bgeu x14, x31, nE27;"

"mul x3, x19, x5;"

"xori x29, x20, 0x39;"

"lw x8, 0x4(%[data_addr]);"

"addi x7, x5, 0xa4;"
"nE2C: "
"ori x7, x31, 0x65;"

"lui x16, 0x95;"

"divu x19, x3, x25;"

"mulhsu x24, x22, x29;"

"srli x1, x12, 0x3;"

"lui x8, 0x79;"

"mulhu x12, x7, x10;"

"sra x8, x3, x19;"

"mul x7, x27, x25;"

"srl x6, x11, x30;"

"slti x12, x19, 0xc9;"

"auipc x7, 0x03;"
"nE2O: "
"mulh x28, x13, x23;"

"sb x10, 0x4(%[data_addr]);"

"bltu x22, x7, nE3L;"

"lbu x12, 0xa(%[data_addr]);"
"nE2S: "
"blt x11, x16, nE4C;"

"bgeu x26, x30, nE25;"

"beq x18, x16, nE3C;"
"nE2V: "
"sw x18, 0xd(%[data_addr]);"

"bgeu x7, x25, nE23;"
"nE2X: "
"srai x9, x30, 0x0;"

"xori x11, x25, 0x23;"

"xori x27, x27, 0x9b;"

"lh x9, 0x5(%[data_addr]);"
"nE23: "
"lui x13, 0xb1;"

"sh x14, 0x8(%[data_addr]);"
"nE25: "
"srai x14, x10, 0x4;"

"mulh x5, x27, x12;"
"nE27: "
"mulh x20, x31, x11;"

"sh x26, 0x6(%[data_addr]);"

"bgeu x17, x1, nE3T;"
"nE3C: "
"xor x26, x24, x16;"

"srli x14, x6, 0xf;"

"ori x17, x26, 0x5e;"

"lui x20, 0x59;"

"auipc x17, 0xdc;"

"div x18, x11, x25;"

"ori x9, x25, 0xea;"

"sw x20, 0x4(%[data_addr]);"

"srli x1, x23, 0xf;"
"nE3L: "
"addi x10, x10, 0xe4;"

"lui x13, 0x5f;"

"rem x10, x5, x3;"

"andi x7, x16, 0xba;"
"nE3P: "
"addi x12, x15, 0xbe;"

"jal x10, nE4A;"

"mulhsu x13, x24, x20;"

"sh x9, 0x0(%[data_addr]);"
"nE3T: "
"blt x10, x16, nE36;"

"sb x9, 0x0(%[data_addr]);"

"lbu x28, 0xc(%[data_addr]);"

"srai x23, x7, 0x8;"

"auipc x14, 0xa8;"

"slti x31, x12, 0x69;"

"div x9, x5, x4;"

"mulh x24, x6, x8;"

"srli x13, x4, 0x1;"

"srli x30, x31, 0xf;"

"bge x17, x19, nE4B;"
"nE36: "
"sw x19, 0xe(%[data_addr]);"

"sll x20, x29, x20;"
"nE4A: "
"andi x23, x29, 0xe7;"
"nE4B: "
"lh x12, 0xe(%[data_addr]);"
"nE4C: "
:
:[data_addr] "r" (data_mem)
);
asm volatile(
"lw x28, 0x50(x2);"
"lw x29, 0x54(x2);"
"lw x30, 0x58(x2);"
"csrrw x0, 0x7C4, x28;"
"csrrw x0, 0x7C5, x29;"
"csrrw x0, 0x7C6, x30;"
"lw x28, 0x44(x2);"
"lw x29, 0x48(x2);"
"lw x30, 0x4C(x2);"
"csrrw x0, 0x7C0, x28;"
"csrrw x0, 0x7C1, x29;"
"csrrw x0, 0x7C2, x30;"
"lw x31, 0x40(x2);"
"lw x30, 0x3c(x2);"
"lw x29, 0x38(x2);"
"lw x28, 0x34(x2);"
"lw x17, 0x30(x2);"
"lw x16, 0x2c(x2);"
"lw x15, 0x28(x2);"
"lw x14, 0x24(x2);"
"lw x13, 0x20(x2);"
"lw x12, 0x1c(x2);"
"lw x11, 0x18(x2);"
"lw x10, 0x14(x2);"
"lw  x7, 0x10(x2);"
"lw  x6, 0x0c(x2);"
"lw  x5, 0x08(x2);"
"lw  x4, 0x04(x2);"
"lw  x3, 0x00(x2);"
"lw x1, 0x5C(x2);"
"addi x2, x2, 96");
return;
}

