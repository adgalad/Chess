//
//  chessBoard.h
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef __Chess__chessBoard__
#define __Chess__chessBoard__

#include "chessPiece.h"

vector<INT8*> vectorMvInit(); // Vector initializer funtion

void imprimir(UINT64 mv, UINT64 board, INT8  x, INT8  y);// Auxiliar function

class ChessBoard
{
public:
    UINT64 whitePieces;
    UINT64 blackPieces;
    UINT64 blackReach[16];
    UINT64 whiteReach[16];
    UINT64 passantCapture;
    vector<INT8> mvList;
    ChessPiece *board[BSIZE*BSIZE];
    

public:
    vector<ChessPiece> wpArray;
    vector<ChessPiece> bpArray;
    
    
    
public:
    
    // Class constructor
    ChessBoard();
    
    void printBoard();
    
    // Get the legal moves of a piece;
    UINT64 getReach(ChessPiece cp);
    
    void setWhitePieces(UINT64 pieces);
    void setBlackPieces(UINT64 pieces);
    UINT64 getWhitePieces();
    UINT64 getBlackPieces();
    
    bool playerMv();
    bool cPlayerMv();
    
    UINT64 getTotalReach(UINT64 reach[16]);
    UINT8 getPiecesFromBitArray(UINT64 pieces);
    
    
};

const vector<INT8*> mvArray = vectorMvInit(); // vector with the information about the piece's movements



#endif /* defined(__Chess__chessBoard__) */
