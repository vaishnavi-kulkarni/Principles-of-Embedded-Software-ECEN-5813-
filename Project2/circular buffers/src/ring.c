/*========================================================================
** Circular buffer`
** ECEN5813
**========================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include "../inc/ring.h"



ring_t *init(int length)
{
	ring_t *ring_ptr; 
	ring_ptr = (ring_t *) malloc(sizeof(ring_t));
	ring_ptr-> Buffer = (char*)malloc(length);
	ring_ptr->Length = length;
	ring_ptr->Ini = 0;
	ring_ptr->Outi =0;
	return (ring_ptr);
}

int insert( ring_t *ring, char data )
{
	//printf("\n\r in insert\n" );
	//Null check for all structure variables
	if(!ring||!ring->Buffer)
		return 0;
	//check if full
	
	if(ring->Outi == ring->Ini+1 || ring->Ini==ring->Outi + (ring->Length-1))
	{   
        printf("\n\rbuffer is full\n\r");
		return 1;
	}
	//transfer data
	ring->Buffer[ring->Ini] = data;
	//printf("\n\rbuffer contains: %c",ring->Buffer[ring->Ini]);
	//increment head after data transfer
	if(ring->Ini==ring->Ini + (ring->Length-1))
		ring->Ini = (ring->Ini+1)%ring->Length;
	else
		ring->Ini++;
	return 2; 
}
int remove_buf( ring_t *ring, char *data )
{
	//printf("\n\r in remove\n" );
	//Null check
	if(!ring||!ring->Buffer)
		return 0;
	//check if buffer is empty
	if(ring->Ini == ring->Outi)
	{
		printf("\n\rbuffer is empty\n\r");
		return 1;
	}
	//remove data
	*data = ring->Buffer[ring->Outi];
	
	//printf("\n\rremoved data : %c", *data);
	//increment tail after data transfer
	if(ring->Outi==ring->Outi + (ring->Length-1))
		ring->Outi = (ring->Outi+1)%ring->Length;
	else
		ring->Outi++;
	return 2;
}
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

