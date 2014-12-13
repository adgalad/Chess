//
//  chess.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/13/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chess.h"

Chess::Chess()
{
    mainScreen = NULL;
}

bool Chess::Chess_Init()
{
    /* Init SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        return false;
    }
    const SDL_VideoInfo *VideoInfo;
    VideoInfo = SDL_GetVideoInfo();
    int h=VideoInfo->current_h;
    int w=VideoInfo->current_w;
    /* Set Video Mode */
    if ((mainScreen=SDL_SetVideoMode(w,h, 32, SDL_HWSURFACE|SDL_DOUBLEBUF))==NULL)
    {
        return false;
    }
    
    /* Set Unicode Translate */
    SDL_EnableUNICODE(1);
    
    /* Enable Key Repeat */
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    
    return true;
}