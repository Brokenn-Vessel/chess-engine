#ifndef BOARD_H
#define BOARD_H

#include "types.h" 
#include "bit_utils.h"
#include "attack_tables.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    u64 bitboards[12] ;
    u64 occupancy[3] ;

    int side ;
    int enpassant ;
    int castling ;
} Board ;

void printBoard(Board* board) ;
void parseFen(Board* board, const char* fen) ;
int isSquareAttacked(Board* board, int square, int side) ;
int pieceAtSquare(Board* board, int square) ;

#endif