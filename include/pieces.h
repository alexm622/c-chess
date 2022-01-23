#ifndef PIECES_H
#define PIECES_H

#include "board.h"

#include <stdbool.h>
//a piece
typedef struct Piece{
	int x_mov;
	int y_mov;
	int posx;
	int posy;
	bool xor_or_and;
	bool limit;
	bool is_pawn;
	TILE Piece;
	bool color; 
} Piece;
//a single move
typedef struct Move {
	char* start;
	char* end;
} Move;
//all possible moves for piece
typedef struct Moves{
	Move** moves;
	int moves_len;
} Moves;



//checks to see if move is valid
bool is_valid_move(Move move, Board board);
//attempts to make a move
bool make_move(char* start, char* end);
//calculate all possible moves for piece p
Moves calculate_moves(Piece p);
//checks if player is in check
bool is_check(Board board, bool player);
//tests for check state change for Move move
bool changes_check(Board board, bool is_check, Move move);
//turn tile enum into Piece type
Piece get_piece(Board board, int x, int y);

#endif
