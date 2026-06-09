#include "search.h" 

int negamax(Board* board, int depth, int alpha, int beta, int* bestMove) {
    if(depth == 0) return evaluate(board) ;

    Moves moveList[1] ;
    moveList->count = 0 ;
    generateMoves(moveList, board) ;

    int legalCount = 0 ;

    for(int i=0; i<moveList->count; i++) {
        copy_board() ;
        if(makeMove(board, moveList->moveList[i], allMoves) == 0) {
            continue ;
        }
        legalCount++ ;
        int dummy = 0 ;
        int score = -negamax(board, depth-1, -beta, -alpha, &dummy) ;

        if(score > alpha) {
            alpha = score ;
            if(bestMove) *bestMove = moveList->moveList[i] ;
        }
        if(alpha >= beta) {
            break ;
        }

        restore_board() ;
    }

    if(legalCount == 0) {
        if(inCheck(board)) return -MATE_SCORE + depth ;
        else return 0 ;
    }

    return alpha ;
}