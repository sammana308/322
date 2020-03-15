#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *args1[argc], *args2[argc];     //First and second commands' arrays

    int PipeFD[2];
    pipe(PipeFD);   //creates ONE pipe

    int n, a = 0;
    for(n = 1; n < argc; n++)
    {
        if(argv[n]!=NULL && strcmp(argv[n],",") == 0)
            break;
        args1[a] = argv[n];
        a++;
    }

    args1[a] = NULL;      //null terminating: to add Null at the end of the string after copying

    int m, b;

    if(argv[n] != NULL)
    {
        n++;
        b=0;
        for(m=n; m<argc;m++)
        {
            args2[b] =argv[m];
            b++;
         }
        args2[b] = NULL;
    }

    if(pipe(PipeFD) == -1)
        fprintf(stderr, "Failed: Pipe does not work. ");

    pid_t  p_id1, p_id2;
    p_id1 = fork();       //Create first Child process

    if (p_id1 == -1)
    {
        //Error
        fprintf(stderr, "ERROR. Cannot fork. %d\n", errno);
        exit(EXIT_FAILURE);
    }
    else if (p_id1 == 0)  //First child process
    {
        //close read end
        close(PipeFD[0]);

        //replace standard out
        dup2(PipeFD[1], 1);

        if(execve(args1[0], args1, NULL) == -1)
           printf("\n ERROR IN Child 1");
    }
    else
    {
          p_id2 = fork();  // Create second child process
          if(p_id1>0 && p_id2 >0)
          {
              fprintf(stderr, "\n%s: $$ = %d", args1[0], p_id1);
              fprintf(stderr, "\n%s: $$ = %d\n", args2[0], p_id2);
          }
        if (p_id2 == 0)  //child 2

        {
            //Child process 2

            //close write end
            close(PipeFD[1]);

            //replace standard input
            dup2(PipeFD[0], 0);

            if(execve(args2[0], args2, NULL) == -1)
                printf("\n ERROR IN Child2");

        }
        int STAT1, STAT2;

        waitpid(p_id1, &STAT1, 0); // wait for first child process to terminate
        close(PipeFD[1]);          //close wr
        waitpid(p_id1, &STAT2, 0); // wait for first child process to terminate

        fprintf(stderr, "\n%s: $? = %d", args1[0], STAT1);
        fprintf(stderr, "\n%s: $? = %d\n", args2[0], STAT2);
        //return 0;
    }
    return 0;
}
