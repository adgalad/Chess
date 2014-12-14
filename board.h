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

typedef struct{
    char mv[4];
    int max;
}cpmv;

class board {
public:
    ChessPiece *space[BSIZE][BSIZE];
    char ts[BSIZE][BSIZE][2];
    vector<ChessPiece> pWhite;
    vector<ChessPiece> pBlack;
    int threat;
    bool pl; // true player, false cp
    int  ccmd[4];
    
public:
    board();
    void fillBoard();
    void fillTS();
    void printboard();
    
    int  command();
    int mvpiece();
    int threatTo(ChessPiece *piece, bool tsb);
    int fcpmv();
    
};

ChessPiece newPiece(int type, int x, int y);

int cpBoard(board *from, board *to);

cpmv mvtree(board *b,int n);

#endif /* defined(__Chess__board__) */
