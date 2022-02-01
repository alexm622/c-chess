#ifndef DEBUG_H
#define DEBUG_H

#include "pieces.h"

void print_moves(Moves moves);
void printf_moves(Moves moves);
char* convert_to_coordinates(uint8_t  position);
void printf_board(Board* board);
#endif
