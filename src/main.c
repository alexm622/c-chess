#include <locale.h>
#include <ncursesw/ncurses.h>
#include <stdio.h>

#include "board.h"
#include "gui.h"

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
  draw_board(board);

  cbreak();
  refresh();

  return 0;
}
