#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "evaluate.h"
#include "board.h"

void init_Array(Array *array, size_t size) {
    array->array = malloc(size * sizeof(Move));
    array->size = size;
    array->used = 0;
}

void append_Array(Array *array, Move elem) {
    if(array->size == array->used) {
        array->size *= 2;
        array->array = realloc(array->array, array->size * sizeof(Move));
    }
    array->array[array->used++] = elem;
}

void free_Array(Array *array) {
    free(array->array);
    array->array = NULL;
    array->size = 0;
    array->used = 0;
}

Piece piece_id = {
    .White  = 16,
    .Black  = 8,

    .None   = 0,
    .King   = 1,
    .Queen  = 2,
    .Rook   = 3,
    .Bishop = 4,
    .Knight = 5,
    .Pawn   = 6
};

const int DirectionOffsets[8] = {8, -8, 1, -1, 7, -7, 9, -9};

int (*precompute_data())[8] {
    static int edge_data[BOARD_AMOUNT*BOARD_AMOUNT][8];
    int north = 0;
    int east = 0;
    int south = 0;
    int west = 0;
    int north_east = 0;
    int south_east = 0;
    int south_west = 0;
    int north_west = 0;
    for(int i = 0; i < BOARD_AMOUNT*BOARD_AMOUNT; i++) {
        int file = i % BOARD_AMOUNT;
        int rank = i / BOARD_AMOUNT;

        north = rank;
        east = (BOARD_AMOUNT - 1) - file;
        south = (BOARD_AMOUNT - 1) - rank;
        west = file;
        north_east = fmin(north, east);
        south_east = fmin(south, east);
        south_west = fmin(south, west);
        north_west = fmin(north, west);


        // theres gotta be a better way
        edge_data[i][0] = north;
        edge_data[i][1] = east;
        edge_data[i][2] = south;
        edge_data[i][3] = west;
        edge_data[i][4] = north_east;
        edge_data[i][5] = south_east;
        edge_data[i][6] = south_west;
        edge_data[i][7] = north_west;
    }
    return edge_data;
}

bool is_sliding_piece(int piece) {
    bool sliding = false;
    enum sliding_pieces {QUEEN = 2, ROOK = 3, BISHOP = 4}; // piece_id.(...)
    switch (piece) {
        case QUEEN:
        case ROOK:
        case BISHOP:
            sliding = true;
            break;
        default:
            break;
    }
    return sliding;
}

void generate_sliding_moves(Board board, Array moves, int pos, int piece, const int edge_data[64][8]) {
    for(int direction = 0; direction < 8; direction++) {
        for(int i = 0; i < edge_data[pos][direction]; i++) {
            int target = pos + DirectionOffsets[direction]*(i+1);
            // block if friendly piece
            if(board.board[target] >> 3 == board.Turn + 1)
                break;

            Move move = {
                .start = pos,
                .end = target
            };
            append_Array(&moves, move);

            // take piece and dont continue moving forward
            if(board.board[target] >> 3 != board.Turn + 1)
                break;
        }
    }
}

void legal_moves(Board board, Array moves, const int edge_data[64][8]) {
    for(int i = 0; i < BOARD_AMOUNT*BOARD_AMOUNT; i++) {
        int piece = board.board[i];
        // dont calculate moves fro friendly pieces
        if(piece >> 3 != board.Turn + 1)
            continue;
        if(is_sliding_piece(piece))
           generate_sliding_moves(board, moves, i, piece, edge_data);
    }
}
