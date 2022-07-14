#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "hamming.h"
#include "fec.h"


void hreduce(uint16_t *data, uint8_t *reduced, int data_len) {
    bzero(reduced, data_len/2);
    for (int i=0; i < data_len; i++) {
        uint16_t tmp = data[i];
        uint8_t col1n3 = (((tmp >> 14) & 0x01) ^ ((tmp >> 12) & 0x01) ^ ((tmp >> 10) & 0x01) ^ ((tmp >> 8) & 0x01) ^ ((tmp >> 6) & 0x01) ^ ((tmp >> 4) & 0x01) ^ ((tmp >> 2) & 0x01) ^ ((tmp >> 0) & 0x01));
        uint8_t col2n3 = (((tmp >> 13) & 0x01) ^ ((tmp >> 12) & 0x01) ^ ((tmp >> 9) & 0x01) ^ ((tmp >> 8) & 0x01) ^ ((tmp >> 5) & 0x01) ^ ((tmp >> 4) & 0x01) ^ ((tmp >> 1) & 0x01) ^ ((tmp >> 0) & 0x01));
        uint8_t row1n3 = (((tmp >> 11) & 0x01) ^ ((tmp >> 10) & 0x01) ^ ((tmp >> 9) & 0x01) ^ ((tmp >> 8) & 0x01) ^ ((tmp >> 3) & 0x01) ^ ((tmp >> 2) & 0x01) ^ ((tmp >> 1) & 0x01) ^ ((tmp >> 0) & 0x01));
        uint8_t row2n3 = (((tmp >> 7) & 0x01) ^ ((tmp >> 6) & 0x01) ^ ((tmp >> 5) & 0x01) ^ ((tmp >> 4) & 0x01) ^ ((tmp >> 3) & 0x01) ^ ((tmp >> 2) & 0x01) ^ ((tmp >> 1) & 0x01) ^ ((tmp >> 0) & 0x01));
        uint8_t col;
        uint8_t row;
        if (col1n3 && col2n3) {
            col = 3;
        }else if (col1n3 && !col2n3) {
            col = 1;
        }else if (!col1n3 && col2n3) {
            col = 2;
        }else {
            col = 0;
        }
        if (row1n3 && row2n3) {
            row = 3;
        }else if (row1n3 && !row2n3) {
            row = 1;
        }else if (!row1n3 && row2n3) {
            row = 2;
        }else {
            row = 0;
        }
        tmp ^= 0x0001 << (16-(row*4+col)-1);

        data[i] |= ((tmp >> 12) & 0x01) << 7;
        data[i] |= ((tmp >> 10) & 0x01) << 6;
        data[i] |= ((tmp >> 9) & 0x01) << 5;
        data[i] |= ((tmp >> 8) & 0x01) << 4;
        data[i] |= ((tmp >> 6) & 0x01) << 3;
        data[i] |= ((tmp >> 5) & 0x01) << 2;
        data[i] |= ((tmp >> 4) & 0x01) << 1;
        data[i] |= ((tmp >> 3) & 0x01) << 0;
    }
}

void enlarge(uint16_t *enlarged, uint8_t *data, int data_len) {
    bzero(enlarged, data_len*2);
    for (int i=0; i < data_len; i++) {
        uint16_t tmp = data[i];
        enlarged[i] |= ((tmp >> 7) & 0x01) << 12;
        enlarged[i] |= ((tmp >> 6) & 0x01) << 10;
        enlarged[i] |= ((tmp >> 5) & 0x01) << 9;
        enlarged[i] |= ((tmp >> 4) & 0x01) << 8;
        enlarged[i] |= ((tmp >> 3) & 0x01) << 6;
        enlarged[i] |= ((tmp >> 2) & 0x01) << 5;
        enlarged[i] |= ((tmp >> 1) & 0x01) << 4;
        enlarged[i] |= ((tmp >> 0) & 0x01) << 3;
        enlarged[i] |= (((tmp >> 7) & 0x01) ^ ((tmp >> 6) & 0x01) ^ ((tmp >> 4) & 0x01) ^ ((tmp >> 3) & 0x01) ^ ((tmp >> 1) & 0x01) ^ ((tmp >> 0) & 0x01)) << 14;
        enlarged[i] |= (((tmp >> 7) & 0x01) ^ ((tmp >> 5) & 0x01) ^ ((tmp >> 4) & 0x01) ^ ((tmp >> 2) & 0x01) ^ ((tmp >> 1) & 0x01)) << 13;
        enlarged[i] |= (((tmp >> 6) & 0x01) ^ ((tmp >> 5) & 0x01) ^ ((tmp >> 4) & 0x01) ^ ((tmp >> 0) & 0x01)) << 12;
        enlarged[i] |= (((tmp >> 3) & 0x01) ^ ((tmp >> 2) & 0x01) ^ ((tmp >> 1) & 0x01) ^ ((tmp >> 0) & 0x01)) << 7;
        enlarged[i] |= (((enlarged[i] >> 14) & 0x01) ^ ((enlarged[i] >> 13) & 0x01) ^ ((enlarged[i] >> 12) & 0x01) ^ ((enlarged[i] >> 11) & 0x01) ^ ((enlarged[i] >> 10) & 0x01) ^ ((enlarged[i] >> 9) & 0x01) ^ ((enlarged[i] >> 8) & 0x01) ^ ((enlarged[i] >> 7) & 0x01) ^ ((enlarged[i] >> 6) & 0x01) ^ ((enlarged[i] >> 5) & 0x01) ^ ((enlarged[i] >> 4) & 0x01) ^ ((enlarged[i] >> 3) & 0x01) ^ ((enlarged[i] >> 2) & 0x01) ^ ((enlarged[i] >> 1) & 0x01) ^ ((enlarged[i] >> 0) & 0x01)) << 14;
    }
}
