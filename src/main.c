#include <stdio.h>

#include <curses.h>

#include "gui.h"

int main(void) {
  printf("Hello World\n");

  /* initialize curses */

  initscr();
  cbreak();
  noecho();

  clear();

  draw();

  cbreak();
  refresh();

  return 0;
}
