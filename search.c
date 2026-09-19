#include "search.h" 

int negamax(Board* board, int depth, int alpha, int beta, int* bestMove, int ply) {
    if(depth == 0) return evaluate(board) ;

    Moves moveList[1] ;
    moveList->count = 0 ;
    generateMoves(moveList, board) ;

    int legalCount = 0 ;

    for(int i=0; i<moveList->count; i++) {
        copy_board() ;
        if(makeMove(board, moveList->moveList[i], allMoves) == 0) {
            restore_board() ;
            continue ;
        }

        legalCount++ ;
        int dummy = 0 ;
        int score = -negamax(board, depth-1, -beta, -alpha, &dummy, ply+1) ;
        restore_board() ;
        
        // printf("depth: %d, move: %s%s, score: %d, legalCount: %d\n", 2-depth, square[getSourceSquare(moveList->moveList[i])], square[getTargetSquare(moveList->moveList[i])], score, legalCount) ;
        if(score > alpha) {
            alpha = score ;
            if(bestMove) *bestMove = moveList->moveList[i] ;
        }

        // peuning
        if(alpha >= beta) {
            break ;
        }

    }

    if(legalCount == 0) {
        // printf("Checking whether the king is under check!, legalCount: %d\n", legalCount) ;
        if(inCheck(board)){
            // printf("Checkmate!!!!");
            return -MATE_SCORE + ply ;
        } 
        else{
            // printf("King was not found under check!") ;
            return 0 ;
        }
    }

    return alpha ;
}