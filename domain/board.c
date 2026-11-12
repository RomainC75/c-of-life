#include <stdlib.h>

#include "./board.h"

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
    for (int x = 0 ; x<xLen ; x++ ){
        Cell **line = (Cell **)malloc(sizeof(Cell*)*yLen);
        for(int y=0 ; y<yLen ; y++){
            PositionResult pRes = CreatePosition(x, y);
            if (pRes.error != POSITION_OK){

            }
            DimensionResult dRes = CreateDimension(x,y);
            if (dRes.error != DIMENSION_OK){

            }
            
            line[y]=CreateCell(pRes.position, dRes.dimension);
        }
    }
    return cells;
}

Cell *GetCell(Board *self, Position p){
    if ( IsOutOfBoard(self->dimension, p)){
        return NULL;
    }
    return self->cells[p.x][p.y];
}

static void iterate(Board *self, void (*operate)(Board *board, Cell *cell)){
    Dimension dimension = self->dimension;
    for (int y = 0 ; y < dimension.y ; y++ ){
        for (int x = 0 ; x < dimension.x ; x++ ){
            Cell *cell = self->cells[x][y];
            operate(self, cell);
        }
    }
}

void Next(Board *self){
    iterate(self, DetermineState);
}
