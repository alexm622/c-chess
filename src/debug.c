#include "debug.h"



#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief print all the moves with curses
 * 
 * @param moves 
 */
void print_moves(Moves moves) {
  int cursor_y = 0;
  int cursor_x = 0;
  for (int i = 0; i < moves.moves_len; i++) {
    char *pos_start = convert_to_coordinates(moves.start);
    char *pos_end = convert_to_coordinates(moves.moves[i]);
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
/**
 * @brief printf all of the moves
 * 
 * @param moves 
 */
void printf_moves(Moves moves) {
  int cursor_y = 0;
  int cursor_x = 0;
  for (int i = 0; i < moves.moves_len; i++) {
    char *pos_start = convert_to_coordinates(moves.start);
    char *pos_end = convert_to_coordinates(moves.moves[i]);
    char *move_num = calloc(sizeof(char), 20);
    sprintf(move_num, "Move number %d:\n", i);
    printf("%s",move_num);
    cursor_x += strlen(move_num);
    char* move = calloc(sizeof(char), 20);
    sprintf(move, "%s -> %s  \n", pos_start, pos_end);
    printf("%s",move);
    free(move);
    free(pos_end);
    free(pos_start);
    free(move_num);
  }
}
/**
 * @brief conver the integer representation of the character to the readable coordinates
 * 
 * @param position 
 * @return char* 
 */
char *convert_to_coordinates(uint8_t position) {
  char *move = malloc(sizeof(char) *3);
  char move_y, move_x;
  uint8_t piece_y = (position & 0x0F);
  uint8_t piece_x = (position & 0xF0) >> 4;
  char horizontal[] = "abcdefgh";
  char vert[] = "12345678";
  move_y = vert[piece_y];
  move_x = horizontal[piece_x];
  char* str = calloc(sizeof(char), 3);
  str[0] = move_x;
  str[1] = move_y;
  sprintf(move, "%s", str);
  free(str);
  return move;
}
