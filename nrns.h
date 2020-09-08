#ifndef DGOV_NRNS_H
#define DGOV_NRNS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <gmp.h>

const uint64_t primes[8] = { 4294967111,
                             4294967143,
                             4294967161,
                             4294967189,
                             4294967197,
                             4294967231,
                             4294967279,
                             4294967291};

typedef uint64_t rnum[8];


#ifdef __GMP_H__

void mcrt(uint64_t* ps, uint64_t* n, uint64_t len, mpz_t res) {
    mpz_t p, prod, sum;
    mpz_inits(p, prod, sum, NULL);
    mpz_t temp, temp2;
    mpz_inits(temp, temp2, NULL);
    mpz_set_ui(prod, 1);
    mpz_set_ui(sum, 0);
    uint64_t i;
    for (i = 0; i < len; ++i) mpz_mul_ui(prod, prod, ps[i]);
    for (i = 0; i < len; ++i) {
        mpz_div_ui(p, prod, ps[i]);
        mpz_set_ui(temp2, ps[i]);
        mpz_invert(temp, p, temp2);
        mpz_mul(temp, temp, p);
        mpz_mul_ui(temp, temp, n[i]);
        mpz_add(sum, sum, temp);
    }

    mpz_mod(res, sum, prod);
    mpz_clears(p, prod, sum, temp, temp2, NULL);
}

#endif

uint64_t gcdext(uint64_t a, uint64_t b, uint64_t* x, uint64_t* y) {
    *x = 1;
    *y = 0;
    uint64_t x1, y1, a1, b1;
    x1 = 0;
    y1 = 1;
    a1 = a;
    b1 = b;
    while (b1) {
        uint64_t q = a1 / b1;
        uint64_t nx1, ny1, nb1;
        nx1 = *x - q * x1;
        *x = x1;
        x1 = nx1;

        ny1 = *y - q * y1;
        *y = y1;
        y1 = ny1;

        nb1 = a1 - q * b1;
        a1 = b1;
        b1 = nb1;
    }
    return a1;
}

void cexteuc(uint64_t a, uint64_t b, uint64_t* pGcd, int64_t* pX, int64_t *pY) {
    int64_t x1 = 1, y1 = 0;
    uint64_t a1 = a;
    int64_t x0 = 0, y0 = 1;
    uint64_t a2 = b, q = 0;

    while (a2 != 0) {
        int64_t x2 = x0 - ((int64_t) q) * x1;
        int64_t y2 = y0 - ((int64_t) q) * y1;
        x0 = x1;
        y0 = y1;
        uint64_t a0 = a1;
        x1 = x2;
        y1 = y2;
        a1 = a2;

        q = a0 / a1;
        a2 = a0 - q * a1;
    }
    *pX = x1;
    *pY = y1;
    *pGcd = a1;
}

uint64_t minveuc(uint64_t a, uint64_t n, bool* err) {
    int64_t x, y;
    uint64_t g;
    cexteuc(a, n, &g, &x, &y);
    if (g != 1) {
        *err = true;
        return 0;
    }
    x = ((x % n) + n) % n;
    return x;
}

uint64_t scrt(uint64_t* n, uint64_t* a, uint64_t len) {
    uint64_t p, i, prod = 1, sum = 0;
    for (i = 0; i < len; ++i) prod *= n[i];

    bool err = false;
    for (i = 0; i < len; ++i) {
        p = prod / n[i];
        sum += a[i] * minveuc(p, n[i], &err) * p;
    }
    return sum % prod;
}

bool requal(rnum a, rnum b) {
    return (a[0] == b[0]) * (a[1] == b[1]) * (a[2] == b[2]) * (a[3] == b[3]) * (a[4] == b[4]) * (a[5] == b[5]) * (a[6] == b[6]) * (a[7] == b[7]);
}

void rset(rnum c, uint64_t a) {
    c[0] = a % primes[0];
    c[1] = a % primes[1];
    c[2] = a % primes[2];
    c[3] = a % primes[3];
    c[4] = a % primes[4];
    c[5] = a % primes[5];
    c[6] = a % primes[6];
    c[7] = a % primes[7];
}

