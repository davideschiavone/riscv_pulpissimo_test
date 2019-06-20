// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include <stdio.h>
#include <stdlib.h>

extern void riscv_ugp();
extern void riscy_ugp();

void __attribute__((interrupt)) __test_exceptions_handler()
{
    asm volatile(
                "csrrw x15, mepc, x0\n"
                "add x15, x15, 4\n"
                "csrrw x0, mepc, x15\n" : : : "x15");
}

int random_data[28];

#include <stdint.h>

unsigned short lfsr(unsigned short in)
{
    /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
    unsigned bit  = ((in >> 0) ^ (in >> 2) ^ (in >> 3) ^ (in >> 5) ) & 1;
    return (in >> 1) | (bit << 15);
};

int main ()
{


    unsigned short start_state = 0xACE1;  /* Any nonzero start state will work. */

    for(int i=0;i<28;i++)
        random_data[i] = start_state = lfsr(start_state);

    asm volatile(
        "la x31, %[random_data];"
        "lw x3,  0(x31);"
        "lw x4,  4(x31);"
        "lw x5,  8(x31);"
        "lw x6,  12(x31);"
        "lw x7,  16(x31);"
        "lw x8,  20(x31);"
        "lw x9,  24(x31);"
        "lw x10, 28(x31);"
        "lw x11, 32(x31);"
        "lw x12, 36(x31);"
        "lw x13, 40(x31);"
        "lw x14, 44(x31);"
        "lw x15, 48(x31);"
        "lw x16, 52(x31);"
        "lw x17, 56(x31);"
        "lw x18, 60(x31);"
        "lw x19, 64(x31);"
        "lw x20, 68(x31);"
        "lw x21, 72(x31);"
        "lw x22, 76(x31);"
        "lw x23, 80(x31);"
        "lw x24, 84(x31);"
        "lw x25, 88(x31);"
        "lw x26, 92(x31);"
        "lw x27, 96(x31);"
        "lw x28, 100(x31);"
        "lw x29, 104(x31);"
        "lw x30, 108(x31);"
        : : [random_data] "i" (random_data) :
                "x3", "x4", "x5", "x6", "x7", "x8", "x9",
        "x10", "x11", "x13", "x14", "x15", "x16", "x17", "x18", "x19",
        "x20", "x21", "x23", "x24", "x25", "x26", "x27", "x28", "x29",
        "x30");

    rt_irq_set_handler (0, __test_exceptions_handler);
    riscv_ugp();
    riscy_ugp();

    return 0;
}