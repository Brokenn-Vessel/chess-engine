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

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO) ;

    SDL_Event event ;
    int quit = 0 ;

    SDL_Window* window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE) ;
    if(!window) {
        printf("couldn't create window") ;
        return -1 ;
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("couldn't initialize imageLoader") ;
        return -1 ;
    }

    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) ;
    initSliderAttacks() ;
    initTextures(renderer) ;
    initBoardCoordinates() ;

    Board board[1] ;
    parseFen(board, "r1bqk2r/pp2bppp/2np1n2/1B2p3/4P3/2N2N2/PPP2PPP/R1BQ1RK1 b kq - 3 8") ;
    int sourceSquare = nsq ;
    int targetSquare = nsq ;

    Moves moveList[1] ;

    generateMoves(moveList, board) ;
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = 1 ;
            }

            if(event.type == SDL_MOUSEBUTTONDOWN) {
                printf("up\n");
                int mousex = event.button.x ;
                int mousey = event.button.y ;

                int boardx = BOARD_CENTER_X - BOARD_WIDTH/2 ;
                int boardy = BOARD_CENTER_Y - BOARD_HEIGHT/2 ;

                int x = (mousex - boardx) / SQUARE_SIZE ;
                int y = (mousey - boardy) / SQUARE_SIZE ;

                sourceSquare = square(y, x) ; printf("ss: %s", square[sourceSquare]);

                generateMoves(moveList, board) ;
                printMoveList(moveList) ;
            }

            if(event.type == SDL_MOUSEBUTTONUP) {
                printf("down\n");

                int mousex = event.button.x ;
                int mousey = event.button.y ;

                int boardx = BOARD_CENTER_X - BOARD_WIDTH/2 ;
                int boardy = BOARD_CENTER_Y - BOARD_HEIGHT/2 ;

                int x = (mousex - boardx) / SQUARE_SIZE ;
                int y = (mousey - boardy) / SQUARE_SIZE ;

                targetSquare = square(y, x) ;
                printf("ts: %s", square[targetSquare]);

                int move = isLegal(moveList, sourceSquare, targetSquare) ;
                printf("\n%d", move) ;
                if(move != 0) {
                    makeMove(board, move, allMoves) ;
                    printBoard(board) ;
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) ;
        SDL_RenderClear(renderer) ;
        
        renderBoard(renderer, board) ;

        SDL_RenderPresent(renderer) ;
        SDL_Delay(16) ;
    }

    SDL_DestroyWindow(window) ;
    IMG_Quit() ;
    SDL_Quit() ;

    return 0 ;
}

