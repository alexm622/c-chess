#include "board.h"

#include <stdlib.h>
Board *set_board(bool color, bool initialized) {
  Board *board = malloc(sizeof(Board));

  board = alloc_board(board, initialized);
  set_black(color, board);
  set_white(color, board);
  return board;
}

// allocate memory for the board
// TODO for some reason the defines are not working properly
Board *alloc_board(Board *board, bool board_initialized) {
  if (board_initialized) {
    return board;
  }
  board->tiles = malloc(sizeof(long *) * 8);
  for (int y = 0; y < BOARD_L; y++) {
    board->tiles[y] = calloc(sizeof(long *), 8);
    for (int x = 0; x < BOARD_W; x++) {
      board->tiles[y][x] = EMPTY_TILE;
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
    board->tiles[i][y] = WHITE_PAWN;
  }
  y += (color == IS_WHITE) ? 1 : -1;
  // draw the rest of the tiles
  board->tiles[0][y] = WHITE_ROOK;
  board->tiles[1][y] = WHITE_KNIGHT;
  board->tiles[2][y] = WHITE_BISHOP;
  board->tiles[3][y] = (color == IS_WHITE) ? WHITE_QUEEN : WHITE_KING;
  board->tiles[4][y] = (color == IS_BLACK) ? WHITE_QUEEN : WHITE_KING;
  board->tiles[5][y] = WHITE_BISHOP;
  board->tiles[6][y] = WHITE_KNIGHT;
  board->tiles[7][y] = WHITE_ROOK;
}

void set_black(bool color, Board *board) {
  // offset for where tiles should be placed starting with pawns
  int y;
  int yoff = (color == IS_BLACK) ? 6 : 1;
  y = yoff;
  // set the tiles:
  for (int i = 0; i < BOARD_W; i++) {
    board->tiles[i][y] = BLACK_PAWN;
  }
  y += (color == IS_WHITE) ? -1 : 1;
  // draw the rest of the tiles
  board->tiles[0][y] = BLACK_ROOK;
  board->tiles[1][y] = BLACK_KNIGHT;
  board->tiles[2][y] = BLACK_BISHOP;
  board->tiles[3][y] = (color == IS_WHITE) ? BLACK_QUEEN : BLACK_KING;
  board->tiles[4][y] = (color == IS_BLACK) ? BLACK_QUEEN : BLACK_KING;
  board->tiles[5][y] = BLACK_BISHOP;
  board->tiles[6][y] = BLACK_KNIGHT;
  board->tiles[7][y] = BLACK_ROOK;
}

short charstr_to_short(char* chstr){
  char vert_a[] = "12345678";
  char horizontal_a[] = "abcdefgh";
  char vert = chstr[1];
  char horizontal = chstr[0];
  short pos_x, pos_y;
  for(int i = 0; i < 8; i++){
    if(vert_a[i] == vert){
      pos_x = i;
    }
  }
  for(int i = 0; i < 8; i++){
    if(horizontal_a[i] == horizontal){
      pos_y = i;
    }
  }

  short return_val = (pos_y) | ((pos_x) << 8);
  return return_val;
}
