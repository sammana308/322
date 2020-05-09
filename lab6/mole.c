#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//main function
int main(int argc, char **argv){
    FILE * filePointer= fopen("lab6.log", "a+");
    if (filePointer == NULL){
        fprintf(stderr, "Error message: No log file created");
    }
    if (filePointer != 0){
        char * mole;
        if (argc > 1 && strcmp(argv[1], "1") == 0)
            mole = "Pop mole1";
        else
            mole = "Pop mole2";
        fputs(mole, filePointer);//gives command
        fclose(filePointer);    
    }
    return 0;
}
