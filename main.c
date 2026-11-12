#include "./domain/board.h"
#include <stdio.h>
#include <stdlib.h>

void SetAlive(Board *board){
    PositionResult pr1 = CreatePosition(2,3);
    PositionResult pr2 = CreatePosition(2,4);
    PositionResult pr3 = CreatePosition(2,5);
    PositionResult pr4 = CreatePosition(1,4);
    int positionLn =4;
    
    Position *positions = (Position *)malloc(sizeof(Position)*2);
    positions[0]=pr1.position;
    positions[1]=pr2.position;
    positions[2]=pr3.position;
    positions[3]=pr4.position;
    InitiateLivingCells(board, positions, positionLn);
}

int main(){
    Board *b = CreateBoard(8,8);
    SetAlive(b);
    Display(b);
    
    printf("\n");
    Next(b);
    Display(b);
    
    // printf("\n");
    
    // Next(b);
    // Display(b);

    // printf("\n");

    // Next(b);
    // Display(b);
}