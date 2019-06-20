int volatile data_mem[100];

void riscy_ugp(){
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
"sw x31, 0x62(x2);"
"li x8, 0x00000003;"
"csrrw x12, 0x300, x8;"
"li x8, 0x0000000e;"
"csrrw x9, 0x300, x8;"
"li x8, 0x00000001;"
"csrrw x12, 0x7A1, x8;"
"li x8, 0x00000003;"
"csrrw x9, 0x7A1, x8;"
"li x8, 0x00000001;"
"csrrw x12, 0x7A0, x8;"
"li x8, 0x00000000;"
"csrrw x9, 0x7A0, x8;"
"addi x5, x0, 2;"
"csrrc x21, 0x7A0, x5;"
"csrrs x21, 0x7A0, x5;"
"csrrc x21, 0x7A1, x5;"
"csrrs x21, 0x7A1, x5;"
"csrrc x21, 0x780, x5;"
"csrrs x21, 0x780, x5;"
"addi x5, x0, 2;"
"csrrc x21, 0x306, x5;"
"csrrs x21, 0x306, x5;"
"pv.extract.h x13, x14, 0x01;"
"pv.extract.b x13, x14, 0x01;"
"pv.extractu.b x13, x14, 0x01;"
"pv.extractu.h x13, x14, 0x01;"
"pv.insert.h x13, x14, 0x01;"
"pv.insert.b x16, x15, 0x01;"
"li x6, 3423;"
"li x1, 4368246;"
"lb x31, 0x4(%[data_addr]);"
"divu x22, x1, x6;"
"lw x31, 0x1(%[data_addr]);"
"lb x31, 0x4(%[data_addr]);"
"lw x30, 0x3(%[data_addr]);"

"p.macsRN x11,x27,x30,0x5;"

"p.sletu x6, x15, x28;"

"p.beqimm x26, 0x5, nPNHR;"

"p.muls x26, x26, x29;"
"nPNHR: "
"pv.cmpgtu.sci.b x14, x31, 0xe;"

"slti x17, x6, 0x10;"

"pv.or.sci.b x3, x18, 0xe;"

"pv.sdotup.h x27, x3, x9;"

"p.mulhhuN x9,x14,x6,0x0;"

"p.mulhhs x15, x20, x27;"

"sw x15, 0x3(%[data_addr]);"

"pv.cmpne.sci.h x15, x16, 0xb;"

"pv.cmpeq.sci.b x9, x17, 0x8;"

"pv.avgu.b x6, x9, x18;"

"pv.abs.b x4, x8;"

"p.maxu x28, x16, x13;"

"pv.shuffleI2.sci.b x17, x23, 0xc;"

"or x8, x12, x7;"

"csrr x6, 0xF14;"

"p.subRNr x20, x22, x11;"

"p.insertr x18, x4, x12;"

"pv.cmpgt.sci.h x7, x28, 0x1;"

"lui x24, 0x2b;"

"p.extractur x13, x7, x29;"

"slli x24, x11, 0xf;"

"pv.minu.sc.b x25, x12, x30;"

"p.addNr x25, x22, x13;"

"pv.avgu.sc.h x26, x30, x20;"

"p.beqimm x3, 0x5, nPNJH;"

"mulhsu x23, x7, x30;"

"p.mulu x26, x17, x31;"

"xori x3, x24, 0xb0;"

"pv.cmpne.b x17, x23, x9;"

"csrr x1, 0x342;"

"pv.cmpne.h x30, x7, x4;"

"p.clipu x6, x9 , 0x5 ;"

"pv.dotusp.b x17, x6, x11;"

"p.muls x27, x21, x7;"

"blt x7, x19, nPNJU;"

"pv.cmpgt.b x13, x21, x1;"

"p.subN x14, x3 , x4 , 0x7 ;"

"slti x7, x6, 0x8f;"

"sub x31, x15, x22;"

"pv.sdotsp.sci.b x8, x26, 0xa;"

"divu x22, x11, x3;"

"pv.cmple.sc.h x12, x25, x16;"

"p.mac x17, x17, x15;"

"srl x16, x30, x17;"

"p.extractr x20, x4, x27;"

"p.clip x9, x1 , 0x8 ;"

"srli x16, x7, 0xa;"

"pv.minu.sci.h x11, x23, 0x8;"

"sub x26, x18, x3;"

"slti x28, x3, 0xf9;"

"sll x25, x15, x30;"

"pv.minu.sc.h x8, x11, x22;"

"rem x9, x25, x26;"

"lui x23, 0x08;"

"pv.abs.b x1, x8;"

"pv.add.sc.h x21, x29, x7;"

"p.subRN x31, x17 , x3 , 0x1 ;"

"pv.cmplt.b x29, x1, x23;"

"pv.max.sci.h x7, x24, 0x1;"
"nPNJH: "
"p.clipu x23, x3 , 0xd ;"

"lui x9, 0xf6;"

"remu x31, x15, x20;"

"pv.sdotup.sc.b x23, x6, x3;"

"p.exthz x28, x27 ;"

"p.cnt x20, x26 ;"

"srl x15, x15, x15;"

"p.addN x22, x24 , x6 , 0x0 ;"

"pv.avg.sc.h x31, x17, x28;"

"srai x14, x4, 0x8;"

"pv.sdotsp.sc.b x4, x29, x26;"

"auipc x13, 0xa2;"

"pv.abs.b x13, x1;"

"pv.min.sci.b x30, x9, 0x4;"

"lw x30, 0x2(%[data_addr]);"

"pv.sra.h x31, x6, x9;"
"nPNJU: "
"sltu x26, x29, x6;"

"srai x1, x26, 0x4;"

"pv.abs.b x7, x27;"

"pv.avg.h x11, x15, x3;"

"p.clip x15, x4 , 0x4 ;"

"pv.xor.b x17, x9, x26;"

"bgeu x31, x6, nPNKM;"

"remu x13, x27, x16;"

"pv.minu.sc.b x30, x30, x17;"

"slli x3, x1, 0x2;"

"pv.packlo.b x30, x8, x12;"

"sw x3, 0x2(%[data_addr]);"

"divu x23, x26, x6;"

"sb x31, 0x9(%[data_addr]);"

"andi x20, x8, 0xa0;"

"slli x14, x24, 0x5;"

"p.beqimm x11, 0x1, nPNKW;"

"srai x7, x26, 0x6;"

"jal x7, nPNLA;"

"pv.cmpgtu.h x12, x26, x6;"

"p.muls x31, x3, x29;"

"pv.srl.sc.h x18, x9, x30;"

"lw x21, 0x1(%[data_addr]);"

"pv.cmpleu.sc.h x1, x31, x19;"

"pv.cmpleu.sc.b x8, x17, x17;"
"nPNKM: "
"pv.dotup.b x25, x26, x25;"

"pv.cmpltu.sc.h x4, x3, x15;"

"pv.dotsp.sc.h x25, x18, x21;"

"sub x28, x15, x12;"

"slli x18, x20, 0x8;"

"p.min x23, x24, x19;"

"srai x28, x11, 0x0;"

"csrr x15, 0x7A0;"

"p.abs x24, x8 ;"

"addi x5,x0, 0xc; "
"p.sw x25, x4(x5!);"

"add x30, x26, x14;"
"nPNKW: "
"sltu x11, x25, x21;"

"pv.minu.b x23, x24, x9;"

"pv.sll.sc.h x12, x25, x11;"

"p.ff1 x1, x12 ;"

"pv.cmpgtu.sci.b x6, x19, 0xa;"

"pv.shuffle2.h x11, x29, x8;"

"p.msu x18, x27, x26;"

"pv.add.sci.b x20, x19, 0x8;"

"p.beqimm x21, 0xb, nPNLJ;"

"pv.sdotup.sci.b x1, x27, 0x3;"

"pv.cmpgeu.b x26, x30, x25;"
"nPNLA: "
"lui x9, 0x6a;"

"pv.packhi.b x7, x13, x4;"

"pv.abs.b x13, x12;"

"rem x27, x29, x14;"

"p.mulhhs x26, x21, x28;"

"p.bneimm x14, 0x7, nPNLI;"

"p.bset x29, x24, 0x3, 0x1 ;"

"pv.cmplt.sc.b x12, x28, x17;"

"p.maxu x8, x18, x7;"
"nPNLI: "
"bge x20, x25, nPNLN;"
"nPNLJ: "
"pv.or.sc.b x22, x16, x20;"

"p.subuNr x24, x8, x28;"

"p.addRNr x21, x31, x15;"

"auipc x27, 0x4b;"
"nPNLN: "
"pv.dotsp.h x29, x24, x29;"

"addi x5,x0, 0xc; "
"p.sw x22, x4(x5!);"

"lui x23, 0xc9;"

"pv.and.sci.b x24, x23, 0x7;"

"pv.cmple.sci.h x19, x13, 0xe;"

"pv.cmpleu.sci.b x6, x12, 0x7;"

"rem x23, x20, x19;"

"bne x31, x18, nPNL3;"

"p.beqimm x20, 0xe, nPNLX;"

"p.max x14, x17, x25;"
"nPNLX: "
"auipc x22, 0x69;"

"pv.min.sc.b x31, x3, x13;"

"pv.cmpleu.h x6, x28, x14;"

"p.addN x26, x23 , x23 , 0x3 ;"
"nPNL3: "
"p.bneimm x15, 0x9, nPNL4;"
"nPNL4: "






 "p.extbs x4, x11 ;"

    "pv.cmpltu.sc.h x13, x29, x28;"

    "p.subRNr x27, x24, x26;"

    "nop;"

    "csrr x15, 0x7A1;"

    "p.extbz x22, x19 ;"

    "p.min x30, x24, x16;"

        "or x14, x25, x11;"

    "p.clipur x19, x3, x1;"

    "p.beqimm x1, 0xd, nXMQV;"

    "p.extbs x4, x11 ;"

    "pv.cmpltu.sc.h x13, x29, x28;"

    "p.subRNr x27, x24, x26;"

    "p.beqimm x24, 0x7, nXMQH;"

                "csrr x25, 0x300;"

    "p.extbs x23, x16 ;"

    "pv.shuffleI2.sci.b x9, x19, 0x2;"

    "divu x3, x21, x29;"

    "pv.cmple.sci.b x19, x11, 0x6;"

    "p.clipr x19, x16, x11;"

    "p.mac x22, x18, x30;"

    "p.machhuRN x18,x12,x9,0xf;"

    "pv.sdotsp.sci.h x18, x23, 0x6;"

        "sll x24, x26, x11;"

        "slt x31, x14, x27;"

    "pv.abs.b x15, x11;"

    "mul x26, x1, x3;"

    "p.clip x13, x1 , 0x5 ;"

    "pv.add.h x8, x21, x22;"

    "p.clip x17, x7 , 0x3 ;"

    "pv.cmplt.sci.b x19, x8, 0xd;"

    "p.adduRN x26, x6 , x11 , 0xa ;"

        "sb x9, 0xb(%[data_addr]);"

    "pv.cmplt.h x20, x26, x20;"

    "pv.packlo.b x27, x27, x4;"

    "p.clb x17, x28 ;"

    "srli x6, x23, 0x0;"

        "sll x24, x28, x4;"

    "pv.srl.sci.h x14, x9, 0xd;"

    "pv.abs.b x1, x4;"

                "csrr x1, 0x014;"

    "srli x23, x26, 0x5;"

    "pv.srl.sci.b x22, x7, 0x0;"

        "slti x14, x24, 0xdc;"

    "p.adduRNr x7, x9, x17;"

    "p.subuRN x21, x24 , x26 , 0xd ;"

        "sb x13, 0x2(%[data_addr]);"

    "srli x15, x22, 0x1;"

    "mulhsu x22, x18, x22;"

    "pv.minu.sc.b x14, x16, x8;"

    "pv.cmpgtu.b x18, x3, x22;"

    "pv.dotsp.h x24, x3, x30;"

    "pv.abs.b x11, x26;"

    "addi x5,x0, 0xc; "
    "p.sw x30, x4(x5!);"

    "p.subuRN x24, x18 , x14 , 0x7 ;"

    "pv.sdotusp.sci.b x17, x19, 0x0;"

    "pv.packhi.b x26, x18, x25;"

        "auipc x3, 0x5a;"

    "p.slet x29, x31, x29;"

                "csrr x21, 0x014;"

        "or x8, x23, x13;"

    "pv.sdotusp.sc.h x11, x23, x17;"

        "sra x14, x28, x16;"

    "div x6, x14, x4;"

    "pv.sub.sc.h x23, x27, x26;"

        "lui x4, 0x65;"

    "p.insertr x23, x19, x6;"

    "pv.cmpgeu.h x1, x16, x22;"

        "lh x29, 0x3(%[data_addr]);"

    "srai x8, x4, 0x5;"


        "lw x16, 0x4(%[data_addr]);"

    "pv.sdotsp.sc.b x16, x4, x12;"

    "pv.shuffle.sci.h x3, x22, 0x4;"

    "pv.cmpleu.sc.b x15, x4, x20;"

        "srl x30, x29, x28;"

    "pv.dotup.sc.h x1, x12, x21;"

    "addi x5,x0, 0xc; "
    "p.sw x7, x4(x5!);"

    "pv.sll.sci.h x14, x23, 0x2;"

    "p.subuNr x28, x30, x17;"

    "p.addN x12, x14 , x21 , 0xf ;"

    "p.subN x12, x30 , x15 , 0xd ;"

        "bne x3, x22, nXMSE;"

    "p.macsRN x14,x11,x20,0xb;"

    "addi x5,x0, 0xc; "
    "p.sw x1, x4(x5!);"

    "pv.cmpne.b x14, x12, x30;"

    "addi x5,x0, 0xc; "
    "p.sw x13, x4(x5!);"

    "pv.cmpne.sci.b x20, x15, 0xd;"

    "p.muluRN x8,x25,x30,0x5;"
      "nXMQH: "
    "addi x5,x0, 0xc; "
    "p.sw x23, x4(x5!);"

    "srai x22, x16, 0x2;"

       // "sb x30, 0xe(%[data_addr]);"

    "div x13, x31, x23;"

    "pv.avgu.sci.b x14, x25, 0x6;"

    "addi x5,x0, 0xc; "
    "p.sw x15, x4(x5!);"

    "p.maxu x16, x9, x21;"

    "pv.dotusp.sci.h x16, x6, 0x4;"

    "p.extractur x25, x7, x15;"

    "remu x11, x19, x27;"

        "xori x1, x15, 0x7e;"

    "pv.cmplt.sc.b x17, x19, x1;"

    "pv.abs.b x17, x9;"

    "p.ff1 x14, x22 ;"
        "nXMQV: "
    "pv.dotsp.sci.b x17, x25, 0x4;"

        "sh x11, 0x4(%[data_addr]);"

    "pv.sll.sc.h x31, x16, x26;"

    "pv.and.sc.b x25, x25, x23;"

    "p.clipu x31, x31 , 0x3 ;"

    "pv.minu.sci.h x14, x4, 0x3;"

    "pv.shuffle2.b x6, x13, x17;"

    "pv.cmpleu.sci.h x28, x25, 0xf;"

    "pv.cmpltu.sci.b x7, x23, 0xf;"

    "pv.avgu.sc.b x25, x13, x14;"

    "pv.maxu.sc.b x25, x22, x25;"

    "p.clipu x3, x1 , 0xf ;"

    "p.maxu x9, x29, x24;"

    "slli x23, x4, 0x6;"

    "p.clipu x13, x17 , 0xb ;"

    "pv.abs.b x21, x7;"

    "addi x5,x0, 0xc; "
    "p.sw x8, x4(x5!);"

    "srai x23, x9, 0x7;"

    "slli x24, x21, 0x1;"

    "p.extractr x9, x21, x27;"

    "p.insert x8, x17, 0x7, 0x4 ;"

    "p.addN x27, x16 , x18 , 0x7 ;"

    "addi x5,x0, 0xc; "
    "p.sw x14, x4(x5!);"

    "p.exthz x17, x23 ;"

        "lw x31, 0x9(%[data_addr]);"

    "p.mulu x16, x22, x1;"

                "csrr x25, 0x014;"

    "pv.min.b x6, x18, x28;"

    "p.msu x13, x22, x15;"

    "p.subuNr x12, x17, x9;"

    "p.msu x27, x16, x6;"

        "sra x1, x18, x27;"

    "pv.cmpgt.sci.h x4, x24, 0xa;"

    "pv.max.b x30, x16, x14;"

    "p.clb x20, x3 ;"

        "sh x28, 0xf(%[data_addr]);"

    "p.subuN x16, x7 , x31 , 0xf ;"

    "pv.and.sci.h x25, x27, 0xc;"

    "pv.abs.b x15, x15;"

        "lui x24, 0x69;"

    "pv.sra.sc.h x22, x9, x22;"

                "csrr x26, 0x342;"

    "addi x5,x0, 0xc; "
    "p.sw x17, x4(x5!);"

    "addi x5,x0, 0xc; "
    "p.sw x30, x4(x5!);"

    "pv.maxu.sc.b x26, x7, x19;"

    "pv.cmpeq.sci.h x18, x17, 0x7;"

    "pv.min.h x1, x11, x7;"
        "nXMSE: "
    "pv.cmpeq.sci.h x23, x24, 0x2;"

    "p.subRN x12, x26 , x11 , 0x0 ;"

    "p.machhuRN x8,x4,x6,0x0;"

    "p.abs x31, x19 ;"

    "p.bneimm x8, 0x3, nXMS4;"

    "pv.cmpne.h x9, x29, x15;"

    "p.clipu x12, x12 , 0x2 ;"

        "lui x8, 0x57;"

    "pv.cmpgt.b x28, x19, x3;"

    "pv.max.sci.h x1, x9, 0xb;"

    "pv.abs.b x7, x16;"

    "pv.avgu.h x28, x22, x14;"

    "pv.avgu.h x18, x17, x19;"

                "csrr x19, 0xF14;"

        "auipc x8, 0x0f;"

    "addi x5,x0, 0xc; "
    "p.sw x16, x4(x5!);"

    "p.muls x26, x30, x12;"

    "pv.maxu.b x16, x8, x22;"

    "p.bsetr x30, x16, x15;"

    "p.clipu x9, x18 , 0x0 ;"

    "p.mac x31, x16, x29;"

    "p.subRN x19, x28 , x30 , 0x3 ;"

    "p.mulhhs x19, x23, x13;"

        "slti x17, x16, 0x29;"
          "nXMS4: "
    "p.beqimm x11, 0x6, nXMTB;"

    "pv.xor.h x1, x12, x17;"

    "p.mulhhuN x31,x7,x28,0x8;"

    "p.msu x24, x11, x16;"

    "p.minu x28, x20, x4;"
        "nXMTB: "
    "srli x20, x30, 0xb;"

        "lui x7, 0x53;"

    "p.ror x22, x25, x14;"

    "pv.abs.b x28, x12;"

    "pv.srl.sc.b x8, x25, x17;"

    "pv.srl.sc.h x27, x12, x25;"

        "beq x9, x6, nXMTL;"

        "sltiu x20, x7, 0x37;"

    "pv.and.sci.h x18, x26, 0x0;"

    "pv.sdotup.sc.b x9, x11, x28;"
        "nXMTL: "
    "p.fl1 x15, x24 ;"

        "j nXMTS;"

    "pv.sdotusp.sc.h x3, x3, x17;"

        "j nXMTR;"

        "auipc x30, 0x64;"

    "pv.minu.sc.b x3, x30, x28;"
        "nXMTR: "
    "p.beqimm x16, 0x9, nXMTU;"
        "nXMTS: "
    "p.sletu x28, x12, x7;"

    "pv.min.h x20, x30, x20;"
        "nXMTU: "
    "p.mulhhuRN x28,x11,x23,0x9;"

    "pv.abs.b x26, x15;"

        "bgeu x15, x8, nXMTZ;"

    "p.bneimm x26, 0x0, nXMTY;"
        "nXMTY: "
        "sll x1, x24, x28;"
          "nXMTZ: "
:
:[data_addr] "r" (data_mem)
);


