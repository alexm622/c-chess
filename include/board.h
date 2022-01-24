#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define IS_WHITE true
#define IS_BLACK false

#define BOARD_W 8
#define BOARD_L 8



//none
#define EMPTY_TILE 0
//white
#define WHITE_KING 1
#define WHITE_QUEEN 2
#define WHITE_ROOK 3
#define WHITE_BISHOP 4
#define WHITE_KNIGHT 5
#define WHITE_PAWN 6

//black
#define BLACK_KING 7
#define BLACK_QUEEN 8
#define BLACK_ROOK 9
#define BLACK_BISHOP 10
#define BLACK_KNIGHT 11
#define	BLACK_PAWN 12




typedef struct Tile{
	long tile;
}Tile;

typedef struct Board{
	long** tiles;
}Board;





Board* set_board(bool color, bool initialized);

Board* alloc_board(Board* board, bool board_initialized);

void set_white(bool color, Board* board);
void set_black(bool color, Board* board);

#endif
