#include "./domain/board.h"
#include <stdio.h>

void SetAlive(){

}

int main(){
    Board *b = CreateBoard(8,8);
    
    Next(b);
    Display(b);
    
    // printf("\n");
    
    // Next(b);
    // Display(b);

    // printf("\n");

    // Next(b);
    // Display(b);
}