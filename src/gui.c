#include "gui.h"

#include <curses.h>
#include <stdlib.h>

void draw() {
  int cursor = 0;
  mvprintw(0, cursor, "balls");
}
