#include<stdio.h>
int main(){
    int R0=1;

    LOOP:
        R0=R0+1;
        if(R0==10) goto EXIT;
        printf("R0=%d\n",R0);
        goto LOOP;
    EXIT:
        return 0;
}
// @M
// M=1
// @0
// M=M+1
// @2
// 0;JMPs