#include <stdlib.h>

#include "./position.h"

PositionResult CreatePosition(int x, int y) {
    if (x < 0 || y < 0) {
        return (PositionResult){
            .error = POSITION_INVALID_COORDINATES
        };
    }

    return (PositionResult) {
        .position = {
            .x = x,
            .y = y,
        },
        .error = POSITION_OK
    };
}

int GetX(Position p) {
    return p.x;
}

int GetY(Position p) {
    return p.y;
}

IsSamePositionE IsSamePosition(Position self, Position other){
    if (self.x == other.x && self.y == other.y){
        return IS_SAME_POSITION;
    }
    return IS_POSITION_DIFFERENT;
}
