#include "../board.h"
#include "../position.h"
#include <assert.h>
#include <stdlib.h>

Position pr1 = {
    .x= 1,
    .y= 1
};
Position pr2 = {
    .x= 1,
    .y= 2
};

void SetAlive(Board *board){
    
    int positionLn =2;
    
    Position *positions = (Position *)malloc(sizeof(Position)*2);
    positions[0]=pr1;
    positions[1]=pr2;

    InitiateLivingCells(board, positions, positionLn);
}

void test_board_init(){
    Board *b = CreateBoard(5,5);

    Cell *c1 = GetCell(b, pr1);
    assert(IsAlive(c1) == 0);

    SetAlive(b);
    Cell *c2 = GetCell(b, pr1);
    assert(IsAlive(c2) == 1);
}