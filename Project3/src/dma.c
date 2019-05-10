/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/29/19
Description: dma.c of Project 3 for Principles of Embedded Software

Details: Contains all function implementations required for DMA transfer
between ADC and the double buffer

This file and its contents are heavily inspired by NXP Community member
Manuel Alejandro Rodriguez and his work from 11/25/14:

https://community.nxp.com/docs/DOC-102951
*/

//Header files
#include "dma.h"
#include "fsl_debug_console.h"

uint16_t destination[buffersize]; //"destination" array of the DMA transfer
extern int bufferflag; //flag to keep track of which half of the double buffer we are operating on

/**
* Name: dma_init
* Description: This function initializes Direct Memory Access (DMA) of the FRDM KL25Z. It sets the DMA up to transfer data from the ADC
* output register to an array of our choosing. The following options are enabled for the DMA:
* 1. DMA transfer triggers an interrupt upon completion
* 2. DMA transfer requests from the ADC are ignored when the BCR counts down to zero
* 3. The ADC (a peripheral) requests each DMA transfer
* 4. Run the DMA continuously until BCR reaches zero
* 5. 16-bit size for the source data and destination data
* 6. increment the destination address after every transfer (so the next transfer doesnt overwrite the previous one)
* 7. Transfer 256 bytes (128 16-bit words) before triggering the interrupt
*/
void dma_init(void)
{
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK; //enable clock access for the DMAMUX
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK; //enable clock access for the DMA
	
	DMAMUX0->CHCFG[0] = 0x00; //to start, disable the DMAMUX. It needs to be disabled before its settings can be changed

	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK; //clear any pre-existing errors by setting the done mask

	// Configure DMA
	DMA0->DMA[0].SAR = (uint32_t)&(ADC0->R[0]); //set the source address of the DMA transfer to be the ADC output

	DMA0->DMA[0].DAR = (uint32_t)&destination; //set the destination address of the DMA transfer to be our global array
	
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(buffersize); //set the DMA to transfer the number of bytes defined by the macro "buffersize"
	
	DMA0->DMA[0].DCR |= (DMA_DCR_EINT_MASK  | //Enable the DMA transfer to trigger an interrupt upon completion
						 DMA_DCR_D_REQ_MASK | //When BCR counts down to zero, disable the ability for the ADC to request a DMA transfer
						 DMA_DCR_ERQ_MASK   | //Enable the ADC (a peripheral) to request a DMA transfer (this should start the transfers if the ADC is already running)
						 DMA_DCR_CS_MASK    | //Enable "cycle stealing" which allows the DMA to run continuously until BCR reaches zero
						 DMA_DCR_DSIZE(2)   | //Set the source data size to be 16 bits in size
						 DMA_DCR_SSIZE(2)   | //Set the destination data size to be 16 bits in size
						 DMA_DCR_DINC_MASK  ); //increment the destination address after every transfer (so the next transfer doesnt overwrite the previous one)
				 
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(40); // Enable DMA channel in the DMAMUX and set ADC0 as the source
	
	NVIC_EnableIRQ(DMA0_IRQn); //enable interrupts
}

/**
* Name: begintransfer
* Description: This function sets DCR[ERQ] bit to enable peripheral requests, thus starting DMA transfers if the ADC is already running
*/
void begintransfer(void)
{
	DMA0->DMA[0].DCR |= DMA_DCR_ERQ_MASK; //enable the ADC to trigger the transfer(s)
}

/**
* Name: led_init
* Description: This function initializes the red LED (of the on-board RGB LED) because the project document
* calls for a GPIO pin to be toggled. The team decided to toggle an LED rather than just some random pin
*/
void led_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //enable Port B
	PORTB->PCR[18] |= (PORT_PCR_MUX(1));  //Enable the red LED (Port B pin 18)
	GPIOB->PDDR |= (1 << 18); //Set the GPIO pin as an output (it will be logic HIGH to start)
}

/**
* Name: toggle_led
* Description: This function merely toggles the GPIO pin connected to the red LED the team is using.
* If it was on, it will turn off. If it was off, it will turn on
*/
void toggle_led(void)
{
	GPIOB->PTOR |= (1 << 18); // toggles the RED LED
}

/**
* Name: DMA0_IRQHandler
* Description: This function is the interrupt service routine for the DMA. It handles the DMA0 interrupt, resets
* the BCR register and clears the DONE flag
*/
void DMA0_IRQHandler(void)
{
	toggle_led(); //toggle the GPIO pin at the beginning of the ISR as per project requirements

    if(DMA0->DMA[0].DSR_BCR & DMA_DSR_BCR_CE_MASK)
    {
    	PRINTF("\n\r configuration error");
    }

    if(DMA0->DMA[0].DSR_BCR & DMA_DSR_BCR_BES_MASK)
    {
       	PRINTF("\n\r Bus error on source");
    }

    if(DMA0->DMA[0].DSR_BCR & DMA_DSR_BCR_BED_MASK)
    {
           	PRINTF("\n\r Bus error on Destination");
    }

	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK; //Clear the "Done" flag for the DMA
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_BCR(buffersize); //set the DMA to transfer the number of bytes defined by the macro "buffersize"

	if(bufferflag == 1)
	{
		DMA0->DMA[0].DAR = (uint32_t)&destination[(buffersize/2)]; //change the destination of the DMA transfer to the second half of the "destination" array
		bufferflag = 0;
	}

	else
	{
		DMA0->DMA[0].DAR = (uint32_t)&destination[0]; //change the destination of the DMA transfer to the first half of the "destination" array
		bufferflag = 1;
	}

	toggle_led(); //toggle the GPIO pin at the end of the ISR as per project requirements
	begintransfer(); //after resetting the DMA, begin transferring again
}