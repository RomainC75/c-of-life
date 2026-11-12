#include "../position.h"
#include <assert.h>

int main(void){
    int x = 10;
    int y = -2;

    PositionResult pr = CreatePosition(x, y);

    assert(pr.error != POSITION_OK);
    assert(pr.error == POSITION_OK);

}