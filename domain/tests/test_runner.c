#include <stdio.h>
// #include "./test_board.c"
// #include "./test_position.c"


void test_position_init(void);
void test_board_init(void);


int main(void){
    printf("Running unit tests...\n\n");

    printf("[POSITION TESTS]\n");
    test_position_init();

    printf("[BOARD TESTS]\n");
    test_board_init();

    printf("\nAll tests passed!\n");

    return 0;
}