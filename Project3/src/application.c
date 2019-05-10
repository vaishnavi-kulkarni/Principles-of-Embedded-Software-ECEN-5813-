/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/29/19
Description: application.c of Project 3 for Principles of Embedded Software
*/

//Header files
#include "application.h"
#include "dma.h"
#include "lookup.h"

/**
* Name: application
* Description: This function completes the "Application" (Part 5) of the project. It identifies the largest value in the buffer(s)
* and performs the provided decay calculation until a new peak is found
*/
void application(int index)
{
	float log; //the dBFS value for the current peak being operated on by the application
	uint16_t peak; //the largest value found in the current buffer under analysis
	static uint16_t previouspeak; //the largest value found to date
	static uint16_t clippedpeak; //the output of the decay calculation when a new peak is not found
	
	static uint16_t previouspeakflag = 1; //flag to indicate if this is the first time through the application or not
	static uint16_t clippedpeakflag = 0; //flag for if a new peak was not found and thus the decay calculation must be done

	peak = destination[index]; //initially, set the peak equal to the first element in the buffer

	if(index == 0) //if we're operating on the first half of the buffer (the first 128 elements)
	{
		for(index = 0; index<((buffersize/2)-1); index++) //for every element in this half of the buffer
		{
			if(abs(destination[index]) > abs(peak)) //if the absolute value of this element of the buffer is bigger than any encountered up to this point
			{
				peak = destination[index]; //declare the peak equal to this value found in this element of the buffer
			}
		}
	}

	else //if we're operating on the second half of the buffer (the last 128 elements)
	{
		for(index=(buffersize/2); index<(buffersize-1); index++) //for every element in this half of the buffer
		{
			if(abs(destination[index]) > abs(peak)) //if the absolute value of this element of the buffer is bigger than any encountered up to this point
			{
				peak = destination[index]; //declare the peak equal to this value found in this element of the buffer
			}
		}
	}

	if(previouspeakflag == 1) //if this is the first time running "application()", meaning there are no previous peaks or values, use the following
	{
	   previouspeak = 0;
	   clippedpeak = 0;
	   previouspeakflag = 0; //lower the "previouspeak" flag so this if-statement will no longer be executed in the future
	}

	if((previouspeakflag == 0) && (previouspeak > peak) && (clippedpeakflag == 1)) //if the previous peak is larger than the current one
	{
		clippedpeak = (alpha * previouspeak); //execute the decay calculation provided in the project outline
	}

	if((previouspeakflag == 0) && (previouspeak > peak)) //if the previous peak is larger than the current one
	{
		if(clippedpeakflag == 0)
		{
			clippedpeak = alpha*clippedpeak; //execute the decay calculation provided in the project outline
		}

		peak = clippedpeak; //set peak equal to the result of the decay calculation so it can be printed
		clippedpeakflag = 0; //lower the "clippedpeak" flag so subsequent decay calculations will operate on this already-decaying value
	}

	if(previouspeak < peak) //if a new peak has been found
	{
		previouspeak = peak; //keep track of this new highest value by setting previouspeak equal to it
		clippedpeakflag = 1; //raise the "clippedpeak" flag because future decay calculations will need to operate on this new value and not the old one previously operated on
	}

	log = loglookup[peak/771]; //use the lookup table in lookup.h to find the scaled dBFS value for the peak value in question

	PRINTF("\n\r PEAK = %d   DBFS = %f", peak, log); //print both the peak (or decaying value) and its associated dBFS value
}