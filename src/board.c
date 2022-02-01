#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Set the board
 * 
 * @param board 
 * @param color 
 * @param initialized 
 * @return Board* 
 */
Board *set_board(Board* board, bool color, bool initialized) {
  if(!initialized){
    board = malloc(sizeof(Board));

    board = alloc_board(board);
  }
  set_black(color, board);
  set_white(color, board);
  return board;
}


/**
 * @brief allocate memory for the board
 * 
 * @param board board pointer
 * @param board_initialized whether the board was initialized before
 * @return Board* the board
 */
Board *alloc_board(Board *board) {
  board->tiles = malloc(sizeof(long *) * 8);
  for (int y = 0; y < BOARD_L; y++) {
    board->tiles[y] = calloc(sizeof(long *), 8);
    for (int x = 0; x < BOARD_W; x++) {
      board->tiles[y][x] = EMPTY_TILE;
    }
  }
  return board;
}
/**
 * @brief free the board object
 * 
 * @param board 
 */
void free_board(Board* board){
  for(int i = 0; i < BOARD_L; i++){
    free(board->tiles[i]);
  }
  free(board->tiles);
  free(board);
}


/**
 * @brief Set the white pieces
 * 
 * @param color controlled by IS_WHITE and IS_BLACK
 * @param board the board object
 */
void set_white(bool color, Board *board) {
  // offset for where tiles should be placed starting with pawns
  int y;
  int yoff = (color == IS_WHITE) ? 1 : 6;
  y = yoff;
  // set the tiles:
  for (int i = 0; i < BOARD_W; i++) {
    board->tiles[i][y] = WHITE_PAWN;
  }
  y += (color == IS_WHITE) ? -1 : 1;
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
/**
 * @brief Set the black pieces
 * 
 * @param color controlled by IS_WHITE and IS_BLACK
 * @param board the board object
 */
void set_black(bool color, Board *board) {
  // offset for where tiles should be placed starting with pawns
  int y;
  int yoff = (color == IS_BLACK) ? 1 : 6;
  y = yoff;
  // set the tiles:
  for (int i = 0; i < BOARD_W; i++) {
    board->tiles[i][y] = BLACK_PAWN;
  }
  y += (color == IS_WHITE) ? 1 : -1;
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

/**
 * @brief convert the position charstring (ex. e2) to an 8 bit representation
 * 
 * @param chstr the character string
 * @return uint8_t the 8 bit representation of the move
 */
uint8_t charstr_to_byte(char* chstr){
  char vert_a[] = "12345678";
  char horizontal_a[] = "abcdefgh";
  char vert = chstr[1];
  char horizontal = chstr[0];
  uint8_t pos_x, pos_y;
  for(int i = 8; i > 0; i--){
    if(vert_a[8-i] == vert){
      pos_y = 8-i;
    }
  }
  for(int i = 8; i > 0; i--){
    if(horizontal_a[8-i] == horizontal){
      pos_x = 8-i;
    }
  }
  //construct the return value
  uint8_t return_val = (pos_y) | ((pos_x) << 4);
  return return_val;
}
