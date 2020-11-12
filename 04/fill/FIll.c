while(1){
    if(M[24576]!=0){
        for(int i=16384;i<=24575;i++){
            M[i]=-1;
        }
    }
}
while(1){
    if(M[24576]!=0){
        int i=16384;
        while(i<24576){
            M[i]=-1;
            i++;
        }
    }
}
    
```cpp
WHILE1:                 //(WHILE1)
    int i=16384:        //@16384,D=A,@i,M=D  

    WHILE2:             //(WHILE2)
        if(i>=24576)    //@24576,D=A,@i,D=M-D
            goto WEND2; //@WEND2,D;JGE
        int color=0;    //@color,M=0
        if(M[24576]==0) //@24576,M=0
            goto NEXT;  //@NEXT,0JMP
        color=-1;       //@color,M=-1
    NEXT:               //(NEXT)
        M[i]=color;     //@color,D=M,@i,A=M,M=D
        i++;            //@i,D=M,D=D+1,M=D
        goto WHILE2;    //@WHILE2,0;JMP
    WEND2:              //(WEND2)

    goto WHILE1;        //@WHILE1,0;JMP