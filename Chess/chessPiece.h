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



vector<UINT8*> vectorInit(); // Vector initializer funtion

void imprimir(char mvList[56], UINT8  x, UINT8  y);

class PieceGraph
{
    UINT64 *reach[BSIZE][BSIZE]; // movement graph of each type of piece
    
public:
    
    // Class constructor
    PieceGraph();
    
    // Graph Initializar
    void initGraph(UINT8 type);
    
    // Get the legal moves of a piece;
    void getReach(UINT8 x, UINT8 y, UINT8 mvList[MAXMV],UINT64 board);
    
};

const vector<UINT8*> mvArray = vectorInit(); // vector with the information about the piece's movements



#endif
