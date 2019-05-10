/*
Authors: Ranger Beguelin and Vaishnavi Kulkarni
Date: 4/29/19
Description: dma.h of Project 3 for Principles of Embedded Software

This file and its contents are heavily inspired by NXP Community member
Manuel Alejandro Rodriguez and his work from 11/25/14:

https://community.nxp.com/docs/DOC-102951
*/

//Header Files
#include "MKL25Z4.h"

//Macro Definitions
#define buffersize (256)

//Variables
extern uint16_t destination[buffersize];
extern int bufferflag;

//Function Prototypes
void dma_init(void);
void DMA0_IRQHandler(void);
void begintransfer(void);
void toggle_led(void);
void led_init(void);