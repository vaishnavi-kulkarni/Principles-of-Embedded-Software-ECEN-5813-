/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 2/25/19
Description: quit.c of Project 1 for Principles of Embedded Software
*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "quit.h"
#include "main.h"
#include "fsl_debug_console.h"

/**
* Name: quit
* Description: This function ends the program and returns the user to the command line
*/
int32_t quit()
{
	PRINTF("\n\rProgram will now shut down\n\r");
	exit(0);
	return 0;
}
