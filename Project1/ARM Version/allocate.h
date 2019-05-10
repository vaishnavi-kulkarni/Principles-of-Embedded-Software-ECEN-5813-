#include <stdint.h>
#include <stdlib.h>

int32_t allocate_memory(void);
extern int32_t *mem_pointer; //pointer that will later point to the beginning of the allocated section of memory when "allocate" is executed
extern uint32_t alloc, byte;
extern uint32_t allocate_flag; //a flag that will be used to alert other functions whether or not "allocate" has been executed
