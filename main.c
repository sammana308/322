#include <stdio.h>
#include <math.h>

//Binary to Decimal Function
int BinToDeci(int a[]){
    int i =0, Deci = 0, b = 0;

    for(i = 7; i >= 1; i--){
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

//Print Function
void Print(int a[]){
    int i;
    //Original Number
    for(i = 0; i < 8; i++){
        printf("%d", a[i]);
    }
    printf("\t");

    //ASCII
    printf("%c", BinToDeci(a));

    //Decimal
    printf("%8d\t", BinToDeci(a));

    //Parity
    printf("%s", Parity(a));
}

//File Reader Function
void ReadFile( int argc, char** argv) {
    int value[9] = {0};
    int fileEOF = 0, i = 0, NUM = 0, Length = 4, a = 0;

    if (argc < 2) {
        printf("Please Enter The File Name:\n");
        scanf("%s", argv[1]);
    }

    FILE *fileT = fopen(argv[1], "r");   //this is to opne the file and asks to read the content

    printf("Original    ASCII   Decimal   Parity \n");
    printf("--------    -----   -------   -------- \n");

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