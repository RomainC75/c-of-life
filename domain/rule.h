#ifndef RULE_H
#define RULE_H

#include "./cell.h"

typedef enum {
    SHOULD_NOT_DIE,
    SHOULD_DIE
} IS_SHOULD_DIE;

typedef int (*RuleFn)(Cell *cell, int livingNeighbourQty);

IS_SHOULD_DIE ShouldDieIfSolitude(Cell *cell, int livingNeighoutQty);
IS_SHOULD_DIE ShouldDieIfOverpopulation(Cell *cell, int livingNeighoutQty);

int ShouldACellBeBorn(Cell *cell, int livingNeighoutQty);

#endif