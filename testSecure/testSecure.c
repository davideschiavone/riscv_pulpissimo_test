// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.


#include "pulp.h"
#include "riscv_test.h"

//64 bytes protection
static volatile unsigned char protected_data[64];
static volatile unsigned int return_here_instr;

static volatile unsigned int __attribute__ ((aligned (4))) stack_data[31];

#define PUSH_ALL "sw x1,  0(x18)\n" \
                 "sw x9,  32(x18)\n" \
                 "sw x10, 36(x18)\n" \
                 "sw x11, 40(x18)\n" \
                 "sw x12, 44(x18)\n" \
                 "sw x13, 48(x18)\n" \
                 "sw x14, 52(x18)\n" \
                 "sw x15, 56(x18)\n" \
                 "sw x16, 60(x18)\n" \
                 "sw x17, 64(x18)\n" \

#define POP_ALL  "lw x1,  0(x18)\n" \
                 "lw x9,  32(x18)\n" \
                 "lw x10, 36(x18)\n" \
                 "lw x11, 40(x18)\n" \
                 "lw x12, 44(x18)\n" \
                 "lw x13, 48(x18)\n" \
                 "lw x14, 52(x18)\n" \
                 "lw x15, 56(x18)\n" \
                 "lw x16, 60(x18)\n" \
                 "lw x17, 64(x18)\n" \

#define INSTR_ACC_FAULT  1
#define ILLEGAL_INSTR    2
#define LOAD_ACC_FAULT   5
#define STORE_ACC_FAULT  7
#define ECALL_MCAUSE     11
#define ECALL_UCAUSE     8


int check_load_tor(void);

int main()
{

#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  int error = 0;
  int failed = 0;
  if(get_core_id() == 0) {

    for(int i=0;i<64;i++)
      protected_data[i] = 0;

    // Check if the PMP can prevent X, R and W from protected regions
    error = check_xrw_tor();

    if(error != 0)
      printf("TEST XRW FAILED :( - errors %d \n", error);
    else
      printf("TEST XRW OK :)\n" );

    failed+=error;

    error = check_special_case();

    if(error != 0)
      printf("TEST SPECIAL FAILED :( - errors %d \n", error);
    else
      printf("TEST SPECIAL OK :)\n" );

    failed+=error;

    // Check if writing to Machine CSRs or executing Machine instructions is causing exceptions
    error = check_user_exceptions();

    if(error != 0)
      printf("TEST USER EXCEPTIONS FAILED :( - errors %d \n", error);
    else
      printf("TEST USER EXCEPTIONS OK :)\n" );

    failed+=error;


  }


  return failed;


}

void __attribute__((aligned)) task_user()
{
  unsigned int A = 0;

  for(int i=0;i<64;i++)
      protected_data[i] = i;

  for(int i=0;i<64;i++)
      A+=protected_data[i];

    asm volatile("ecall");

}

void __attribute__((aligned)) task_user_exeption()
{
    //asm volatile(".word 0x00007123;");
    asm volatile("csrrw x0, mepc, x15");

}

void __attribute__((interrupt)) __perturbation_handler()
{

}

