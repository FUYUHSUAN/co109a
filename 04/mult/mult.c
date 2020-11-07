#include<stdio.h>

int main()
{
    int R0=5;
    // @0
    // M=15
    int R1=5;
    // @1
    // M=3
    int R2=0;
    // @2
    // M=0
    LOOP:
        if(R1==0) goto EXIT;
        // @1
        // D=M
        // @EXIT
        // D;JEQ 
        R2+=R0;
        // @0
        // D=M
        // @2
        // M=M+D
        R1--;
        // @1
        //M=M-1
        goto LOOP;
        
    EXIT:
    printf("%d",R2);
    return 0;
}