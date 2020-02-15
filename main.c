#include <stdio.h>
#include <math.h>

//global array of NonPrint ASCII
char* NonPrint[33] = {"NUL", "SOH","STX","ETX","EOT","ENQ","ACK","BEL","BS","HT","LF","VT","FF","CR","SO","SI","DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB","CAN","EM","SUB","ESC","FS","GS","RS","US"};


//Binary to Decimal Function
int BinToDeci(int a[]){
    int i =0, Deci = 0, b = 0;

    for(i = 7; i >= 0; i--){
        Deci += a[i] * pow(2, b);
        b++;
    }
    return Deci;
}

//Parity Function that returns ODD or EVEN
char* Parity(int a[]){
    int Tally = 0, i;
    for(i = 0; i < 8; i++){
        Tally += a[i];
    }
    if (Tally % 2 == 0)
        return "EVEN";
    else
        return "ODD";
}

///Print Function
void Print(int a[]){
    int i;
    //Original Number
    for(i = 0; i < 8; i++){
        printf("%d", a[i]);
    }
    printf("\t");

    //ASCII
    int x = BinToDeci(a);
    if(x>=32 && x<127){
        printf("%c", x);
    }
        // for non print
    else if(x < 32){
        printf("%s", *(NonPrint + x)); //NonPrint[a]
    }
    else if(x==127)
        printf("DEL");
    else
        printf("man ASCII");


    //Decimal
    printf("%15d\t", BinToDeci(a));

    //Parity
    printf("%8s", Parity(a));
}

//File Reader Function
void ReadFile( int argc, char** argv) {
    int value[9] = {0};
    int a = 0;
    FILE *fileT;

    char str[] = "test.txt"; 
    if (argc < 2) {
        //printf("Please Enter The File Name:\n");
        //scanf("%s", str);
        fileT = fopen(str, "r");   //this is to open the file and asks to read the content
    }
else{

    fileT = fopen(argv[1], "r");   //this is to opne the file and asks to read the content
}

    printf("Original    ASCII        Decimal   Parity \n");
    printf("--------    -----        -------   -------- \n");

    char buffer[9];

    while (fscanf(fileT, "%s", buffer) == 1){
        //printf("%s  \n", buffer);
        int i;
        for(i = 0; i < 8; i++){
            if(buffer[i] == 48 || buffer[i] == 49) {
                value[i] = buffer[i] - 48;
            }
        }

        Print(value);
        printf("\n");
        for (a = 0; a < 8; a++) {
            value[a] = 0;
            buffer[a] = 0;
        }
    }
}


//main function
int main(int argc, char** argv){
    ReadFile(argc, argv);
    return 0;
}