//
//  chessmen.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 11/29/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessmen.h"

ChessPiece::ChessPiece(int type, char x, char y)
{
    this->type = type;
    this->x    = x;
    this->y    = y;
}

int ChessPiece::mvp(char X, char Y, bool pl, bool eat)
{
    
    if (type & PAWN)
    {
        if (not((!eat && X == x  && ((  (Y == y+1 || (y == 1 && Y == 3)) && pl)
                                  || ((Y == y-1 || (y == 6 && Y == 4))&& !pl)))
                ||(eat && abs(x-X)==1 && ((pl && Y == y+1)||(!pl && Y == y-1)))
            ))
            return false;
    }
    else if (type & KNIGHT){
        
        if(not(((X == x-1 || X == x+1) && (Y == y+2 || Y == y-2)) ||
                ((Y == y-1 || Y == y+1) && (X == x+2 || X == x-2))
               )
           )
            return false;
    }
    else if (type & BISHOP)
    {
        if (not( abs(Y-y) == abs(X-x)))
            return false;
    }
    else if (type & ROOK)
    {
        if(not( (Y == y && abs(X-x) > 0) || (X == x && abs(Y-y) > 0)))
            return false;
    }
    else if (type & QUEEN)
    {
        if( not( abs(Y-y) == abs(X-x)  ||
                 ( (Y == y && abs(X-x) > 0) || (X == x && abs(Y-y) > 0) )
               )
           )
        return false;
    }
    else if (type & KING && not(abs(X-x) <= 1 && abs(Y-y) <= 1))
    {
        return false;
    }
    x = X;
    y = Y;
    return true;
}
