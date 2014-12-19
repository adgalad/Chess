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
    UINT64 blackThreat = 0, whiteThreat = 0;
    while(1){
        
        blackThreat=0;
        whiteThreat=0;
        for(int i = 0; i < 16 ; i++)
        {
            blackThreat |= a.getReach(a.wpArray[i]);
            whiteThreat |= a.getReach(a.bpArray[i]);
        }
        imprimir(blackThreat,a.getBlackPieces()|a.getWhitePieces(),a.wpArray[x].x,a.wpArray[x].y);
        imprimir(whiteThreat,a.getBlackPieces()|a.getWhitePieces(),a.wpArray[x].x,a.wpArray[x].y);
        a.playerMv();
        
        blackThreat=0;
        whiteThreat=0;
        for(int i = 0; i < 16 ; i++)
        {
            blackThreat |= a.getReach(a.wpArray[i]);
            whiteThreat |= a.getReach(a.bpArray[i]);
        }
        imprimir(blackThreat,a.getBlackPieces()|a.getWhitePieces(),a.wpArray[x].x,a.wpArray[x].y);
        imprimir(whiteThreat,a.getBlackPieces()|a.getWhitePieces(),a.wpArray[x].x,a.wpArray[x].y);
    }
    
    return 0;
}
