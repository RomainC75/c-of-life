#include <stdlib.h>
#include <stdio.h>

#include "./board.h"
#include "./cell.h"

struct Board {
    Dimension dimension;
    Cell ***cells;
};

static Cell ***GenerateCells(int xLen, int yLen);

Board *CreateBoard(int xLen, int yLen){
    if (xLen <0 || yLen <0){
        return NULL;
    }

    Board *board = (Board *)malloc(sizeof(Board));
    
    board->cells = GenerateCells(xLen, yLen);
    DimensionResult dimensionRes = CreateDimension(xLen, yLen);
    board->dimension = dimensionRes.dimension;
    return board;
}

static Cell ***GenerateCells(int xLen, int yLen){
    Cell ***cells = (Cell ***)malloc(sizeof(Cell**)*yLen);
    for (int y = 0 ; y<yLen ; y++ ){
        Cell **line = (Cell **)malloc(sizeof(Cell*)*xLen);
        for(int x=0 ; x<xLen ; x++){
            PositionResult pRes = CreatePosition(x, y);
            if (pRes.error != POSITION_OK){

            }
            DimensionResult dRes = CreateDimension(x,y);
            if (dRes.error != DIMENSION_OK){

            }
            line[x]=CreateCell(pRes.position, dRes.dimension);
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

Cell *GetCell(Board *self, Position p){
    if ( IsOutOfBoard(self->dimension, p)){
        return NULL;
    }
    return self->cells[p.x][p.y];
}

void Display(Board *self){
    Dimension dimension = self->dimension;
    for (int y = 0 ; y < dimension.y ; y++ ){
        for (int x = 0 ; x < dimension.x ; x++ ){
            Cell *cell = self->cells[x][y];
            int state = IsAlive(cell);
            if (state == 0){
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
            Cell *cell = self->cells[x][y];
            operate(cell, self);
        }
    }
}

void Next(Board *self){
    iterate(self, DetermineState);
}