void __attribute__((interrupt)) __test_exceptions_handler()
{

    unsigned int mcause;
    asm volatile (
        "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));

    switch(mcause)
    {

        case INSTR_ACC_FAULT:
            my_dataerr_handler();
            break;
        case LOAD_ACC_FAULT:
            my_dataerr_handler();
            break;
        case STORE_ACC_FAULT:
            my_dataerr_handler();
            break;
        case ECALL_UCAUSE:
            my_exception();
        case ILLEGAL_INSTR:
            my_exception();
            break;
    }

    //go back to M mode
    asm volatile (
        "csrrw x0, mstatus, %[mpp_user]\n"
        :  : [mpp_user] "r" (0x1800));

}


void __attribute__((inline)) my_exception()
{
    asm volatile(
                "lw x15, 0x0(%[return_addr])\n"
                "csrrw x0, mepc, x15\n"
                "csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
                : : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");
}

void __attribute__((inline)) my_dataerr_handler()
{
  asm volatile(
                "lw x15, 0x0(%[return_addr])\n"
                "csrrw x0, mepc, x15\n"
                "csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
                : : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");

}

//================================================================
// Check XRW permission with 1 Region using the TOR mode
//================================================================
int check_xrw_tor(void) {

  unsigned int i;
  unsigned int error = 0;

  unsigned int lower_bound_data = protected_data;
  unsigned int upper_bound_data = lower_bound_data + 64;

  unsigned int lower_bound_instr = task_user;
  unsigned int upper_bound_instr = task_user + 64;


  volatile int mcause = 0;

  unsigned int debug_addr = 0x1A110000;

  unsigned int pert_addr  = debug_addr | 0x600;

  unsigned int pert_instr_stall_mode_addr  = pert_addr | 0x10;
  unsigned int pert_instr_maxstall         = pert_addr | 0x14;
  unsigned int pert_instr_grant_stall      = pert_addr | 0x18;
  unsigned int pert_instr_valid_stall      = pert_addr | 0x1C;

  unsigned int pert_data_stall_mode_addr   = pert_addr | 0x0;
  unsigned int pert_data_maxstall          = pert_addr | 0x4;
  unsigned int pert_data_grant_stall       = pert_addr | 0x8;
  unsigned int pert_data_valid_stall       = pert_addr | 0xC;


  unsigned int pert_irq_mode_addr          = pert_addr | 0x20;
  unsigned int pert_irq_min_cycles         = pert_addr | 0x24;
  unsigned int pert_irq_max_cycles         = pert_addr | 0x28;
  unsigned int pert_irq_min_id             = pert_addr | 0x2C;
  unsigned int pert_irq_max_id             = pert_addr | 0x30;
  unsigned int pert_irq_resp_is            = pert_addr | 0x34;
  unsigned int pert_irq_valid_stall        = pert_addr | 0x38;



  lower_bound_data = lower_bound_data >> 2;
  upper_bound_data = upper_bound_data >> 2;

  lower_bound_instr = lower_bound_instr >> 2;
  upper_bound_instr = upper_bound_instr >> 2;

  int irq = rt_irq_disable();

#ifdef PERTURBATION_INSTR
  //set random stalls on Instruction Fetch Interface
  asm volatile ("set_random_stall_instr:"
                "sw %[maxstall], 0x(%[pert_instr_maxstall])\n"
                "sw %[random_mode], 0x(%[pert_instr_stall_mode_addr])\n" : : [maxstall] "r" (4), [random_mode] "r" (2), \
                                                                             [pert_instr_maxstall] "r" (pert_instr_maxstall), \
                                                                             [pert_instr_stall_mode_addr] "r" (pert_instr_stall_mode_addr));
#endif

#ifdef PERTURBATION_DATA
  //set random stalls on Data Interface
  asm volatile ("set_random_stall_data:"
                "sw %[maxstall], 0x(%[pert_data_maxstall])\n"
                "sw %[random_mode], 0x(%[pert_data_stall_mode_addr])\n" : : [maxstall] "r" (4), [random_mode] "r" (2), \
                                                                             [pert_data_maxstall] "r" (pert_data_maxstall), \
                                                                             [pert_data_stall_mode_addr] "r" (pert_data_stall_mode_addr));
#endif

  rt_irq_set_handler (0, __test_exceptions_handler);

  //give to every entry all the accesses but addr1
  asm volatile (
                "csrrw x0, mtvec, %[bootaddr]\n"

                "la x14, return_here_1\n"
                "sw x14, 0(%[return_addr])\n"

                //NO X in REGION 4 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "csrrw x0, 0x3A1, %[pmpcfg1]\n"
                "csrrw x0, 0x3A2, %[pmpcfg2]\n"
                "csrrw x0, 0x3A3, %[pmpcfg3]\n"

                "csrrw x0, 0x3B0, %[pmpaddr0]\n"
                "csrrw x0, 0x3B1, %[pmpaddr1]\n"
                "csrrw x0, 0x3B2, %[pmpaddr2]\n"
                "csrrw x0, 0x3B3, %[pmpaddr3]\n"

                "csrrw x0, 0x3B4, %[pmpaddr4]\n"
                "csrrw x0, 0x3B5, %[pmpaddr5]\n"
                "csrrw x0, 0x3B6, %[pmpaddr6]\n"
                "csrrw x0, 0x3B7, %[pmpaddr7]\n"

                "csrrw x0, 0x3B8, %[pmpaddr8]\n"
                "csrrw x0, 0x3B9, %[pmpaddr9]\n"
                "csrrw x0, 0x3BA, %[pmpaddra]\n"
                "csrrw x0, 0x3BB, %[pmpaddrb]\n"

                "csrrw x0, 0x3BC, %[pmpaddrc]\n"
                "csrrw x0, 0x3BD, %[pmpaddrd]\n"
                "csrrw x0, 0x3BE, %[pmpaddre]\n"
                "csrrw x0, 0x3BF, %[pmpaddrf]\n"
                "mv x18, %[stack_data]\n"
                PUSH_ALL
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, %[mepc]\n"
                "mret\n"
                "return_here_1: \n"
                POP_ALL
                :  : [pmpcfg0] "r" (0x0B0F0F0F), [pmpcfg1] "r" (0x0F0F0F0F), [pmpcfg2] "r" (0x0F0F0F0F), [pmpcfg3] "r" (0x0F0F0F0F),
                     [pmpaddr0] "r" (lower_bound_data), [pmpaddr1] "r" (upper_bound_data), [pmpaddr2] "r" (lower_bound_instr), [pmpaddr3] "r" (upper_bound_instr),
                     [pmpaddr4] "r" (0xFFFFFFFF), [pmpaddr5] "r" (0xFFFFFFFF), [pmpaddr6] "r" (0xFFFFFFFF), [pmpaddr7] "r" (0xFFFFFFFF),
                     [pmpaddr8] "r" (0xFFFFFFFF), [pmpaddr9] "r" (0xFFFFFFFF), [pmpaddra] "r" (0xFFFFFFFF), [pmpaddrb] "r" (0xFFFFFFFF),
                     [pmpaddrc] "r" (0xFFFFFFFF), [pmpaddrd] "r" (0xFFFFFFFF), [pmpaddre] "r" (0xFFFFFFFF), [pmpaddrf] "r" (0xFFFFFFFF),
                     [mepc] "r" (task_user), [bootaddr] "r" (0x1C008000), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x15", "x14", "x18");

            //in the main we initialized to 0, be sure they haven't been modified
            for(int i=0;i<64;i++) {
              if(protected_data[i] != 0)
                error++;
            }
            if (error != 0) printf("ERROR: X access failed\n");

            asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));

            if(mcause != INSTR_ACC_FAULT)
              error++;
            if (error != 0) printf("ERROR: X CAUSE failed\n");

            if (error != 0) return error;

            //in the main we initialized to 0, be sure they haven't been modified
            asm volatile (
                "la x14, return_here_2\n"
                "sw x14, 0(%[return_addr])\n"

                //NO W in REGION 1 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "mv x18, %[stack_data]\n"
                PUSH_ALL
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, %[mepc]\n"
                "mret\n"
                "return_here_2: \n"
                POP_ALL

                :  : [pmpcfg0] "r" (0x0F0F0D0F),
                     [mepc] "r" (task_user), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x14", "x18");

            for(int i=0;i<64;i++) {
              if(protected_data[i] != 0)
                error++;
            }
            if (error != 0) printf("ERROR: W access failed\n");

            asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
            if(mcause != STORE_ACC_FAULT)
              error++;
            if (error != 0) printf("ERROR: W CAUSE failed\n");

            if (error != 0) return error;


            asm volatile (
                "la x14, return_here_3\n"
                "sw x14, 0(%[return_addr])\n"

                //NO R in REGION 1 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "mv x18, %[stack_data]\n"
                PUSH_ALL
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, %[mepc]\n"
                "mret\n"
                "return_here_3: \n"
                POP_ALL

                :  : [pmpcfg0] "r" (0x0F0F0E0F),
                     [mepc] "r" (task_user), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x14", "x18");

            for(int i=0;i<64;i++) {
              if(protected_data[i] != i)
                error++;
            }
            if (error != 0) printf("ERROR: R access failed\n");

            asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
            if(mcause != LOAD_ACC_FAULT)
              error++;
            if (error != 0) printf("ERROR: R CAUSE failed\n");

            if (error != 0) return error;


            asm volatile (
                "la x14, return_here_4\n"
                "sw x14, 0(%[return_addr])\n"

                //Everything ok in REGION 1 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "la x1, return_here_4\n"
                "mv x18, %[stack_data]\n"
                PUSH_ALL
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, %[mepc]\n"
                "mret\n"
                "return_here_4: \n"
                POP_ALL

                :  : [pmpcfg0] "r" (0x0F0F0F0F),
                     [mepc] "r" (task_user), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x14", "x18");

            for(int i=0;i<64;i++) {
              if(protected_data[i] != i)
                error++;
            }

#ifdef PERTURBATION_INSTR
  //set random stalls on Instruction Fetch Interface
  asm volatile (
                "sw x0, 0x(%[pert_instr_grant_stall])\n"
                "sw x0, 0x(%[pert_instr_valid_stall])\n"
                "sw %[random_mode], 0x(%[pert_instr_stall_mode_addr])\n" : : [pert_instr_grant_stall] "r" (0), [pert_instr_valid_stall] "r" (1), \
                                                                             [random_mode] "r" (1), \
                                                                             [pert_instr_stall_mode_addr] "r" (pert_instr_stall_mode_addr));
#endif

#ifdef PERTURBATION_DATA
  //set random stalls on Data Interface
  asm volatile (
                "sw x0, 0x(%[pert_data_grant_stall])\n"
                "sw x0, 0x(%[pert_data_valid_stall])\n"
                "sw %[random_mode], 0x(%[pert_data_stall_mode_addr])\n" : : [pert_data_grant_stall] "r" (0), [pert_data_valid_stall] "r" (1), \
                                                                             [random_mode] "r" (1), \
                                                                             [pert_data_stall_mode_addr] "r" (pert_data_stall_mode_addr));
#endif
  return error;

}


int check_special_case(void) {

  unsigned int i;
  unsigned int error = 0;

  unsigned int lower_bound_data = protected_data;
  unsigned int upper_bound_data = lower_bound_data + 64;

  unsigned int lower_bound_instr = task_user;
  unsigned int upper_bound_instr = task_user + 64;


  volatile int mcause = 0;

  unsigned int debug_addr = 0x1A110000;

  unsigned int pert_addr  = debug_addr | 0x600;

  unsigned int pert_instr_stall_mode_addr  = pert_addr | 0x10;
  unsigned int pert_instr_maxstall         = pert_addr | 0x14;
  unsigned int pert_instr_grant_stall      = pert_addr | 0x18;
  unsigned int pert_instr_valid_stall      = pert_addr | 0x1C;

  unsigned int pert_data_stall_mode_addr   = pert_addr | 0x0;
  unsigned int pert_data_maxstall          = pert_addr | 0x4;
  unsigned int pert_data_grant_stall       = pert_addr | 0x8;
  unsigned int pert_data_valid_stall       = pert_addr | 0xC;

  unsigned int pert_irq_mode_addr          = pert_addr | 0x20;
  unsigned int pert_irq_min_cycles         = pert_addr | 0x24;
  unsigned int pert_irq_max_cycles         = pert_addr | 0x28;
  unsigned int pert_irq_min_id             = pert_addr | 0x2C;
  unsigned int pert_irq_max_id             = pert_addr | 0x30;
  unsigned int pert_irq_resp_is            = pert_addr | 0x34;
  unsigned int pert_irq_pc_trig            = pert_addr | 0x38;


  lower_bound_data = lower_bound_data >> 2;
  upper_bound_data = upper_bound_data >> 2;

  lower_bound_instr = lower_bound_instr >> 2;
  upper_bound_instr = upper_bound_instr >> 2;

  int irq = rt_irq_disable();


  rt_irq_set_handler (0, __test_exceptions_handler);

  int test_val      = 0xabbaabba;
  protected_data[0] = 0xdeadbeef;

  //give to every entry all the accesses but addr1
  asm volatile (
                "csrrw x0, mtvec, %[bootaddr]\n"
                :  : [bootaddr] "r" (0x1C008000) : "x15");

           asm volatile (
                "la x14, return_here_sc_1\n"
                "sw x14, 0(%[return_addr])\n"
                "mv x16, %[DEAD_VAL]\n"
                //NO W in REGION 1 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "la x14, user_mode_1\n"
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, x14\n"
                "mret\n"
                "user_mode_1: \n"
                "lw x16, 0(%[addr_prohibited])\n"
                "loop_1: jal x0, loop_1\n"
                //cycle0: load in EX sent address to PMP, JMP in ID is jumping
                //cycle1: data error arrives to the pipeline, now exception and return to return_here_sc_1
                "return_here_sc_1: nop\n"
                "mv %[check_val], x16\n"

                : [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr),
                     [addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

    if(test_val == 0xdeadbeef){
        printf("Error! test_val is %x, expected %x\n", test_val, 0xabbaabba);
        error++;
    }
    asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
            if(mcause != LOAD_ACC_FAULT)
              error++;



  test_val = 0xabbaabba;
  protected_data[0] = 0xdeadbeef;

           asm volatile (
                "la x14, return_here_sc_2\n"
                "sw x14, 0(%[return_addr])\n"
                "mv x16, %[DEAD_VAL]\n"
                //NO W in REGION 1 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "la x14, user_mode_2\n"
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, x14\n"
                "mret\n"
                "user_mode_2: \n"
                "lw x16, 0(%[addr_prohibited])\n"
                "csrrs x0, 0x041, x0\n"
                //cycle0: load in EX sent address to PMP, CSR in ID is moving the PIPELINE at the next STATE
                //cycle1: data error arrives and exception and return to return_here_sc_2
                "return_here_sc_2: nop\n"
                "mv %[check_val], x16\n"

                : [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr),
                     [addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

    if(test_val == 0xdeadbeef){
        printf("Error! test_val is %x, expected %x\n", test_val, 0xabbaabba);
        error++;
    }
    asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
            if(mcause != LOAD_ACC_FAULT)
              error++;


  test_val = 0xabbaabba;
  protected_data[0] = 0xdeadbeef;
           asm volatile (
                "la x14, return_here_sc_3\n"
                "sw x14, 0(%[return_addr])\n"
                "mv x16, %[DEAD_VAL]\n"
                //NO W in REGION 1 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "la x14, user_mode_3\n"
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, x14\n"
                "mret\n"
                "user_mode_3: \n"
                "lw x16, 0(%[addr_prohibited])\n"
                "csrrs x0, 0x300, x0\n" //--> access to MSTATUS cause illegal in U mode
                //cycle0: load in EX sent address to PMP, illegal in ID is moving the PIPELINE at the next STATE
                //cycle1: data error arrives and exception and return to return_here_sc_3
                "return_here_sc_3: nop\n"
                "mv %[check_val], x16\n"

                : [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr),
                     [addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

    if(test_val == 0xdeadbeef){
        printf("Error! test_val is %x, expected %x\n", test_val, 0xabbaabba);
        error++;
    }
    asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
            if(mcause != LOAD_ACC_FAULT)
              error++;

  test_val = 0xabbaabba;
  protected_data[0] = 0xdeadbeef;
           asm volatile (
                "la x14, return_here_sc_4\n"
                "sw x14, 0(%[return_addr])\n"
                "mv x16, %[DEAD_VAL]\n"
                //NO W in REGION 1 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "la x14, user_mode_4\n"
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, x14\n"
                "mret\n"
                "user_mode_4: \n"
                "lw x16, 0(%[addr_prohibited])\n"
                "ecall\n"
                //cycle0: load in EX sent address to PMP, ecall in ID is moving the PIPELINE at the next STATE
                //cycle1: data error arrives and exception and return to return_here_sc_4
                "return_here_sc_4: nop\n"
                "mv %[check_val], x16\n"

                : [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr),
                     [addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

    if(test_val == 0xdeadbeef){
        printf("Error! test_val is %x, expected %x\n", test_val, 0xabbaabba);
        error++;
    }
    asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
            if(mcause != LOAD_ACC_FAULT)
              error++;


#ifdef PERTURBATION_ITC
    *((unsigned int *)pert_irq_mode_addr) = 3; //PC TRIG MODE
    rt_irq_set_handler (18, __perturbation_handler); //perturbation IRQ is 0x12

  test_val = 0xabbaabba;
           asm volatile (
                "csrrs x0, 0x300, 0x8\n"
                "la x14, return_here_sc_5\n"
                "sw x14, 0(%[return_addr])\n"
                "mv x16, %[DEAD_VAL]\n"
                //NO W in REGION 1 - TOR
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "la x14, stop_instr_5\n"
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, x14\n"
                "la x14, stop_instr_5\n"
                "sw x14, 0(%[pert_irq_pc_trig])\n"
                "mret\n"
                "stop_instr_5: lw x16, 0(%[addr_prohibited])\n"
                "nop\n" //this instruction will be interrupted as the INT_REQ is registered
                //cycle0: load in EX sent address to PMP, IRQ in ID is moving the PIPELINE at the next STATE
                //cycle1: data error arrives and exception and return to return_here_sc_5
                "return_here_sc_5: nop\n"
                "mv %[check_val], x16\n"
                : [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr), [pert_irq_pc_trig] "r" (pert_irq_pc_trig),
                     [addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

    if(test_val != 0xDEAD){
        printf("Error! test_val is %x\n", test_val);
        error++;
    }

#endif

  return error;

}


//================================================================
// Check USER Exceptions
//================================================================
int check_user_exceptions(void) {

  unsigned int i;
  unsigned int error = 0;
  volatile int mcause = 0;


  int irq = rt_irq_disable();

  rt_irq_set_handler (0, __test_exceptions_handler);


  asm volatile (
                "csrrw x0, mtvec, %[bootaddr]\n"

                "la x14, return_here_illegal\n"
                "sw x14, 0(%[return_addr])\n"

                //NO restrictions for USER
                "csrrw x0, 0x3A0, %[pmpcfg0]\n"
                "csrrw x0, 0x3A1, %[pmpcfg1]\n"
                "csrrw x0, 0x3A2, %[pmpcfg2]\n"
                "csrrw x0, 0x3A3, %[pmpcfg3]\n"

                "csrrw x0, 0x3B0, %[pmpaddr0]\n"
                "csrrw x0, 0x3B1, %[pmpaddr1]\n"
                "csrrw x0, 0x3B2, %[pmpaddr2]\n"
                "csrrw x0, 0x3B3, %[pmpaddr3]\n"

                "csrrw x0, 0x3B4, %[pmpaddr4]\n"
                "csrrw x0, 0x3B5, %[pmpaddr5]\n"
                "csrrw x0, 0x3B6, %[pmpaddr6]\n"
                "csrrw x0, 0x3B7, %[pmpaddr7]\n"

                "csrrw x0, 0x3B8, %[pmpaddr8]\n"
                "csrrw x0, 0x3B9, %[pmpaddr9]\n"
                "csrrw x0, 0x3BA, %[pmpaddra]\n"
                "csrrw x0, 0x3BB, %[pmpaddrb]\n"

                "csrrw x0, 0x3BC, %[pmpaddrc]\n"
                "csrrw x0, 0x3BD, %[pmpaddrd]\n"
                "csrrw x0, 0x3BE, %[pmpaddre]\n"
                "csrrw x0, 0x3BF, %[pmpaddrf]\n"
                "mv x18, %[stack_data]\n"
                PUSH_ALL
                "csrrw x0, mstatus, %[mpp_user]\n"
                "csrrw x0, mepc, %[mepc]\n"
                "mret\n"
                "return_here_illegal: \n"
                POP_ALL
                :  : [pmpcfg0] "r" (0x0F0F0F0F), [pmpcfg1] "r" (0x0F0F0F0F), [pmpcfg2] "r" (0x0F0F0F0F), [pmpcfg3] "r" (0x0F0F0F0F),
                     [pmpaddr0] "r" (0xFFFFFFFF), [pmpaddr1] "r" (0xFFFFFFFF), [pmpaddr2] "r" (0xFFFFFFFF), [pmpaddr3] "r" (0xFFFFFFFF),
                     [pmpaddr4] "r" (0xFFFFFFFF), [pmpaddr5] "r" (0xFFFFFFFF), [pmpaddr6] "r" (0xFFFFFFFF), [pmpaddr7] "r" (0xFFFFFFFF),
                     [pmpaddr8] "r" (0xFFFFFFFF), [pmpaddr9] "r" (0xFFFFFFFF), [pmpaddra] "r" (0xFFFFFFFF), [pmpaddrb] "r" (0xFFFFFFFF),
                     [pmpaddrc] "r" (0xFFFFFFFF), [pmpaddrd] "r" (0xFFFFFFFF), [pmpaddre] "r" (0xFFFFFFFF), [pmpaddrf] "r" (0xFFFFFFFF),
                     [mepc] "r" (task_user_exeption), [bootaddr] "r" (0x1C008000), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x15", "x14", "x18");

            asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));

            if(mcause != ILLEGAL_INSTR)
              error++;
            if (error != 0) printf("ERROR: X CAUSE failed\n");

            asm volatile (
                "csrrw x0, mtvec, %[bootaddr]\n"

                "la x14, return_here_illegal_2\n"
                "sw x14, 0(%[return_addr])\n"

                "mv x18, %[stack_data]\n"
                PUSH_ALL
                "csrrw x0, 0x041, %[uepc]\n"
                "uret\n"
                "return_here_illegal_2: \n"
                POP_ALL
                :  : [uepc] "r" (task_user_exeption), [bootaddr] "r" (0x1C008000), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data) : "x15", "x14", "x18");

            asm volatile (
                "csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));

            if(mcause != ILLEGAL_INSTR)
              error++;
            if (error != 0) printf("ERROR: X CAUSE failed\n");


            return error;

}