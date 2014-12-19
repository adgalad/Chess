//
//  main.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessBoard.h"


int main()
{
    ChessBoard a = ChessBoard();

    INT8  x= 4;
    imprimir(a.getReach(a.wpArray[x]),a.getBlackPieces()|a.getWhitePieces(),a.wpArray[x].x,a.wpArray[x].y);

    return 0;
}
