#ifndef SEARCH_H
#define SEARCH_H

#include "types.h"
#include "board.h"
#include "evaluation.h"
#include "move.h"
#include "movegen.h"
#include "makemove.h"

extern int bestMove ;

int negamax(Board* board, int depth, int alpha, int beta, int* bestMove) ;

#endif