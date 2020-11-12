### mult.asm

* code
```
//WHILE1:
(WHILE1)                
  //  int i=16384:        
    @16384,D=A,@i,M=D
    //WHILE2:
    (WHILE2)             
      //  if(i>=24576)    
        //    goto WEND2;
        @24576,D=A,@i,D=M-D
        @WEND2,D;JGE
       // int color=0;
        @color,M=0    
       // if(M[24576]==0)
         //   goto NEXT; 
         @24576,D=M
        @NEXT,D;JEQ
       // color=-1;
       @color,M=-1       
    //NEXT:
    (NEXT)               
     //   M[i]=color;
     @color,D=M,@i,A=M,M=D
       // i++;            
       @i,D=M,D=D+1,M=D
       // goto WHILE2;    
       @WHILE2,0;JMP
   // WEND2:              
   (WEND2)

    //goto WHILE1;        
    @WHILE1,0;JMP 
```
* picture
<img src="picture/fill.png" width="1000" height="650">