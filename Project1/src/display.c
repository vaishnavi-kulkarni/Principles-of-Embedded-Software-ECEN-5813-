/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 2/25/19
Description: display.c of Project 1 for Principles of Embedded Software
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/display.h"
#include "../inc/allocate.h"

/**
* Name: display_memory
* Description: This function allows the user to display the memory they have allocated. What prints out is the memory location and the value 
* stored at that location (both in hexadecimal)
*/
int32_t display_memory() 
{
    location = mem_pointer; //function was written to use pointer "location", this line makes sure location has the same value as mem_pointer to start

    if (location != NULL) //if the pointer to the start of the memory block is not NULL
    {
    	printf("\n\rThe values found in this location are:\n\r");
        for (uint32_t i = 0; i < alloc; i++) //for every word the user set aside
    	{
    		printf("%p: %08X\n\r",((int32_t*) location), *((int32_t*) location)); //print the memory location (in hexadecimal) and the value stored at that location (also in hexadecimal)
    		location++; //increment to the next word
    	}
    }

    else
    {
    	printf("WARNING: Memory is not allocated yet, Please allocate memory\r\n"); //error message
    }

    printf("\n\rPlease enter next command\n\r");
    return 0;
}
