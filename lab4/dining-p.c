#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<semaphore.h>
#include<pthread.h>
#include<malloc.h>
#include<sys/types.h>

void eat(int);
void think(int);
void myhandler(int sig);
void initSem(void);
void* Philosoph(void *num);

//Global variables
sem_t Philosopher;                      //semaphore
sem_t chopStick[100];                   //semaphore  - chopsticks array of size 100
int *philosophers;                      //Philosophers - array
int number;                             //Philosophers - count number
int *CYCLE;                             //for counting Eat or think rotation for each philosopher
int counter=0;                          //SIGTERM counter

//function for eating
void eat(int i)
{
    printf("\nPhilospher %d is eating", i);
}

//function for thinking
void think(int i)
{
    printf("\nPhilosopher %d is thinking", i);
}

//Signal handler for SIGTERM
void myhandler(int signal)
{
    int a;
    if(signal == SIGTERM)
    {
        counter++;
        for(a = 0; a < number; a++)
        {
            fprintf(stderr,"\nPhilosopher  %d completed %d cycles", a, CYCLE[a]);
            sem_close(&chopStick[a]);
            sem_destroy(&chopStick[a]);
        }
    }
    exit(signal);
}

void* Philosoph(void *num)
{
    //check for SIGTERM and exit if it is received
    while(counter == 0)
    {
        int *i = num;
        sem_wait(&Philosopher);
        sem_wait(&chopStick[*i]);                           //this is for left chopstick
        sem_wait(&chopStick[(*(i+1))%(num]);                //this is for right chopstick
        eat(*i);
        usleep(rand()%1000000);

        sem_post(&chopStick[*i]);                          //leaves left chopstick
        sem_post(&chopStick[(*(i+1))%(num)]);              //leaves right chopstick
        think(*i);
        usleep(rand()%1000000);

        sem_post(&Philosopher);
        CYCLE[*i]++;
    }
}

//function for initialising semaphores
void initSem()
{
    int b;
    //for philosophers and cycle array
    for(b = 0; b < number; b++)
    {
        philosophers[b] = b;
        CYCLE[b] = 0;
    }

    //for N chopsticks semaphores
    for(b = 0; b < number; b++)
        if(sem_init(&chopStick[b], 0, 1) < 0)
        {
            printf("\nFound error while initialising semaphores!");
            exit(EXIT_FAILURE);
        }

    if(sem_init(&Philosopher, 0, number - 1) < 0) //semaphore that allows only N-1 philosophers to eat at a time
    {
        printf("\nError while initializing semaphores!");
        exit(EXIT_FAILURE);
    }
}

int main(int argc,char *argv[])
{
    if(argc < 1)
    {
        printf("Error. Do not have enough arguments");
        exit(EXIT_FAILURE);
    }
    int seats, a;
    seats = argv[1][0] - '0';

    number = seats;                                 //global variable number of philosopher assignment
    pthread_t thread_id[number];

    //memory allocation
    philosophers=(int*)malloc(number*sizeof(int)); //memory allocation (array - number of philosophers)
    CYCLE=(int*)malloc(number*sizeof(int));        //memory allocation (array - number of cycles for eat/think for each philosopher)


    initSem();

    signal(SIGTERM, myhandler);                           //to catch SIGTERM

    fprintf(stderr,"\nPID = %d", getpid());

    //printing PID for each philosopher thread
    for(a = 0; a < number; a++)
    {
        pthread_create(&thread_id[a], NULL, Philosoph, &philosophers[a]);
        printf("\nPID of philosopher[%d]=%d", a, getpid());
    }

    for(a = 0; a < number; a++)
        pthread_join(thread_id[a],NULL);   //combine the threads after termination

    exit(EXIT_SUCCESS);
}