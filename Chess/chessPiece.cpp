//
//  chessPiece.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessPiece.h"


ChessPiece::ChessPiece(){
    lastLastPos = 0;
    lastPos = 0;
}

void ChessPiece::initChessPiece(INT8 type, INT8 color,INT8 id, INT8 x, INT8 y)
{
    this->type = type;
    this->color = color;
    this->id    = id;
    this->x     = x;
    this->y    = y;
}