#include "pieces.h"

#include <stdio.h>
#include <stdlib.h>

Moves calculate_moves(Board *board, uint8_t position, bool color) {
  uint8_t piece_y = (position & 0x0F);
  uint8_t piece_x = (position & 0xF0) >> 4;
  printf("pos x: %u \npos y: %u \n", piece_x, piece_y);

  long piece = board->tiles[piece_x][piece_y];

  Moves moves;
  printf("Piece is %ld \n", piece);
  if (piece != 0) {

    piece--;
    piece %= 6;
    printf("Piece is %ld \n", piece);
    switch (piece) {
    case 0:
      moves = king_moves(position);
      break;
    case 1:
      moves = queen_moves(board, position);
      break;
    case 2:
      moves = rook_moves(board, position);
      break;
    case 3:
      moves = bishop_moves(board, position);
      break;
    case 4:
      moves = knight_moves(position);
      break;
    case 5:
      moves = pawn_moves(board, position, color);
      break;
    default:
      moves.moves_len = 0;
      break;
    }
  } else {
    moves.moves_len = 0;
    return moves;
  }
  moves.start = position;

  // TODO do something to rule out moves that do not end check
  // TODO something to valid moves too
  remove_invalid(&moves, color, board);
  return moves;
}
/**
 * @brief remove invalid moves
 *
 * @param moves
 * @param color
 */
void remove_invalid(Moves *moves, bool color, Board *board) {
  for (int i = 0; i < moves->moves_len; i++) {
    uint8_t position = moves->moves[i];
    uint8_t piece_y = (position & 0x0F);
    uint8_t piece_x = (position & 0xF0) >> 4;
    if ((board->tiles[piece_x][piece_y] != 0) &&
        ((((board->tiles[piece_x][piece_y] - 6) > 0) && !color) ||
         (((board->tiles[piece_x][piece_y] - 6) <= 0) && color))) {
      // its trying to take a piece of the same color, not allowed
      for (int j = 0; j < moves->moves_len; j++) {
        if (j > i) {
          moves->moves[j - 1] = moves->moves[j];
        }
      }
      moves->moves =
          realloc(moves->moves, sizeof(uint8_t) * (moves->moves_len - 1));
      moves->moves_len--;
      i--;
    }
  }
}
/**
 * @brief free moves object
 *
 * @param moves
 */
void free_moves(Moves *moves) { free(moves->moves); }
/**
 * @brief increase the number of moves by one
 *
 * @param moves
 */

void expand_moves(Moves *moves) {
  int size = moves->moves_len;

  moves->moves = realloc(moves->moves, (size + 1));
  moves->moves_len++;
}
/**
 * @brief calculate the moves for the king
 *
 * @param position
 * @return Moves
 */
Moves king_moves(uint8_t position) {
  Moves moves;
  moves.moves = malloc(sizeof(unsigned char));
  moves.moves_len = 0;
  moves.start = position;

  uint8_t piece_y = (position & 0x0F);
  uint8_t piece_x = (position & 0xF0) >> 4;
  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      if (piece_x + x < 0 || piece_x + x > 7) {
        break;
      }
      if (piece_y + y < 0 || piece_y + y > 7) {
        continue;
      }

      expand_moves(&moves);
      uint8_t end = (piece_y + y) | ((piece_x + x) << 4);

      moves.moves[moves.moves_len - 1] = end;
    }
  }
  return moves;
}
/**
 * @brief calculate the moves for the bishop
 *
 * @param board
 * @param position
 * @return Moves
 */
