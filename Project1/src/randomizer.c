/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 3/5/19
Description: randomizer.c of Project 1 for Principles of Embedded Software
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/write_pattern.h"
#include "../inc/allocate.h"

/**
* Name: randomizer
* Description: This function is what actually does the pseudo-random number generation using values specified in other functions
*/
uint32_t randomizer(void) 
{
	seed = ((34567 * seed) + 2147483640)%(2147483640);
	return seed;
}
