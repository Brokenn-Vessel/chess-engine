#include "renderer.h"

SDL_Texture* pieceTextures[12] ;
int boardCoordinates[64][2] ;

void drawRect(SDL_Renderer* renderer, SDL_Rect* rect, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a) ;
    SDL_RenderFillRect(renderer, rect) ;
}

void renderBoard(SDL_Renderer* renderer, Board* board) {

    int color = 0 ;

    int y = BOARD_CENTER_Y - BOARD_HEIGHT/2 ;

    for(int i=0; i<8; i++) {

        color = !color ;
        int x = BOARD_CENTER_X - BOARD_WIDTH/2 ;


        for(int j=0; j<8; j++) {

            if(color) {
                SDL_Rect rect = {x, y, SQUARE_SIZE, SQUARE_SIZE} ;
                drawRect(renderer, &rect, 255, 255, 255, 255) ;
            }
            else {
                SDL_Rect rect = {x, y, SQUARE_SIZE, SQUARE_SIZE} ;
                drawRect(renderer, &rect, 129, 182, 76, 127) ;
            }
            int sq = square(i, j) ;
            
            int piece = pieceAtSquare(board, sq) ;
            if(piece != -1) {
                renderPiece(renderer, piece, sq) ;
            }

            color = !color ;
            x += SQUARE_SIZE ;
        }

        y += SQUARE_SIZE ;
    }
}

SDL_Texture* getTexture(SDL_Renderer* renderer, const char* filename) {

    SDL_Surface* surface = IMG_Load(filename) ;

    if(!surface) {
        printf("image file error") ;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface) ;
    SDL_FreeSurface(surface) ;

    return texture ;
}

//need to be called during initialization
void initTextures(SDL_Renderer* renderer) {
    pieceTextures[P] = getTexture(renderer, "assets/wp.png") ;
    pieceTextures[N] = getTexture(renderer, "assets/wn.png") ;
    pieceTextures[B] = getTexture(renderer, "assets/wb.png") ;
    pieceTextures[R] = getTexture(renderer, "assets/wr.png") ;
    pieceTextures[Q] = getTexture(renderer, "assets/wq.png") ;
    pieceTextures[K] = getTexture(renderer, "assets/wk.png") ;
    pieceTextures[p] = getTexture(renderer, "assets/bp.png") ;
    pieceTextures[n] = getTexture(renderer, "assets/bn.png") ;
    pieceTextures[b] = getTexture(renderer, "assets/bb.png") ;
    pieceTextures[r] = getTexture(renderer, "assets/br.png") ;
    pieceTextures[q] = getTexture(renderer, "assets/bq.png") ;
    pieceTextures[k] = getTexture(renderer, "assets/bk.png") ;
}

void initBoardCoordinates() {
    for(int i=0; i<64; i++) {
        int r = rank(i) , f = file(i) ;
        int xo = BOARD_CENTER_X - (BOARD_WIDTH/2) ;
        int yo = BOARD_CENTER_Y - (BOARD_HEIGHT/2) ;

        int x = xo + f * SQUARE_SIZE, y = yo + (8 - r) * SQUARE_SIZE ;

        boardCoordinates[i][0] = x ;
        boardCoordinates[i][1] = y ;
    }
}

void renderPiece(SDL_Renderer* renderer, int piece, int square) {

    SDL_Rect rect = {boardCoordinates[square][0], boardCoordinates[square][1], SQUARE_SIZE, SQUARE_SIZE} ;

    SDL_RenderCopy(renderer, pieceTextures[piece], NULL, &rect) ;

}

void resetUIB(userInputBundle* uib) {
    uib->moveList->count = 0 ;
    uib->sourceSquare = uib->targetSquare = 0 ;
}

void eventHandling(Board* board, SDL_Event* event, userInputBundle* uib, int* areMovesGenerated, int* quit, int myColor) {

    while(SDL_PollEvent(event)) {
        if(event->type == SDL_QUIT) {
            *quit = 1 ;
        }
        if(board->side == myColor) {
            if(event->type == SDL_MOUSEBUTTONDOWN) {
                printf("up\n");
                int mousex = event->button.x ;
                int mousey = event->button.y ;
    
                int boardx = BOARD_CENTER_X - BOARD_WIDTH/2 ;
                int boardy = BOARD_CENTER_Y - BOARD_HEIGHT/2 ;
    
                int x = (mousex - boardx) / SQUARE_SIZE ;
                int y = (mousey - boardy) / SQUARE_SIZE ;
                if(x>=0 && y>=0 && x<8 && y<8) 
                    uib->sourceSquare = square(y, x) ;
                printf("ss: %s", square[uib->sourceSquare]);
                printMoveList(uib->moveList) ;
            }
    
            if(event->type == SDL_MOUSEBUTTONUP) {
                printf("down\n");
    
                int mousex = event->button.x ;
                int mousey = event->button.y ;
    
                int boardx = BOARD_CENTER_X - BOARD_WIDTH/2 ;
                int boardy = BOARD_CENTER_Y - BOARD_HEIGHT/2 ;
    
                int x = (mousex - boardx) / SQUARE_SIZE ;
                int y = (mousey - boardy) / SQUARE_SIZE ;
                if(x>=0 && y>=0 && x<8 && y<8)
                    uib->targetSquare = square(y, x) ;
                printf("ts: %s", square[uib->targetSquare]);
                int move = 0 ;
                if(uib->sourceSquare != nsq && uib->targetSquare != nsq)
                    move = getMoveIfLegal(uib->moveList, uib->sourceSquare, uib->targetSquare) ;
                printf("\n%d", move) ;
                if(move != 0) {
                    makeMove(board, move, allMoves) ;
                    *areMovesGenerated = 0 ;
                    printBoard(board) ;
                }
            }
        }
    }
}
