#include <stdlib.h>
#include <stdio.h>

#include "./cell.h"
#include "./board.h"
#include "./rule.h"


struct Cell{
    Position position;
    CellState state;
};

Cell *CreateCell(Position position, Dimension boardDimensions){
    Cell *cell = (Cell *)malloc(sizeof(Cell));

    cell -> position = position;
    cell -> state = 0;


    return cell;
}

void SetCellAlive(Cell *cell){
    cell -> state = IS_ALIVE;
}

void SetCellDead(Cell *cell){
    cell -> state = IS_DEAD;
}

void CopyCellState(Cell *from, Cell *to){
    to->state=from->state;
}

CellState GetCellState(Cell *cell){
    return cell->state;
}

Position CellPosition(Cell *cell){
    return cell -> position;
}

NeighbourPositionResult NeighbourPositions(Cell *self, Dimension boardDimension){
    Position *nPositions = (Position *)malloc(sizeof(Position)*9);
    int index = 0;
    Position selfPosition = CellPosition(self);
    for (int y=GetY(selfPosition)-1 ; y<=GetY(selfPosition)+1 ; y++){
        for (int x=GetX(selfPosition)-1 ; x<=GetX(selfPosition)+1 ; x++){
            PositionResult nbRes = CreatePosition(x,y);
            if (nbRes.error == POSITION_OK && IsSamePosition(self->position, nbRes.position) == IS_POSITION_DIFFERENT && x<boardDimension.x && y<boardDimension.y){
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

