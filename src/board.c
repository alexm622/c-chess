#include "board.h"

#include <stdlib.h>

void set_board(bool color) {
  alloc_board();
  set_black(color);
  set_white(color);
}

// allocate memory for the board
void alloc_board() {
  if (board_initialized) {
    return;
  }
  board = malloc(sizeof(Board *));
  board->tiles = malloc(sizeof(Tile ***));
  for (int y = 0; y < BOARD_L; y++) {
    board->tiles[y] = calloc(sizeof(Tile **), BOARD_W);
    for (int x = 0; x < BOARD_W; x++) {
      board->tiles[y][x] = malloc(sizeof(Tile));
      board->tiles[y][x]->tile = EMPTY;
    }
  }
  board_initialized = true;
}

void set_white(bool color) {
  // offset for where tiles should be placed starting with pawns
  int y;
  int yoff = (color == COLOR_WHITE) ? 6 : 1;
  y = yoff;
  // set the tiles:
  for (int i = 0; i < BOARD_W; i++) {
    board->tiles[i][y]->tile = W_PAWN;
  }
  y += (color == COLOR_WHITE) ? 1 : -1;
  // draw the rest of the tiles
  board->tiles[0][y]->tile = W_ROOK;
  board->tiles[1][y]->tile = W_KNIGHT;
  board->tiles[2][y]->tile = W_BISHOP;
  board->tiles[3][y]->tile = (color == COLOR_WHITE) ? W_QUEEN : W_KING;
  board->tiles[4][y]->tile = (color == COLOR_BLACK) ? W_QUEEN : W_KING;
  board->tiles[5][y]->tile = W_BISHOP;
  board->tiles[6][y]->tile = W_KNIGHT;
  board->tiles[7][y]->tile = W_ROOK;
}

void set_black(bool color) {
  // offset for where tiles should be placed starting with pawns
  int y;
  int yoff = (color == COLOR_BLACK) ? 6 : 1;
  y = yoff;
  // set the tiles:
  for (int i = 0; i < BOARD_W; i++) {
    board->tiles[i][y]->tile = B_PAWN;
  }
  y += (color == COLOR_WHITE) ? 1 : -1;
  // draw the rest of the tiles
  board->tiles[0][y]->tile = B_ROOK;
  board->tiles[1][y]->tile = B_KNIGHT;
  board->tiles[2][y]->tile = B_BISHOP;
  board->tiles[3][y]->tile = (color == COLOR_WHITE) ? B_QUEEN : B_KING;
  board->tiles[4][y]->tile = (color == COLOR_BLACK) ? B_QUEEN : B_KING;
  board->tiles[5][y]->tile = B_BISHOP;
  board->tiles[6][y]->tile = B_KNIGHT;
  board->tiles[7][y]->tile = B_ROOK;
}
