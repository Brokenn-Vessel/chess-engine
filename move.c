#include "move.h" 

void addMove(Moves* moveList, int move) {
    moveList->moveList[moveList->count] = move ;
    moveList->count++ ; 
}

void printMove(int move) {

    printf("Source square  :%s\n", square[getSourceSquare(move)]) ;
    printf("Target square  :%s\n", square[getTargetSquare(move)]) ;
    printf("Piece moved    :%s\n", pieceAscii[getPiece(move)]) ;
    printf("Promoted to    :%c\n", getPromotedPiece(move) ? promotedPieces[getPromotedPiece(move)] : '-') ;
    printf("Capture        :%d\n", getCaptureFlag(move) ? 1 : 0) ;
    printf("Double Push    :%d\n", getDoublePushFlag(move) ? 1 : 0) ;
    printf("Enpassant      :%d\n", getEnpassantFlag(move) ? 1 : 0) ;
    printf("Castling       :%d\n", getCastlingFlag(move) ? 1 : 0) ;

}

void printMoveList(Moves* moveList) {
    
    printf("Move       Promotion      Capture      Double      Enpassant      Castling\n") ;

    for(int count = 0; count < moveList->count; count++) {

        int move = moveList->moveList[count] ;

        printf("%c%s%s      %c              %d            %d           %d              %d\n", pieceAscii[getPiece(move)],
                                                                                              square[getSourceSquare(move)],
                                                                                              square[getTargetSquare(move)],
                                                                                              getPromotedPiece(move) ? promotedPieces[getPromotedPiece(move)] : '-',
                                                                                              getCaptureFlag(move) ? 1 : 0,
                                                                                              getDoublePushFlag(move) ? 1 : 0,
                                                                                              getEnpassantFlag(move) ? 1 : 0,
                                                                                              getCastlingFlag(move) ? 1 : 0) ;

    }

    printf("Total Moves : %d", moveList->count) ;

}

int parseMove(const char* str, Moves* moveList) {
    int sf = str[0] - 'a' ; // 'e' - 'a = 4
    int sr = 8 - (str[1] - '0') ;
    int source = square(sr, sf) ;

    printf("source found: %s\n", square[source]) ;

    int df = str[2] - 'a';
    int dr = 8 - (str[3] - '0');
    int dest = square(dr, df) ;

    printf("destination found: %s\n", square[dest]) ; 

    int prom = 0 ;
    if(str[4] != '\0') {
        prom = pieceIndex[str[4]] ;
        printf("promoted to: %c\n", str[4]) ;
    }


    for(int i=0; i<moveList->count; i++) {
        int move = moveList->moveList[i] ;
        if((getSourceSquare(move) == source) && (getTargetSquare(move) == dest) && (getPromotedPiece(move) == prom)) {
            return move ;
        } 
    }

    return -1 ;
}