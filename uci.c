#include "uci.h"

void uci_loop() {
    char buffer[4096] ;
    Board board[1] ;
    int depth = -1 ;

    while(fgets(buffer, sizeof(buffer),stdin)) {
        // uci
        if(strncmp(buffer, "uci", 3) == 0) {
            printf("id name %s\n", ENGINE_NAME) ;
            printf("id author %s\n", ENGINE_AUTHOR) ;
            printf("uciok\n") ;
        }

        // isready
        if(strncmp(buffer, "isready", 7) == 0) {
            printf("readyok\n") ;
        }
        // ucinewgame
        if(strncmp(buffer, "ucinewgame", 10) == 0) {
            printf("new game\n") ;
            parseFen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ") ;
            printBoard(board) ;
        }

        // position
        if(strncmp(buffer, "position", 8) == 0) {
            printf("position\n") ;
            if(*(buffer + 8) == '\0') continue;
            char* token = buffer + 9 ;

            printf("%s\n", token) ;

            if(strncmp(token, "startpos", 8) == 0) {
                printf("startpos\n") ;
                parseFen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ") ;
                printBoard(board) ;

                if(*(token + 8) == '\0') continue;
                token += 9 ;
                if(strncmp(token, "moves", 5) == 0) {
                    printf("%s\n", token) ;
                    if(*(token + 5) == '\0') continue;
                    token += 6 ;

                    while(*token != '\0') {
                        Moves movelist[1] ;
                        generateMoves(movelist, board) ;
                        int move = parseMove(token, movelist) ;
                        makeMove(board, move, allMoves) ;
                        
                        printBoard(board) ;
                        while(*token != '\0' && *token != ' ') token++ ;
                        if(*token == ' ') token++ ;
                    }

                }
            }

            if(strncmp(token, "fen", 3) == 0) {
                printf("fen\n") ;
                token += 4 ;
                printf("%s\n", token) ;
                parseFen(board, token) ;
                printBoard(board) ;
            }
        }

        // go 
        if(strncmp(buffer, "go", 2) == 0) {
            printf("go\n") ;
            if(*(buffer + 2) == '\0' || *(buffer + 3) == '\0') continue; 

            char* token = buffer + 3 ;

            if(strncmp(token, "depth", 5) == 0) {
                if(*(token + 5) == '\0' || *(token + 6) == '\0') continue;
                token += 6 ;
                
                depth = atoi(token) ;
                printf("depth: %d\n", depth) ;
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
}