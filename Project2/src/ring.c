/*

Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/11/19
Description: ring.c of Project 2 for Principles of Embedded Software

*/

#include <stdlib.h>
#include <stdio.h>
#include "ring.h"
#include "uart.h"


ring_t *init_buffer(int length)
{
	ring_t *ring_ptr; 
	ring_ptr = (ring_t *) malloc(sizeof(ring_t));
	ring_ptr-> Buffer = (char*)malloc(length);
	ring_ptr->Length = length;
	ring_ptr->Ini = 0;
	ring_ptr->Outi =0;
	return (ring_ptr);
}

int insert( ring_t *ring, char data )
{
	//Null check for all structure variables
	if(!ring||!ring->Buffer)
	{
		return 0;
	}

	//check if the buffer is full
	if(ring->Outi == ring->Ini+1 || ring->Ini==ring->Outi + (ring->Length-1))
	{
		return 1;
	}

	//insert the data
	ring->Buffer[ring->Ini] = data;

	//increment the head after inserting the data
	if(ring->Ini==ring->Ini + (ring->Length-1))
	{
		ring->Ini = (ring->Ini+1)%ring->Length;
	}
	else
	{
		ring->Ini++;
	}

	return 2; //return 2 if the function execution is successful
}

int remove_buf( ring_t *ring, char *data )
{
	//Null check for all structure variables
	if(!ring||!ring->Buffer)
	{
		return 0;
	}

	//check if buffer is empty
	if(ring->Ini == ring->Outi)
	{
		return 1;
	}

	//remove the next piece of data in line
	*data = ring->Buffer[ring->Outi];

	//increment tail after data transfer
	if(ring->Outi==ring->Outi + (ring->Length-1))
	{
		ring->Outi = (ring->Outi+1)%ring->Length;
	}
	else
	{
		ring->Outi++;
	}

	return 1;
}

int entries( ring_t *ring )
{
	if(!ring||!ring->Buffer)
	{
		return 33;
	}
	
	if(ring->Ini == ring->Outi)
	{
		return 34;
	}
	
	int dec;
	dec = (ring->Ini - ring->Outi); //get the number of entries
    
    return dec;
}