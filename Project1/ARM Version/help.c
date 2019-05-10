/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 2/18/19
Description: help.c of Project 1 for Principles of Embedded Software
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include "help.h"
//#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
//#include "board.h"
//#include "pin_mux.h"

/**
* Name: help_menu
* Description: This function prints out the help menu when "help" is entered into the terminal
*/
int32_t help_menu(void) 
{
    PRINTF("\n\rWelcome to the help menu! Valid commands and their descriptions have been listed below\n\n\r"); //added two newlines here so there can be a gap between the welcome message and the commands themselves
    PRINTF("help: End up back at this menu\n\r");
    PRINTF("allocate: Allocates a user-specified number of bytes or words in memory\n\r");
    PRINTF("free: Free up the amount of memory set aside with 'allocate'\n\r");
    PRINTF("display: Display the contents of memory in hex format\n\r");
    PRINTF("write: Write a 32 bit value to a specified address\n\r");
    PRINTF("invert: Execute a NOT operation to invert all bits in a memory location\n\r");
    PRINTF("write_pattern: Write a PRNG pattern in a specified area of memory\n\r");
    PRINTF("verify_pattern: Verify a PRNG pattern in a specified area of memory\n\r");
    PRINTF("quit: Quit the program and return to the command line\n\r");
    PRINTF("\n\rPlease enter next command\n\r");
    return 0;
}
