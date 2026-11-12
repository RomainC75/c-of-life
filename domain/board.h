#ifndef BOARD_H
#define BOARD_H

#include "./cell.h"
#include "./dimension.h"
#include "./position.h"

// private
typedef struct Board Board;

Board *CreateBoard(int xLen, int yLen);

Cell *GetCell(Board *self, Position p);

void Next(Board *self);

void Display(Board *self);

void InitiateLivingCells(Board *self, Position *positions, int ln);

#endif
