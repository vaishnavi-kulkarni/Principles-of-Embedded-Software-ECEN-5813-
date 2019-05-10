/*
Author: Ranger Beguelin
Date: 3/18/19
Description: ring.h of Ring Buffer homework for Principles of Embedded Software
*/

#ifndef RING_H
#define RING_H

typedef struct //no tag for the struct so be careful if you have to declare another one somewhere
{
	char *Buffer; //an array of chars that will be our buffer
	int Ini; //the "head" or whatever data is coming in
	int Outi; //the "tail" or whatever data is going out
	int Length; //the maximum length of the ring buffer
	int next;
} ring_t; //variable name for this struct

ring_t *init( int length );
int insert( ring_t *ring, char data );
int removal( ring_t *ring, char *data );
int entries( ring_t *ring );
char * removal_data; //if i understand this correctly a global variable like this one will be set equal to the value that is being removed from the buffer
					 //because how else would you be able to get access to the value being removed? ex: removal(ring_t *ring, removal_data);
					 //the function returns an int indicating success or failure, it doesnt return a pointer to a char that could be made equal to the 
					 //value being removed

#endif