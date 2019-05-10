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
#include "allocate.h"
#include "fsl_debug_console.h"

int32_t *mem_pointer; //pointer that will later point to the beginning of the allocated section of memory when "allocate" is executed
uint32_t alloc, byte;
uint32_t allocate_flag; //a flag that will be used to alert other functions whether or not "allocate" has been executed


/**
* Name: allocate_memory
* Description: This function allows the user to allocate memory for use by the program
*/
int32_t allocate_memory(void) 
{
    if (allocate_flag == 1)
    {
        PRINTF("\n\rError. Cannot allocate at this time\n\r");
        PRINTF("Allocate has already been executed\n\r");
        PRINTF("\n\rPlease enter next command\n\r");
        return 0;
    }

    PRINTF("\n\rHow many 4-byte words would you like to allocate?\n\r"); //instructions for user
    SCANF(" %d", &alloc); //allow the user to type something in
     
    if ((alloc > 0) && (alloc < 1000)) 
    {
        byte = alloc * 8; //go from words to bytes
        mem_pointer = malloc(byte); //allocate the number of bytes the user requests
        allocate_flag = 1; //raise the flag so other functions know that "allocate" has been executed
    }    

    else if (mem_pointer == NULL)
    {
        PRINTF ("\n\rError. Cannot allocate at this time\n\r");
        PRINTF ("NULL pointer to memory location\n\r");
        exit(-1);
    }

    PRINTF("\n\rPlease enter next command\n\r");
    return 0;
}
