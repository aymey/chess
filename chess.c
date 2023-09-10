#include <raylib.h>
#include <stdio.h>
#include <math.h>

#include "evaluate.h"
#include "board.h"

const Color BACKGROUND  = {031, 031, 031, 255};

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, "chess");
    // SetTargetFPS(3);

    /* setup */
    Board board;
    const int (*edge_data)[8] = precompute_data();
    Array moves;
    init_Array(&moves, 128);
    const char *starting_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    parse_FEN(starting_FEN, &board.board);

    int screen_width = 0;
    int screen_height = 0;
    while (!WindowShouldClose()) {
        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();

        legal_moves(board, moves, edge_data);
        // make_move(&board.board, moves, 0);
        board.Turn = !board.Turn;

        input_handler(&board.board);

        BeginDrawing();
            ClearBackground(BACKGROUND);
            draw_board(screen_width, screen_height, board.board);
        EndDrawing();
    }

    free_Array(&moves);
    board_free();
    CloseWindow();
    return 0;
}
