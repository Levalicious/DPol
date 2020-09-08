#ifndef DGOV_BLABLA_H
#define DGOV_BLABLA_H

#include <stdint.h>

#define BLABLA_KEY_LEN (32)
#define BLABLA_NONCE_LEN (16)

#define F(a) for (i = 0; i < a; ++i)
#define R(v, n) (((v) >> (n)) | ((v) << (64LU - (n))))
#define X(a, b) (t) = (a), (a) = (b), (b) = (t)



typedef struct {
    uint64_t q[16];
} blabla_ctx;


void blabla_setkey(blabla_ctx *c, const void *key, const void *nonce) {
    int i;

    c->q[0] = 0x6170786593810fabLU;
    c->q[1] = 0x3320646ec7398aeeLU;
    c->q[2] = 0x79622d3217318274LU;
    c->q[3] = 0x6b206574babadadaLU;

    F(4) c->q[i + 4] = ((uint64_t*) key)[i];

    c->q[8] = 0x2ae36e593e46ad5fLU;
    c->q[9] = 0xb68f143029225fc9;
    c->q[10] = 0x8da1e08468303aa6;
    c->q[11] = 0xa48a209acd50a4a7;
    c->q[12] = 0x7fdc12f23f90778c;

    c->q[13] = 1;

    F(2) c->q[i + 14] = ((uint64_t*) nonce)[i];
}

void blabla_stream(blabla_ctx *s, void *out) {
    uint64_t a, b, c, d, i, t, r, *x = (uint64_t*) out;
    uint16_t v[8] = { 0xC840, 0xD951, 0xEA62, 0xFB73, 0xFA50, 0xCB61, 0xD872, 0xE943 };

    F(16) x[i] = s->q[i];

    F(80) {
        d = v[i % 8LU];
        a = (d & 15LU);
        b = (d >> 4LU & 15LU);
        c = (d >> 8LU & 15LU);
        d >>= 12LU;

        for (r = 0x3F101820LU; r; r >>= 8LU)
            x[a] += x[b],
            x[d] = R(x[d] ^ x[a], (r & 255LU)),
            X(a, c), X(b, d);
    }

    F(16) x[i] += s->q[i];

    s->q[13]++;
}

void blabla_encrypt(blabla_ctx *ctx, void *buf, uint64_t len) {
    uint64_t i, r;
    uint8_t c[128], *p = (uint8_t *) buf;

    while (len) {
        blabla_stream(ctx, c);
        r = (len > 128) ? (128) : (len);
        F(r) p[i] ^= c[i];
        len -= r;
        p += r;
    }
}

void blabla_keystream(blabla_ctx *c, void *buf, size_t len) {
    uint64_t i;

    F(len)((uint8_t*)buf)[i]=0;           // zero initialize buffer
    blabla_encrypt(c, buf, len);    // encrypt it
}


#endif
