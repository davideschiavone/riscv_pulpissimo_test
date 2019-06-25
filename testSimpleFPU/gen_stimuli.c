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
//#include <fenv.h>
//#pragma STDC FENV_ACCESS ON
#define N 50

void writeFloat (FILE *fp, float *A, int n, char* name)
{
    int i;
    fprintf(fp, "int %s[] = {\n",name );

    for (i=0;i<n;i++)
        if(isnan(A[i]) == 0)
            fprintf(fp, "0x%x,\n", *((int*)(&A[i])) );
        else{
            printf("Found NaN number at %d: %f(%x) (%s) \n",i,A[i],*((int *)(&A[i])),name);
            fprintf(fp, "0x7FC00000,\n");
        }

    fprintf(fp, "};\n");

  return;

}

void writeInt (FILE *fp, int *A, int n, char* name)
{
    int i;
    fprintf(fp, "int %s[] = {\n",name );

    for (i=0;i<n;i++)
        fprintf(fp, "0x%x,\n", A[i] );

    fprintf(fp, "};\n");

  return;

}

int main ()
{

    // store the original rounding mode
//    const int originalRounding = fegetround( );
//    fesetround(FE_TONEAREST);

    int i;
    int rand_int;
    float A_float[N], B_float[N], C_float[N];
    float add[N], sub[N], min[N], max[N], sqrt[N], mul[N], div[N], madd[N];
    int   eq[N], lt[N], le[N];
    FILE *fp;

    for (i=0;i<N;i++){
        rand_int = rand();
        A_float[i] = *((float *)(&rand_int));
        if(isnan(A_float[i])) A_float[i] = 0.1f;
        rand_int = rand();
        B_float[i] = *((float *)(&rand_int));
        if(isnan(B_float[i])) B_float[i] = 0.2f;
        rand_int = rand();
        C_float[i] = *((float *)(&rand_int));
        if(isnan(C_float[i])) C_float[i] = 0.3f;

        add[i]  = A_float[i] + B_float[i];
        sub[i]  = A_float[i] - B_float[i];
        min[i]  = A_float[i] <= B_float[i] ? A_float[i] : B_float[i];
        max[i]  = A_float[i] >= B_float[i] ? A_float[i] : B_float[i];
        sqrt[i] = sqrtf(A_float[i]);
        mul[i]  = A_float[i]*B_float[i];
        div[i]  = A_float[i]/B_float[i];
        madd[i] = fmaf(A_float[i],B_float[i],C_float[i]);
        eq[i]   = A_float[i] == B_float[i];
        lt[i]   = A_float[i] <  B_float[i];
        le[i]   = A_float[i] <= B_float[i];

    }

    fp = fopen("fpu_stimuli.h", "w");

    fprintf(fp,"#define N %d\n",N );

    writeFloat(fp,A_float,N,"A_float");
    writeFloat(fp,B_float,N,"B_float");
    writeFloat(fp,C_float,N,"C_float");

    writeFloat(fp,add,N,"add_exp");
    writeFloat(fp,sub,N,"sub_exp");
    writeFloat(fp,min,N,"min_exp");
    writeFloat(fp,max,N,"max_exp");
    writeFloat(fp,sqrt,N,"sqrt_exp");
    writeFloat(fp,mul,N,"mul_exp");
    writeFloat(fp,div,N,"div_exp");
    writeFloat(fp,madd,N,"madd_exp");
    writeInt(fp,eq,N,"eq_exp");
    writeInt(fp,lt,N,"lt_exp");
    writeInt(fp,le,N,"le_exp");

    writeFloat(fp,A_float,N,"add_act");
    writeFloat(fp,A_float,N,"sub_act");
    writeFloat(fp,A_float,N,"min_act");
    writeFloat(fp,A_float,N,"max_act");
    writeFloat(fp,A_float,N,"sqrt_act");
    writeFloat(fp,A_float,N,"mul_act");
    writeFloat(fp,A_float,N,"div_act");
    writeFloat(fp,A_float,N,"madd_act");
    writeInt(fp,eq,N,"eq_act");
    writeInt(fp,lt,N,"lt_act");
    writeInt(fp,le,N,"le_act");


    fclose(fp);


//    fesetround(originalRounding);

}