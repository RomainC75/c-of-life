#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>

#include "./display.h"
#include "./board.h"

#define DELAY 1300000

void NewDisplay(Board *b){
     int x = 0;

    initscr();
    noecho();
     curs_set(FALSE);

 while(1) {
    if (x==10){
        break;  
    }

    if (x == 8){
      printf("lkjsdf");
    }

    clear(); // Clear the screen of all
    
    DisplayCells(b, mvprintw);

    char buffer[30];
    sprintf(buffer,"%d", x);
    mvprintw(21,21, buffer);
   
    refresh();
    Next(b);

    usleep(DELAY); // Shorter delay between movements
    x++; // Advance the ball to the right
 }

 endwin();
}

