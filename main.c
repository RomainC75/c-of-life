#include "./domain/board.h"
#include <stdio.h>
#include <stdlib.h>

void SetAlive(Board *board){
    
    int positionLn =5;
    Position positions[] = {
        {3, 3},
        {3, 4},
        {4, 4},
        {4, 5},
        {5, 5}
    };
    
    InitiateLivingCells(board, positions, positionLn);
}

int main(){
    Board *b = CreateBoard(10,10);
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