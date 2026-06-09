#include "board.h"

void printBoard(Board* board) {

    printf("\n") ;

    for(int rank = 0; rank < 8; rank++) {

        printf("%d    ", 8 - rank);
        for(int file = 0; file < 8; file++) {
            
            int square = square(rank, file) ;
            char piece = '.' ;

            for (int bb_piece = P; bb_piece <= k; bb_piece++) {
                if(get_bit(board->bitboards[bb_piece], square)) piece = pieceAscii[bb_piece] ;
            }

            printf(" %c ", piece) ;

        }
        printf("\n") ;
    }

    printf("\n      a  b  c  d  e  f  g  h\n") ;

    printf("\n      side      :      %s", (board->side == WHITE) ? "white" : (board->side == BLACK) ? "black" : "-" ) ;
    printf("\n      castling  :       %c%c%c%c", (board->castling & WK) ? 'K' : '-', (board->castling & WQ) ? 'Q' : '-', (board->castling & BK) ? 'k' : '-', (board->castling & BQ) ? 'q' : '-') ;
    printf("\n      enpassant :         %s", (board->enpassant == nsq) ? "-" : square[board->enpassant]) ;


    printf("\n") ;
}

void parseFen(Board* board, const char* fen) {
    
    memset(board->bitboards, 0ULL, sizeof(board->bitboards)) ;
    memset(board->occupancy, 0ULL, sizeof(board->occupancy)) ;

    board->side = WHITE ; board->castling = 0 ; board->enpassant = nsq ;

    int square = 0;

    //"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

    while(*fen != ' ') {
        
        if(*fen >= '0' && *fen <= '9') {

            square += (*fen - '0') ;

        }

        //BLACK PIECE 
        else if(*fen >= 'a' && *fen <= 'z') {

            set_bit(board->bitboards[pieceIndex[*fen]], square) ;
            set_bit(board->occupancy[BLACK], square) ;
            set_bit(board->occupancy[BOTH], square) ;

            square++ ;

        }

        //WHITE PIECES
        else if(*fen >= 'A' && *fen <= 'Z') {

            set_bit(board->bitboards[pieceIndex[*fen]], square) ;
            set_bit(board->occupancy[WHITE], square) ;
            set_bit(board->occupancy[BOTH], square) ;

            square++ ;

        }

        fen++ ;

    }

    fen++ ;

    if(*fen == 'w') board->side = WHITE ;
    else if(*fen == 'b') board->side = BLACK ;
    else board->side = -1 ;

    fen += 2 ;

    while(*fen != ' ') {

        if(*fen == 'K') board->castling |= WK ;
        else if(*fen == 'Q') board->castling |= WQ ;
        else if(*fen == 'k') board->castling |= BK ;
        else if(*fen == 'q') board->castling |= BQ ;

        fen++ ;
    }

    fen++ ;

    int rank = 0, file = 0 ;
    int fail =  0;
    while(*fen != ' ') {

        if(*fen >= 'a' && *fen <= 'h') file = (*fen - 'a') ;
        else if(*fen >= '1' && *fen <= '8') rank = 8 - (*fen - '0') ;
        else fail = 1 ;

        fen++ ;
    }

    if(!fail) {
        board->enpassant = rank * 8 + file ;
    }

    fen++ ;

}

int isSquareAttacked(Board* board, int square, int side) {

    //pawn
    if((side == WHITE) ? (pawnAttackTable[BLACK][square] & board->bitboards[P]) : (pawnAttackTable[WHITE][square] & board->bitboards[p])) return 1 ;

    //knight
    if((knightAttackTable[square] & ((side == WHITE) ? board->bitboards[N] : board->bitboards[n]))) return 1 ;

    //king
    if(kingAttackTable[square] & ((side == WHITE) ? board->bitboards[K] : board->bitboards[k])) return 1 ;

    //rooks
    if(getRookAttack(square, board->occupancy[BOTH]) & ((side == WHITE) ? board->bitboards[R] : board->bitboards[r])) return 1 ;

    //bishop
    if(getBishopAttack(square, board->occupancy[BOTH]) & ((side == WHITE) ? board->bitboards[B] : board->bitboards[b])) return 1 ;

    //queen
    if(getQueenAttack(square, board->occupancy[BOTH]) & ((side == WHITE) ? board->bitboards[Q] : board->bitboards[q])) return 1 ;
    
    //else 
    return 0 ;
}

int pieceAtSquare(Board* board, int square) {
    if(!get_bit(board->occupancy[BOTH], square)) return -1 ;

    if(get_bit(board->bitboards[P], square)) return P ;
    if(get_bit(board->bitboards[N], square)) return N ;
    if(get_bit(board->bitboards[B], square)) return B ;
    if(get_bit(board->bitboards[R], square)) return R ;
    if(get_bit(board->bitboards[Q], square)) return Q ;
    if(get_bit(board->bitboards[K], square)) return K ;
    if(get_bit(board->bitboards[p], square)) return p ;
    if(get_bit(board->bitboards[n], square)) return n ;
    if(get_bit(board->bitboards[b], square)) return b ;
    if(get_bit(board->bitboards[r], square)) return r ;
    if(get_bit(board->bitboards[q], square)) return q ;
    if(get_bit(board->bitboards[k], square)) return k ;

}

int inCheck(Board* board) {
    if(isSquareAttacked(board, get_ls1b_index(board->bitboards[(board->side == WHITE)? K : k]), BLACK)) {
        return 1 ;
    }

    return 0 ;
}