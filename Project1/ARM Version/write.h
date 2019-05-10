#include <stdint.h>
#include <stdlib.h>
int32_t write_memory();
extern int32_t *write_pointer;
extern uint32_t offset;
extern uint32_t value;
extern int32_t addressing_mode;
extern int32_t *addressing_value;
extern int32_t directflag;
extern int32_t indirectflag;
extern int32_t int_mem;
extern int32_t valid_location_flag;
extern int32_t *hold_pointer;
extern int32_t *end_value;
