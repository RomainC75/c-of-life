#ifndef POSITION_H
#define POSITION_H

typedef struct Position {
    int x;
    int y;
} Position;

typedef enum {
    POSITION_OK,
    POSITION_INVALID_COORDINATES,
} PositionError;

typedef struct {
    Position position;
    PositionError error;
} PositionResult;

PositionResult CreatePosition(int x, int y);

int GetX(Position p);

int GetY(Position p);

int IsSamePosition(Position self, Position other);

#endif
