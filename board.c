#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include <string.h>

#include "board.h"

#define BOARD_AMOUNT 8
#define BOARD_OFFSET 10
#define CONTROL_WIDTH 256

const Color LIGHTSQ     = {241, 217, 192, 255};
const Color DARKSQ      = {169, 122, 101, 255};

Piece piece = {
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

void draw_board(int width, int height, int board[64]) {
    /* board display */
    int length = fmin(width - CONTROL_WIDTH, height) / BOARD_AMOUNT;
    for(int i = 0; i < BOARD_AMOUNT; i++) {
        for(int j = 0; j < BOARD_AMOUNT; j++) {
            DrawRectangle(length*j, length*i, length, length, ((i+j) % 2) ? DARKSQ : LIGHTSQ);
        }
    }

    /* draw FEN */
    Texture2D tile_piece = LoadTexture("./pieces/dk.png");
    for(int i = 0; i < BOARD_AMOUNT*BOARD_AMOUNT; i++) {
        switch(board[i]) {
            case 16 | 6: // piece.White | piece.Pawn
                tile_piece = LoadTexture("./pieces/lp.png");
                break;
            case 8 | 6: // piece.Black | piece.Pawn
                tile_piece = LoadTexture("./pieces/dp.png");
                break;
            case 16 | 3: // piece.White | piece.Rook
                tile_piece = LoadTexture("./pieces/lr.png");
                break;
            case 8 | 3: // piece.Black | piece.Rook
                tile_piece = LoadTexture("./pieces/dr.png");
                break;
            case 16 | 4: // piece.White | piece.Bishop
                tile_piece = LoadTexture("./pieces/lb.png");
                break;
            case 8 | 4: // piece.Black | piece.Bishop
                tile_piece = LoadTexture("./pieces/db.png");
                break;
            case 16 | 5: // piece.White | piece.Knight
                tile_piece = LoadTexture("./pieces/ln.png");
                break;
            case 8 | 5: // piece.Black | piece.Knight
                tile_piece = LoadTexture("./pieces/dn.png");
                break;
            case 16 | 2: // piece.White | piece.Queen
                tile_piece = LoadTexture("./pieces/lq.png");
                break;
            case 8 | 2: // piece.Black | piece.Queen
                tile_piece = LoadTexture("./pieces/dq.png");
                break;
            case 16 | 1: // piece.White | piece.King
                tile_piece = LoadTexture("./pieces/lk.png");
                break;
            case 8 | 1: // piece.Black | piece.King
                tile_piece = LoadTexture("./pieces/dk.png");
                break;
            case 0: // piece.None
            default:
                continue;
        }
        Vector2 test = {(i % 8)*length, (i/8)*length};
        DrawTextureEx(tile_piece, test, 0, length/(64.0*8*2), RAYWHITE);
    }
}

void parse_FEN(char *FEN, int *board) {
    printf("reading FEN: \"%s\"\n", FEN);

    // clear board
    for(int i = 0; i < BOARD_AMOUNT*BOARD_AMOUNT; i++)
        board[i] = piece.None;

    int tile = 0;
    for(int i = 0; i < strlen(FEN); i++) {
        switch(FEN[i]) {
            case '/':
                tile -= (tile % 8) - 1;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                tile += FEN[i] - 48; // convert FEN number to dec, ascii sequential order from 48
                break;
            case 'K':
                board[tile++] = piece.White | piece.King;
                break;
            case 'k':
                board[tile++] = piece.Black | piece.King;
                break;
            case 'Q':
                board[tile++] = piece.White | piece.Queen;
                break;
            case 'q':
                board[tile++] = piece.Black | piece.Queen;
                break;
            case 'R':
                board[tile++] = piece.White | piece.Rook;
                break;
            case 'r':
                board[tile++] = piece.Black | piece.Rook;
                break;
            case 'B':
                board[tile++] = piece.White | piece.Bishop;
                break;
            case 'b':
                board[tile++] = piece.Black | piece.Bishop;
                break;
            case 'N':
                board[tile++] = piece.White | piece.Knight;
                break;
            case 'n':
                board[tile++] = piece.Black | piece.Knight;
                break;
            case 'P':
                board[tile++] = piece.White | piece.Pawn;
                break;
            case 'p':
                board[tile++] = piece.Black | piece.Pawn;
                break;
            case ' ':
                goto exitt; //temporary
            default:
                break;
        }
    }
    exitt: // temporary


    printf("read FEN\n");
}
