//
//  main.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "gameInterface.h"


int SDL_main(int argc, char **argv)
{
    GameInterface game;
    do
    {
        game.newGame = false;
        game = GameInterface();
        game.executeGame();
    }while(game.newGame);
    return 0;
}
