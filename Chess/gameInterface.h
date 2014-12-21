//
//  gameInterface.h
//  Chess
//
//  Created by Carlos Spaggiari on 12/20/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef __Chess__gameInterface__
#define __Chess__gameInterface__

#include "chessBoard.h"
#include "SDLSurfaceRenderTools.h"

const UINT8 SDLPieceSurfacePosition[7] = {5,5,4,3,2,1,0};



class GameInterface
{
    SDL_Surface *mainScreen;
    ChessBoard  mainBoard;
    SDL_Event   event;
    vector<SDL_Surface*> surfaceArray;
    
    INT8 pickedPiece;  // needed to move pieces with the mouse
    
public:
    GameInterface();
    bool initGame();
    void exitGame();
    void executeGame();
    bool eventGame();
    bool loopGame();
    bool renderGame();
};


#endif /* defined(__Chess__gameInterface__) */