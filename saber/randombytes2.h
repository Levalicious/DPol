#ifndef RANDOMBYTES_H
#define RANDOMBYTES_H

#define _GNU_SOURCE

#include <unistd.h>

void randombytessa(unsigned char *x, size_t xlen);

#endif