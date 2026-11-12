#include "./domain/board.h"


int main(){
    Board *b = CreateBoard(4,4);
    Next(b);
    Display(b);
}