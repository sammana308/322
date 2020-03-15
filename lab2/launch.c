#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t  p_ID = fork();

    if (p_ID == -1)
    {
        // There is an error
        fprintf(stderr, "Unable to fork due to some error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    else if (p_ID == 0)
    {
        //Child process
        execve(argv[1], argv + 1, NULL);
    }
    else
    {
        //Parent process
        int STAT;
        fprintf(stderr, "%s: $$ = %d \n", argv[1], p_ID);
        waitpid(p_ID, &STAT, 0);
        fprintf(stderr, "%s: $? = %d \n", argv[1], STAT);
    }
    return 0;
}
