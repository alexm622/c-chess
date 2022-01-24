#ifndef GUI_H
#define GUI_H

#include "board.h"

int cursor_x;
int cursor_y;

long window_x;
long  window_y;

void start();

void init_colors();

void build_charset();

void draw_charset();

void draw_board(Board* board);

#endif

