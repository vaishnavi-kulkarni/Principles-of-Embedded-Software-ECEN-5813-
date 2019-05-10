/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 3/5/19
Description: write_pattern.c of Project 1 for Principles of Embedded Software

Timing functionality inspired by StackOverflow user "coderredoc" and his post from January 3rd, 2017
tinyurl.com/y2ltbjeh
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/write_pattern.h"
#include "../inc/allocate.h"
#include "../inc/write.h"

/**
* Name: write_pattern
* Description: This functions executes a pseudo-random number generator and stores the resulting values in memory as per the user's specifications
*/
int32_t write_pattern(void) 
{
    pattern_pointer = NULL; //the pointer to the memory location that will hold the start of the pattern
    hold_pointer = NULL; //pointer later used to copy mem_pointer for a brief operation
    end_value = NULL; //pointer to the ending memory location when testing patterns with direct addressing mode
    addressing_value = NULL; //the pointer used to point to the memory location the user wants to write to in direct addressing mode

    writedirectflag = 0; //flag for if the user wants to use direct addressing mode (manually entering in the memory address)
    writeindirectflag = 0; //flag for if the user wants to use indirect addressing mode (use offset values)
    valid_location_flag = 0; //flag for if the user enters in a valid memory location in Direct Addressing Mode
    addressing_mode = 0;
    
    if (mem_pointer != NULL) //if allocate() has been executed successfully and thus there is memory to write to
    {
        printf("\n\rEnter 1 for Direct Addressing Mode or 2 for Indirect Addressing Mode\n\r");
        printf("Direct Addressing Mode: Exact memory address of the pattern starting location required\n\r");
        printf("Indirect Addressing Mode: Offset value for the pattern starting location required\n\r");
        scanf("%d", &addressing_mode);
        
        if(addressing_mode == 1) //if using direct addressing mode
        {
            printf("\n\rPlease enter the memory address where you would like the pattern to begin\n\r");
            scanf("%p", &addressing_value);

            hold_pointer = mem_pointer; //we dont want to mess with mem_pointer just yet, so "hold_pointer" will be used as a stand-in for the same information

            for(int i = 0; i < alloc; i++) //for every element in the allocated block of memory
            {
                if ((addressing_value) == (hold_pointer)) //if the value the user entered matches anything found in the allocated block
                {
                    valid_location_flag = 1; //raise the flag indicating that the user has entered in a valid location
                    writedirectflag = 1;//raise the flag indicating direct addressing mode
                }

                else //if the user-entered value and the current index of the allocated block do not match
                {
                    hold_pointer++; //increment hold_pointer to check the next element in the allocated block
                }
            }

            if (valid_location_flag == 0) //if it is found that a valid memory location was NOT entered
            {
                printf("\n\rThis address is not within the allocated block.\n\r");
                printf("Please enter a valid address next time\n\r");
            }
        }

        if(addressing_mode == 2) //if using indirect addressing mode
        {           
            printf("\n\rPlease enter an offset value\n\r");
            printf("Offset: where in the allocated block you wish to store this value\n\r"); //instructions for user
            printf("(Acceptable values are from 0 to %d):\n\r", (alloc - 1));

            scanf("%d", &pattern_offset); //allow the user to type something in

            if ((pattern_offset > (alloc - 1)) || (pattern_offset < 0)) //if the user tries to write to a location outside of the allocated block
            {
                printf("Sorry, %d is not a valid entry\n\r", pattern_offset); //error message
            }

            else
            {
                writeindirectflag = 1; //raise the flag indicating indirect addressing mode
            }
        }

        if((addressing_mode != 1) && (addressing_mode != 2)) //if the user doesnt make a valid selection right off the bat
        {
            printf("\n\rError: That is not a valid selection\n\r");
            printf("Please select either 1 or 2 next time\n\r");
        }

        if((writeindirectflag == 1)||(valid_location_flag == 1))//if the user enters in a valid memory location (a valid offset value or memory address)
        {
            if(writedirectflag == 1)
            {
                printf("\n\rPlease enter the ending location of the pattern you want to write:\n\r");
                scanf("%p", &end_value);
                
                if(end_value < addressing_value)
                {
                    printf("Error: The memory location must be greater than or equal to your starting location\n\r");
                    printf("\n\rPlease enter next command\n\r");
                    return 0;
                }

                if(end_value > (mem_pointer + (alloc-1)))
                {
                    printf("Error: The memory location must be within the bounds of the allocated block of memory\n\r");
                    printf("\n\rPlease enter next command\n\r");
                    return 0;
                }
            }

            if (writeindirectflag == 1)
            {
                printf("\n\rPlease enter the length of your pattern:\n\r");
                printf("(Acceptable values are from 1 to %d):\n\r", (alloc - pattern_offset));
                scanf("%d", &length); //allow the user to type something in
            
                if ((length < 1) || (length > (alloc - pattern_offset))) //if the user tries to enter in a negative value or a value greater than 31
                {
                    printf("\n\rError: This is not a valid entry\r\n"); //error message
                    printf("(Acceptable values are from 1 to %d):\n\r", (alloc - pattern_offset));
                    printf("\n\rPlease enter next command\n\r");
                    return 0;
                }
            }

            printf("\n\rPlease enter a seed value for this pattern:\n\r");
            printf("Acceptable values are between 0 and ((2^31) - 1)\n\r");
            scanf("%d", &seed); //allow the user to type something in

            if ((seed < 0) || (seed >= 2147483648)) //if the user tries to enter in a negative value or a value greater than or equal to (2^31)
            {
                printf("\n\rError: This is not a valid entry\r\n"); //error message
                printf("Acceptable values are between 0 and ((2^31) - 1)\r\n"); //explanation
                printf("\n\rPlease enter next command\n\r");
                return 0;
            }

            clock_t start_time = clock(); //"clock()" in Linux returns the amount of processor time used so far by the program. "start_time" will serve as a timestamp for the start of the function
            
            if(addressing_mode == 2)
            {
                pattern_pointer = mem_pointer + pattern_offset; //direct the pointer to the specific location in memory that you want to write to by adding the offset to the zeroeth element of the block of memory
            }

            else
            {
                pattern_pointer = addressing_value;
                length = ((end_value) - (pattern_pointer)) + 1; //length is never given a value up until now if youre using addressing mode 1, this line corrects that
                                                               //length is given the value equal to the distance from the starting location (addressing_value) to the end of the allocated block
            }

            for (int i = 0; i <= (length - 1); i++) //for the entire length of the block of memory you wanted to write to
            {
                *pattern_pointer= randomizer(); //call randomizer to do the PRNG calculation(s), set this value equal to the memory location specified
                pattern_pointer++; //increment the pointer to point at the next location for the next time around
            }

            clock_t end_time = clock();//"end_time" will serve as a timestamp for the end of the function
            float time_spent = (float)(end_time - start_time); //calculate the difference in time between the starting timestamp and the ending timestamp
            printf("Process took %.2f microseconds\n", time_spent); //print the number of microseconds used
        }
    } 

    else
    {
        printf("WARNING: This command cannot be run before 'allocate' has been executed\n\r");  
    }

    printf("\n\rPlease enter next command\n\r");
    return 0;
}
