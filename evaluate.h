#ifndef __EVALUATE_H_
#define __EVALUATE_H_

#include "board.h"

typedef struct {
    const int King;
    const int Queen;
    const int Rook;
    const int Bishop;
    const int Knight;
    const int Pawn;
} Score;

void legal_moves(Board *board);

#endif // __EVALUATE_H_
