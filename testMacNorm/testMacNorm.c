// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

// This testbench checks the basic functionality of:
//

//p.mulsN
//p.muluN
//p.mulsRN
//p.muluRN
//p.macsN
//p.macuN
//p.macsRN
//p.macuRN

#include <stdio.h>
#include "pulp.h"

#define MULSNR   "p.mulsN"
#define MULUNR   "p.muluN"
#define MULSNRR  "p.mulsRN"
#define MULUNRR  "p.muluRN"
#define MACSNR   "p.macsN"
#define MACUNR   "p.macuN"
#define MACSNRR  "p.macsRN"
#define MACUNRR  "p.macuRN"

void check_mulsNr  (testresult_t *result, void (*start)(), void (*stop)());
void check_muluNr  (testresult_t *result, void (*start)(), void (*stop)());
void check_mulsNrR (testresult_t *result, void (*start)(), void (*stop)());
void check_muluNrR (testresult_t *result, void (*start)(), void (*stop)());
void check_macsNr  (testresult_t *result, void (*start)(), void (*stop)());
void check_macuNr  (testresult_t *result, void (*start)(), void (*stop)());
void check_macsNrR (testresult_t *result, void (*start)(), void (*stop)());
void check_macuNrR (testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "mulsNr"    , .test = check_mulsNr     },
  { .name = "macsNr"    , .test = check_macsNr     },
  { .name = "muluNr"    , .test = check_muluNr     },
  { .name = "macuNr"    , .test = check_macuNr     },
  { .name = "mulsNrR"   , .test = check_mulsNrR    },
  { .name = "macsNrR"   , .test = check_macsNrR    },
  { .name = "muluNrR"   , .test = check_muluNrR    },
  { .name = "macuNrR"   , .test = check_macuNrR    },
  {0, 0}
};

int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if(get_core_id() == 0) {
    return run_suite(testcases);
  }

  return 0;
}

#include "testMacNorm_stimuli.h"


//################################################################################
//# T E S T    M U L {S, U, US} Nr
//################################################################################

void check_mulsNr(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check p.mulsN
  //-----------------------------------------------------------------
  for(i = 0; i < NumberOfStimuli; i++) {

    asm volatile (MULSNR " %[c], %[a], %[b],%[imm]\n"
                  : [c] "=r" (res)
                  : [a] "r"  (g_mulsNr_a[i]), [b] "r" (g_mulsNr_b[i]), [imm] "i" (g_mulsNr_IMM));

    check_uint32(result, "mulsNr", res,  g_mulsNr_exp[i]);

  }

}


void check_muluNr(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check p.muluN
  //-----------------------------------------------------------------
  for(i = 0; i < NumberOfStimuli; i++) {

    asm volatile (MULUNR " %[c], %[a], %[b],%[imm]\n"
                  : [c] "=r" (res)
                  : [a] "r"  (g_muluNr_a[i]), [b] "r" (g_muluNr_b[i]), [imm] "i" (g_muluNr_IMM));

    check_uint32(result, "muluNr", res,  g_muluNr_exp[i]);
  }

}

//################################################################################
//# T E S T    M U L {S, U, US} NrR
//################################################################################

void check_mulsNrR(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check p.mulsRN
  //-----------------------------------------------------------------
  for(i = 0; i < NumberOfStimuli; i++) {

    asm volatile (MULSNRR " %[c], %[a], %[b],%[imm]\n"
                  : [c] "=r" (res)
                  : [a] "r"  (g_mulsNrR_a[i]), [b] "r" (g_mulsNrR_b[i]), [imm] "i" (g_mulsNrR_IMM));

    check_uint32(result, "mulsNrR", res,  g_mulsNrR_exp[i]);


  }

}


void check_muluNrR(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check p.muluRN
  //-----------------------------------------------------------------
  for(i = 0; i < NumberOfStimuli; i++) {

    asm volatile (MULUNRR " %[c], %[a], %[b],%[imm]\n"
                  : [c] "=r" (res)
                  : [a] "r"  (g_muluNrR_a[i]), [b] "r" (g_muluNrR_b[i]), [imm] "i" (g_muluNrR_IMM));

    check_uint32(result, "muluNrR", res,  g_muluNrR_exp[i]);

  }

}

//################################################################################
//# T E S T    M A C {S, U, US} Nr
//################################################################################

void check_macsNr(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check p.macsN
  //-----------------------------------------------------------------
  for(i = 0; i < NumberOfStimuli; i++) {

    asm volatile (MACSNR " %[c], %[a], %[b],%[imm]\n"
                  : [c] "+r" (g_macsNr_c[i])
                  : [a] "r"  (g_macsNr_a[i]), [b] "r" (g_macsNr_b[i]), [imm] "i" (g_macsNr_IMM));

    check_uint32(result, "macsNr", g_macsNr_c[i],  g_macsNr_exp[i]);


  }
}

void check_macuNr(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check p.macuN
  //-----------------------------------------------------------------
  for(i = 0; i < NumberOfStimuli; i++) {

    asm volatile (MACUNR " %[c], %[a], %[b],%[imm]\n"
                  : [c] "+r" (g_macuNr_c[i])
                  : [a] "r"  (g_macuNr_a[i]), [b] "r" (g_macuNr_b[i]), [imm] "i" (g_macuNr_IMM));

    check_uint32(result, "macuNr", g_macuNr_c[i],  g_macuNr_exp[i]);


  }

}

//################################################################################
//# T E S T    M A C {S, U, US} NrR
//################################################################################

void check_macsNrR(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check p.macsRN
  //-----------------------------------------------------------------
  for(i = 0; i < NumberOfStimuli; i++) {

    asm volatile (MACSNRR " %[c], %[a], %[b],%[imm]\n"
                  : [c] "+r" (g_macsNrR_c[i])
                  : [a] "r"  (g_macsNrR_a[i]), [b] "r" (g_macsNrR_b[i]), [imm] "i" (g_macsNrR_IMM));

    check_uint32(result, "macsNrR", g_macsNrR_c[i],  g_macsNrR_exp[i]);


  }
}

void check_macuNrR(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check p.macuRN
  //-----------------------------------------------------------------
  for(i = 0; i < NumberOfStimuli; i++) {

    asm volatile (MACUNRR " %[c], %[a], %[b],%[imm]\n"
                  : [c] "+r" (g_macuNrR_c[i])
                  : [a] "r"  (g_macuNrR_a[i]), [b] "r" (g_macuNrR_b[i]), [imm] "i" (g_macuNrR_IMM));

    check_uint32(result, "macuNrR", g_macuNrR_c[i],  g_macuNrR_exp[i]);

  }

}