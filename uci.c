#include "uci.h"

#define cnull '\0'

void uci_loop() {
    char buffer[4096] ;
    Board board[1] ;
    int depth = -1 ;
    // string input taken by fgets is terminated by \n and not \0
    while(fgets(buffer, sizeof(buffer),stdin)) {
        // uci
        if(strncmp(buffer, "uci", 3) == 0) {
            printf("id name %s\n", ENGINE_NAME) ;
            printf("id author %s\n", ENGINE_AUTHOR) ;
            // options
            printf("uciok\n") ;
            fflush(stdout) ;
        }

        // isready
        if(strncmp(buffer, "isready", 7) == 0) {
            printf("readyok\n") ;
            fflush(stdout) ;
        }
        // ucinewgame
        if(strncmp(buffer, "ucinewgame", 10) == 0) {
            // printf("new game\n") ;
            parseFen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ") ;
            depth = -1 ;
            // printBoard(board) ;
        }

        // position
        if(strncmp(buffer, "position", 8) == 0) {
            char* str = buffer + 8 ;
            while(*str && *str <= ' ') str++ ;
            if(*str == cnull) {
                // fprintf(stderr, "Expected: position [startpos | fen <fen_string>] [moves <move_list>] : Missing argument", 404) ;
                continue;
            }

            if(strncmp(str, "startpos", 8) == 0) {
                // printf("startpos\n") ;
                str += 8 ;
                parseFen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ") ;
                // printBoard(board) ;

                while(*str && *str <= ' ') str++; 
            }
            else if(strncmp(str, "fen", 3) == 0) {
                // printf("fen\n") ;
                str += 3 ;
                while(*str && *str <= ' ') str++ ;
                if(*str == cnull) {
                    // fprintf(stderr, "Expected a fen string!\n") ;
                    continue;  
                }

                parseFen(board, str) ;
                // printBoard(board);
                // printf("Parsing complete!\n") ;

                while(*str && strncmp(str, "moves", 5) != 0) str++ ;
            }

            // printf("%s\n", str) ;
            if(*str == cnull) {
                continue ;
            }

            if(strncmp(str, "moves", 5) == 0) {
                // printf("moves\n") ;
                str += 5 ;

                while(*str) {
                    while(*str && *str <= ' ') str++ ;
                    if(*str == cnull) break ;
                    Moves moves[1] ;
                    generateMoves(moves, board) ;
                    int move = parseMove(str, moves) ;
                    
                    if(move == -1 || !makeMove(board, move, allMoves)) {
                        // fprintf(stderr, "Illegal move detected!\n") ;
                        break ;
                    }
                    // printBoard(board) ;

                    // printf("%s\n", str) ; 

                    while(*str && *str > ' ') str++;
                }

                // printf("Moves parsed!\n") ;
                // printBoard(board) ;
            }
            
        }

        // go 
        if(strncmp(buffer, "go", 2) == 0) {
            // printf("go\n") ;
            if(*(buffer + 2) == '\0' || *(buffer + 3) == '\0') continue; 

            char* token = buffer + 3 ;

            if(strncmp(token, "depth", 5) == 0) {
                if(*(token + 5) == '\0' || *(token + 6) == '\0') continue;
                token += 6 ;
                
                depth = atoi(token) ;
                // printf("depth: %d\n", depth) ;

                int bestMove = 0 ;
                int alpha = negamax(board, depth, -inf, inf, &bestMove, 0) ;

                if(alpha >= MATE_THRESHOLD) {
                    // mate
                    printf("info depth %d score mate %d\n", depth, MATE_SCORE - alpha) ;
                }
                else if(alpha <= -MATE_THRESHOLD) {
                    printf("info depth %d score mate %d\n", depth, -MATE_SCORE - alpha) ;
                }
                else {
                    printf("info depth %d score cp %d\n", depth, alpha) ;
                }

                fflush(stdout) ;
                printf("bestmove %s%s%c\n", square[getSourceSquare(bestMove)], square[getTargetSquare(bestMove)], getPromotedPiece(bestMove)==0 ? ' ' : promotedPieces[getPromotedPiece(bestMove)]) ;
                fflush(stdout) ;
            }

        }

        // stop

        // quit
        if(strncmp(buffer, "quit", 4) == 0) {
            break ;
        }
        // 
    }

    printf("uciquit\n") ;
    fflush(stdout) ;
}