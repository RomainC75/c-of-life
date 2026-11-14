#ifndef CELL_H
#define CELL_H

#include "./position.h"
#include "./dimension.h"

typedef enum {
    IS_DEAD,
    IS_ALIVE
} CellState;

typedef struct {
    Position *positions;
    int ln;
} NeighbourPositionResult;

typedef struct Cell Cell;

typedef struct Board Board;
typedef void (*CellOperation)(Cell *cell, Cell *nextCell, Board *board);

Cell *CreateCell(Position position, Dimension boardDimensions);
void SetCellAlive(Cell *cell);
CellState GetCellState(Cell *cell);
void SetCellDead(Cell *cell);
void CopyCellState(Cell *from, Cell *to);
Position CellPosition(Cell *cell);
NeighbourPositionResult NeighbourPositions(Cell *self, Dimension boardDimension);
void DetermineState(Cell *self, Board *board);

// void DefineIfCellSurvives(Cell *self, Cell *nextCell, Board *board);

// void DefineIfCellIsBorn(Cell *self, Cell *nextCell, Board *board);

#endif
