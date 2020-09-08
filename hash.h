#ifndef DGOV_HASH_H
#define DGOV_HASH_H

#include "blake3/blake3.h"
#include <stdlib.h>
#include <string.h>


uint8_t* blake3(char* m, uint64_t len) {
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    unsigned char buf[65536];
    uint64_t read = 0;
    while (read < len) {
        uint64_t toRead = (len < 65536) ? (len) : (65536);
        memcpy(buf, m, toRead);
        read += toRead;
        blake3_hasher_update(&hasher, buf, toRead);
    }

    uint8_t* output = calloc(BLAKE3_OUT_LEN, 1);
    blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);
    return output;
}

#endif