Moves bishop_moves(Board *board, uint8_t position) {
  uint8_t piece_y = (position & 0x0F);
  uint8_t piece_x = (position & 0xF0) >> 4;
  Moves moves;
  moves.moves = malloc(sizeof(unsigned char));
  moves.moves_len = 0;

  // up right
  int dist_x = 7 - piece_x;
  int dist_y = 7 - piece_y;
  int iter = (dist_y > dist_x) ? dist_x : dist_y;
  if (iter > 0) {
    for (int i = 1; i < iter; i++) {
      uint8_t end = (piece_y + i) | ((piece_x + i) << 4);
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end;
      if (board->tiles[((end & 0xF0) >> 4)][(end & 0x0F)] != EMPTY_TILE) {
        break;
      }
    }
  }
  // up left
  dist_x = 7 - dist_x;
  iter = (dist_y > dist_x) ? dist_x : dist_y;
  if (iter > 0 && iter < 7) {
    for (int i = 1; i < iter; i++) {
      uint8_t end = (piece_y + i) | ((piece_x - i) << 4);
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end;
      if (board->tiles[((end & 0xF0) >> 4)][(end & 0x0F)] != EMPTY_TILE) {
        break;
      }
    }
  }
  // down left
  dist_y = 7 - dist_y;
  iter = (dist_y > dist_x) ? dist_x : dist_y;
  if (iter > 0 && iter < 7) {
    for (int i = 0; i < iter; i++) {
      uint8_t end = (piece_y - i) | ((piece_x - i) << 4);
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end;
      if (board->tiles[((end & 0xF0) >> 4)][(end & 0x0F)] != EMPTY_TILE) {
        break;
      }
    }
  }
  // down right
  dist_x = 7 - piece_x;
  iter = (dist_y > dist_x) ? dist_x : dist_y;
  if (iter > 0 && iter < 7) {
    for (int i = 0; i < iter; i++) {
      uint8_t end = (piece_y + i) | ((piece_x + i) << 4);
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end;
      if (board->tiles[((end & 0xF0) >> 4)][(end & 0x0F)] != EMPTY_TILE) {
        break;
      }
    }
  }
  return moves;
}
/**
 * @brief return the current possible pawn moves
 *
 * @param board the board
 * @param position the position of the piece
 * @param color true = white, false = black
 * @return Moves
 */
