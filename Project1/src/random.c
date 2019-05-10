/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 3/5/19
Description: random.c of Project 1 for Principles of Embedded Software
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/write_pattern.h"
#include "../inc/allocate.h"

/**
* Name: random
* Description: 
*/
uint32_t randomizer(uint32_t seed) 
{
	random_value = ((34567 * seed) + 7654321)%(7654321);
	return random_value;
}
