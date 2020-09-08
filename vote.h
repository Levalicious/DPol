/* Copyright (c) 2020 Lev Knoblock, see LICENSE */
#ifndef DGOV_VOTE_H
#define DGOV_VOTE_H
#include <sodium.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct vtstrct vote;
typedef vote* vptr;
struct vtstrct {
    bool vote;
    vptr delegate;
};





#endif
