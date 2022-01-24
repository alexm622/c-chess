#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define IS_WHITE true
#define IS_BLACK false

#define BOARD_W 8
#define BOARD_L 8



typedef enum {
	//none
	EMPTY_TILE = 0,
	//white
	WHITE_KING = 1,
	WHITE_QUEEN = 2,
	WHITE_ROOK = 3,
	WHITE_BISHOP = 4,
	WHITE_KNIGHT = 5,
	WHITE_PAWN = 6,

	//black
	BLACK_KING = 7,
	BLACK_QUEEN = 8,
	BLACK_ROOK = 9,
	BLACK_BISHOP = 10,
	BLACK_KNIGHT = 11,
	BLACK_PAWN = 12


}TILE;

typedef struct Tile{
	TILE tile;
}Tile;

typedef struct Board{
	Tile*** tiles;
}Board;





Board* set_board(bool color, bool initialized);

Board* alloc_board(Board* board, bool board_initialized);

void set_white(bool color, Board* board);
void set_black(bool color, Board* board);

#endif
