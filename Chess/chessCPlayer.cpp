//
//  chessCPlayer.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/19/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessBoard.h"

UINT64 ChessBoard::getTotalReach(UINT64 reach[16])
{
    return reach[0]  | reach[1]  | reach[2]  | reach[3]  |
           reach[4]  | reach[5]  | reach[6]  | reach[7]  |
           reach[8]  | reach[9]  | reach[10] | reach[11] |
           reach[12] | reach[13] | reach[14] | reach[15];
}
UINT8 ChessBoard::getPiecesFromBitArray(UINT64 pieces)
{

    UINT8 max = 0;
    UINT8 res = 0;
    for (UINT8 i = 0; i < BSIZE*BSIZE && pieces > 0 ; i++)
    {
        if (pieces & 1 && board[i] != NULL && max < board[i]->type)
        {
            max = board[i]->type;
            res = i;
        }
        pieces >>=1;
    }
    return res;
}

bool ChessBoard::cPlayerMv()
{
    UINT64 bm = getTotalReach(blackReach);
    UINT64 wm = getTotalReach(whiteReach);
    UINT64 nextMv = blackPieces & wm & ~bm;
    
    if (nextMv != 0)
    {
        printf("1\n");
        UINT8 oldPos = getPiecesFromBitArray(nextMv);
        UINT8 a = getPiecesFromBitArray(blackReach[board[oldPos]->id]| ~wm);
        blackPieces &= ~bitPos[oldPos];
        blackPieces |= bitPos[a];
        board[a] = board[oldPos];
        board[oldPos] = NULL;
        board[a]->x = a%8;
        board[a]->y = a/8;
        blackReach[board[a]->id] = getReach(*board[a]);
        return true;
    }
    nextMv = whitePieces & bm & ~wm;
    if (nextMv != 0)
    {
        printf("2\n");
        UINT8 wt =0;
        while (!(nextMv & 1))
        {
            wt++;
            nextMv >>=1;
        }
        imprimir(whitePieces & bm & ~wm, blackPieces|whitePieces, 0, 0);
        printf("(%d,%d) \n",wt%8,wt/8);
        for (INT8 i = 0; i < BSIZE*2; i++)
        {
            if (blackReach[i] & bitPos[wt])
            {
                i = bpArray[i].y*8 + bpArray[i].x;
                printf("(%d,%d) => (%d,%d)\n",i%8,i/8,wt%8,wt/8);
                blackPieces &= ~bitPos[i];
                blackPieces |= bitPos[wt];
                board[wt] = board[i];
                board[i] = NULL;
                board[wt]->x = wt%8;
                board[wt]->y = wt/8;
                blackReach[board[wt]->id] = getReach(*board[wt]);
                return true;
            }
        }
        return false;
    }
    nextMv = bm & ~wm & ~blackPieces;
    if (nextMv != 0)
    {
        printf("3\n");
        INT8 wt=0;
        
        while (!(nextMv & 1))
        {
            wt++;
            nextMv >>=1;
        }
        
        for (INT8 i = 0; i < BSIZE*2; i++)
        {
            if (blackReach[i] & bitPos[wt])
            {
                i = bpArray[i].y*8 + bpArray[i].x;
                printf("(%d,%d) => (%d,%d)\n",i%8,i/8,wt%8,wt/8);
                blackPieces &= ~bitPos[i];
                blackPieces |= bitPos[wt];
                board[wt] = board[i];
                board[i] = NULL;
                board[wt]->x = wt%8;
                board[wt]->y = wt/8;
                blackReach[board[wt]->id] = getReach(*board[wt]);
                return true;
            }
        }
        return false;
    }
    return true;
}