#include <raylib.h>
#include <string.h>

#include "board.h"

const Color BACKGROUND  = {031, 031, 031, 255};

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, "chess");

    int screen_width = 0;
    int screen_height = 0;

    SetTargetFPS(1);

    /* internal board */
    int board[64];
    const char *starting_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    parse_FEN(starting_FEN, &board);

    for(int i = 0; i < (64); i++) {
        printf("%d, ", board[i]);
    }
    printf("\n");

    while (!WindowShouldClose()) {

        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();
        BeginDrawing();
            draw_board(screen_width, screen_height, board); // TODO: only redraw if mb pressed or something
            ClearBackground(BACKGROUND);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
