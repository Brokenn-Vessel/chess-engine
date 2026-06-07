#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "board.h"
#include "types.h"
#include "move.h"
#include "attack_tables.h"
#include "bit_utils.h"

void generateMoves(Moves* moveList, Board* board) ;

#endif