#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <fcntl.h>          
#include <syslog.h>
#include <signal.h>

//Global variables
static pid_t  moleChild;
static int num;

//function for choosing random molechild
void randomMole(){
    num = rand() % 2;
    char snum[16];
    sprintf( snum, "%d", num + 1);
    char *mArgv[] = {"mole", snum, 0};
   moleChild = fork();
   if(moleChild == 0){
       execv(mArgv[0], mArgv);
   }
}

//Signal handler function:
static void sigHandler(int signo) {
    if (signo == SIGTERM) {
        kill(moleChild, SIGTERM);
        exit(0);
    } else if (signo == SIGUSR1) {
        if (num == 0 && moleChild > 0){
            kill(moleChild, SIGCHLD);
        }
        randomMole();
        (void) signal(SIGUSR1, sigHandler);
    } else if (signo == SIGUSR2) {
        if(num == 1){
            kill(moleChild, SIGCHLD);
        }
        randomMole();
        (void) signal(SIGUSR2, sigHandler);
    }
}

//main function
    int main(int argc, char **argv) {
    const char *filePointer = "/lab6.log";
        pid_t pid;
        pid_t sid;

        //Forking begins
        pid = fork();

        if (pid < 0) {        //less than 0 means ERROR
            printf("Error. Something went wrong.");
        }
        if (pid > 0) {        //greater than 0 means parent process
            printf("This is the process ID %d\n", pid);
            exit(0);        //daemon runs now
        }

        //setting file creation mask to 0
        umask(0);
        
        //Create new session
        sid = setsid();
        if (sid < 0) {       //less than 0 means ERROR
            fprintf(stderr, "Error message: Failed\n");
            exit(1);
        }
        close(STDIN_FILENO);
        if(open("/dev/null", O_RDONLY) < 0)
            printf("Error message: Failed to open");

        int fd1;
        fd1 = open(filePointer,O_WRONLY|O_CREAT|O_APPEND, 0644);

        //redirecting stdout, stderr to the log file
        if (dup2(fd1, STDOUT_FILENO) < 0) {
            fprintf(stderr, "Error: STDOUT Failure\n");
        }

        if (dup2(fd1, STDERR_FILENO) < 0) {
            fprintf(stderr, "Error: STDERR Failure\n");
        }
       close(fd1);
    (void) signal(SIGTERM, sigHandler);
    (void) signal(SIGUSR1, sigHandler);
    (void) signal(SIGUSR2, sigHandler);


 moleChild = fork();
        while (1) {
            sleep(1);
            printf("Meanwhile. .\n");
            if(moleChild == 0){
                int num = rand() % 2;
                char snum[16];
                sprintf(snum, "%d", num + 1);
                char *mArgv[] = {"mole", snum, 0};
                execv(mArgv[0], mArgv );
            }
        }
        return 0;
    }