void radd(rnum c, const rnum a, const rnum b) {
    c[0] = (a[0] + b[0]) % primes[0];
    c[1] = (a[1] + b[1]) % primes[1];
    c[2] = (a[2] + b[2]) % primes[2];
    c[3] = (a[3] + b[3]) % primes[3];
    c[4] = (a[4] + b[4]) % primes[4];
    c[5] = (a[5] + b[5]) % primes[5];
    c[6] = (a[6] + b[6]) % primes[6];
    c[7] = (a[7] + b[7]) % primes[7];
}

void rsub(rnum c, const rnum a, const rnum b) {
    c[0] = (a[0] - b[0] + primes[0]) % primes[0];
    c[1] = (a[1] - b[1] + primes[1]) % primes[1];
    c[2] = (a[2] - b[2] + primes[2]) % primes[2];
    c[3] = (a[3] - b[3] + primes[3]) % primes[3];
    c[4] = (a[4] - b[4] + primes[4]) % primes[4];
    c[5] = (a[5] - b[5] + primes[5]) % primes[5];
    c[6] = (a[6] - b[6] + primes[6]) % primes[6];
    c[7] = (a[7] - b[7] + primes[7]) % primes[7];
}

void rmul(rnum c, const rnum a, const rnum b) {
    c[0] = (a[0] * b[0]) % primes[0];
    c[1] = (a[1] * b[1]) % primes[1];
    c[2] = (a[2] * b[2]) % primes[2];
    c[3] = (a[3] * b[3]) % primes[3];
    c[4] = (a[4] * b[4]) % primes[4];
    c[5] = (a[5] * b[5]) % primes[5];
    c[6] = (a[6] * b[6]) % primes[6];
    c[7] = (a[7] * b[7]) % primes[7];
}

void rdiv(rnum c, const rnum a, const rnum b) {
    bool err = false;
    c[0] = (a[0] * minveuc(b[0], primes[0], &err)) % primes[0];
    c[1] = (a[1] * minveuc(b[1], primes[1], &err)) % primes[1];
    c[2] = (a[2] * minveuc(b[2], primes[2], &err)) % primes[2];
    c[3] = (a[3] * minveuc(b[3], primes[3], &err)) % primes[3];
    c[4] = (a[4] * minveuc(b[4], primes[4], &err)) % primes[4];
    c[5] = (a[5] * minveuc(b[5], primes[5], &err)) % primes[5];
    c[6] = (a[6] * minveuc(b[6], primes[6], &err)) % primes[6];
    c[7] = (a[7] * minveuc(b[7], primes[7], &err)) % primes[7];
}

void rdivext(rnum c, const rnum a, const rnum b) {
    rnum binv;

    int valInd = -1;

    for (int i = 7; i >= 0; --i) if (b[i]) valInd = i;

    if (valInd == -1) {
        rset(c, 0);
        return;
    }
    bool err = false;
    for (int i = 0; i < 8; ++i) {
        if (b[i]) {
            binv[i] = minveuc(b[i], primes[i], &err);
        } else {
            uint64_t ps[2] = { primes[i], primes[valInd] };
            uint64_t vs[2] = { b[i], b[valInd] };
            uint64_t mod = primes[i] * primes[valInd];
            uint64_t val = scrt(ps, vs, 2);
            uint64_t inv = minveuc(val, mod, &err);
            if (err) printf("Something is fucked\n");
            binv[i] = inv % primes[i];
        }
    }

    rmul(c, a, binv);
}

void rinv(rnum binv, rnum b) {
    int valInd = -1;

    for (int i = 7; i >= 0; --i) if (b[i]) valInd = i;

    if (valInd == -1) {
        rset(binv, 0);
        return;
    }
    bool err = false;
    for (int i = 0; i < 8; ++i) {
        if (b[i]) {
            binv[i] = minveuc(b[i], primes[i], &err);
        } else {
            uint64_t ps[2] = { primes[i], primes[valInd] };
            uint64_t vs[2] = { b[i], b[valInd] };
            uint64_t mod = primes[i] * primes[valInd];
            uint64_t val = scrt(ps, vs, 2);
            uint64_t inv = minveuc(val, mod, &err);
            if (err) printf("Something is fucked\n");
            binv[i] = inv % primes[i];
        }
    }
}

#endif
