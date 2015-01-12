//
//  chessHeader.h
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef Chess_chessHeader_h
#define Chess_chessHeader_h


#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <SDL_mixer/SDL_mixer.h>
#include <SDL_ttf/SDL_ttf.h>

using namespace std;

typedef unsigned long int UINT64;
typedef int8_t INT8;
typedef uint8_t UINT8;


/* CHESS GAME DEFINITIONS */
const INT8 lenghtMv[8]    = {0,6,6,16,8,8,16,16};
const INT8 pawnMvBlack[8] = { 0,-1, 1,-1 ,-1,-1 , 0,-2};
const INT8 pawnMvWhite[8] = { 0,1 , 1,1 , -1,1 , 0,2};
const INT8 knightMv[16]   = {2,1,2,-1,-2,1,-2,-1,1,2,1,-2,-1,2,-1,-2};
const INT8 bishopMv[8]    = {1,1,1,-1,-1,1,-1,-1};
const INT8 rookMv[8]      = {0,1,1,0,0,-1,-1,0};
const INT8 queenMv[16]    = {1,1,1,-1,-1,1,-1,-1,1,0,-1,0,0,1,0,-1};
const INT8 kingMv[16]     = {1,1,1,-1,-1,1,-1,-1,1,0,-1,0,0,1,0,-1};
const UINT8 blockedPath[8] = {0,7,0x7,0xff,0xf,0xf,0xff,0xff};
const UINT64 bitPos[64] =
   {0x1,               0x2,               0x4,               0x8,
    0x10,              0x20,              0x40,              0x80,
    0x100,             0x200,             0x400,             0x800,
    0x1000,            0x2000,            0x4000,            0x8000,
    0x10000,           0x20000,           0x40000,           0x80000,
    0x100000,          0x200000,          0x400000,          0x800000,
    0x1000000,         0x2000000,         0x4000000,         0x8000000,
    0x10000000,        0x20000000,        0x40000000,        0x80000000,
    0x100000000,       0x200000000,       0x400000000,       0x800000000,
    0x1000000000,      0x2000000000,      0x4000000000,      0x8000000000,
    0x10000000000,     0x20000000000,     0x40000000000,     0x80000000000,
    0x100000000000,    0x200000000000,    0x400000000000,    0x800000000000,
    0x1000000000000,   0x2000000000000,   0x4000000000000,   0x8000000000000,
    0x10000000000000,  0x20000000000000,  0x40000000000000,  0x80000000000000,
    0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000,
    0x1000000000000000,0x2000000000000000,0x4000000000000000,0x8000000000000000};


#define BSIZE  8
#define MAXMV  57

#define OUT    0
#define WPAWN  1
#define BPAWN  2
#define KNIGHT 3
#define BISHOP 4
#define ROOK   5
#define QUEEN  6
#define KING   7

#define BLACK 0
#define WHITE 1

#define PAWNV 1 
#endif
