#include <stdio.h>
#include <string.h>

typedef struct {
    char cnd[];
    char val[];
    char name[];
    int num;
}map;

map dMap[8] = 
{[0]={.cnd = "", .val = "000"},
 [1]={.cnd = "M", .val = "001"},
 [2]={.cnd = "D", .val = "010"},
 [3]={.cnd = "MD", .val = "011"},
 [4]={.cnd = "A", .val = "100"},
 [5]={.cnd = "AM", .val = "101"},
 [6]={.cnd = "AD", .val = "110"},
 [7]={.cnd = "AMD", .val = "111"},}

map cMap[28] =
{[0]={.cnd = "0", .val = "0101010"},
 [1]={.cnd = "1", .val = "0101010"},
 [2]={.cnd = "-1", .val = "0101010"}, 
 [3]={.cnd = "D", .val = "0101010"},
 [4]={.cnd = "A", .val = "0101010"},
 [5]={.cnd = "!D", .val = "0101010"},
 [6]={.cnd = "!A", .val = "0101010"},
 [7]={.cnd = "-D", .val = "0101010"},
 [8]={.cnd = "-A", .val = "0101010"},
 [9]={.cnd = "D+1", .val = "0101010"},
 [10]={.cnd = "A+1", .val = "0101010"},
 [11]={.cnd = "D-1", .val = "0101010"},
 [12]={.cnd = "A-1", .val = "0101010"},
 [13]={.cnd = "D+A", .val = "0101010"},
 [14]={.cnd = "D-A", .val = "0101010"},
 [15]={.cnd = "A-D", .val = "0101010"},
 [16]={.cnd = "D&A", .val = "0101010"},
 [17]={.cnd = "D|A", .val = "0101010"},
 [18]={.cnd = "M", .val = "0101010"},
 [19]={.cnd = "!M", .val = "0101010"},
 [20]={.cnd = "-M", .val = "0101010"},
 [21]={.cnd = "M+1", .val = "0101010"},
 [22]={.cnd = "M-1", .val = "0101010"},
 [23]={.cnd = "D+M", .val = "0101010"},
 [24]={.cnd = "D-M", .val = "0101010"},
 [25]={.cnd = "M-D", .val = "0101010"},
 [26]={.cnd = "D&M", .val = "0101010"},
 [27]={.cnd = "D|M", .val = "0101010"}}

map jMap[8] = 
{[0]={.cnd = "", .val = "000"},
 [1]={.cnd = "JGT", .val = "001"},
 [2]={.cnd = "JEQ", .val = "010"},
 [3]={.cnd = "JGE", .val = "011"},
 [4]={.cnd = "JLT", .val = "100"},
 [5]={.cnd = "JNE", .val = "101"},
 [6]={.cnd = "JLE", .val = "110"},
 [7]={.cnd = "JMP", .val = "111"}}

map symMap[23] = 
{[0]={.name = "R0", .num = 0},
 [1]={.name = "R1", .num = 1},
 [2]={.name = "R2", .num = 2},
 [3]={.name = "R3", .num = 3},
 [4]={.name = "R4", .num = 4},
 [5]={.name = "R5", .num = 5},
 [6]={.name = "R6", .num = 6},
 [7]={.name = "R7", .num = 7},
 [8]={.name = "R8", .num = 8},
 [9]={.name = "R9", .num = 9},
 [10]={.name = "R10", .num = 10},
 [11]={.name = "R11", .num = 11},
 [12]={.name = "R12", .num = 12},
 [13]={.name = "R13", .num = 13},
 [14]={.name = "R14", .num = 14},
 [15]={.name = "R15", .num = 15},
 [16]={.name = "SCREEN", .num = 16384},
 [17]={.name = "KBD", .num = 24576},
 [18]={.name = "SP", .num = 0},
 [19]={.name = "LCL", .num = 0},
 [20]={.name = "ARG", .num = 2},
 [21]={.name = "THIS", .num = 3},
 [22]={.name = "THAT", .num = 4}}

void symDump(map *inputmap){
    printf("=================symMap===================\n");
    for(int i=0;i<inputmap.length();i++) {
       printf("%s %d",inputmap[i].name,inputmap[i].num)
    }
}

char *parse(char *line) {
  char *codePtr = line, *codeEnd = line;
  while (strchr("\t ", *codePtr) != NULL) codePtr++;
  while (*codeEnd != '\0' && strchr("/\n\r", *codeEnd) == NULL) codeEnd++;
  *codeEnd = '\0';
  return codePtr;
}