asm volatile(
 "la x10, illegal_store;"
".word 0x00007123;"
"illegal_store: la x10, illegal_load;"
".word 0x0004bf03;"
"illegal_load: la x10, illegal_load_reg;"
".word 0xfff4ff03;"
"illegal_load_reg: la x10, illegal_jalr;"
".word 0xF0FFF67;"
"illegal_jalr: la x10, illegal_alu_sll_imm;"
".word 0x0e719213;"
"illegal_alu_sll_imm: la x10, illegal_opimm;"
".word 0xd001d213;"
"illegal_opimm: la x10, illegal_op_bitMan;"
".word 0xfffe5233;"
"illegal_op_bitMan: la x10, illegal_op_alu;"
".word 0x0e0372b3;"
"illegal_op_alu: la x10, illegal_opvec;"
".word 0xfff3f257;"
"illegal_opvec: la x10, illegal_opsystem;"
".word 0x0ff48473;"
"illegal_opsystem: la x10, illegal_opsystem2;"
".word 0x0072c273;"
"illegal_opsystem2: la x10, illegal_hwloop;"
".word 0x0000387b;"
"illegal_hwloop: la x10, illegal_hwloop2;"
".word 0x0000607b;"
"illegal_hwloop2: la x10, label_ecall;"
".word 0x00000073;"
"label_ecall: la x5, afterJump;"
"jalr x3, x5 , 0 ;"
"afterJump: la x10, illegal_C0_default;"
".word 0x8190;"
"illegal_C0_default: la x10, illegal_C0_1;"
".word 0x2000;"
"illegal_C0_1: la x10, illegal_C0_2;"
".word 0x6000;"
"illegal_C0_2: la x10, illegal_C0_3;"
".word 0xa000;"
"illegal_C0_3:  la x10, illegal_C0_4;"
".word 0xe000;"
"illegal_C0_4: la x10, illegal_C1_li;"
".word 0x4001;"
"illegal_C1_li: la x10, illegal_C1_lui;"
".word 0x6001;"
"illegal_C1_lui: la x10, illegal_C1_srli_srai;"
".word 0x9401;"
"illegal_C1_srli_srai: la x10, illegal_C1_srli_srai2;"
".word 0x8001;"
"illegal_C1_srli_srai2: la x10, illegal_C1_srli_srai_F;"
".word 0x8405;"
"illegal_C1_srli_srai_F: la x10, illegal_C1_subw1;"
".word 0x9d85;"
"illegal_C1_subw1: la x10, illegal_C1_subw2;"
".word 0x9da5;"
"illegal_C1_subw2: la x10, illegal_C1_subw3;"
".word 0x9dc5;"
"illegal_C1_subw3:la x10, illegal_C1_subw4;"
".word 0x9de5;"
"illegal_C1_subw4: la x10, illegal_C2_1;"
".word 0x1002;"
"illegal_C2_1: la x10, illegal_C2_F;"
".word 0x0c0e;"
"illegal_C2_F:la x10, illegal_C2_Cond;"
".word 0x0c02;"
"illegal_C2_Cond: la x10, illegal_C2_2;"
".word 0x2002;"
"illegal_C2_2: la x10, illegal_C2_3;"
".word 0x4002;"
"illegal_C2_3:la x10, illegal_C2_4T;"
".word 0x9006;"
"illegal_C2_4T: la x10, illegal_C2_4F;"
".word 0x9002;"
"illegal_C2_4F:la x10, illegal_C2_5;"
".word 0xa002;"
"illegal_C2_5: la x10, illegal_C2_6;"
".word 0xe002;"
"illegal_C2_6: la x10, illegal_C2_7;"
".word 0x6002;"
"illegal_C2_7: p.mulsRN x24, x20, x21, 0x1;"
"pv.extract.h x13, x14, 0x01;"
"pv.extractu.b x13, x14, 0x01;"
"pv.insert.h x13, x14, 0x01;"

"lp.counti x0, 10;"
"lp.starti x0, start_HWLP;"
"lp.endi   x0, end_HWLP;"
"start_HWLP: addi x3, x3, 1;"
"            xori x18, x12, 1;"
"            sub x4, x12, x16;"
"end_HWLP:   p.bclrr x7, x9, x12;"
"            pv.shuffle2.h x8, x18, x19;"

"li x4, 10;"
"lp.count x0, x4;"
"lp.starti x0, start_HWLP2;"
"lp.endi   x0, end_HWLP2;"
"start_HWLP2: addi x3, x3, 1;"
"            xori x18, x12, 1;"
"            sub x4, x12, x16;"
"end_HWLP2:   p.bclrr x7, x9, x12;"
"            pv.shuffle2.h x8, x18, x19;"
);
asm volatile(
"lw x31, 0x62(x2);"
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
"addi x2, x2, 96"
);
return;
}

void illegal_insn_handler_c();
void ecall_insn_handler_c();

