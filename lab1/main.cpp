#include <stdio.h>
#include <time.h>         //time()
#include <unistd.h>       //fork()
#include <cstdlib>       //EXIT_FAILURE
#include <sys/wait.h>
#include <sys/times.h>

int main() {
 //Time
 time_t Time;
 time(&Time);
 int STAT;

 printf("START: %ld\n", Time);

 //Fork
 int cpid = fork();
 if(cpid == 0){
     //CHILD EXECUTES THIS
     printf("PPID: %ld, PID:%ld\n", getppid(), getpid());
 }
 else if(cpid > 0){
     //PARENT EXECUTES THIS
    waitpid(cpid,&STAT,0);     //waitpid(process to hold, return the status, 0)
    int i;
    for(i=0; i<1000000; i++)
        time(NULL);

    struct tms t;
    clock_t boot;
    boot = times(&t);

    //printf("\nChild process with PID = %ld is exiting\n", cpid);   //DEBUG
    printf("PPID: %ld, PID:%ld, CPID: %ld, RETVAL: %d\n", getppid(), getpid(), cpid, STAT);

    printf("USER: %ld, SYS:%ld\n", (long)t.tms_utime, t.tms_stime);
    printf("CUSER: %ld, CSYS: %ld\n",(long)t.tms_cutime, t.tms_cstime);
     printf("End: %ld\n", Time);
 }
 else{
     printf("SOMETHING WENT WRONG");
     exit(EXIT_FAILURE);
 }

 //time for processes
 clock_t times(struct tms *buf);




 return 0;
}
