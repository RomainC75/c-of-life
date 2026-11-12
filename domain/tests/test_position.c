#include "../position.h"
#include <assert.h>

void test_position_init(void){
    PositionResult pr = CreatePosition(10, -23);
    assert(pr.error == POSITION_INVALID_COORDINATES);
    
    pr = CreatePosition(-2, 4);
    assert(pr.error == POSITION_INVALID_COORDINATES);

    pr = CreatePosition(0, 0);
    assert(pr.error == POSITION_OK);

    pr = CreatePosition(2, 4);
    assert(pr.error == POSITION_OK);
    assert(GetX(pr.position) == 2);
    assert(GetY(pr.position) == 4);
}