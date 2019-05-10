/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 2/18/19
Description: help.c of Project 1 for Principles of Embedded Software
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include "../inc/help.h"

/**
* Name: help_menu
* Description: This function prints out the help menu when "help" is entered into the terminal
*/
int32_t help_menu(void) 
{
    printf("\n\rWelcome to the help menu! Valid commands and their descriptions have been listed below\n\n\r"); //added two newlines here so there can be a gap between the welcome message and the commands themselves
    printf("help: End up back at this menu\n\r");
    printf("allocate: Allocates a user-specified number of bytes or words in memory\n\r");
    printf("free: Free up the amount of memory set aside with 'allocate'\n\r");
    printf("display: Display the contents of memory in hex format\n\r");
    printf("write: Write a 32 bit value to a specified address\n\r");
    printf("invert: Execute a NOT operation to invert all bits in a memory location\n\r");
    printf("write_pattern: Write a PRNG pattern in a specified area of memory\n\r");
    printf("verify_pattern: Verify a PRNG pattern in a specified area of memory\n\r");
    printf("quit: Quit the program and return to the command line\n\r");
    printf("\n\rPlease enter next command\n\r");
    return 0;
}
