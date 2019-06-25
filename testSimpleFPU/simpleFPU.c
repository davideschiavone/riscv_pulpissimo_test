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
#include <math.h>
#include "fpu_stimuli.h"

int checkFloat (float *B, float *A, int n, char* name)
{
    int i;
    int err = 0;
    for (i=0;i<n;i++){
        if(A[i]!=B[i]){
            err++;
            printf("[%s] Error at %d, expected %x but result is %x\n",name,i,*((int*)(&A[i])),*((int*)(&B[i])));
        }
    }

  return err;

}

int checkInt (int *B, int *A, int n, char* name)
{
    int i, type_a, type_b;
    int err = 0;
    for (i=0;i<n;i++){
        if(A[i]!=B[i]){
            err++;
            printf("[%s] Error at %d, expected %x but result is %x\n",name,i,A[i],B[i]);
        }
    }

  return err;

}


int main ()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif


    int i, ri;
    int err=0;
    float A, B, C, rf;

    for (i=0;i<N;i++){

        A           = *(float *)(&A_float[i]);
        B           = *(float *)(&B_float[i]);
        C           = *(float *)(&C_float[i]);

        rf  =  (A  +  B);
        add_act[i] = *(int *)(&rf);

        rf  =  (A  -  B);
        sub_act[i] = *(int *)(&rf);

        //rf  =  (A  <=  B ? A  :  B);
        asm volatile("fmin.s %[fd], %[fs1], %[fs2]" : [fd] "=f" (rf) : [fs1] "f" (A), [fs2] "f" (B));
        min_act[i] = *(int *)(&rf);

        //rf  =  (A  >=  B ? A  :  B);
        asm volatile("fmax.s %[fd], %[fs1], %[fs2]" : [fd] "=f" (rf) : [fs1] "f" (A), [fs2] "f" (B));
        max_act[i] = *(int *)(&rf);

        //rf  = sqrtf(A);
        asm volatile("fsqrt.s %[fd], %[fs1]" : [fd] "=f" (rf) : [fs1] "f" (A));
        sqrt_act[i] = *(int *)(&rf);

        rf  =  (A * B);
        mul_act[i] = *(int *)(&rf);

        rf  =  (A / B);
        div_act[i] = *(int *)(&rf);

        //rf  =  (A * B + C);
        asm volatile("fmadd.s %[fd], %[fs1], %[fs2], %[fs3]" : [fd] "=f" (rf) : [fs1] "f" (A), [fs2] "f" (B), [fs3] "f" (C));
        madd_act[i] = *(int *)(&rf);

        ri  =  (A  ==  B);
        eq_act[i] = ri;

        ri  =  (A  <   B);
        lt_act[i] = ri;

        ri  =  (A  <=  B);
        le_act[i] = ri;

    }

    err+=checkInt(add_act,add_exp,N,"add");
    err+=checkInt(sub_act,sub_exp,N,"sub");
    err+=checkInt(min_act,min_exp,N,"min");
    err+=checkInt(max_act,max_exp,N,"max");
    err+=checkInt(sqrt_act,sqrt_exp,N,"sqrt");
    err+=checkInt(mul_act,mul_exp,N,"mul");
    err+=checkInt(div_act,div_exp,N,"div");
    err+=checkInt(madd_act,madd_exp,N,"madd");

    err+=checkInt(eq_act,eq_exp,N,"eq");
    err+=checkInt(lt_act,lt_exp,N,"lt");
    err+=checkInt(le_act,le_exp,N,"le");


    printf("Number of errors %d\n",err );

    return err;
}