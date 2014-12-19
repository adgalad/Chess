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
#include <vector>

using namespace std;

typedef unsigned long int UINT64;
typedef char UINT8;

const UINT8 lenghtMv[8]    = {0,6,6,16,8,8,16,16};
const UINT8 pawnMvBlack[8] = { 0,1 , 1,1 , -1,1 , 0,2};
const UINT8 pawnMvWhite[8] = { 0,-1, 1,-1 ,-1,-1 , 0,-2};
const UINT8 knightMv[16]   = {2,1,2,-1,-2,1,-2,-1,1,2,1,-2,-1,2,-1,-2};
const UINT8 bishopMv[8]    = {1,1,1,-1,-1,1,-1,-1};
const UINT8 rookMv[8]      = {0,1,1,0,0,-1,-1,0};
const UINT8 queenMv[16]    = {1,1,1,-1,-1,1,-1,-1,1,0,-1,0,0,1,0,-1};
const UINT8 kingMv[16]     = {1,1,1,-1,-1,1,-1,-1,1,0,-1,0,0,1,0,-1};




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


#endif
