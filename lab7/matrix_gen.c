
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void matrixGenerator(int argc, char** argv);

int main(int argc, char** argv){
    matrixGenerator(argc,argv);
    return EXIT_SUCCESS;
}

void matrixGenerator(int argc, char** argv){
    unsigned int upper, lower;
    upper=100;
    lower=-100;
    int N = atoi(argv[1]);

    if (argc != 2){
        fprintf(stderr, "Error message: Invalid argument entry.\n");
        exit(EXIT_FAILURE);
    }
    int a,b;
    for(a = 0; a < N; a++){
        for(b = 0; b < N; b++){
            fprintf(stdout,"%4d",(rand()%(upper-lower+1))+lower);
        }
        printf("\n");
    }
}