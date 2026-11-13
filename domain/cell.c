#include <stdlib.h>
#include <stdio.h>

#include "./cell.h"
#include "./board.h"

struct Cell{
    Position position;
    Position *neighbourPositions;
    int neighbourPositionLn;
    CellState state;
};

Cell *CreateCell(Position position, Dimension boardDimensions){
    Cell *cell = (Cell *)malloc(sizeof(Cell));

    cell -> position = position;
    cell -> state = 0;
    NeighbourPositionResult nbRes = NeighbourPositions(cell, boardDimensions);
    cell -> neighbourPositions = nbRes.positions;
    cell -> neighbourPositionLn = nbRes.ln;

    return cell;
}

void SetCellAlive(Cell *cell){
    cell -> state = IS_ALIVE;
}

void SetCellDead(Cell *cell){
    cell -> state = IS_DEAD;
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
    for (int x=GetX(self->position)-1 ; x<=GetX(self->position)+1 ; x++){
        for (int y=GetY(self->position)-1 ; y<=GetY(self->position)+1 ; y++){
            PositionResult nbRes = CreatePosition(x,y);
            if (nbRes.error == POSITION_OK && IsSamePosition(self->position, nbRes.position) !=0 && x<boardDimension.x && y<boardDimension.y){
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

int countNeighbours(Cell *self, Board *board){
    int livingNeighbourQty = 0;
    for (int npI = 0 ; npI<self->neighbourPositionLn ; npI++){
        Cell *c = GetCell(board, self->neighbourPositions[npI]);
        if (GetCellState(c) == IS_ALIVE){
            livingNeighbourQty ++;
        }
    }
    return livingNeighbourQty;
}

void SetStateAccordingToRules(Cell *self, Board *board){
    int livingNeighbourQty = countNeighbours(self, board);
    // underpopulation or overpopulation
    if (livingNeighbourQty<2 || livingNeighbourQty>3){
        SetCellDead(self);
    } else if (GetCellState(self) == IS_ALIVE && (livingNeighbourQty ==2 || livingNeighbourQty ==3 ))
    {   
        // stay alive
        return ;
    // reproduction
    } else if (GetCellState(self) == IS_DEAD && livingNeighbourQty == 3)
     {
        SetCellAlive(self);
    }
}


