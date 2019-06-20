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

// p.mac
// p.msu
// p.macs
// p.macu
// p.muls
// p.mulu
// p.machhs
// p.machhu
// p.mulhhs
// p.mulhhu


#include "pulp.h"
#include <stdio.h>
#include "riscv_test.h"

#define MAC      "p.mac"
#define MSU      "p.msu"
#define MACS     "p.macs"
#define MACU     "p.macu"
#define MULS     "p.muls"
#define MULUU    "p.mulu"
#define MACHHS   "p.machhs"
#define MACHHU   "p.machhu"
#define MULHHS   "p.mulhhs"
#define MULHHU   "p.mulhhu"

void check_mac(void);
void check_mac_subword(void);

int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if(get_core_id() == 0) {
    test_init();

    check_mac();
    check_mac_subword();

    test_report();

    return test_get_num_errors() != 0;
  } else return 0;
}

#include "testMAC3_stimuli.h"

#define util_check_mac(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    : [c] "+r" (prefix ## _act[i]) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
    }


void check_mac(void) {
  unsigned int i;

  //-----------------------------------------------------------------
  // Check p.mac p.msu
  //-----------------------------------------------------------------

  util_check_mac      (MAC,  i, g_mac);
  util_check_mac      (MSU,  i, g_msu);

}

void check_mac_subword(void) {
    unsigned int i;

    util_check_mac (MACS     , i, g_macs     );
    util_check_mac (MACU     , i, g_macu     );

    util_check_mac (MULS     , i, g_muls     );
    util_check_mac (MULUU    , i, g_muluu    );

    util_check_mac (MACHHS   , i, g_machhs   );
    util_check_mac (MACHHU   , i, g_machhu   );

    util_check_mac (MULHHS   , i, g_mulhhs   );
    util_check_mac (MULHHU   , i, g_mulhhu   );

}
