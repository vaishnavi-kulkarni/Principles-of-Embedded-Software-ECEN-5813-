#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "main.h"
#include "pin_mux.h"

typedef struct { char *input; int32_t (*fp)();}lookup_table; //a lookup table for all of the functions used in this program and their associated command keyword

/**
* Name: main
* Description: none
*/
int32_t main(void)
{
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

    PRINTF("\n\rPrinciples of Embedded Software Project 1\n\r"); //welcome message
    PRINTF("Enter a valid command or type 'help' for more information\n\r"); //basic instructions

    uint32_t k = 0; //counter variable for iterating through the for-loop below
    char in[15]; //15 element array of chracters because our largest command (verify_pattern) is 14 characters long
    lookup_table list[]={{"help",&help_menu},{"allocate",&allocate_memory},{"write",&write_memory},{"display",&display_memory},
                        {"free",&free_memory},{"invert",&invert_memory},{"quit",&quit},{"write_pattern",&write_pattern},{"verify_pattern",&verify_pattern}};
   do
   {
      SCANF("%s",in); //allow the user to enter a command keyword
      PRINTF("%s\n\r", in);
      uint32_t h = 0;//a flag used to track whether a valid command has been entered or not (see below)

      for(k = 0; k < 9; k++) //for every one of the elements in the lookup table (the range of this loop needs to be extended as new commands are added to the program)
      {
         if(strcmp(in,list[k].input) == 0)	//Check if user-entered input is present in the lookup table
         {
            h++; //if the program gets inside this if-statement it means the user input matches a valid command in the lookup table. Raise the flag to signify that the user input was valid
            (*list[k].fp)(); //Call the function that user wants to perform
         }
      }

      if ((strcmp(in, "\n")) == 0)
      {
        /*
        Scanf considers the newline character that results when the user presses the enter key as a separate string
        which meant that the "This is not a valid command, Please try again" message would come up no matter what. This if
        statement "catches" this newline character so it can be ignored and not considered to be a new, erroneous input
        */
        break;
      }

      else if(h == 0)
      {
        PRINTF("\n\rThis is not a valid command, Please try again\n\r");
        PRINTF("Use command 'help' to see a full list of valid commands\n\r");
        PRINTF("\n\rPlease enter next command\n\r");
      }
   }
   while(strcmp(in,"quit") != 0);
}
