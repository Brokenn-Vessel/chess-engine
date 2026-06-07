#ifndef MOVE_H
#define MOVE_H

#include "types.h"
#include <stdio.h>

/*
          binary move bits                               hexidecimal constants
    
    0000 0000 0000 0000 0011 1111    source square       0x3f
    0000 0000 0000 1111 1100 0000    target square       0xfc0
    0000 0000 1111 0000 0000 0000    piece               0xf000
    0000 1111 0000 0000 0000 0000    promoted piece      0xf0000
    0001 0000 0000 0000 0000 0000    capture flag        0x100000
    0010 0000 0000 0000 0000 0000    double push flag    0x200000
    0100 0000 0000 0000 0000 0000    enpassant flag      0x400000
    1000 0000 0000 0000 0000 0000    castling flag       0x800000

*/

#define getSourceSquare(move) ((move) & 0x3f)
#define getTargetSquare(move) (((move) & 0xfc0) >> 6)
#define getPiece(move) (((move) & 0xf000) >> 12)
#define getPromotedPiece(move) (((move) & 0xf0000) >> 16) 
#define getCaptureFlag(move) (((move) & 0x100000) >> 20) 
#define getDoublePushFlag(move) (((move) & 0x200000) >> 21)
#define getEnpassantFlag(move) (((move) & 0x400000) >> 22) 
#define getCastlingFlag(move) (((move) & 0x800000) >> 23)

#define encodeMove(ss, ts, piece, promotedPiece, capture, doublePush, enpassant, castling) ((ss) | ((ts) << 6) | ((piece) << 12) | ((promotedPiece) << 16) | ((capture) << 20) | ((doublePush) << 21) | ((enpassant) << 22) | ((castling) << 23))

typedef struct {
    int moveList[256] ;
    int count ;
} Moves ;

void addMove(Moves* moveList, int move) ;
void printMove(int move) ;
void printMoveList(Moves* moveList) ;

#endif