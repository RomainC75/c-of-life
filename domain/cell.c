#include <stdlib.h>

#include "./cell.h"
#include "./board.h"


struct Cell{
    Position position;
    Position *neighbourPositions;
    int neighbourPositionLn;
    int isAlive;
};

Cell *CreateCell(Position position, Dimension boardDimensions){
    Cell *cell = (Cell *)malloc(sizeof(Cell));

    cell -> position = position;
    cell -> isAlive = 0;
    NeighbourPositionResult nbRes = NeighbourPositions(cell, boardDimensions);
    cell -> neighbourPositions = nbRes.positions;
    cell -> neighbourPositionLn = nbRes.ln;

    return cell;
}

void SetCellAlive(Cell *cell){
    cell -> isAlive = 1;
}

int IsAlive(Cell *cell){
    return cell->isAlive;
}

void SetCellDead(Cell *cell){
    cell -> isAlive = 0;
}

Position CellPosition(Cell *cell){
    return cell -> position;
}

NeighbourPositionResult NeighbourPositions(Cell *self, Dimension boardDimension){
    Position *nPositions = (Position *)malloc(sizeof(Position)*9);
    int index = 0;
    for (int x=GetX(self->position)-1 ; x<=GetX(self->position)+1 ; x++){
        for (int y=GetY(self->position)-1 ; y<=GetY(self->position)+1 ; y++){
            PositionResult nbRes = CreatePosition(x,y);
            if (nbRes.error == POSITION_OK && IsSamePosition(self->position, nbRes.position) !=0){
                nPositions[index] = nbRes.position;
                index ++;
            }
        }
    }
    return (NeighbourPositionResult){
        .positions = nPositions,
        .ln = index,
    };
}

void DetermineState(Board *board, Cell *self){
    int aliveCellQty = 0;
    for (int npI = 0 ; npI<self->neighbourPositionLn ; npI++){
        Cell *c = GetCell(board, self->neighbourPositions[npI]);
        if (IsAlive(c)){
            aliveCellQty ++;
        }
    }
    // ! verify 
    if (aliveCellQty>1){
        self->isAlive = 1;
    } else {
        self->isAlive = 0;
    }

}


