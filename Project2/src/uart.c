/*

Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/11/19
Description: uart.c of Project 2 for Principles of Embedded Software

*/

#include <uart.h>
#include <MKL25Z4.h>
#include "ring.h"


char isr_input;
int rxflag=0;
int txflag=0;
int waitflag;
uint32_t count[255];

/**
* Name: uart_init
* Description: This function initializes UART0 of the KL25Z. UART is set for 115200 baud rate
*/
void uart_init()
{
	SIM->SCGC4 = SIM_SCGC4_UART0_MASK; //clock enabled for UART0
	SIM->SCGC5 = SIM_SCGC5_PORTA_MASK; //clock enabled for PORTA

	PORTA->PCR[2] = PORT_PCR_MUX(2); //"Chip specific alternative" for TX and RX pins
	PORTA->PCR[1] = PORT_PCR_MUX(2); //"Chip specific alternative" for TX and RX pins

	SIM->SOPT2 = (SIM_SOPT2_UART0SRC(1) | SIM_SOPT2_PLLFLLSEL(0)); //MCGFLLCLK clock selected

	UART0->C2 = UART0_C2_value_init; //disable TX and RX so other settings can be set

    #if UART_MODE == INTERRUPT_MODE //if using Interrupt Mode (non-blocking implementation)
		UART0->C2 |= UART0_C2_RIE_MASK; //enable the Reciever Interrupt
		UART0->C2 |= UART0_C2_TIE_MASK; //enable the Transmitter Interrupt
		NVIC_EnableIRQ(UART0_IRQn); //enable UART0 interrupts in the NVIC
    #endif

	UART0->BDH = (UART0_BDH_SBR_MASK & 0x00); //clear SBR before changing the values below (as per Sorabh's suggestion)
	UART0->BDL = (UART0_BDL_SBR_MASK & 0x00); //clear SBR before changing the values below (as per Sorabh's suggestion)

	UART0->BDH = 0x00; //High bits of SBR (set them equal to zero because we dont need an SBR value this large)
	UART0->BDL = 0x0C; //Low bits of SBR (SBR set to 12)
	UART0->C4 = 0x0F; //set the over sampling rate (OSR) to 15

    UART0->C1 = UART0_C1_value; //set the UART to use an 8 bit symbol
    UART0->C2 |= UART0_C2_value_end; //enable TX and RX

    #if UART_MODE == INTERRUPT_MODE //if using Interrupt Mode (non-blocking implementation)
    	__enable_irq(); //enable interrupts
    #endif
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
* Name: tx_available
* Description: This function waits until the Transmit Data Register Empty (TDRE) flag is raised meaning the buffer is empty 
*/
void tx_available(void)
{
	while(((UART0->S1) & UART_S1_TDRE_MASK) == 1); //waste time until UART_D is empty
}

/**
* Name: rx_available
* Description: This function waits until the Receive Data Register Full (RDFR) flag is raised (meaning the buffer is full)
* and the Transmission Complete (TC) flag is zero (meaning there are no pending transmissions)
*/
void rx_available(void)
{
	while (((UART0->S1) & UART_S1_RDRF_MASK) != 1 && !(UART0->S1 & UART_S1_TC_MASK)); //waste time until UART_D is full
}

/**
* Name: get_char
* Description: This function receives data from the terminal
*/
char get_char(void)
{
	char input; //local variable "input"
	rx_available(); //wait until the data register is full of data
	input = receiver(); //assign "input" the value of the data typed into the terminal
	return input; //return this value
}

/**
* Name: put_char
* Description: This function puts data onto the terminal for the user to read
*/
void put_char(char put_char_input)
{
	tx_available(); //wait until the data register is empty and ready to be written to
	transmitter(put_char_input); //write the desired value to the data register, thus printing it to the terminal
}

/**
* Name: transmitter
* Description: This function actually puts the requested data into the UART0_D register so it can be printed to the terminal
*/
void transmitter(char tx_input)
{
	UART0->D = tx_input;
}

/**
* Name: receiver
* Description: This function actually gets the data present in the UART0_D register that has been entered in by the user
*/
char receiver(void)
{
	char rx_input; //local variable "rx_input"
	rx_input = UART0->D; //assign "rx_input" the value of the data present in UART0_D
	return rx_input; //return this data
}

/**
* Name: putstr
* Description: This function prints strings to the terminal one character at a time
*/
void putstr(char *str)
{
	while(*str != '\0') //while the string is not NULL (meaning there is actually something to print)
	{
		UART0->C2 |= UART0_C2_TIE_MASK; // enable the transmit enable interrupt in the event it has been disabled 
										// If you dont enable it it won't go back into the ISR and set txflag = 1

		while(waitflag == 0); // wait until previous character is successfully transmitted

		UART0->D = *str ; //put data into the UART0_D register to print it to the terminal

        if(txflag == 1)
		{
            str++; //if and only if previous character is transmitted move on to the next one
		    waitflag = 0; //set waitflag = 0 to so this process of sending characters using putstr can continue
		}

		txflag = 0; //lower txflag, it will be set again in the ISR
	}
}

/**
* Name: i_tx_available
* Description: While it feels unnecessary, this function is asked for explicitly in the project document. All it does
* is wait until the same flags from tx_available have been set, but we needed it in a slightly different format when
* writing the interrupt version of our code
*/
int i_tx_available(void)
{
	if (((UART0->S1) & UART_S1_TDRE_MASK) != 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
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
* Name: UART0_IRQHandler
* Description: This is the interrupt service routine that drives our application
*
* Why is the value that is inserted into the circular buffer immediately removed? If the user is entering in values slowly, everything will play out
* exactly as shown. The character will be inserted, removed, and counted. This will achieve the goal of this project, but it is superfluous.
* What the team anticipates is interrupts on interrupts, the user will be typing in characters so fast that the ISR will be interrupted by itself.
* If this occurs, there likely wont be enough time to do the removal and counting steps, and we will be lucky enough that the values are inserted into
* the circular buffer for safekeeping. Only as all these threads are resolved and each subsequent ISR ends will the characters be removed and counted
*/
void UART0_IRQHandler(void)
{
	char isr_input;
	int buff_remove;
	int buff_insert;

	if (((UART0->S1) & UART_S1_RDRF_MASK) != 1) //if a character is received from the user
	{
		isr_input = receiver(); //key is pressed, values is written to local variable "isr_input"
		
		buff_insert = insert(ringptr, isr_input); //the value of isr_input is immediately inserted into the circular buffer
		buff_remove = remove_buf(ringptr, h); //if time, the next value in line will be removed from the circular buffer to be used to build our printed report
		
		count[*h]++; //increment the number of occurrences of the character that was just removed from the circular buffer
		
		rxflag = 1; //raise the flag that will trigger the printing of our report
	}

	if (((UART0->S1) & UART_S1_TDRE_MASK)) //if a value is transmitted to the terminal
	{
        waitflag = 1; // we poll this flag to prevent uart from going crazy and printing the same letter more than once
		txflag = 1;
		UART0->C2 &= 0x7F; //disable the Transmitter Interrupt
	}
}