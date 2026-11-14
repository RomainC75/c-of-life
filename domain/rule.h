#ifndef RULE_H
#define RULE_H

#include "./cell.h"

typedef enum {
    SHOULD_NOT_DIE,
    SHOULD_DIE
} IS_SHOULD_DIE;

typedef int (*RuleFn)(Cell *nextCell,int livingNeighbourQty);

IS_SHOULD_DIE ShouldDieIfSolitude(Cell *nextCell, int livingNeighoutQty);
IS_SHOULD_DIE ShouldDieIfOverpopulation(Cell *nextCell, int livingNeighoutQty);

int ShouldACellBeBorn(Cell *nextCell, int livingNeighoutQty);

#endif