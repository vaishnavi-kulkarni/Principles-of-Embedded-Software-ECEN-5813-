/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 2/25/19
Description: free.c of Project 1 for Principles of Embedded Software
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include "../inc/allocate.h"
#include "../inc/free.h"
#include "../inc/write_pattern.h"
#include "../inc/verify_pattern.h"

/**
* Name: free_memory
* Description: This function allows the user to free the memory they previously allocated with the "allocate" command
*/
int32_t free_memory(void) 
{
	if (mem_pointer!= NULL)
	{
		free(mem_pointer);
		printf("\n\rAll of the allocated memory has been freed\n\r");
		mem_pointer = NULL;
		allocate_flag = 0; //lower the flag so other functions know that "allocate" can be executed again
	}

	else
	{
		printf("\n\rPlease enter a valid pointer\n\r");
		printf("If you are consistently seeing this error message it may mean 'allocate' needs to be executed\n\r");
    }

    printf("\n\rPlease enter next command\n\r");
    return 0;
}
