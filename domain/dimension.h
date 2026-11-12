#ifndef DIMENSION_H
#define DIMENSION_H

#include "./position.h"

typedef struct {
    int x;
    int y;
} Dimension;

typedef enum {
    DIMENSION_OK,
    DIMENSION_INVALID,
} DimensionError;

typedef struct {
    Dimension dimension;
    DimensionError error; 
} DimensionResult;

DimensionResult CreateDimension(int x, int y);

int IsOutOfBoard(Dimension self, Position position);

#endif
