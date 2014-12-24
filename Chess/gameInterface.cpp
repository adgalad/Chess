//
//  gameInterface.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/20/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "gameInterface.h"



GameInterface::GameInterface()
{
    mainScreen = NULL;
    mainBoard = ChessBoard();
    idle = false;
    checkmate = false;
}

void GameInterface::executeGame()
{
    if (initGame() == false)
    {
        printf("error\n");
    }
    bool run = true;
    renderGame();
    while (run) {
        
        while (SDL_WaitEvent(&event) >= 0 )
        {
            if (event.type != SDL_MOUSEMOTION || idle)
            {
                if (!eventGame())
                {
                  exitGame();
                  return;
                        
                }
                renderGame();
            }
        }
    }
    exitGame();
}

bool GameInterface::eventGame()
{
    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                return false;
            else if (event.key.keysym.unicode == 'n')
            {
                newGame = true;
                return false;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            if (event.button.button == SDL_BUTTON_LEFT &&
                event.motion.x >= 44 && event.motion.x < 584 &&
                event.motion.y >= 43 && event.motion.y < 583)
            {
                if (pickedPiece == -1)
                {
                    mainBoard.str[0] = (event.motion.x-44)/68;
                    mainBoard.str[1] = (event.motion.y-43)/68;
                    int pos = 8*mainBoard.str[1]+mainBoard.str[0];
                    printf("%d pos\n",pos);
                    if (mainBoard.whitePieces & bitPos[pos])
                    {
                        if (mainBoard.board[pos]->type >0)
                        pickedPiece = mainBoard.board[pos]->id;
                    }
                    idle = true;
                }
                else
                {
                    
                    mainBoard.str[2] = (event.motion.x-44)/68;
                    mainBoard.str[3] = (event.motion.y-43)/68;
                    
                    if (mainBoard.playerMv())
                    {
                        pickedPiece = -1;
                        Mix_PlayMusic(moveSound, 1);
                        if (!mainBoard.cPlayerMv())
                        {
                            checkmate = true;
                            newGame = true;
                            return false;
                        }
                    }
                    else{
                        pickedPiece = -1;
                    }
                    idle = false;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {

            break;
        }
        case SDL_QUIT:
            return false;
            break;
        default:
            break;
    }
    return true;
}

bool GameInterface::loopGame()
{
    return true;
}
bool GameInterface::renderGame()
{
    Csurface::OnDraw(mainScreen, surfaceArray[0], 0, 0);
    for (int i = 0; i < 16; i++)
    {
        if (pickedPiece != i && mainBoard.wpArray[i].type)
        {
            Csurface::OnDraw(mainScreen, surfaceArray[1],
                         mainBoard.wpArray[i].x*68+44,
                         mainBoard.wpArray[i].y*68+43,
                         (SDLPieceSurfacePosition[mainBoard.wpArray[i].type-1])*68,
                         68, 68, 68);
        }
        if (mainBoard.bpArray[i].type)
        {
            Csurface::OnDraw(mainScreen, surfaceArray[1],
                         mainBoard.bpArray[i].x*68+44,
                         mainBoard.bpArray[i].y*68+43,
                         (SDLPieceSurfacePosition[mainBoard.bpArray[i].type-1])*68,
                         0, 68, 68);
        }
    }
    if (pickedPiece > -1) {
        Csurface::OnDraw(mainScreen, surfaceArray[1],
                         event.motion.x-34,
                         event.motion.y-34,
                         (SDLPieceSurfacePosition[mainBoard.wpArray[pickedPiece].type-1])*68,
                         68, 68, 68);
    }
    SDL_Flip(mainScreen);
    return true;
}

bool GameInterface::initGame()
{
    /* Init SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        return false;
    }
    const SDL_VideoInfo *VideoInfo;
    VideoInfo = SDL_GetVideoInfo();
    //int h=VideoInfo->current_h;
   // int w=VideoInfo->current_w;
    int w = 628;
    int h = 628;
    /* Set Video Mode */
    if ((mainScreen=SDL_SetVideoMode(w,h, 32, SDL_HWSURFACE|SDL_DOUBLEBUF))==NULL)
    {
        return false;
    }
    
    /* Set Unicode Translate */
    SDL_EnableUNICODE(1);
    
    /* Enable Key Repeat */
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    
    /*Enable Music mixer */
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    moveSound = Mix_LoadMUS("/Users/carlosspaggiari/Desktop/C-C++/PROYECTOS/Chess/Chess/Resource/moveSound.wav");
    string img = path + "board.jpg";
    surfaceArray.push_back(Csurface::OnLoad(&img[0]));
    img = path + "pieces.png";
    surfaceArray.push_back(Csurface::OnLoad(&img[0]));
    Csurface::Transparent(surfaceArray[1], 251, 166, 82);
    pickedPiece = -1;
    return true;
}

void GameInterface::exitGame()
{
    SDL_FreeSurface(mainScreen);
    Mix_FreeMusic(moveSound);
    Mix_CloseAudio();
    SDL_Quit();
}