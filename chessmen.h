//
//  chesspiece.h
//  Chess
//
//  Created by Carlos Spaggiari on 11/29/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef __Chess__chesspiece__
#define __Chess__chesspiece__

#include "chessHeader.h"
using namespace std;

class ChessPiece {
public:
    unsigned int type;
    char x;
    char y;
    

public:
    ChessPiece(int type, char x, char y);
    int mvp(char X,char Y,bool pl,bool eat);
};





#endif /* defined(__Chess__chesspiece__) */
