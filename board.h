#ifndef __BOARD_H_
#define __BOARD_H_

#include <raylib.h>

#define BOARD_AMOUNT 8

/* 5 bit id*/
typedef struct {
    /* two left (colour) bits */
    const int White;
    const int Black;

    /* right (type) bits */
    const int None;
    const int King;
    const int Queen;
    const int Rook;
    const int Bishop;
    const int Knight;
    const int Pawn;
} Piece;

typedef struct {
    int board[BOARD_AMOUNT*BOARD_AMOUNT];
    bool Turn;  // white: true (2), black: false (1)
} Board;

Vector2 translate(Vector2 pos);
void draw_board(int width, int height, int board[64]);
void parse_FEN(char *string, int *board);

#endif // __BOARD_H_
