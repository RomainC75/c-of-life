#ifndef CELL_H
#define CELL_H

#include "./position.h"
#include "./dimension.h"

typedef struct Cell Cell;

// Forward declaration: cell.h only needs Board *, so it does not include board.h
// (board.h includes cell.h, including it back would create a cycle).
typedef struct Board Board;
typedef void (*CellOperation)(Cell *cell, Cell *nextCell, Board *board);

typedef enum {
    IS_DEAD,
    IS_ALIVE
} CellState;

typedef struct {
    Position *positions;
    int ln;
} NeighbourPositionResult;


Cell *CreateCell(Position position, Dimension boardDimensions);

void SetCellAlive(Cell *cell);

CellState GetCellState(Cell *cell);

void SetCellDead(Cell *cell);

void CopyCellState(Cell *from, Cell *to);

Position CellPosition(Cell *cell);

NeighbourPositionResult NeighbourPositions(Cell *self, Dimension boardDimension);

void DetermineState(Cell *self, Board *board);

void DefineIfCellSurvives(Cell *self, Cell *nextCell, Board *board);

void DefineIfCellIsBorn(Cell *self, Cell *nextCell, Board *board);

#endif
