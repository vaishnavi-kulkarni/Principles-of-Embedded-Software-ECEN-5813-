/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/29/19
Description: application.h of Project 3 for Principles of Embedded Software
*/

//Header files
#include "fsl_debug_console.h"
#include "MKL25Z4.h"
#include <stdlib.h>
#include <stdio.h>

//Macro Definitions
#define alpha (0.5)

//Variables
extern int peakflag;

//Function Prototypes
void application(int index);