/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 2/25/19
Description: invert.c of Project 1 for Principles of Embedded Software

Timing functionality inspired by StackOverflow user "coderredoc" and his post from January 3rd, 2017
tinyurl.com/y2ltbjeh
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/invert.h"
#include "../inc/allocate.h"
#include "../inc/write.h"
/**
* Name: invert_memory
* Description: This function allows the user to invert all the ones to zeros and zeros to ones in a word of their choosing
* inside the allocated block of memory
*/
int32_t invert_memory(void) 
{
    addressing_value = NULL; //the pointer used to point to the memory location the user wants to write to in direct addressing mode
    hold_pointer = NULL; //pointer later used to copy mem_pointer for a brief operation
    invert_pointer = NULL; //create a pointer to the specific word in memory you want to invert
    end_value = NULL; //pointer to the ending memory location when testing patterns with direct addressing mode
    
    valid_location_flag = 0; //flag for if the user enters in a valid memory location in Direct Addressing Mode
    invertindirectflag = 0; //flag that will be used to indicate the selection of indirect addressing mode
    invertdirectflag = 0; //flag that will be used to indicate the selection of direct addressing mode
    addressing_mode = 0;
    if (mem_pointer != NULL) //if allocate() has been executed successfully and thus there is memory to write to
    {
        printf("\n\rEnter 1 for Direct Addressing Mode or 2 for Indirect Addressing Mode\n\r");
        printf("Direct Addressing Mode: Exact memory address of the pattern starting location required\n\r");
        printf("Indirect Addressing Mode: Offset value for the pattern starting location required\n\r");
        scanf("%d", &addressing_mode);

        if(addressing_mode == 1) //if using direct addressing mode
        {
            printf("\n\rPlease enter the memory address of the first location you would like to invert\n\r");
            scanf("%p", &addressing_value);

            hold_pointer = mem_pointer; //we dont want to mess with mem_pointer just yet, so "hold_pointer" will be used as a stand-in for the same information

            for(int i = 0; i < alloc; i++) //for every element in the allocated block of memory
            {
                if ((addressing_value) == (hold_pointer)) //if the value the user entered matches anything found in the allocated block
                {
                    valid_location_flag = 1; //raise the flag indicating that the user has entered in a valid location
                    invertdirectflag = 1; //raise the flag indicating direct addressing mode
                }

                else //if the user-entered value and the current index of the allocated block do not match
                {
                    hold_pointer++; //increment hold_pointer to check the next element in the allocated block
                }
            }

            if (valid_location_flag == 0)
            {
                printf("\n\rThis address is not within the allocated block.\n\r");
                printf("Please enter a valid address next time\n\r");
            }
        }

        if(addressing_mode == 2) //if using indirect addressing mode
        {
            printf("\n\rPlease enter an offset value\n\r");
    	    printf("Offset: where in the allocated block you wish to invert a value\n\r"); //instructions for user
    	    printf("(Acceptable values are from 0 to %d):\n\r", (alloc - 1));
    	    scanf("%d", &invert_offset); //allow the user to type something in

           if ((invert_offset > (alloc - 1)) || (invert_offset < 0)) //if the user tries to write to a location outside of the allocated block
           {
                printf("Sorry, %d is not a valid entry\n\r", invert_offset); //error message
           }

           else
           {
                invertindirectflag = 1; //raise the flag indicating indirect addressing mode
           }
        }   

        if((addressing_mode != 1) && (addressing_mode != 2)) //if the user doesnt make a valid selection right off the bat
        {
            printf("\n\rError: That is not a valid selection\n\r");
            printf("Please select either 1 or 2 next time\n\r");
        }

        if((invertindirectflag == 1)||(valid_location_flag == 1)) //if the user enters in a valid memory location (a valid offset value or memory address)
        {
            if(invertdirectflag == 1)
            {
                printf("\n\rPlease enter the memory address of the last location you would like to invert\n\r");
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

            if(invertindirectflag == 1) //if using indirect addressing mode
            {
                printf("\n\rPlease enter number of blocks you wish to invert\n\r");
                printf("(Acceptable values are between 1 and %d)\n\r", (alloc - invert_offset));
                scanf("%d", &blocks);

                if ((blocks > (alloc - invert_offset)) || blocks < 1)
                {
                    printf("\n\rError: This is not a valid entry\r\n"); //error message
                    printf("(Acceptable values are from 1 to %d):\n\r", (alloc - invert_offset));
                    printf("\n\rPlease enter next command\n\r");
                    return 0;
                }

                invert_pointer = mem_pointer + invert_offset; //direct the pointer to the specific word in memory that you want to invert by adding the offset to the zeroeth element of the block of memory
            }

            else
            {
                invert_pointer = addressing_value;
                blocks = ((end_value) - (invert_pointer)) + 1;
            }

            clock_t start_time = clock(); //"clock()" in Linux returns the amount of processor time used so far by the program. "start_time" will serve as a timestamp for the start of the function
            
            for(int j = 0; j < blocks; j++)
            {
                *invert_pointer = ~(*invert_pointer); //invert the value at the specified location in memory
                 invert_pointer++; //move on to the next sequential memory location
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
