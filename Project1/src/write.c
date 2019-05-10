/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 2/25/19
Description: write.c of Project 1 for Principles of Embedded Software
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/write.h"
#include "../inc/allocate.h"

/**
* Name: write_memory
* Description: This function allows the user to write an integer of their choosing to a location of their choosing within the allocated block of memory
*/
int32_t write_memory() 
{
    addressing_value = NULL; //the pointer used to point to the memory location the user wants to write to in direct addressing mode
    write_pointer = NULL; //create a pointer that will later point to the specific location in memory you want to write to
    hold_pointer = NULL; //pointer later used to copy mem_pointer for a brief operation

    valid_location_flag = 0; //flag for if the user enters in a valid memory location in Direct Addressing Mode
    directflag = 0; //flag that will be used to indicate the selection of direct addressing mode
    indirectflag = 0; //flag that will be used to indicate the selection of indirect addressing mode
    addressing_mode = 0;
    if (mem_pointer != NULL)
    {   
        printf("\n\rEnter 1 for Direct Addressing Mode or 2 for Indirect Addressing Mode\n\r");
        printf("Direct Addressing Mode: Exact memory address of the pattern starting location required\n\r");
        printf("Indirect Addressing Mode: Offset value for the pattern starting location required\n\r");
        scanf("%d", &addressing_mode);
        
        if(addressing_mode == 1)
        {
            printf("\n\rPlease enter the memory address you would like to write to\n\r");
            scanf("%p", &addressing_value);
            
            hold_pointer = mem_pointer; //we dont want to mess with mem_pointer just yet, so "hold_pointer" will be used as a stand-in for the same information

            for(int i = 0; i < alloc; i++) //for every element in the allocated block of memory
            {
                if ((addressing_value) == (hold_pointer)) //if the value the user entered matches anything found in the allocated block
                {
                    valid_location_flag = 1; //raise the flag indicating that the user has entered in a valid location
                    directflag = 1;//raise the flag indicating direct addressing mode
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

        if(addressing_mode == 2)
        {    
    	   printf("\n\rPlease enter an offset value\n\r");
    	   printf("Offset: where in the allocated block you wish to store this value\n\r"); //instructions for user
    	   printf("(Acceptable values are from 0 to %d):\n\r", (alloc - 1));

    	   scanf("%d", &offset); //allow the user to type something in
           
           if((offset > (alloc - 1)) || (offset < 0)) //if the user tries to write to a location outside of the allocated block
           {
               printf("Sorry, %d is not a valid entry\n\r", offset); //error message
           }

           else
           {
                indirectflag = 1; //raise the flag indicating indirect addressing mode
           }
        }

        if((addressing_mode != 1) && (addressing_mode != 2)) //if the user doesnt make a valid selection right off the bat
        {
            printf("\n\rError: That is not a valid selection\n\r");
            printf("Please select either 1 or 2 next time\n\r");
        }
           
    	if((indirectflag == 1)||(valid_location_flag == 1)) //if the user enters in a valid memory location (a valid offset value or memory address)
        {
    		printf("\n\rPlease enter an integer to store at this location:\n\r");
    		scanf("%ld", &value); //allow the user to type something in
    		
            if ((value < 0) || (value >= 2147483648)) //if the user tries to enter in a negative value or a value greater than or equal to (2^31)
    		{
    			printf("\n\rError: This is not a valid entry\r\n"); //error message
    			printf("Acceptable values are between 0 and ((2^31) - 1)\r\n"); //explanation
    			printf("\n\rPlease enter next command\n\r");
    			return 0;
    		}
    		
            if(addressing_mode == 2) //if youre using indirect addressing mode (in other words, using offset values)
            {
                write_pointer = mem_pointer + offset; //direct the pointer to the specific location in memory that you want to write to by adding the offset to the zeroeth element of the block of memory
            }

            else //if youre using direct addressing mode (using specific memory locations)
            {
                write_pointer = addressing_value; //set the pointer where you will write a value equal to the one the user entered
            }

    		*write_pointer = value; //assign the value at this location equal to the value you wanted to write
        }
    }

    else
    {
    	printf("WARNING: Memory is not allocated yet, Please allocate memory\r\n"); //error message
    }

    printf("\n\rPlease enter next command\n\r");
    return 0;
}
