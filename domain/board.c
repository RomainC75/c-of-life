#include <stdlib.h>
#include <stdio.h>

#include "./board.h"
#include "./cell.h"

struct Board {
    Dimension dimension;
    Cell ***cells;
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

static void iterate(Board *self, void (*operate)(Cell *cell, Board *board)){
    Dimension dimension = self->dimension;
    for (int y = 0 ; y < dimension.y ; y++ ){
        for (int x = 0 ; x < dimension.x ; x++ ){
            Cell *cell = self->cells[y][x];
            operate(cell, self);
        }
    }
}

void Next(Board *self){
    iterate(self, DefineIfCellIsBorn); 
    iterate(self, DefineIfCellSurvives);
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