
/*========================================================================
** ring.h
** Circular buffer
** ECEN5813
**========================================================================*/
#include <stdint.h>

typedef struct
{
	char *Buffer;
	int Length;
	int Ini;
	int Outi;
} ring_t;
extern ring_t *ringptr;
extern char *h;
extern char *data;
ring_t *init_buffer( int length );
int insert( ring_t *ring, char data );
int remove_buf( ring_t *ring, char *data );
int entries( ring_t *ring );


