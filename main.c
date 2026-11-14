#include "./domain/board.h"
#include "./domain/display.h"
#include <stdio.h>
#include <stdlib.h>


void SetAlive(Board *board){
    
    int positionLn =5;
    Position positions[] = {
        {4, 1},
        {5, 2},
        {3, 3},
        {4, 3},
        {5, 3},
    };
    
    InitiateLivingCells(board, positions, positionLn);
}

int main(){
    Board *b = CreateBoard(20,20);
    SetAlive(b);

    NewDisplay(b);
}