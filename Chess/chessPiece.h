//
//  chessPiece.h
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef Chess_chessPiece_h
#define Chess_chessPiece_h

#include "chessHeader.h"

class ChessPiece
{
public:
    INT8 type;
    INT8 x;
    INT8 y;
    
    ChessPiece();
    void initChessPiece(INT8 type, INT8 x, INT8 y);
};



#endif
