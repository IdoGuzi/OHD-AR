#ifndef _BFEC_H_
#define _BFEC_H_


#include <stdint.h>
void hreduce(uint16_t *data, uint8_t *reduced, int data_len);

void enlarge(uint16_t *enlarged, uint8_t *data, int data_len);


#endif /*_BFEC_H_*/