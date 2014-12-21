//
//  SDLSurfaceRenderTools.h
//  Chess
//
//  Created by Carlos Spaggiari on 12/20/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef Chess_SDLSurfaceRenderTools_h
#define Chess_SDLSurfaceRenderTools_h

#include <SDL/SDL.h>
#include "SDL_image/SDL_image.h"
#include <string>
#include <time.h>

const std::string path = "/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Chess/Chess/Resource/";


class Csurface
{
public:
    Csurface();
    static SDL_Surface *OnLoad(char* file);
    static bool OnDraw(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y);
    static bool OnDraw(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
    static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
};

#endif
