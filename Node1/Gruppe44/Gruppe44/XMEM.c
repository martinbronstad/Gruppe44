#include <stdint.h>

void xmem_write ( uint8_t data , uint16_t addr ){
	volatile char * ext_mem = ( char *) 0x1000 ;
	ext_mem [ addr ]= data ;
}

uint8_t xmem_read ( uint16_t addr ){
	volatile char * ext_mem = ( char *) 0x1000 ;
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val ;
}