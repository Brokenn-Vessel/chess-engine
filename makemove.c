#include "makemove.h"

int makeMove(Board* board, int move, int move_type) {

    if(move_type == allMoves) {

        copy_board() ;

        int source = getSourceSquare(move) ;
        int target = getTargetSquare(move) ;
        int piece = getPiece(move) ;
        int promoted = getPromotedPiece(move) ;
        int capture = getCaptureFlag(move) ;
        int double_push = getDoublePushFlag(move) ;
        int enpassant = getEnpassantFlag(move) ;
        int castling = getCastlingFlag(move) ;

        pop_bit(board->bitboards[piece], source) ;
        set_bit(board->bitboards[piece], target) ;

        //Handling capture
        if(capture) {

            int start, end ;

            if(board->side == WHITE) {
                start = p ; 
                end = k ;
            }
            else {
                start = P ;
                end = K ;
            }

            for(int bb_piece = start ; bb_piece <= end ; bb_piece++) {

                if(get_bit(board->bitboards[bb_piece], target)) {

                    pop_bit(board->bitboards[bb_piece], target) ;
                    break ;

                }

            }

        }

        //Handle pawn promotions
        if(promoted) {

            pop_bit(board->bitboards[(board->side == WHITE) ? P : p], target) ;

            set_bit(board->bitboards[promoted], target) ;

        }

        //enpassant handling
        if(enpassant) {

            (board->side == WHITE) ? pop_bit(board->bitboards[p], target + 8) : pop_bit(board->bitboards[P], target - 8) ;

        }

        board->enpassant = nsq ;

        //Double pushes
        if(double_push) {

            (board->side == WHITE) ? (board->enpassant = target + 8) : (board->enpassant = target - 8) ;

        }


        //Handle Castling
        if(castling) {

            switch(target) {

                case(g1) :
                    pop_bit(board->bitboards[R], h1) ;
                    set_bit(board->bitboards[R], f1) ;
                    break ;

                case(c1) :
                    pop_bit(board->bitboards[R], a1) ;
                    set_bit(board->bitboards[R], d1) ;
                    break ;

                case(g8) :
                    pop_bit(board->bitboards[r], h8) ;
                    set_bit(board->bitboards[r], f8) ;
                    break ;
                
                case(c8) :
                    pop_bit(board->bitboards[r], a8) ;
                    set_bit(board->bitboards[r], d8) ;
                    break ;

            }

        }

        board->castling &= castlingRights[source] ;
        board->castling &= castlingRights[target] ;

        memset(board->occupancy, 0ULL, sizeof(board->occupancy)) ;

        for(int bb_piece = P; bb_piece <= K; bb_piece++) 
            board->occupancy[WHITE] |= board->bitboards[bb_piece] ;

        for(int bb_piece = p; bb_piece <= k; bb_piece++) 
            board->occupancy[BLACK] |= board->bitboards[bb_piece] ;

        board->occupancy[BOTH] |= (board->occupancy[WHITE] | board->occupancy[BLACK]) ;


        board->side ^= 1 ;

        if(isSquareAttacked(board, (board->side == WHITE) ? get_ls1b_index(board->bitboards[k]) : get_ls1b_index(board->bitboards[K]), board->side)) {

            restore_board() ;

            return 0 ;

        }

        else return 1 ;

    }

    else {

        if(getCaptureFlag(move)) {

            return makeMove(board, move, allMoves) ;

        }

        else return 0 ;

    }

}

int getMoveIfLegal(Moves* moveList, int ss, int ts) {

    for(int i=0; i<moveList->count; i++) {
        if(ss == getSourceSquare(moveList->moveList[i])) {
            if(ts == getTargetSquare(moveList->moveList[i])) {
                return moveList->moveList[i] ;
            }
        }
    }

    return 0 ;
}