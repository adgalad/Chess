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



vector<INT8*> vectorInit(); // Vector initializer funtion

void imprimir(UINT64 mv, UINT64 board, INT8  x, INT8  y);

class PieceGraph
{
public:
    
    // Class constructor
    PieceGraph();
    
    
    // Get the legal moves of a piece;
    UINT64 getReach(INT8 type, INT8 x, INT8 y, INT8 mvList[MAXMV],UINT64 board);
    
};

const vector<INT8*> mvArray = vectorInit(); // vector with the information about the piece's movements



#endif
