#include <locale.h>
#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#include "board.h"
#include "gui.h"
#include "pieces.h"
#include "debug.h"
long window_x;
long window_y;

int main(void) {

  setlocale(LC_ALL, "");

  /* initialize curses */
  /*
  initscr();
  cbreak();
  noecho();

  window_x = getmaxx(stdscr);
  window_y = getmaxy(stdscr);

  clear();
  */

  //Board *board = set_board(true, false);
  start();
  while (true) {
    //draw_board(board);
    char* location = convert_to_coordinates(charstr_to_short("e4"));
    char* printme = malloc(sizeof(char*)*20);
    sprintf(printme, "unsigned short - %d \n characters - %s", charstr_to_short("e4"), "e4");
    //mvaddstr(0, 0, printme);
    printf(printme);
    cbreak();
    refresh();
    
    usleep(10000000);
  }

  return 0;
}
