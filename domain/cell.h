#ifndef CELL_H
#define CELL_H

#include "./position.h"
#include "./dimension.h"

typedef struct Cell Cell;

// Forward declaration: cell.h only needs Board *, so it does not include board.h
// (board.h includes cell.h, including it back would create a cycle).
typedef struct Board Board;

typedef struct {
    Position *positions;
    int ln;
} NeighbourPositionResult;


Cell *CreateCell(Position position, Dimension boardDimensions);

void SetCellAlive(Cell *cell);

int IsAlive(Cell *cell);

void SetCellDead(Cell *cell);

Position CellPosition(Cell *cell);

NeighbourPositionResult NeighbourPositions(Cell *self, Dimension boardDimension);

void DetermineState(Board *board, Cell *self);


#endif
