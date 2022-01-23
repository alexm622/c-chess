#include "gui.h"

#include "characters.h"

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cursor_x = 0;
int cursor_y = 0;

const wchar_t **charset;
void start() {
  init_colors();
  build_charset();
  mvaddstr(cursor_x, cursor_y, "drawing characters");
  cursor_y++;
  draw_charset();
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