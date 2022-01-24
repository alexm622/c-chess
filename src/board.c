#include "board.h"

#include <stdlib.h>
bool board_initialized = false;
Board *set_board(bool color, bool initialized) {
  Board *board = malloc(sizeof(Board));

  board = alloc_board(board, initialized);
  set_black(color, board);
  set_white(color, board);
  return board;
}

// allocate memory for the board
Board *alloc_board(Board *board, bool board_initialized) {
  if (board_initialized) {
    return board;
  }
  board->tiles = malloc(sizeof(Tile ***));
  for (int y = 0; y < BOARD_L; y++) {
    board->tiles[y] = calloc(sizeof(Tile **), BOARD_W);
    for (int x = 0; x < BOARD_W; x++) {
      board->tiles[y][x] = malloc(sizeof(Tile));
      board->tiles[y][x]->tile = EMPTY_TILE;
    }
  }
  board_initialized = true;
  return board;
}

void set_white(bool color, Board *board) {
  // offset for where tiles should be placed starting with pawns
  int y;
  int yoff = (color == IS_WHITE) ? 6 : 1;
  y = yoff;
  // set the tiles:
  for (int i = 0; i < BOARD_W; i++) {
    board->tiles[i][y]->tile = WHITE_PAWN;
  }
  y += (color == IS_WHITE) ? 1 : -1;
  // draw the rest of the tiles
  board->tiles[0][y]->tile = WHITE_ROOK;
  board->tiles[1][y]->tile = WHITE_KNIGHT;
  board->tiles[2][y]->tile = WHITE_BISHOP;
  board->tiles[3][y]->tile = (color == IS_WHITE) ? WHITE_QUEEN : WHITE_KING;
  board->tiles[4][y]->tile = (color == IS_BLACK) ? WHITE_QUEEN : WHITE_KING;
  board->tiles[5][y]->tile = WHITE_BISHOP;
  board->tiles[6][y]->tile = WHITE_KNIGHT;
  board->tiles[7][y]->tile = WHITE_ROOK;
}

void set_black(bool color, Board *board) {
  // offset for where tiles should be placed starting with pawns
  int y;
  int yoff = (color == IS_BLACK) ? 6 : 1;
  y = yoff;
  // set the tiles:
  for (int i = 0; i < BOARD_W; i++) {
    board->tiles[i][y]->tile = BLACK_PAWN;
  }
  y += (color == IS_WHITE) ? 1 : -1;
  // draw the rest of the tiles
  board->tiles[0][y]->tile = BLACK_ROOK;
  board->tiles[1][y]->tile = BLACK_KNIGHT;
  board->tiles[2][y]->tile = BLACK_BISHOP;
  board->tiles[3][y]->tile = (color == IS_WHITE) ? BLACK_QUEEN : BLACK_KING;
  board->tiles[4][y]->tile = (color == IS_BLACK) ? BLACK_QUEEN : BLACK_KING;
  board->tiles[5][y]->tile = BLACK_BISHOP;
  board->tiles[6][y]->tile = BLACK_KNIGHT;
  board->tiles[7][y]->tile = BLACK_ROOK;
}
