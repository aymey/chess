#include <raylib.h>
#include "evaluate.h"
#include "board.h"

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

Score score = {
    .King = 100,
    .Queen = 90,
    .Rook = 50,
    .Bishop = 30,
    .Knight = 30,
    .Pawn = 10
};

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

int generate_sliding_moves(int start) {
    int end = start;
    // for()
}

void legal_moves(Board *board) {
    for(int i = 0; i < BOARD_AMOUNT*BOARD_AMOUNT; i++) {
        int piece = board->board[i];
        if(piece >> 3 != board->Turn)
            continue;
        // if(is_sliding_piece(piece))
           // generate_sliding_moves(i);
    }
}
