/*

Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/11/19
Description: main.c of Project 2 for Principles of Embedded Software

*/

#include <stdio.h>
#include "MKL25Z4.h"
#include "uart.h"
#include "ring.h"


ring_t *ringptr;
char *h;
char *data;

int main(void)
{
 	char str[50]; //declare an array of chars that will later be the string we print out
    int n1, n2, n3; //declare the operands used in calculating the Fibonacci Sequence
    h = (char *)malloc(10); //h is the pointer we use to temporarily store data once it is removed from the ring buffer

 	//starting values for the Fibonacci Sequence calculation
    n1 = 0;
    n2 = 1;

 	ringptr = init_buffer(255); //initialize a ring buffer of size 255
 	led_init(); //initialize the red on-board LED (Port B, GPIO Pin 18). The assignment calls for a GPIO pin to be toggled, so we chose an LED
 	uart_init(); //initialize the UART

    if (UART_MODE == POLLING_MODE) //if using Polling Mode (blocking implementation)
    {
	    char data;
	    while(1)
	    {
	    	data = get_char();
	    	put_char(data);
	    }
	}

	if (UART_MODE == INTERRUPT_MODE) //if using Interrupt Mode (non-blocking implementation)
	{
		int i; //counter variable for the for-loop below

	    while(1)
	    {
	    	if(rxflag == 1) //if the user has pressed a key
	    	{
	    		for(i = 0; i < 255; i++) //for every element in the ASCII table
	    		{
	    			if((count[i] != 0) && (i != '\0')) //Print only the characters that have been entered at least once
	    			{
					    sprintf(str, "\n\rCharacter is %c->%d\n\r", i, count[i]); //Form a string for each character and the number of times it was entered
					    waitflag = 1; //An added wait required before executing putstr
					    putstr(str); //print out the string made above
					}
	    		}

	    		sprintf(str,"\n\rFibonacci output is %d\n\r", n3); //Form the string of the current calculation of the Fibonacci Sequence
	    		waitflag = 1; //An added wait required before executing putstr
	    		putstr(str); //print the string created above
	    		rxflag = 0; //clear the data entry flag
	    	}

            //Fibonacci Sequence calculation
	    	n3 = (n1 + n2);
            n1 = n2;
            n2 = n3;

	    	toggle_led();
	    }
	}
}
