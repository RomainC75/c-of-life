#include <stdio.h>
#include "./rule.h"

IS_SHOULD_DIE ShouldDieIfSolitude(Cell *nextCell, int livingNeighoutQty){
    if(livingNeighoutQty <= 1){
        SetCellDead(nextCell);
        return 1;
    }
    return 0;
}

IS_SHOULD_DIE ShouldDieIfOverpopulation(Cell *nextCell, int livingNeighoutQty){
    if(livingNeighoutQty >= 4){
        SetCellDead(nextCell);
        return 1;
    }
    return 0;
}

int ShouldACellBeBorn(Cell *nextCell, int livingNeighoutQty){
    if(livingNeighoutQty == 3){
        SetCellAlive(nextCell);
        return 1;
    }
    return 0;
}