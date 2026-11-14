#include <stdio.h>
#include "./rule.h"

IS_SHOULD_DIE ShouldDieIfSolitude(Cell *cell, int livingNeighoutQty){
    if(livingNeighoutQty <= 1){
        SetCellDead(cell);
        return 1;
    }
    return 0;
}

IS_SHOULD_DIE ShouldDieIfOverpopulation(Cell *cell, int livingNeighoutQty){
    if(livingNeighoutQty >= 4){
        SetCellDead(cell);
        return 1;
    }
    return 0;
}

int ShouldACellBeBorn(Cell *cell, int livingNeighoutQty){
    if(livingNeighoutQty == 3){
        SetCellAlive(cell);
        return 1;
    }
    return 0;
}