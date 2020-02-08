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

//Parity Function
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



int main(int argc, char** argv){
    ReadFile(argc, argv);
    return 0;
}