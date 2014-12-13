//
//  chessHeader.h
//  Chess
//
//  Created by Carlos Spaggiari on 11/29/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef Chess_chessHeader_h
#define Chess_chessHeader_h

#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <iostream>

#define BSIZE 8

/* TYPE */
#define ISBLACK  1      // 1
#define PAWN     2      // 2
#define KNIGHT   4      // 3
#define BISHOP   8      // 4
#define ROOK     16     // 5
#define QUEEN    32     // 6
#define KING     64     // 7
#define INGAME   128    // 8
#define VALUE    256    // 9
    #define VALUEP 0xf00
/* END_TYPE */

#define THREAT 0
#define SAVE   1



#define PAWNV   1
#define KNIGHTV 3
#define BISHOPV 3
#define ROOKV   5
#define QUEENV  9
#define KINGV   10



#endif /* END_CHESS_CHESSHEADER_H */

