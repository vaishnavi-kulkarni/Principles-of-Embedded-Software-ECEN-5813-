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
#include "allocate.h"
#include "free.h"
#include "write_pattern.h"
#include "verify_pattern.h"
#include "fsl_debug_console.h"

/**
* Name: free_memory
* Description: This function allows the user to free the memory they previously allocated with the "allocate" command
*/
int32_t free_memory(void) 
{
	if (mem_pointer!= NULL)
	{
		free(mem_pointer);
		PRINTF("\n\rAll of the allocated memory has been freed\n\r");
		mem_pointer = NULL;
		allocate_flag = 0; //lower the flag so other functions know that "allocate" can be executed again
	}

	else
	{
		PRINTF("\n\rPlease enter a valid pointer\n\r");
		PRINTF("If you are consistently seeing this error message it may mean 'allocate' needs to be executed\n\r");
    }

    PRINTF("\n\rPlease enter next command\n\r");
    return 0;
}
