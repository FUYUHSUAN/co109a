## mult.asm
>* Step1:先把程式寫成C語言，並執行他
>* Step2:然後改成C的組合語言的語法(組合語言只有if ,goto ,和一些標籤語言(e.g LOOP:,EXIT:...))
>* Stap3:接者，就可以開始使用組合語言將C語言一行一行的轉換

* 首先是我寫的C
```
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
```
* 接者是mult.asm
```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

//#include<stdio.h>

//int main()
//{
    //int R0=5;

     //@5
     //D=A
     //@0
     //M=D

    //int R1=5;
     //@3
     //D=A
     //@1
     //M=D

    //int R2=0;

     @2
     M=0

    //LOOP:
        (loop)
        //if(R1==0) goto EXIT;

         @1
         D=M
         @exit
         D;JEQ 

        //R2+=R0;

         @0
         D=M
         @2
         M=M+D
         //R1--;
         @1
         M=M-1
        

        //goto LOOP;
        @loop
        0;JMP
    //EXIT:
    (exit)
    @exit
    0;JMP
    //return 0;
//}
```