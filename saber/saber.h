#ifndef DGOV_SABER_H
#define DGOV_SABER_H

#include <stdint.h>
#include <stdlib.h>
#include "SABER_params.h"

uint8_t** genKeypairSbr() {
    uint8_t** out = malloc(sizeof(uint8_t*) * 2);
    out[0] = malloc(SABER_SECRETKEYBYTES);
    out[1] = malloc(SABER_PUBLICKEYBYTES);

    crypto_kem_keypair(out[1], out[0]);
    return out;
}

uint8_t* sbrEnc(uint8_t* msg, uint8_t* pk) {
    uint8_t* out = malloc(SABER_KEYBYTES);
    crypto_kem_enc(msg, out, pk);
    return out;
}

uint8_t* sbrDec(uint8_t* msg, uint8_t* sk) {
    uint8_t* out = malloc(SABER_KEYBYTES);
    crypto_kem_dec(out, msg, sk);
    return out;
}

#endif
