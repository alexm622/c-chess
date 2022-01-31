#ifndef PIECES_H
#define PIECES_H

#include "board.h"

#include <stdbool.h>
//a single move
typedef struct Move {
	unsigned short start; //a 16 bit representation of the move
	unsigned short end;
} Move;
//all possible moves for piece
typedef struct Moves{
	Move** moves;
	int moves_len;
} Moves;

Moves knight_moves(Board* board, unsigned short location);
Moves bishop_moves(Board* board, unsigned short location);
Moves pawn_moves(Board* board, unsigned short location, bool color);
Moves king_moves(unsigned short location);
Moves queen_moves(Board* board, unsigned short location);
Moves rook_moves(Board* board, unsigned short location);

//checks to see if move is valid
bool is_valid_move(Move move, Board* board, long piece);
//attempts to make a move
bool make_move(unsigned short start, unsigned short end);
//calculate all possible moves for piece p
Moves calculate_moves(Board* board, unsigned short position, bool color);
//checks if player is in check
bool is_check(Board* board, bool player);

//devise a "hot squares" method for determining check
bool is_checkmate(Board* board, bool player);

//TODO need something to handle pawn promotion

//remove invalid moves
void remove_invalid(Moves* moves, bool color);

void free_moves(Moves moves);
void expand_moves(Moves *moves);
#endif
