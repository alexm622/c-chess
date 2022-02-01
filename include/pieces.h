#ifndef PIECES_H
#define PIECES_H

#include "board.h"

#include <stdbool.h>
#include <stdint.h>
//all possible moves for piece
typedef struct Moves{
	uint8_t* moves;
	uint8_t start; //starting position
	int moves_len; //length of the object
} Moves;

Moves knight_moves(uint8_t location);
Moves bishop_moves(Board* board, uint8_t location);
Moves pawn_moves(Board* board, uint8_t location, bool color);
Moves king_moves(uint8_t location);
Moves queen_moves(Board* board, uint8_t location);
Moves rook_moves(Board* board, uint8_t location);

//checks to see if move is valid
bool is_valid_move(uint8_t start, uint8_t end, Board* board, long piece);
//attempts to make a move
bool make_move(unsigned short start, uint8_t end);
//calculate all possible moves for piece p
Moves calculate_moves(Board* board, uint8_t position, bool color);
//checks if player is in check
bool is_check(Board* board, bool player);

//devise a "hot squares" method for determining check
bool is_checkmate(Board* board, bool player);

//TODO need something to handle pawn promotion

//remove invalid moves
void remove_invalid(Moves *moves, bool color, Board* board);

void free_moves(Moves *moves);
void expand_moves(Moves *moves);
void remove_move(Moves *moves, int index);
#endif
