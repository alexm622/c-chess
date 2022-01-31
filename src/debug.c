#include "debug.h"

#include <curses.h>
#include <stdlib.h>
#include <string.h>

void print_moves(Moves moves) {
  int cursor_y = 0;
  int cursor_x = 0;
  for (int i = 0; i < moves.moves_len; i++) {
    char *pos_start = convert_to_coordinates(moves.moves[i]->start);
    char *pos_end = convert_to_coordinates(moves.moves[i]->start);
    char *move_num = "";
    sprintf(move_num, "Move number %d:", i);
    mvaddstr(cursor_y, cursor_x, move_num);
    cursor_x += strlen(move_num);
    char *move = "";
    sprintf(move, "%s -> %s", pos_start, pos_end);
    mvaddstr(cursor_y, cursor_x, move);
    free(move);
    free(pos_end);
    free(pos_start);
    free(move_num);
  }
}

char *convert_to_coordinates(short position) {
  char *move = malloc(sizeof(char) * 3);
  char move_y, move_x;
  short piece_x = (position ^ 0x00FF);
  short piece_y = (position ^ 0xFF00) >> 8;
  char vert[] = "abcdefgh";
  char horizontal[] = "12345678";
  move_y = vert[piece_y];
  move_x = horizontal[piece_x];
  sprintf(move, "%s%s", &move_x, &move_y);
  return move;
}
