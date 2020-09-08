#ifndef DGOV_MCRYPT_H
#define DGOV_MCRYPT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sodium.h>
#include <gsl/gsl_matrix.h<
#include <string.h>

#define PRIME (4294967291)

uint64_t* genKeypair(uint64_t size, uint64_t pubSize) {
    uint64_t* privKey = malloc(size * sizeof(uint64_t));
    randombytesk(((unsigned char *) privKey), size * sizeof(uint64_t));
    uint64_t* pubKey = malloc(size * pubSize * sizeof(uint64_t));
    randombytesk(((unsigned char *) pubKey), size * pubSize * sizeof(uint64_t));
    for (uint64_t i = 0; i < size; ++i) {
        privKey[i] %= PRIME;
    }
    for (uint64_t i = 0; i < size * pubSize; ++i) {
        pubKey[i] %= PRIME;
    }
    uint64_t* out = malloc(sizeof(uint64_t) * 4);
    uint64_t** out2 = out;
    out[0] = size;
    out[1] = pubSize;
    out2[2] = privKey;
    out2[3] = pubKey;

    return out;
}

uint64_t* genErr(uint64_t size) {
    uint64_t* err = malloc(size * sizeof(uint64_t));
    randombytesk(((unsigned char *) err), size * sizeof(uint64_t));
    for (int i = 0; i < size; ++i) {
        err[i] %= 3;
        err[i] = (err[i] == 0) * (PRIME - 1) + (err[i] != 0) * (err[i] - 1);
    }
    return err;
}

void eval(uint64_t* pubKey, uint64_t pubSize, uint64_t* privKey, uint64_t privSize, uint64_t* err, uint64_t* res) {
    memset(res, 0, sizeof(uint64_t) * privSize);
    for (uint64_t x = 0; x < privSize; ++x) {
        for (uint64_t y = 0; y < pubSize; ++y) {
            res[x] += ((pubKey[y * privSize + x] * privKey[x]) % PRIME);
            res[x] %= PRIME;
        }
    }
    for (uint64_t x = 0; x < privSize; ++x) {
        res[x] += err[x];
        res[x] %= PRIME;
    }
}



#endif
