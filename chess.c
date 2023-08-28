#include <raylib.h>
#include <string.h>

#include "evaluate.h"
#include "board.h"

const Color BACKGROUND  = {031, 031, 031, 255};


// TODO: Function to convert mouse press coordinates to grid coordinates

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, "chess");

    int screen_width = 0;
    int screen_height = 0;

    SetTargetFPS(1);

    /* internal board */
    Board board = {
        .Turn = 2 // white: 2, black: 1
    };
    const char *starting_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    parse_FEN(starting_FEN, &board);

    for(int i = 0; i < (64); i++) {
        printf("%d, ", board.board[i]);
    }
    printf("\n");

    while (!WindowShouldClose()) {
        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();
        BeginDrawing();
            ClearBackground(BACKGROUND);
            draw_board(screen_width, screen_height, board.board);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
