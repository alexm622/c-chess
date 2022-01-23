#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <stddef.h>
#include <wchar.h>

const wchar_t* W_KING = L"\x2654";
const wchar_t* W_QUEEN = L"\x2655";
const wchar_t* W_ROOK = L"\x2656";
const wchar_t* W_BISHOP = L"\x2657";
const wchar_t* W_KNIGHT = L"\x2658";
const wchar_t* W_PAWN = L"\x2659";
const wchar_t* B_KING = L"\x265A";
const wchar_t* B_QUEEN = L"\x265B";
const wchar_t* B_ROOK = L"\x265C";
const wchar_t* B_BISHOP = L"\x265D";
const wchar_t* B_KNIGHT = L"\x265E";
const wchar_t* B_PAWN = L"\x265F";

const wchar_t* EMPTY = L"\x0020";

const wchar_t** charset;

int charset_size = 13;

#endif