Moves pawn_moves(Board *board, uint8_t position, bool color) {
  Moves moves;
  moves.moves = malloc(sizeof(unsigned char));
  moves.moves_len = 0;
  moves.start = position;
  uint8_t piece_y = (position & 0x0F);
  uint8_t piece_x = (position & 0xF0) >> 4;
  // by default moving down board
  int dy = +1;
  // if white move up
  if (color) {
    dy = 1;
  }
  // move 2 spaces
  if (((position & 0x01) == 0x01) && color) {
    if (board->tiles[piece_x][piece_y + dy + dy] == EMPTY_TILE) {
      int temp_dy = dy + dy;

      uint8_t end_pos = (piece_y + temp_dy) | ((piece_x) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
  } else if (((position & 0x06) == 0x06) && !color) {
    if (board->tiles[piece_x][piece_y + dy + dy] == EMPTY_TILE) {
      int temp_dy = dy + dy;

      uint8_t end_pos = (piece_y + temp_dy) | ((piece_x) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
  }

  int start = (piece_x - 1 < 0) ? 0 : -1;
  int end = (piece_x + 1 > 7) ? 0 : 1;
  for (int dx = start; dx <= end; dx++) {
    if (board->tiles[piece_x + dx][piece_y + dy] != EMPTY_TILE) {
      if (dx != 0) {

        uint8_t end_pos = (piece_y + dy) | ((piece_x + dx) << 4);

        expand_moves(&moves);
        moves.moves[moves.moves_len - 1] = end_pos;
      }
    } else {
      if (dx == 0) {

        uint8_t end_pos = (piece_y + dy) | ((piece_x) << 4);

        expand_moves(&moves);
        moves.moves[moves.moves_len - 1] = end_pos;
      }
    }
  }
  return moves;
}
/**
 * @brief calculate the moves for the knight
 *
 * @param position
 * @return Moves
 */
Moves knight_moves(uint8_t position) {
  Moves moves;
  moves.moves = malloc(sizeof(unsigned char));
  moves.start = position;
  moves.moves_len = 0;

  uint8_t piece_y = (position & 0x0F);
  uint8_t piece_x = (position & 0xF0) >> 4;
  // vertical
  if (piece_x >= 1) {
    // up left
    if (piece_y < 7 - 2) {
      uint8_t end_pos = (piece_y + 2) | ((piece_x - 1) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
    // down left
    if (piece_y > 2) {
      uint8_t end_pos = (piece_y - 2) | ((piece_x - 1) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
  }
  // vertical
  if (piece_x < 7) {
    // up right
    if (piece_y < 7 - 2) {
      uint8_t end_pos = (piece_y + 2) | ((piece_x + 1) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
    // down right
    if (piece_y > 3) {
      uint8_t end_pos = (piece_y - 2) | ((piece_x + 1) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
  }

  // horizontal
  if (piece_y >= 1) {
    // right down
    if (piece_x < 7 - 2) {
      uint8_t end_pos = (piece_y - 1) | ((piece_x + 2) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
    // left down
    if (piece_x > 2) {
      uint8_t end_pos = (piece_y - 1) | ((piece_x - 2) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
  }
  // vertical
  if (piece_y <= 7 - 2) {
    // right up
    if (piece_x < 7 - 2) {
      uint8_t end_pos = (piece_y + 1) | ((piece_x + 2) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
    // left down
    if (piece_x > 2) {
      uint8_t end_pos = (piece_y + 1) | ((piece_x - 2) << 4);

      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = end_pos;
    }
  }

  // left and right
  return moves;
}
/**
 * @brief calculate the moves for the rook
 *
 * @param board
 * @param position
 * @return Moves
 */
Moves rook_moves(Board *board, uint8_t position) {
  uint8_t piece_y = (position & 0x0F);
  uint8_t piece_x = (position & 0xF0) >> 4;
  Moves moves;
  moves.moves = malloc(sizeof(unsigned char));
  moves.moves_len = 0;
  uint8_t dist_y_up = 7 - piece_y - 1;
  uint8_t dist_y_down = 7 - dist_y_up;
  uint8_t dist_x_right = 7 - piece_x - 1;
  uint8_t dist_x_left = 7 - dist_x_right;
  bool breaking = false;
  for (int vert = 0; vert < dist_y_up; vert++) {
    if ((board->tiles[piece_y + vert][piece_x] != EMPTY_TILE)) {
      breaking = true;
    }

    uint8_t end_pos = (piece_y + vert) | ((piece_x) << 4);

    expand_moves(&moves);
    moves.moves[moves.moves_len - 1] = end_pos;
    if (breaking) {
      breaking = false;
      break;
    }
  }
  for (int vert = 0; vert > -1 * (dist_y_down); vert--) {
    if ((board->tiles[piece_y + vert][piece_x] != EMPTY_TILE)) {
      breaking = true;
    }

    uint8_t end_pos = (piece_y + vert) | ((piece_x) << 4);

    expand_moves(&moves);
    moves.moves[moves.moves_len - 1] = end_pos;
    if (breaking) {
      breaking = false;
      break;
    }
  }
  for (int horizontal = 1; horizontal < dist_x_right; horizontal++) {
    if ((board->tiles[piece_y][piece_x + horizontal] != EMPTY_TILE)) {
      breaking = true;
    }

    uint8_t end_pos = (piece_y) | ((piece_x + horizontal) << 4);

    expand_moves(&moves);
    moves.moves[moves.moves_len - 1] = end_pos;
    if (breaking) {
      breaking = false;
      break;
    }
  }
  for (int horizontal = 1; horizontal > -1 * (dist_x_left); horizontal--) {
    if ((board->tiles[piece_y][piece_x + horizontal] != EMPTY_TILE)) {
      breaking = true;
    }

    uint8_t end_pos = (piece_y) | ((piece_x + horizontal) << 4);

    expand_moves(&moves);
    moves.moves[moves.moves_len - 1] = end_pos;
    if (breaking) {
      break;
    }
  }
  return moves;
}
/**
 * @brief calculate the moves for the queen
 *
 * @param board
 * @param location
 * @return Moves
 */
Moves queen_moves(Board *board, uint8_t location) {
  Moves move_rook = rook_moves(board, location);
  Moves move_bishop = bishop_moves(board, location);
  Moves moves;
  moves.moves = malloc(sizeof(unsigned char));
  moves.moves_len = 0;
  for (int i = 0; i < move_rook.moves_len; i++) {
    expand_moves(&moves);
    moves.moves[moves.moves_len - 1] = move_rook.moves[i];
  }
  for (int i = 0; i < move_bishop.moves_len; i++) {
    expand_moves(&moves);
    moves.moves[moves.moves_len - 1] = move_bishop.moves[i];
  }

  free(move_rook.moves);
  free(move_bishop.moves);
  return moves;
}
