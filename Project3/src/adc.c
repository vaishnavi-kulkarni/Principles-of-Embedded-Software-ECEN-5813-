/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/29/19
Description: adc.c of Project 3 for Principles of Embedded Software

This file and its contents are heavily inspired by NXP Community member
Manuel Alejandro Rodriguez and his work from 11/25/14:

https://community.nxp.com/docs/DOC-102951
*/

//Header files
#include "adc.h"
#include "MKL25Z4.h"

/**
* Name: adc_init
* Description: This function initializes Analog Digital Controller (ADC) of the FRDM KL25Z. It sets the ADC up for 16 bit resolution,
* single ended mode, run by the 24MHz bus clock
*/
void adc_init(void)
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;	// enable the clock gate to the ADC0 module

	ADC0->CFG1 = 0x0C; //Set the ADC for 16 bit, single ended mode with bus clock divided by 1
	/*
	As per the KL25Z reference manual Bus Clock is 24MHz, so with no pre-divider we are
	feeding the full 24MHz into the ADC
	*/
	
	ADC0->SC2 |= ADC_SC2_DMAEN_MASK; //Make a DMA request upon completion of an ADC conversion
	ADC0->SC3 |= (ADC_SC3_ADCO_MASK | ADC_SC3_AVGE_MASK); //enable continuous conversions which requires hardware averaging to be used
														  //The smallest hardware averaging was selected, just 4 samples

	ADC0->SC1[0] |= 0x1F; //set SC1A (SC1[0]) equal to 00011111
						  //This will disable the module so no conversions are made until the ADC is enabled later
}

/**
* Name: beginconversion
* Description: This function writes to SC1A register to start the conversion
*/
void beginconversion(void)
{
	ADC0->SC1[0] = (0 & ADC_SC1_ADCH_MASK); //write to SC1A to start conversion on input channel zero (pin PTE20)
}