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
    UINT64 board;
    a.initGraph(BPAWN);
    char c[MAXMV];
    UINT8  x= 4;
    UINT8  y= 1;
    a.getReach(x,y,c,board);
    imprimir(c,x,y);
    return 0;
}
