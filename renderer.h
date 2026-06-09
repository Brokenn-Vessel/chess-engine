#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "types.h"
#include "board.h"
#include "move.h"
#include "makemove.h"

typedef struct {
    int sourceSquare ;
    int targetSquare ;
    Moves moveList[1] ;

} userInputBundle ;

void resetUIB(userInputBundle* uib) ;
extern SDL_Texture* pieceTextures[12] ;
extern int boardCoordinates[64][2] ;

//need to be called during initialization
void initTextures(SDL_Renderer* renderer) ;
void initBoardCoordinates() ;

void drawRect(SDL_Renderer* renderer, SDL_Rect* rect, int r, int g, int b, int a) ;
void renderBoard(SDL_Renderer* renderer, Board* board) ;
SDL_Texture* getTexture(SDL_Renderer* renderer, const char* filename) ;

void renderPiece(SDL_Renderer* renderer, int piece, int square) ;

void eventHandling(Board* board, SDL_Event* event, userInputBundle* uib, int* areMovesGenerated, int* quit, int myColor) ;

#endif