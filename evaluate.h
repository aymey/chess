#ifndef __EVALUATE_H_
#define __EVALUATE_H_

#include <stddef.h>
#include "board.h"

enum Score {
    King = 100,
    Queen = 90,
    Rook = 50,
    Bishop = 30,
    Knight = 30,
    Pawn = 10
};

typedef struct {
    int start;
    int end;
} Move;

typedef struct {
    Move *array;
    size_t size;
    size_t used;
} Array;

void init_Array(Array *array, size_t size);
void append_Array(Array *array, Move elem);
void free_Array(Array *array);


int (*precompute_data())[8]; // this cannot be best practice???? idk how else to do it
void make_move(int *board, Array moves, int index);
void legal_moves(Board board, Array moves, const int edge_data[64][8]);

#endif // __EVALUATE_H_
