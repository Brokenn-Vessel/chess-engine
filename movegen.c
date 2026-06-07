#include "movegen.h"

void generateMoves(Moves* moveList, Board* board) {

    moveList->count = 0 ;

    int source_square, target_square ;
    u64 bitboard, attacks ;

    for(int piece = P; piece <= k ; piece++) {

        bitboard = board->bitboards[piece] ;

        //White moves generation
        if(board->side == WHITE) {

            //pawn move generation
            if(piece == P) {

                while(bitboard) {

                    source_square = get_ls1b_index(bitboard) ;

                    target_square = source_square - 8 ;

                    //quiet pawn moves
                    if(!(target_square < a8) && !(get_bit(board->occupancy[BOTH], target_square))) {

                        //Quiet promotions
                        if(source_square >= a7 && source_square <= h7) {

                            addMove(moveList, encodeMove(source_square, target_square, piece, Q, 0, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, R, 0, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, B, 0, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, N, 0, 0, 0, 0)) ;

                        }

                        else {

                            //single push
                            addMove(moveList, encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0)) ;

                            //double push
                            if((source_square >= a2 && source_square <= h2) && !(get_bit(board->occupancy[BOTH], target_square - 8))) {
                                
                                addMove(moveList, encodeMove(source_square, target_square - 8, piece, 0, 0, 1, 0, 0)) ;

                            }

                        }

                    }

                    attacks = pawnAttackTable[board->side][source_square] & board->occupancy[BLACK] ;

                    while(attacks) {

                        target_square = get_ls1b_index(attacks) ;


                        //capture promotions
                        if(source_square >= a7 && source_square <= h7) {

                            addMove(moveList, encodeMove(source_square, target_square, piece, Q, 1, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, R, 1, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, B, 1, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, N, 1, 0, 0, 0)) ;

                        }

                        //captures
                        else {

                            addMove(moveList, encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0)) ;

                        }

                        pop_ls1b(attacks) ;

                    }

                    //enpassant captures
                    if(board->enpassant != nsq) {

                        u64 enpassant_attacks = pawnAttackTable[WHITE][source_square] & (1ULL << board->enpassant) ;

                        if(enpassant_attacks) {

                            int target_enp = get_ls1b_index(enpassant_attacks) ;
                            addMove(moveList, encodeMove(source_square, target_enp, piece, 0, 1, 0, 1, 0)) ;

                        }

                    }

                    pop_ls1b(bitboard) ;

                }

            }

            if(piece == K) {
                
                //King side castling
                if(board->castling & WK) {
                    //make sure squares in the path are neither occupied nor attacked
                    if((!get_bit(board->occupancy[BOTH], f1)) && (!get_bit(board->occupancy[BOTH], g1))) {

                        if((!isSquareAttacked(board, e1, BLACK)) && (!isSquareAttacked(board, f1, BLACK))) {

                            addMove(moveList, encodeMove(e1, g1, piece, 0, 0, 0, 0, 1)) ;

                        }

                    }

                }

                //queen side castling
                if(board->castling & WQ) {

                    if((!get_bit(board->occupancy[BOTH], d1)) && (!get_bit(board->occupancy[BOTH], c1)) && (!get_bit(board->occupancy[BOTH], b1))) {

                        if((!isSquareAttacked(board, e1, BLACK)) && (!isSquareAttacked(board, d1, BLACK))) {

                            addMove(moveList, encodeMove(e1, c1, piece, 0, 0, 0, 0, 1)) ;

                        }

                    }

                }

            }

        }

        else {

            if(piece == p) {

                while(bitboard) {

                    source_square = get_ls1b_index(bitboard) ;

                    target_square = source_square + 8 ;

                    //quiet pawn moves
                    if(!(target_square > h1) && !(get_bit(board->occupancy[BOTH], target_square))) {

                        //Quiet promotions
                        if(source_square >= a2 && source_square <= h2) {

                            addMove(moveList, encodeMove(source_square, target_square, piece, Q, 0, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, R, 0, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, B, 0, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, N, 0, 0, 0, 0)) ;

                        }

                        else {

                            //single push
                            addMove(moveList, encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0)) ;

                            //double push
                            if((source_square >= a7 && source_square <= h7) && !(get_bit(board->occupancy[BOTH], target_square + 8))) {
                                
                                addMove(moveList, encodeMove(source_square, target_square + 8, piece, 0, 0, 1, 0, 0)) ;

                            }

                        }

                    }

                    attacks = pawnAttackTable[board->side][source_square] & board->occupancy[WHITE] ;

                    while(attacks) {

                        target_square = get_ls1b_index(attacks) ;


                        //capture promotions
                        if(source_square >= a2 && source_square <= h2) {

                            addMove(moveList, encodeMove(source_square, target_square, piece, q, 1, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, r, 1, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, b, 1, 0, 0, 0)) ;
                            addMove(moveList, encodeMove(source_square, target_square, piece, n, 1, 0, 0, 0)) ;

                        }

                        //captures
                        else {

                            addMove(moveList, encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0)) ;

                        }

                        pop_ls1b(attacks) ;

                    }

                    //enpassant captures
                    if(board->enpassant != nsq) {

                        u64 enpassant_attacks = pawnAttackTable[BLACK][source_square] & (1ULL << board->enpassant) ;

                        if(enpassant_attacks) {

                            int target_enp = get_ls1b_index(enpassant_attacks) ;
                            addMove(moveList, encodeMove(source_square, target_enp, piece, 0, 1, 0, 1, 0)) ;

                        }

                    }

                    pop_ls1b(bitboard) ;

                }

            }

            if(piece == k) {
                
                //King side castling
                if(board->castling & BK) {
                    //make sure squares in the path are neither occupied nor attacked
                    if((!get_bit(board->occupancy[BOTH], f8)) && (!get_bit(board->occupancy[BOTH], g8))) {

                        if((!isSquareAttacked(board, e8, WHITE)) && (!isSquareAttacked(board, f8, WHITE))) {

                            addMove(moveList, encodeMove(e8, g8, piece, 0, 0, 0, 0, 1)) ;

                        }

                    }

                }

                //queen side castling
                if(board->castling & BQ) {

                    if((!get_bit(board->occupancy[BOTH], d8)) && (!get_bit(board->occupancy[BOTH], c8)) && (!get_bit(board->occupancy[BOTH], b8))) {

                        if((!isSquareAttacked(board, e8, WHITE)) && (!isSquareAttacked(board, d8, WHITE))) {

                            addMove(moveList, encodeMove(e8, c8, piece, 0, 0, 0, 0, 1)) ;

                        }

                    }

                }

            }

        }

        //knight moves
        if((board->side == WHITE) ? piece == N : piece == n) {

            while(bitboard) {

                source_square = get_ls1b_index(bitboard) ;
                attacks = knightAttackTable[source_square] & ((board->side == WHITE) ? ~board->occupancy[WHITE] : ~board->occupancy[BLACK]) ;

                while(attacks) {

                    target_square = get_ls1b_index(attacks) ;

                    if(!get_bit(((board->side == WHITE) ? board->occupancy[BLACK] : board->occupancy[WHITE]), target_square)) {

                        //Quiet knight moves
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0)) ;

                    }

                    else {

                        //capture
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0)) ;

                    }

                    pop_ls1b(attacks) ;

                }

                pop_ls1b(bitboard) ;

            }

        }

        if((board->side == WHITE) ? piece == B : piece == b) {

            while(bitboard) {

                source_square = get_ls1b_index(bitboard) ;
                attacks = getBishopAttack(source_square, board->occupancy[BOTH]) & ((board->side == WHITE) ? ~board->occupancy[WHITE] : ~board->occupancy[BLACK]) ;

                while(attacks) {

                    target_square = get_ls1b_index(attacks) ;

                    if(!get_bit(((board->side == WHITE) ? board->occupancy[BLACK] : board->occupancy[WHITE]), target_square)) {
                        //quiet bishop moves
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0)) ;

                    }

                    else {
                        //captures
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0)) ;

                    }

                    pop_ls1b(attacks) ;

                }

                pop_ls1b(bitboard) ;

            }

        }

        if((board->side == WHITE) ? piece == R : piece == r) {

            while(bitboard) {

                source_square = get_ls1b_index(bitboard) ;
                attacks = getRookAttack(source_square, board->occupancy[BOTH]) & ((board->side == WHITE) ? ~board->occupancy[WHITE] : ~board->occupancy[BLACK]) ;

                while(attacks) {

                    target_square = get_ls1b_index(attacks) ;

                    if(!get_bit(((board->side == WHITE) ? board->occupancy[BLACK] : board->occupancy[WHITE]), target_square)) {
                        //quiet rook moves
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0)) ;

                    }

                    else {
                        //captures
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0)) ;

                    }

                    pop_ls1b(attacks) ;

                }

                pop_ls1b(bitboard) ;

            }

        }

        if((board->side == WHITE) ? piece == Q : piece == q) {

            while(bitboard) {

                source_square = get_ls1b_index(bitboard) ;
                attacks = getQueenAttack(source_square, board->occupancy[BOTH]) & ((board->side == WHITE) ? ~board->occupancy[WHITE] : ~board->occupancy[BLACK]) ;

                while(attacks) {

                    target_square = get_ls1b_index(attacks) ;

                    if(!get_bit(((board->side == WHITE) ? board->occupancy[BLACK] : board->occupancy[WHITE]), target_square)) {
                        //quiet queen moves
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0)) ;

                    }

                    else {
                        //captures
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0)) ;

                    }

                    pop_ls1b(attacks) ;

                }

                pop_ls1b(bitboard) ;

            }

        }

        if((board->side == WHITE) ? piece == K : piece == k) {

            while(bitboard) {

                source_square = get_ls1b_index(bitboard) ;
                attacks = kingAttackTable[source_square] & ((board->side == WHITE) ? ~board->occupancy[WHITE] : ~board->occupancy[BLACK]) ;
                
                while(attacks) {

                    target_square = get_ls1b_index(attacks) ;

                    if(!get_bit(((board->side == WHITE) ? board->occupancy[BLACK] : board->occupancy[WHITE]), target_square)) {
                        //quiet king moves
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0)) ;

                    }

                    else {
                        //captures
                        addMove(moveList, encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0)) ;

                    }

                    pop_ls1b(attacks) ;

                }

                pop_ls1b(bitboard) ;

            }

        }

    }

}