#include <stdlib.h>
#include <stdio.h>

#include "./board.h"
#include "./cell.h"
#include "./rule.h"

struct Board {
    Dimension dimension;
    Cell ***cells;
    Cell ***nextCells;
};

static Cell ***GenerateCells(int xLen, int yLen, Dimension dimension);

Board *CreateBoard(int xLen, int yLen){
    if (xLen <0 || yLen <0){
        return NULL;
    }

    Board *board = (Board *)malloc(sizeof(Board));
    
    DimensionResult dimensionRes = CreateDimension(xLen, yLen);
    if (dimensionRes.error == DIMENSION_INVALID){
        printf("dimensions invalid");
        exit(DIMENSION_INVALID);
    }
    board->cells = GenerateCells(xLen, yLen, dimensionRes.dimension);
    board->nextCells = GenerateCells(xLen, yLen, dimensionRes.dimension);
    board->dimension = dimensionRes.dimension;
    return board;
}

static Cell ***GenerateCells(int xLen, int yLen, Dimension dimension){
    Cell ***cells = (Cell ***)malloc(sizeof(Cell**)*yLen);
    for (int y = 0 ; y<yLen ; y++ ){
        Cell **line = (Cell **)malloc(sizeof(Cell*)*xLen);
        for(int x=0 ; x<xLen ; x++){
            PositionResult pRes = CreatePosition(x, y);
            if (pRes.error != POSITION_OK){
                
            }
            line[x]=CreateCell(pRes.position, dimension);
        }
        cells[y]=line;
    }
    return cells;
}

void InitiateLivingCells(Board *self, Position *positions, int ln){
    for (int i=0 ; i<ln ; i++){
        Position d = positions[i];

        Cell *cell = self->cells[d.y][d.x];
        SetCellAlive(cell);
    }
}
 
Dimension BoardDimension(Board *self){
    return self->dimension;
}

Cell *GetCell(Board *self, Position p){
    if ( IsOutOfBoard(self->dimension, p)){
        return NULL;
    }
    return self->cells[p.y][p.x];
}

void Display(Board *self){
    Dimension dimension = self->dimension;
    for (int y = 0 ; y < dimension.y ; y++ ){
        for (int x = 0 ; x < dimension.x ; x++ ){
            Cell *cell = self->cells[y][x];
            CellState state = GetCellState(cell);
            if (state == IS_DEAD){
                printf(" X ");
            }else {
                printf(" O ");
            }
        }
        printf("\n");
    }
}

int countNeighboursAlive(Cell *self, Board *board){
    int livingNeighbourQty = 0;
    NeighbourPositionResult nr = NeighbourPositions(self, BoardDimension(board));
    for (int npI = 0 ; npI < nr.ln ; npI++){
        Cell *c = GetCell(board, nr.positions[npI]);
        if (GetCellState(c) == IS_ALIVE){
            livingNeighbourQty ++;
        }
    }
    return livingNeighbourQty;
}


void DefineIfCellSurvives(Cell *self, Cell *nextCell, Board *board){
    if (GetCellState(self) == IS_DEAD){
        return;
    }
    int livingNeighbourQty = countNeighboursAlive(self, board);
    if (ShouldDieIfSolitude(nextCell, livingNeighbourQty) == SHOULD_DIE){
        return;
    }
    ShouldDieIfOverpopulation(nextCell, livingNeighbourQty);
}

void DefineIfCellIsBorn(Cell *deadCell, Cell *nextCell, Board *board){
    if (GetCellState(deadCell) == IS_ALIVE){
        return ;
    }
    // Position p = CellPosition(deadCell);
    // if (p.x == 6 && p.y == 6){
    //     printf("living Neighboutd qty : \n");
    // }
    int livingNeighbourQty = countNeighboursAlive(deadCell, board);
    ShouldACellBeBorn(nextCell, livingNeighbourQty);
}

static void iterate(Board *self, CellOperation *ops, int opsLn){
    Dimension dimension = self->dimension;
    for (int y = 0 ; y < dimension.y ; y++ ){
        for (int x = 0 ; x < dimension.x ; x++ ){
            Cell *cell = self->cells[y][x];
            Cell *nextCell = self->nextCells[y][x];
            for (int i = 0 ; i< opsLn ; i++){
                ops[i](cell, nextCell, self);
            }
        }
    }
}

void CopyToNext(Cell *cell, Cell *nextCell, Board *board){
    CopyCellState(cell, nextCell);
}

void CopyFromNext(Cell *cell, Cell *nextCell, Board *board){
    CopyCellState(nextCell, cell);
}

void Next(Board *self){
    CellOperation ops1[] = {CopyToNext};
    iterate(self, ops1, 1); 

    CellOperation ops2[] = {DefineIfCellIsBorn, DefineIfCellSurvives};
    iterate(self, ops2, 2); 

    CellOperation ops3[] = {CopyFromNext};
    iterate(self, ops3, 1);
}

void DisplayCells(Board *self, int (display)(int, int, const char *, ...)){
    Dimension dimension = self->dimension;
    for (int y = 0 ; y < dimension.y ; y++ ){
        for (int x = 0 ; x < dimension.x ; x++ ){
            Cell *cell = self->cells[y][x];
            Position p = CellPosition(cell);
            if (GetCellState(cell) == IS_DEAD){
                display(p.x, p.y, ".");
            }else {
                display(p.x, p.y, "O");
            }
        }
    }
}