void pass1(char *inFile) {
  printf("============= PASS1 ================\n");
  char line[100]="";
  FILE *fp = fopen(inFile, "r");
  int address = 0;
  while (fgets(line, sizeof(line), fp)) {
    char *code = parse(line);
    if (strlen(code)==0) continue;
    printf("%02d:%s\n", address, code);
    if (code[0] == '(') {
      char label[100];
      sscanf(code, "(%[^)])", label);
      string lab(label);
      if (symMap.find(lab) == symMap.end())
         symMap[lab] = address; // 記住符號位址，給 pass2 編碼時使用
      else
         printf("error: %s already defined before !", label);
      printf("symbol:%s address=%d\n", label, address);
    } else {
      address ++;
    }
  }
  fclose(fp);
}

char *int2bin(int a, char *bin, int size) {
    bin += size;
    *bin-- = '\0';
    for (int i = size; i > 0; i--) {
        *bin-- = (a & 1) + '0';
        a >>= 1;
    }
    return bin;
}

int bin2int(char *bin) {
  return (int) strtol(bin, NULL, 2);
}

void code2binary(char *code, char *binary) {
  if (code[0]=='@') { // A 指令： ＠number || @symbol
    int address;
    int match = sscanf(code, "@%d", &address);
    if (match == 1)
      int2bin(address, binary, 16);
    else {
      char symbol[100];
      match = sscanf(code, "@%s", symbol);
      string sym(symbol);
      auto it = symMap.find(sym);
      if (it == symMap.end()) { // 宣告變數
        symMap[sym] = varTop; // 新增一個變數
        address = varTop++;
      } else { // 已知變數 (標記) 位址
        address = it->second; // 取值。
      }
      int2bin(address, binary, 16);
    }
  } else { // C 指令
    char d[10], comp[100], j[10];
    string dcode, ccode, jcode;
    if (strchr(code, '=') != NULL) { // d=comp
      sscanf(code, "%[^=]=%s", d, comp);
      string ds(d), comps(comp);
      dcode = dMap[ds];
      ccode = cMap[comps];
      sprintf(binary, "111%s%s000", ccode.c_str(), dcode.c_str());
    } else {
      sscanf(code, "%[^;];%s", comp, j); // comp;j
      string comps(comp), js(j);
      ccode = cMap[comps];
      jcode = jMap[js];
      sprintf(binary, "111%s000%s", ccode.c_str(), jcode.c_str());
    }
  }
}

void pass2(char* inFile, char* hackFile, char* binFile) {
  printf("============= PASS2 ================\n");
  char line[100], binary[17];
  FILE *fp = fopen(inFile, "r"); // 開啟組合語言檔
  FILE *hfp = fopen(hackFile, "w"); // 開啟輸出的 .hack 二進位字串檔案
  FILE *bfp = fopen(binFile, "wb"); // 開啟輸出的 .bin 二進位檔
  int address = 0;
  while (fgets(line, sizeof(line), fp)) { // 一行一行讀
    char *code = parse(line); // 取得該行的程式碼部分
    if (strlen(code)==0) continue;
    if (line[0] == '(') { // 這行是符號 ex: (LOOP)
      printf("%s\n", line); // 印出該符號
    } else {
      code2binary(code, binary); // 將指令編碼為二進位字串 string
      uint16_t b = bin2int(binary); // 將二進位字串 string 轉成 int16
      printf("%02X: %-20s %s %04x\n", address, code, binary, b);
      fprintf(hfp, "%s\n", binary); // 輸出 .hack 的二進位字串檔
      fwrite(&b, sizeof(b), 1, bfp); // 輸出 .bin 的二進位檔
      address ++;
    }
  }
  fclose(fp);
  fclose(hfp);
  fclose(bfp);
}

void assemble(char *file)
{
    char inFile[100], hackFile[100], binFIle[100];
    sprintf(inFile , "%s.asm", file);
    sprintf(hackFile, "%s.hack", file);
    sprintf(binFile, "%s.bin", file);
    +// symDump(&symMap);
    pass1(inFile);
    // symDump(&symMap);
    pass2(inFile, hackFile, binFile);
}
int main(int argc, char *argv[])
{
    assemble(argc[]);
}