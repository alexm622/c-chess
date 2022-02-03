#include <locale.h>
#include <ncursesw/ncurses.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "board.h"
#include "debug.h"
#include "gui.h"
#include "pieces.h"
long window_x;
long window_y;
Board *board;
/**
 * @brief sigint hook
 *
 * @param signum
 */
void signal_callback_handler(int signum) {
  free_board(board);
  endwin();
  exit(0);
}

int main(void) {
  // signal(SIGINT, signal_callback_handler);
  setlocale(LC_ALL, "");

  board = set_board(board, true, false);

  /*
  initscr();
  cbreak();
  noecho();

  window_x = getmaxx(stdscr);
  window_y = getmaxy(stdscr);

  clear();



  start();
  while (true) {
    draw_board(board);

    cbreak();
    refresh();
    usleep(10000000);
  }*/

  char *location = convert_to_coordinates(charstr_to_byte("d1"));
  char *printme = malloc(sizeof(char *) * 20);
  sprintf(printme, "byte - %u \n characters - %s\n", charstr_to_byte("d1"),
          location);
  printf("%s", printme);
  Moves moves = calculate_moves(board, charstr_to_byte("d1"), true);
  printf_moves(moves);
  free_moves(&moves);
  free(printme);
  free(location);
  free_board(board);
  endwin();
  return 0;
}
