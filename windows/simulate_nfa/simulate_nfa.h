#ifndef SIMULATE_NFA_H
#define SIMULATE_NFA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

typedef struct {
    int state_num;
    int state[SIZE];
} NFAStateMartix;

#endif // SIMULATE_NFA_H
