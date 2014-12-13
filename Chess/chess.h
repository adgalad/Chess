//
//  chess.h
//  Chess
//
//  Created by Carlos Spaggiari on 12/13/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef __Chess__chess__
#define __Chess__chess__

#include "board.h"
#include "chessHeader.h"

class Chess
{
    SDL_Surface *mainScreen; // Main screen of the app
    board chessBoard;        // Main chess board
    
    //SDL Funtions
    Chess();
    bool Chess_Init();
    bool Chess_Execute();
    bool Chess_Event();
    bool Chess_Loop();
    bool Chess_Render();
};

#endif /* defined(__Chess__chess__) */
