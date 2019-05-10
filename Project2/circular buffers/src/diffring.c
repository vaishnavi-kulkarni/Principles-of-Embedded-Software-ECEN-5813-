/*
Author: Ranger Beguelin and Vaishnavi Kulkarni
Date: 3/18/19
Description: ring.c of Ring Buffer homework for Principles of Embedded Software

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/diffring.h"

// typedef struct
// {
// 	char *Buffer;
// 	int Ini;
// 	int Outi;
// 	int Length;
// } ring_t;
ring_t *init(int length)
{
    ring_t *ring_ptr; 
    ring_ptr = (ring_t *) malloc(sizeof(ring_t));
    ring_ptr-> Buffer = (char*)malloc(length);
    ring_ptr->Length = length;
    ring_ptr->Ini = 0;
    ring_ptr->Outi =0;
    ring_ptr->next=0;
    return (ring_ptr);
}

int insert(ring_t *ring, char data)
{
    

    

    if(!ring||!ring->Buffer)
        return 0;

    if (ring->next == (ring->Length)) //if "next" is equal to Outi it means the buffer is full. The "head" caught the "tail"
    {
        printf("\n\r Buffer full\n\r");
        return 1; //return a -1 indicating a failure
    }

    /*
    Note the difference between the two if statements, the first one means you've reached the end of the buffer without catching the tail,
    meaning theres no error and everything is working as it should. The second one means you've caught the tail (where in the buffer
    is not important) and now have a problem, continuing to write to the next location would mean you are overwriting data that hasnt been
    removed yet (not good)
    */

    ring->Buffer[ring->Ini] = data;
    ring->next+=1;
    printf("\n\r Buffer contains: %c\n\r",ring->Buffer[ring->Ini]);
    if(ring->Ini==ring->Ini + (ring->Length-1))
        ring->Ini = (ring->Ini+1)%ring->Length;
    else
        ring->Ini++;
    
    return 2;  // return 0 to indicate a success
}

int remove_buf(ring_t *ring, char *data)
{
    
    
    if(!ring||!ring->Buffer)
        return 0;
    if ((ring->Outi) == (ring->Ini))  // if "Outi" equals "Ini" it means the buffer is empty
    {
       printf("\n\r Buffer empty\n\r");
        return 1; //return a -1 indicating a failure
    }

    *data = ring->Buffer[ring->Outi]; //assign the argument pointer "data" to the current location of Outi in the buffer
     ring->next-=1;
    printf("\n\r Removed Data: %c\n\r",*data); 
    if(ring->Outi==ring->Outi + (ring->Length-1))
        ring->Outi = (ring->Outi+1)%ring->Length;
    else
        ring->Outi++;             

    return 2;  // return 0 to indicate a success
}

//Entries should return the number of elements present in the circular buffer
int entries( ring_t *ring )
{
    if(!ring||!ring->Buffer)
        return 0;
    if(ring->Ini == ring->Outi)
    {
        printf("\n\rbuffer is empty for entries\n\r");
        return 1;
    }
    int dec;
    dec = ring->Ini;
    printf("\n\r Number of Entries:%d\n\r ",  (ring->Ini - ring->Outi));
     for(int i =0;i<ring->Length;i++ )
    {
        printf("\n\r :%c ",  ring->Buffer[i]);
    }
    return 2;
}
void main()
{
ring_t *ptr ;
ptr = init(4);
char *h;
h = (char*)malloc(10);
int x, y;
x= insert(ptr, 'v');
x= insert(ptr, 's');
x= insert(ptr, 'k');
x= insert(ptr, 'd');
x= insert(ptr, 'r');

 
y= remove_buf(ptr, h);
x= insert(ptr, 'k');
y= remove_buf(ptr, h);
y= remove_buf(ptr, h);
y= remove_buf(ptr, h);
y= remove_buf(ptr, h);
y= remove_buf(ptr, h);


}