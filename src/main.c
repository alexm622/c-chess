#include <locale.h>
#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <unistd.h>

#include "board.h"
#include "gui.h"
#include "pieces.h"
long window_x;
long window_y;

int main(void) {

  setlocale(LC_ALL, "");

  /* initialize curses */
  initscr();
  cbreak();
  noecho();

  window_x = getmaxx(stdscr);
  window_y = getmaxy(stdscr);

  clear();

  Board *board = set_board(true, false);
  start();
  while (true) {
    draw_board(board);
    cbreak();
    refresh();
    usleep(1000000);
  }

  return 0;
}
