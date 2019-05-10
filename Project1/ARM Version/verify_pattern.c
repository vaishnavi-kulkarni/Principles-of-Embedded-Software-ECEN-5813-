/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 3/5/19
Description: verify_pattern.c of Project 1 for Principles of Embedded Software

Timing functionality inspired by StackOverflow user "coderredoc" and his post from January 3rd, 2017
tinyurl.com/y2ltbjeh
*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "write_pattern.h"
#include "verify_pattern.h"
#include "allocate.h"
#include "write.h"
#include "fsl_debug_console.h"

uint32_t verification_flag;
int32_t *verify_pointer;
int32_t verification_int;
int32_t verifyindirectflag;
int32_t verifydirectflag;

/**
* Name: verify_pattern
* Description: This function verifies whether or not the pattern written to memory by write_pattern() is valid by replicating
* the pseudo-random number generation with the same seed value, memory offset and pattern length
*/
int32_t verify_pattern(void) 
{
	uint32_t cnt = 0;
	float period = (.0208);

    verify_pointer = NULL; //the pointer to the memory location that holds the start of the pattern
    hold_pointer = NULL; //pointer later used to copy mem_pointer for a brief operation
    end_value = NULL; //pointer to the ending memory location when testing patterns with direct addressing mode
    addressing_value = NULL; //the pointer used to point to the memory location the user wants to write to in direct addressing mode

    verification_flag = 0; //flag for whether or not a discrepency is found when the pattern is being looked over
    verifyindirectflag = 0;//flag for if the user wants to use indirect addressing mode (use offset values)
    verifydirectflag = 0; //flag for if the user wants to use direct addressing mode (manually entering in the memory address)
    valid_location_flag = 0; //flag for if the user enters in a valid memory location in Direct Addressing Mode
    addressing_mode = 0;
	if (mem_pointer != NULL) //if allocate() has been executed successfully and thus there is memory to write to
	{
		PRINTF("\n\rEnter 1 for Direct Addressing Mode or 2 for Indirect Addressing Mode\n\r");
		PRINTF("Direct Addressing Mode: Exact memory address of the pattern starting location required\n\r");
		PRINTF("Indirect Addressing Mode: Offset value for the pattern starting location required\n\r");
		SCANF("%d", &addressing_mode);
		PRINTF("%d\n\r", addressing_mode);

		if(addressing_mode == 1)
		{
			PRINTF("\n\rPlease enter the memory address where the pattern begins\n\r");
			SCANF("%x", &addressing_value);
			PRINTF("%p\n\r", addressing_value);

			hold_pointer = mem_pointer; //we dont want to mess with mem_pointer just yet, so "hold_pointer" will be used as a stand-in for the same information

			for(int i = 0; i < alloc; i++) //for every element in the allocated block of memory
			{
				if ((addressing_value) == (hold_pointer)) //if the value the user entered matches anything found in the allocated block
				{
					valid_location_flag = 1; //raise the flag indicating that the user has entered in a valid location
					verifydirectflag = 1;//raise the flag indicating direct addressing mode
				}

				else //if the user-entered value and the current index of the allocated block do not match
				{
					hold_pointer++; //increment hold_pointer to check the next element in the allocated block
				}
			}

			if (valid_location_flag == 0)
			{
				PRINTF("\n\rThis address is not within the allocated block.\n\r");
				PRINTF("Please enter a valid address next time\n\r");
			}
		}

		if(addressing_mode == 2)
		{
			PRINTF("\n\rPlease enter the offset value of the value you want to verify\n\r"); //
			PRINTF("Offset: where in the allocated block you wish to store this value\n\r"); //instructions for user
			PRINTF("(Acceptable values are from 0 to %d):\n\r", (alloc - 1));				 //

			SCANF("%d", &pattern_offset); //allow the user to type something in
			PRINTF("%d\n\r", pattern_offset);

			if ((pattern_offset > (alloc - 1)) || (pattern_offset < 0)) //if the user tries to write to a location outside of the allocated block
			{
				PRINTF("Sorry, %d is not a valid entry\n\r", pattern_offset); //error message
			}

			else
			{
				verifyindirectflag = 1; //raise the flag indicating indirect addressing mode
			}
		}

		if((addressing_mode != 1) && (addressing_mode != 2)) //if the user doesnt make a valid selection right off the bat
		{
			PRINTF("\n\rError: That is not a valid selection\n\r");
			PRINTF("Please select either 1 or 2 next time\n\r");
		}

		if((verifyindirectflag == 1)||(valid_location_flag == 1))//if the user enters in a valid memory location (a valid offset value or memory address)
		{
			if(verifydirectflag == 1)
			{
				PRINTF("\n\rPlease enter the ending location of the pattern you want to verify:\n\r");
				SCANF("%x", &end_value);
				PRINTF("%p\n\r", end_value);

				if(end_value < addressing_value)
				{
					PRINTF("Error: The memory location must be greater than or equal to your starting location\n\r");
					PRINTF("\n\rPlease enter next command\n\r");
					return 0;
				}

				if(end_value > (mem_pointer + (alloc-1)))
				{
					PRINTF("Error: The memory location must be within the bounds of the allocated block of memory\n\r");
					PRINTF("\n\rPlease enter next command\n\r");
					return 0;
				}
			}

			if (verifyindirectflag == 1)
			{
				PRINTF("\n\rPlease enter the length of the pattern you want to verify:\n\r");
				PRINTF("(Acceptable values are from 1 to %d):\n\r", (alloc - pattern_offset));
				SCANF("%d", &length); //allow the user to type something in
				PRINTF("%d\n\r", length);

				if ((length < 1) || (length > (alloc - pattern_offset))) //if the user tries to enter in a negative value or a location outside of the allocated block
				{
					PRINTF("\n\rError: This is not a valid entry\r\n"); //error message
					PRINTF("(Acceptable values are from 1 to %d):\n\r", (alloc - pattern_offset));
					PRINTF("\n\rPlease enter next command\n\r");
					return 0;
				}
			}

			PRINTF("\n\rPlease enter the seed value for the pattern you want to verify:\n\r");
			PRINTF("Acceptable values are between 0 and ((2^31) - 1)\n\r");
			SCANF("%d", &seed); //allow the user to type something in
			PRINTF("%d\n\r", seed);

			if ((seed < 0) || (seed >= 2147483648)) //if the user tries to enter in a negative value or a value greater than or equal to (2^31)
			{
				PRINTF("\n\rError: This is not a valid entry\r\n"); //error message
				PRINTF("Acceptable values are between 0 and ((2^31) - 1)\r\n"); //explanation
				PRINTF("\n\rPlease enter next command\n\r");
				return 0;
			}

			SysTick_Config(16000000); //start the cycle counting

			if(addressing_mode == 2) //if youre using indirect addressing mode (in other words, using offset values)
			{
				verify_pointer = mem_pointer + pattern_offset; //direct the pointer to the specific location in memory where the pattern is supposed to begin
			}

			else //if youre using direct addressing mode (using specific memory locations)
			{
				verify_pointer = addressing_value; //set the pointer where you will start evaluating the pattern equal to the one the user entered
				length = ((end_value) - (verify_pointer)) + 1; //length is never given a value up until now if youre using addressing mode 1, this line corrects that
															   //length is given the value equal to the distance from the starting location (addressing_value) to the end of the allocated block
			}

			while ((verification_flag == 0) && (length > 0))
			{
				verification_int = randomizer(); //call randomizer to do the PRNG calculation(s), save the value for later comparison

				if (*verify_pointer != verification_int) //if the value stored in memory does not match the one calculated on the previous line
				{
					verification_flag = 1; //raise the flag indicating a discrepency (thus ending the loop)
				}

				verify_pointer++; //increment the pointer so the loop looks at the next location in memory the next time around
				length--; //subtract 1 from the length variable. This was added because the while loop wanted to keep going until it seg-faulted outside
						  //the memory allocated for the program. This makes sure it stays within the bounds of the allocated memory
			}

			if (verification_flag == 1) //if a discrepency was found
			{
				PRINTF("\n\rPatterns do not match\n\r");
				PRINTF("Failure occurred at %p\n\r", (--verify_pointer)); //a "--" is required here because the while loop will still increment the pointer even if the flag is raised
				PRINTF("Expected value was: %x\n\r", (verification_int));
				PRINTF("Actual value was: %x\n\r", *(verify_pointer));    //conversely, no "--" is required here because it was done two lines earlier
			}

			else
			{
				PRINTF("\n\rPatterns match!\n\r");
			}

			cnt = 16000000 - SysTick->VAL; //end the cycle counting
			SysTick->CTRL = 0;
			float time_spent = (period * cnt);
			PRINTF("Process took %f microseconds\n", time_spent); //print the number of microseconds used
		}
	}

	else
	{
		PRINTF("WARNING: This command cannot be run before 'allocate' has been executed\n\r");
	}

	PRINTF("\n\rPlease enter next command\n\r");
	return 0;
}
