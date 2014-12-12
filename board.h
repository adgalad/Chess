//
//  board.h
//  Chess
//
//  Created by Carlos Spaggiari on 11/29/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#ifndef __Chess__board__
#define __Chess__board__

#include "chessHeader.h"
#include "chessmen.h"
using namespace std;

class board {
public:
    ChessPiece *space[BSIZE][BSIZE];
    char ts[BSIZE][BSIZE][2];
    vector<ChessPiece> pWhite;
    vector<ChessPiece> pBlack;
    int threat;
    bool pl;
    int  ccmd[4];
    
public:
    board();
    void fillBoard();
    void printboard();
    int  command();
    int mvpiece();
    int threatTo(ChessPiece *piece);
};

ChessPiece newPiece(int type, int x, int y);

int cpBoard(board *from, board *to);

#endif /* defined(__Chess__board__) */
