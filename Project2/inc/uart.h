/*

Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/11/19
Description: uart.h of Project 2 for Principles of Embedded Software

*/

//Header files
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <MKL25Z4.h>

//Macro Definitions
#define BDH_value 0x00u
#define BDL_value 0x1Au
#define UART0_C1_value 0x00u
#define UART0_C2_value_init 0x00u
#define UART0_C2_value_end 0x0Cu
#define UART0_C4_value 0x0Fu

//Polling and Interrupt Mode macros
#define POLLING_MODE 1
#define INTERRUPT_MODE 2


/*
Instructions: Comment out the required UART_MODE macro, below.
1: Polling Mode (blocking implementation)
2: Interrupt Mode (non-blocking implementation)
*/

//#define UART_MODE 1
#define UART_MODE 2


//Function Prototypes
void uart_init();
char get_char(void);
void put_char(char put_char_input);
void rx_available(void);
void tx_available(void);
void transmitter(char tx_input);
char receiver(void);
int i_tx_available(void);
void toggle_led(void);
void led_init(void);
void putstr(char *str);
void UART0_IRQHandler(void);


//global Variables
extern char isr_input; //global variable to hold data from UART_D inside the ISR
extern int rxflag; //this flag is used in the ISR to indicate that the receive operation is successfully done
extern int txflag; //this flag is used in the ISR to indicate that the transmit operation is successfully done
extern int waitflag; //This flag is used to mimic polling when printing values
extern uint32_t count[255]; // this is the data structure to store the whole character report