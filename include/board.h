#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define COLOR_WHITE true
#define COLOR_BLACK false

#define BOARD_W 8
#define BOARD_L 8

typedef enum TILE{
	//none
	EMPTY = 0,
	//white
	W_KING = 1,
	W_QUEEN = 2,
	W_ROOK = 3,
	W_BISHOP = 4,
	W_KNIGHT = 5,
	W_PAWN = 6,

	//black
	B_KING = 7,
	B_QUEEN = 8,
	B_ROOK = 9,
	B_BISHOP = 10,
	B_KNIGHT = 11,
	B_PAWN = 12


}TILE;

typedef struct Tile{
	TILE tile;
}Tile;

typedef struct Board{
	Tile*** tiles;
}Board;

Board* board;

bool board_initialized = false;

void set_board(bool color);

void alloc_board();

void set_white(bool color);
void set_black(bool color);

#endif
