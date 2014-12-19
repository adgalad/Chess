//
//  main.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessPiece.h"


int main()
{
    PieceGraph a = PieceGraph();
    UINT64 board = 23002002340001070;
    INT8 c[MAXMV];
    INT8  x= 4;
    INT8  y= 1;
    for (UINT64 i = 0; i < 1000000 ; i++)
    {
        a.getReach(QUEEN,x,y,c,board);
    }
    imprimir(a.getReach(QUEEN,x,y,c,board),board,x,y);
    
    return 0;
}
