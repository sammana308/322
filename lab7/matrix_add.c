#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <aio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

struct features{
    int size;
    int value;
    int blocks;
    int blockSize;
};
void AddMatrix(struct aiocb *cb, struct features *ft);
void aioInitialize(struct aiocb *cb, off_t offset, size_t blockSize, int fileD);
void matrixRunner(int argc, char **argv);

//Function for matrix addition
void AddMatrix(struct aiocb *cb, struct features *ft){
    unsigned int number;
    char buff[5];

    //read the aiocb buffer
    int i;
    for(i = 0; i < cb->aio_nbytes; i+=4){
        memset(buff, 0, 5);                           //set zero to the char array and then read 4 bytes at a time
        memcpy(buff, (void*)cb->aio_buf+i, 4);

        number = strtol(buff, NULL, 10);      //number from the buffer
        number = number + ft->value;

        memset(buff, 0, 5);                           //set the buffer to 0 and write the number
        sprintf(buff, "%4d", number);

        memcpy((void *)cb->aio_buf+i, buff, 4);       //write buffer to aio buffer
    }
}

//function for aiocb struct initialization for read/write/return
void aioInitialize(struct aiocb *cb, off_t offset, size_t blockSize, int fileD){
    if(fileD == STDIN_FILENO){
        memset(cb, 0, sizeof(struct aiocb));        //aiocb set to 0
        cb->aio_buf = malloc(blockSize);            //allocate aiocb buffer for reading
    }
    cb->aio_reqprio = 0;            //cb have same priority(0)
    cb->aio_fildes = fileD;            //set file descriptors
    cb->aio_nbytes = blockSize;     //setting bytes to read

    if(fileD == STDIN_FILENO){         //setting offset
        cb->aio_offset = offset;
    }
    else{
        cb->aio_offset = 0;
    }
}

//Matrix runner function
void matrixRunner(int argc, char **argv){
    struct features Build;   //change
    struct aiocb last, current, next;
    if (argc < 3){
        fprintf(stderr, "Error message: invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    // checking size of the argument
    Build.size = argv[1][0]-'0';
    Build.blocks = argv[2][0]-'0';

    //for recording times
    clock_t  start, stop;
    start = clock(); //start time
    srand(time(NULL));
    Build.value = rand() % 201;                          //random number for m-addition
    Build.blockSize = Build.size/Build.blocks;    //blocksize
    if(Build.size % Build.blocks){
        fprintf(stderr, "Error message: Size is not divisible by blocks\n");
        exit(EXIT_FAILURE);
    }
    off_t  b_S;
    b_S =  (Build.blockSize*4)*(Build.blockSize*4);

   //Current struct for reading
   aioInitialize(&current, 0, b_S, STDIN_FILENO);

   //Read the first block
   aio_read(&current);
   while(aio_error(&current) == EINPROGRESS);
   aio_return(&current);

   //Async starts here to read blocks
    int i;
    int totalSize = ((Build.size)*(Build.size)*4);
   for(i = b_S; i < totalSize; i += b_S){
       aioInitialize(&next, i, b_S, STDIN_FILENO);          //reading the next block

       aio_read(&next);                                        //READ
       while(aio_error(&next) == EINPROGRESS);
       AddMatrix(&current, &Build);                     //adding values
       memcpy(&last, &current, sizeof(struct aiocb));       //copy the current block

       aioInitialize(&last, i, b_S, STDOUT_FILENO);         //writing the last block

       aio_write(&last);                                    //WRITE
       while(aio_error(&last) == EINPROGRESS);
       aio_return(&last);                                   //RETURN
       memcpy(&current, &next, sizeof(struct aiocb));       //writing over
   }
    AddMatrix(&current, &Build);         //last block

    aioInitialize(&current,i ,b_S, STDOUT_FILENO);
    aio_write(&current);
    while (aio_error(&current) == EINPROGRESS);
    aio_return(&current);

    //record stop time
    stop = clock();
    double total_time=((double)(stop-start))/CLOCKS_PER_SEC;
    printf("\nTotal time required=%f\n ",total_time);

}

//Main function
int main(int argc, char ** argv) {
    matrixRunner(argc, argv);
    return 0;
}
