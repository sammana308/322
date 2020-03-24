#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void printPID();
void my_handler(int signum);
int getNUM(char str[]);
void catcher(int argc, char** argv);
void end();

//Global array of all 31 signals
static const char* SIG[] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE", "KILL",
                              "USR1", "EGV", "USR2", "PIPE", "ALRM", "TERM", "CHLD", "CONT", "STOP",
                              "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF",
                              "WINCH", "IO", "PWR", "SYS"};
//Global variables
static int Ct = 0, Term = 0;

//printPid
void printPID(){
    fprintf(stderr, "catcher: $$ = %d\n", getpid());
}

//Signal handler
void my_handler(int signum){
    time_t seconds;
    time(&seconds);
    printf("\n%s signal caught at %ld", SIG[signum-1], seconds);
    if(signum == 15)
        Term++;
    else
        Term = 0;
    Ct++;
    signal(signum, my_handler);
}
//compare the strings and returns
int getNUM(char str[]) {
    int x = 0;
    while (x < 31 && (strcmp(SIG[x], str) != 0)) {
        x++;
    }
    return ++x;
}
//catcher function
void catcher(int argc, char** argv){
    int x;
    for (x = 1; x < argc; x++) {
        if ((signal(getNUM(argv[x]), my_handler), my_handler) == SIG_ERR) {
            printf("Cannot catch a signal\n");
            //pause();
        }
    }
    while(Term !=3){
        pause();
        int x;
        for (x = 1; x < argc; x++) {
            if ((signal(getNUM(argv[x]), my_handler), my_handler) == SIG_ERR) {
                printf("Cannot catch a signal\n");
            }
        }
    }
}

void end(){
    fprintf(stderr, "catcher: Total signals count = %d\n", Ct);
    exit(EXIT_SUCCESS);
}

//main function
int main(int argc, char** argv) {
    printPID();
    catcher(argc, argv);
    end();
    return 0;
}
