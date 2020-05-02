#include <stdio.h>
#include <stdlib.h>

//function for computing page number
unsigned int page_number(unsigned int address, int pageSize){
    unsigned int page_number =  address / pageSize;
    return page_number;
}

//function for computing offset
unsigned int offset(unsigned int address, int pageSize){
    unsigned int offset = address % pageSize;
    return offset;
}

//main function
int main(int argc, char** argv) {

    const int PAGE_SIZE = 4096;     //set the page size to 4KB = 4096 bytes
    unsigned int address;           //variable for address

    //if the number of arguments are less than 2
    if(argc < 2){
        printf("Error: Invalid entry/n");
        return -1;                  //exit
    }
    if(argc == 2){
        address = atoi(argv[1]);

        //Output lines
        printf("The address %d contains:\n", address);

        printf("Page Number = %d\n", page_number(address, PAGE_SIZE));
        printf("Offset = %d\n", offset(address, PAGE_SIZE));
        exit(EXIT_SUCCESS);         //succesfully exit
    }
    return 0;
}
