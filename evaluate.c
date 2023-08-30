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

void clear_Array(Array *array) {
    array->used = 0;
    array->size = 128;
    array->array = realloc(array->array, array->size * sizeof(Move));
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

        // north = rank;
        // east = (BOARD_AMOUNT - 1) - file;
        // south = (BOARD_AMOUNT - 1) - rank;
        // west = file;
        /* why are the cardinal directions backwards???? */
        south = rank;
        west = (BOARD_AMOUNT - 1) - file;
        north = (BOARD_AMOUNT - 1) - rank;
        east = file;
        north_east = fmin(north, east);
        south_east = fmin(south, east);
        south_west = fmin(south, west);
        north_west = fmin(north, west);


        // theres gotta be a better way
        edge_data[i][0] = north;
        edge_data[i][1] = south;
        edge_data[i][2] = east;
        edge_data[i][3] = west;
        edge_data[i][4] = north_east;
        edge_data[i][5] = south_east;
        edge_data[i][6] = north_west;
        edge_data[i][7] = south_west;
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

bool is_pawn_piece(int piece) {
    bool non_sliding = false;
    const int PAWN = 6;
    switch(piece) {
        case 6:
            non_sliding = true;
            break;
        default:
            break;
    }
    return non_sliding;
}

void generate_sliding_moves(Board board, Array moves, int pos, int piece, const int edge_data[64][8]) {
    const int DirectionOffsets[8] = {8, -8, 1, -1, 7, -7, 9, -9};

    enum sliding_pieces {ROOK = 3, BISHOP = 4};
    int dir_offset = piece == BISHOP ? 4 : 0;
    int dir_bound = piece == ROOK ? 4 : 8;


    for(int direction = dir_offset; direction < dir_bound; direction++) {
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
            printf("possible sliding move for %s: %d To %d\n", board.Turn ? "White" : "Black", move.start, move.end);

            // take piece and dont continue moving forward
            if(board.board[target] >> 3 != board.Turn + 1)
                break;
        }
    }
}

void generate_pawn_moves(Board board, Array moves, int pos, int piece, const int edge_data[64][8]) {
    const int DirectionOffsets[3] = {7, 8, 9};
    const int turn = board.Turn == false;
    for(int direction = 0; direction < 3; direction++) {
        int target = pos + (turn ? +1 : -1) * DirectionOffsets[direction]; // opposite direction for black pawns
        // block if friendly piece
        if(board.board[target] >> 3 == board.Turn + 1)
            continue;
        // pawn take rules
        if((direction != 1 && board.board[target] == 0) || (direction == 1 && board.board[target]!= 0))
            continue;
        // edge case (get it?)
        if((direction == 0 && edge_data[pos][2]) == 0 || ((direction == 2 && edge_data[pos][3] == 0)))
            continue;

        Move move = {
            .start = pos,
            .end = target
        };
        append_Array(&moves, move);
        printf("possible non sliding move for %s: %d To %d\n", board.Turn ? "White" : "Black", move.start, move.end);
    }
}

void make_move(int *board, Array moves, int index) {
    board[moves.array[index].end] = board[moves.array[index].start];
    board[moves.array[index].start] = piece_id.None;
}

void legal_moves(Board board, Array moves, const int edge_data[64][8]) {
    clear_Array(&moves);
    for(int i = 0; i < BOARD_AMOUNT*BOARD_AMOUNT; i++) {
        int piece = board.board[i];
        int piece_type = piece - 8*(board.Turn + 1);
        // dont calculate moves for friendly pieces
        if(piece >> 3 != board.Turn + 1)
            continue;
        if(is_pawn_piece(piece_type))
            generate_pawn_moves(board, moves, i, piece, edge_data);
        else if(is_sliding_piece(piece_type))
           generate_sliding_moves(board, moves, i, piece_type, edge_data);
    }
}
