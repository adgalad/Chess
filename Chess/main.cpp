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
    while(1){

        a.printBoard();
        while(!a.playerMv());
        UINT64 bm = a.getTotalReach(a.blackReach);
        UINT64 wm = a.getTotalReach(a.whiteReach);
        imprimir(bm, a.blackPieces|a.whitePieces, 0, 0);
        imprimir(wm, a.blackPieces|a.whitePieces, 0, 0);
        imprimir(bm & ~wm & ~a.blackPieces, a.blackPieces|a.whitePieces, 0, 0);
        a.printBoard();
        a.cPlayerMv();


    }
    
    return 0;
}
