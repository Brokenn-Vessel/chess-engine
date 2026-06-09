#ifndef EVALUATION_H
#define EVALUATION_H

#include "types.h"
#include "board.h"

extern int materialScore[12] ;
extern const int pawnScore[64] ;
extern const int knightScore[64] ;
extern const int bishopScore[64] ;
extern const int rookScore[64] ;
extern const int kingScore[64] ;
extern const int mirror[64] ;

int evaluate(Board* board) ;

#endif