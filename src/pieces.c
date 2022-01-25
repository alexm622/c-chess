#include "pieces.h"

#include <stdlib.h>

Moves calculate_moves(Board *board, short position, bool color) {
  short piece_x = (position ^ 0x00FF);
  short piece_y = (position ^ 0xFF00) >> 8;

  long piece = board->tiles[piece_x][piece_y];

  Moves moves;

  if (piece != 0) {
    piece--;
    piece %= 6;
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
      moves = knight_moves(board, position);
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
  }

  // TODO do something to rule out moves that do not end check

  return moves;
}

Moves king_moves(short position) {
  Moves moves;
  moves.moves_len = 0;

  short piece_y = (position ^ 0x00FF);
  short piece_x = (position ^ 0xFF00) >> 8;
  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      if (piece_x + x < 0 || piece_x + x > 7) {
        break;
      }
      if (piece_y + y < 0 || piece_y + y > 7) {
        continue;
      }
      Move *move = malloc(sizeof(Move));
      move->start = position;
      expand_moves(&moves);
      short end = (piece_y + y) | ((piece_x + x) << 8);
      move->end = end;
      moves.moves[moves.moves_len - 1] = move;
    }
  }
  return moves;
}

Moves bishop_moves(Board *board, short position) {
  short piece_y = (position ^ 0x00FF);
  short piece_x = (position ^ 0xFF00) >> 8;
  Moves moves;
  moves.moves_len = 0;
  // calculate the 2 right diagonals
  bool positive = false, negative = false;
  short dist = (7 - piece_x < 7 - piece_y) ? 7 - piece_x : 7 - piece_y;
  for (int i = 0; i < dist; i++) {
    if (positive) {
      // do nothing
    } else if (board->tiles[piece_x + i][piece_y + i] != EMPTY_TILE) {
      positive = true;
      Move *move = malloc(sizeof(Move));
      move->start = position;
      short end = (piece_y + i) | ((piece_x + i) << 8);
      move->end = end;
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = move;
    } else {
      Move *move = malloc(sizeof(Move));
      move->start = position;
      short end = (piece_y + i) | ((piece_x + i) << 8);
      move->end = end;
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = move;
    }
    if (negative) {
      // do nothing
    } else if (board->tiles[piece_x + i][piece_y - i] != EMPTY_TILE) {
      negative = true;
      Move *move = malloc(sizeof(Move));
      move->start = position;
      short end = (piece_y - i) | ((piece_x + i) << 8);
      move->end = end;
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = move;
    } else {
      Move *move = malloc(sizeof(Move));
      move->start = position;
      short end = (piece_y - i) | ((piece_x + i) << 8);
      move->end = end;
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = move;
    }
  }
  // calculate the 2 left diagonals
  positive = false, negative = false;
  dist = (piece_x < piece_y) ? piece_x : piece_y;
  for (int i = 0; i < dist; i++) {
    if (positive) {
      // do nothing
    } else if (board->tiles[piece_x - i][piece_y + i] != EMPTY_TILE) {
      positive = true;
      Move *move = malloc(sizeof(Move));
      move->start = position;
      short end = (piece_y + i) | ((piece_x - i) << 8);
      move->end = end;
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = move;
    } else {
      Move *move = malloc(sizeof(Move));
      move->start = position;
      short end = (piece_y + i) | ((piece_x - i) << 8);
      move->end = end;
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = move;
    }
    if (negative) {
      // do nothing
    } else if (board->tiles[piece_x - i][piece_y - i] != EMPTY_TILE) {
      negative = true;
      Move *move = malloc(sizeof(Move));
      move->start = position;
      short end = (piece_y - i) | ((piece_x - i) << 8);
      move->end = end;
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = move;
    } else {
      Move *move = malloc(sizeof(Move));
      move->start = position;
      short end = (piece_y - i) | ((piece_x - i) << 8);
      move->end = end;
      expand_moves(&moves);
      moves.moves[moves.moves_len - 1] = move;
    }
  }
  return moves;
}

Moves pawn_moves(Board *board, short position, bool color) {
  Moves moves;
  moves.moves_len = 0;
  short piece_y = (position ^ 0x00FF);
  short piece_x = (position ^ 0xFF00) >> 8;
  int dy = -1;
  if (color) {
    dy = 1;
  }
  short start = (piece_x - 1 < 0) ? 0 : -1;
  short end = (piece_x + 1 > 7) ? 0 : 1;
  for (int dx = start; dx <= end; dx++) {
    if (board->tiles[piece_x + dx][piece_y + dy] != EMPTY_TILE) {
      if (dx != 0) {
        Move *move = malloc(sizeof(Move));
        move->start = position;
        short end_pos = (piece_y + dy) | ((piece_x + dx) << 8);
        move->end = end_pos;
        expand_moves(&moves);
        moves.moves[moves.moves_len - 1] = move;
      }
    } else {
      if (dx == 0) {
        Move *move = malloc(sizeof(Move));
        move->start = position;
        short end_pos = (piece_y + dx) | ((piece_x) << 8);
        move->end = end_pos;
        expand_moves(&moves);
        moves.moves[moves.moves_len - 1] = move;
      }
    }
  }
  return moves;
}

Moves queen_moves(Board *board, short location) {
  Moves move_rook = rook_moves(board, location);
  Moves move_bishop = bishop_moves(board, location);
  Moves moves;
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

void expand_moves(Moves *moves) {
  int size = moves->moves_len;

  moves->moves = realloc(moves->moves, sizeof(Move *) * (size + 1));
  moves->moves_len++;
}
