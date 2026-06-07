#ifndef MAKE_MOVE_H
#define MAKE_MOVE_H

#include "board.h"
#include "move.h"
#include "types.h"

#define copy_board() u64 bitboards_copy[12], occupancy_copy[3] ;                                                      \
                     int side_copy, castling_copy, enpassant_copy ;                                                   \
                     memcpy(bitboards_copy, board->bitboards, sizeof(board->bitboards)) ;                             \
                     memcpy(occupancy_copy, board->occupancy, sizeof(board->occupancy)) ;                             \
                     side_copy = board->side ; castling_copy = board->castling ; enpassant_copy = board->enpassant    \

#define restore_board() memcpy(board->bitboards, bitboards_copy, sizeof(bitboards_copy)) ;                           \
                        memcpy(board->occupancy, occupancy_copy, sizeof(occupancy_copy)) ;                           \
                        board->side = side_copy, board->castling = castling_copy, board->enpassant = enpassant_copy  \

int makeMove(Board* board, int move, int move_type) ;
int isLegal(Moves* moveList, int ss, int ts) ;
#endif