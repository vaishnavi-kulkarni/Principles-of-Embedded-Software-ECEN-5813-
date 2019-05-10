/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 2/25/19
Description: allocate.c of Project 1 for Principles of Embedded Software
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include "../inc/allocate.h"

/**
* Name: allocate_memory
* Description: This function allows the user to allocate memory for use by the program
*/
int32_t allocate_memory(void) 
{
    if (allocate_flag == 1)
    {
        printf("\n\rError. Cannot allocate at this time\n\r");
        printf("Allocate has already been executed\n\r");
        printf("\n\rPlease enter next command\n\r");
        return 0;
    }

    printf("\n\rHow many 4-byte words would you like to allocate?\n\r"); //instructions for user
    scanf(" %d", &alloc); //allow the user to type something in
     
    if ((alloc > 0) && (alloc < 1000)) 
    {
        byte = alloc * 8; //go from words to bytes
        mem_pointer = malloc(byte); //allocate the number of bytes the user requests
        allocate_flag = 1; //raise the flag so other functions know that "allocate" has been executed
    }    

    else if (mem_pointer == NULL)
    {
        printf ("\n\rError. Cannot allocate at this time\n\r");
        printf ("NULL pointer to memory location\n\r");
        exit(-1);
    }   

    printf("\n\rPlease enter next command\n\r");
    return 0;
}
