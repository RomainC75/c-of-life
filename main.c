#include "./domain/board.h"
#include "./domain/display.h"
#include <stdio.h>
#include <stdlib.h>


void SetAlive(Board *board){
    
    int positionLn =7;
    Position positions[] = {
        {3, 3},
        {3, 4},
        {4, 4},
        {4, 5},
        {5, 5},
        {6, 5},
        {7, 5},
    };
    
    InitiateLivingCells(board, positions, positionLn);
}

int main(){
    Board *b = CreateBoard(10,10);
    SetAlive(b);
    NewDisplay(b);
    // Display(b);
    
    // printf("\n");
    // Next(b);
    // Display(b);
    
    // printf("\n");
    
    // Next(b);
    // Display(b);

    // printf("\n");

    // Next(b);
    // Display(b);
}