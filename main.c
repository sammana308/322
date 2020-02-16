#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

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

//Print Function
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
        //for non print
    else if(x < 32){
        printf("%s", *(NonPrint + x)); //NonPrint[a]
    }
    else if(x==127)
        printf("DEL");
    else
        printf("iascii");

    printf("\t");

    //Decimal
    printf("%8d\t", BinToDeci(a));

    //Parity
    printf("%s", Parity(a));
}

void ReadFile( int argc, char** argv) {
    int value[9] = {0};
    int a = 0;
    int k, j;
    int dec;



    if (argc < 2) {
        printf("Invalid input.\n");
        return;
    } 
else if(argv[1][0] == '-' && argc < 3){
printf("Invalid input. \n");
return;
}

else if (argv[1][0] == '0' || argv[1][0] == '1' || argv[1][0] == '-') {


        printf("Original    ASCII   Decimal   Parity \n");
        printf("--------    -----   -------   -------- \n");

        int count = argc;
        int value[8], l;

        //skipping dash
        for (j = 1; j < count; j++) {
            if (argv[j][0] == '-')
                j++;
            for (l = 0; l < 8;l++)
                value[l] = 0;
            k = 0;
            while (argv[j][k] != '\0') {
                value[k] = argv[j][k] - '0';
                k++;
            }
            Print(value);
            printf("\n");

        }

    }
    else {
        int fileD = open(argv[1], O_RDONLY);



        printf("Original    ASCII        Decimal   Parity \n");
        printf("--------    -----        -------   -------- \n");

        char buffer;

        for(k = 0;k<8;k++){
            value[k] = 0;
        }
            int i =0;
        while (read(fileD, &buffer, 1)){
            if (buffer == 48 || buffer == 49){
                value[i] = buffer - 48;
                i++;
            }
            else if(i ==0 && (buffer != 48 || buffer != 49))
                continue;
            else if((i%8) == 0 || buffer == ' ' || buffer == '\n')
                {



                    Print(value);
                    printf("\n");
                    for (a = 0; a < 8; a++) {
                        value[a] = 0;
                    }
                   i=0;  //reset
                }
        }
    }
}



//main function
int main(int argc, char** argv){
    ReadFile(argc, argv);
    return 0;
}