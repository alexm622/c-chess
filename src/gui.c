#include "gui.h"

#include "board.h"
#include "characters.h"

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const wchar_t **charset;
void start() {
  init_colors();
  build_charset();
  // mvaddstr(cursor_x, cursor_y, "drawing characters");
  // draw_charset();
}

void init_colors() {
  start_color();
  // background color
  // init_pair(1, COLOR_WHITE, COLOR_BLACK);
  // black square
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  // white square
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

void draw_charset() {
  int cursor_y = 0;
  int cursor_x = 0;
  for (int i = 0; i < charset_size; i++) {
    mvaddwstr(cursor_y, cursor_x, charset[i]);
    cursor_y++;
  }
}

void build_charset() {
  charset = malloc(sizeof(const wchar_t *) * charset_size);
  // empty space

  charset[0] = EMPTY;

  // white pieces
  charset[1] = W_KING;
  charset[2] = W_QUEEN;
  charset[3] = W_ROOK;
  charset[4] = W_BISHOP;
  charset[5] = W_KNIGHT;
  charset[6] = W_PAWN;

  // black pieces
  charset[7] = B_KING;
  charset[8] = B_QUEEN;
  charset[9] = B_ROOK;
  charset[10] = B_BISHOP;
  charset[11] = B_KNIGHT;
  charset[12] = B_PAWN;
}

void draw_board(Board *board) {
  const char *boardletter = "abcdefgh";
  int cursor_x = 0;
  int cursor_y = 0;
  // draw letters
  mvaddstr(0, 1, boardletter);
  mvaddstr(BOARD_L + 1, 1, boardletter);
  // draw number
  char str[2];
  for (int i = 1; i <= BOARD_L; i++) {
    sprintf(str, "%d", i);
    mvaddstr(i, 0, str);
    mvaddstr(i, BOARD_W + 1, str);
  }

  cursor_x++;
  cursor_y++;
  for (int y = 0; y < BOARD_L; y++) {
    for (int x = 0; x < BOARD_W; x++) {
      mvaddwstr(cursor_y, cursor_x, charset[board->tiles[x][y]]);
      cursor_x++;
    }
    cursor_x = 1;
    cursor_y++;
  }
}
