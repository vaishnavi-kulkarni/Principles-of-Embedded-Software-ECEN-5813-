/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/29/19
Description: main.c of Project 3 Part 2 for Principles of Embedded Software
*/

//Header Files
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "adc.h"
#include "dma.h"
#include "application.h"

//Variables
int bufferflag;
int peakflag = 1;

int main(void) 
{

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("\n\rPES Project 3\r\n");

    int localbufferflag;
    bufferflag = 1;

    led_init(); //initialize the red LED
    adc_init(); //initialize the ADC
    dma_init(); //initialize the DMA

    beginconversion(); //start the ADC so it will begin taking continuous conversions
    begintransfer(); //enable the DMA so it will make DMA transfers upon request from the running ADC

    while(1)
    {
    	localbufferflag = bufferflag; //This creates a local copy of bufferflag to wait until DMA transfer is finished before processing the other half
    	
        if (bufferflag == 1)
    	{
    		application(buffersize/2); //processes the second half of the buffer
    		bufferflag = 0;            //Once the second half is processed fully we clear bufferflag to start the processing of first half in next iteration
    	}

    	else
    	{
    		application(0); //process the first half of the buffer
    		bufferflag = 1; //Once the first half is processed fully we set bufferflag to start the processing of second half in next iteration
    	}

    	while(localbufferflag == bufferflag); //wait until the bufferflag from DMA.c matches the local one
    }
}