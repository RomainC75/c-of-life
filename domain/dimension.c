#include "./dimension.h"

DimensionResult CreateDimension(int x, int y){
    if (x>10 || y>10){
        return (DimensionResult){
            .error = DIMENSION_INVALID
        };
    }

    return (DimensionResult){
        .dimension = {
            .x = x,
            .y = y,
        },
        .error = DIMENSION_OK,
    };
}

int IsOutOfBoard(Dimension self, Position position){
    if (position.x >= self.x || position.y >= self.y){
        return -1;
    } 
    return 0;
}


