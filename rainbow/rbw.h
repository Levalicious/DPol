#ifndef DGOV_RBW_H
#define DGOV_RBW_H

#include <stdint.h>
#include "rainbow_config.h"
#include "utils.h"
#include "rng.h"
#include "api.h"

uint8_t** genKeypairRbw() {
    unsigned char rnd_seed[48] = {0};
    int rr = byte_from_binfile( rnd_seed , 48 , "/dev/random" );
    if( 0 != rr ) printf("read seed file fail.\n");
    randombytes_initk(rnd_seed, NULL, 256);

    uint8_t* _sk = (uint8_t*) malloc(CRYPTO_SECRETKEYBYTES);
    uint8_t* _pk = (uint8_t*) malloc(CRYPTO_PUBLICKEYBYTES);
    int r = crypto_sign_keypair(_pk, _sk);
    if (0 != r) {
        printf("Genkey failed.\n");
        exit(43);
    }
    uint8_t** out = malloc(sizeof(uint8_t*) * 2);
    out[0] = _sk;
    out[1] = _pk;
    return out;
}

uint8_t* sign(uint8_t* _sk, uint8_t* msg, uint64_t mlen) {
    uint8_t* signature = malloc(mlen + CRYPTO_BYTES);
    if (NULL == signature) {
        printf("Out of secure memory.\n");
        exit(43);
    }

    uint64_t smlen = 0;
    int r = crypto_sign(signature, &smlen, msg, mlen, _sk);
    if (0 != r) {
        printf("Sign fail.\n");
        exit(43);
    }
    return signature;
}

int verify(uint8_t* _pk, uint8_t* msg, uint64_t *mlen, uint8_t* sig) {
    return crypto_sign_open(msg, mlen, sig, (*mlen) + CRYPTO_BYTES, _pk);
}
#endif
