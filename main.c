#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "types.h"
#include "renderer.h"
#include "board.h"
#include "move.h"
#include "movegen.h"
#include "makemove.h"
#include "attack_tables.h"
#include "search.h" 
#include "uci.h"

#define pos1 "r1bqk2r/pp2bppp/2np1n2/1B2p3/4P3/2N2N2/PPP2PPP/R1BQ1RK1 b kq - 3 8"
#define pos0 "rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR w KQkq - 0 1 "

// int main(int argc, char** argv) {
//     SDL_Init(SDL_INIT_VIDEO) ;

//     SDL_Event event ;
//     int quit = 0 ;

//     SDL_Window* window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE) ;
//     if(!window) {
//         printf("couldn't create window") ;
//         return -1 ;
//     }

//     if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
//         printf("couldn't initialize imageLoader") ;
//         return -1 ;
//     }

    
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) ;

//     //initialization
//     initSliderAttacks() ;
//     initTextures(renderer) ;
//     initBoardCoordinates() ;
//     Board board[1] ;
//     parseFen(board, pos0) ;
//     int myColor = WHITE ;
//     userInputBundle uib[1] ;
//     resetUIB(uib) ;
//     int areMovesGenerated = 0 ;
//     int skip = 0 ;
//     int gameEnd = 0 ;
    
//     while(!quit) {

//         skip = 0 ;

//         if(gameEnd == 1) {
//             break ;
//         }

//         if(!areMovesGenerated) {
//             uib->moveList->count = 0 ;
//             generateMoves(uib->moveList, board) ;
//             areMovesGenerated = 1 ;
//         }

//         while(SDL_PollEvent(&event)) {
//             if(event.type == SDL_QUIT) {
//                 quit = 1 ;
//             }
//             if(board->side == myColor) {
//                 if(handleUserInput(board, &event, uib, &areMovesGenerated, myColor) == 0) {

//                     if(inCheck(board)) {
//                         printf("Checkmate. You lost.") ;
//                     }
//                     else {
//                         printf("Stalemate.") ;
//                     }
//                     gameEnd = 1 ;
//                 }
//                 skip = 1 ;
//             }
//         }

//         if(board->side != myColor && skip == 0) {
//             SDL_Delay(3000) ;
//             if(engineInput(board, uib, &areMovesGenerated) == 0) {
//                 if(inCheck(board)) {
//                     printf("Checkmate. Engine Lost.") ;
//                 }
//                 else {
//                     printf("Stalemate") ;
//                 }
//                 gameEnd = 1 ;
//             }
//         }
        
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) ;
//         SDL_RenderClear(renderer) ;
        
//         renderBoard(renderer, board) ;

//         SDL_RenderPresent(renderer) ;
//         SDL_Delay(16) ;
//     }

//     SDL_DestroyWindow(window) ;
//     IMG_Quit() ;
//     SDL_Quit() ;

//     return 0 ;
// }

int main(void) {

    // Board board[1] ;

    // parseFen(board, pos1) ;

    // printBoard(board) ;
    // Moves movelist[1] ;
    // generateMoves(movelist, board) ;

    // int move = parseMove("f6e4", movelist) ;
    // if(move != -1) {
    //     printMove(move) ;
    // }    

    initSliderAttacks() ;
    uci_loop() ;

    // Board board[1] ;
    // parseFen(board, "6k1/5ppp/8/8/8/8/8/R5K1 w - - 0 1") ;
    // printBoard(board) ;
    // int best_move = 0 ;
    // int alpha = negamax(board, 4, -inf, inf, &best_move) ;
    // if(best_move != 0) {
    //     printMove(best_move) ;
    //     printf("alpha: %d\n", alpha) ;
    // }
    // printf("Evluation: %d\n", evaluate(board)) ;
    // makeMove(board, best_move, allMoves) ;
    // printBoard(board) ;
    // printf("Evaluation: %d\n", evaluate(board)) ;

    return 0 ;
}