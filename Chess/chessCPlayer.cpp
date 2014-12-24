//
//  chessCPlayer.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/19/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessBoard.h"


UINT64 ChessBoard::getTotalReach(INT8 color)
{
    if (color == BLACK)
    {
    return getReach(bpArray[0])  | getReach(bpArray[1])  | getReach(bpArray[2])|
           getReach(bpArray[3])  | getReach(bpArray[4])  | getReach(bpArray[5])|
           getReach(bpArray[6])  | getReach(bpArray[7])  | getReach(bpArray[8])|
           getReach(bpArray[9])  | getReach(bpArray[10]) | getReach(bpArray[11])|
           getReach(bpArray[12]) | getReach(bpArray[13]) | getReach(bpArray[14])|
           getReach(bpArray[15]);
    }
    else
    {
    return getReach(wpArray[0])  | getReach(wpArray[1])  | getReach(wpArray[2])|
           getReach(wpArray[3])  | getReach(wpArray[4])  | getReach(wpArray[5])|
           getReach(wpArray[6])  | getReach(wpArray[7])  | getReach(wpArray[8])|
           getReach(wpArray[9])  | getReach(wpArray[10]) | getReach(wpArray[11])|
           getReach(wpArray[12]) | getReach(wpArray[13]) | getReach(wpArray[14])|
           getReach(wpArray[15]);
    }
}
UINT8 ChessBoard::getPiecesFromBitArray(UINT64 pieces)
{

    UINT8 max = 0;
    UINT8 res = 0;
    for (UINT8 i = 0; i < BSIZE*BSIZE && pieces > 0 ; i++)
    {
        if (pieces & 1 && (whitePieces|blackPieces)&bitPos[i])
        {
           if(max < board[i]->type && board[i]->type != 7)
           {
               max = board[i]->type;
               res = i;
           }
        }
        pieces >>=1;
    }
    return res;
}

void ChessBoard::moveBlackPiece(UINT8 oldPos, UINT8 newPos)
{
    blackPieces &= ~bitPos[oldPos];
    blackPieces |= bitPos[newPos];
    board[newPos] = board[oldPos];
    printf("Son nulos: NewPos = %d oldPos = %d \n", newPos,oldPos);
    board[oldPos] = NULL;
    board[newPos]->pos = newPos;
    board[newPos]->bit = bitPos[newPos];
    board[newPos]->x = newPos%BSIZE;
    board[newPos]->y = newPos/BSIZE;
    getNewReach(bitPos[oldPos]|bitPos[newPos]);
}

bool ChessBoard::cPlayerMv()
{
    UINT64 bm = getTotalReach(BLACK);
    UINT64 wm = getTotalReach(WHITE);
    /*************/
    /* MOVE MATE */
    /*************/
    if (wm & bitPos[bpArray[0].pos])
    {
        UINT64 WhiteAttackers = 0;
        for (UINT8 i = 1; i < 16 ; i++)
        {
            if (whiteReach[i] & bitPos[bpArray[0].pos])
            {
                WhiteAttackers |= bitPos[wpArray[i].pos];
            }
        }
        if (bm & WhiteAttackers)
        {
            printf("0.0\n");
            INT8 newPos = 0;
            INT8 oldPos = 0;
            WhiteAttackers &= bm;
            newPos = getPiecesFromBitArray(WhiteAttackers);
            for(UINT8 i = 15; i >= 0 ; i--)
            {
                if (blackReach[i] & bitPos[newPos])
                {
                    oldPos = bpArray[i].pos;
                    break;
                }
            }
            if ((WhiteAttackers & ~bitPos[newPos]) == 0)
            {
                whitePieces &= ~bitPos[newPos];
                board[newPos]->type = OUT;
                moveBlackPiece(oldPos, newPos);
                return true;
            }
        }
        if (blackReach[bpArray[0].id] & ~wm & ~blackPieces & whitePieces)
        {
            printf("0.1\n");
            UINT64 nextMv = blackReach[bpArray[0].id] & ~wm & ~blackPieces & whitePieces;
            INT8 newPos = 0;
            while (!(nextMv & 1))
            {
                newPos++;
                nextMv >>=1;
            }
            
            whitePieces &= ~bitPos[newPos];
            board[newPos]->type = OUT;
            moveBlackPiece(bpArray[0].pos, newPos);
            return true;
        }
        else if (blackReach[bpArray[0].id] & ~wm & ~blackPieces)
        {
            printf("0.2\n");
            imprimir(wm,0 , -1, -1);
            UINT64 nextMv = blackReach[bpArray[0].id] & ~wm & ~blackPieces;
            INT8 newPos = 0;
            while (!(nextMv & 1))
            {
                newPos++;
                nextMv >>=1;
            }
            moveBlackPiece(bpArray[0].pos, newPos);
            getNewReach(bitPos[bpArray[0].pos]|bitPos[newPos]);
            return true;
        }
        return false;
    }
    
    UINT64 nextMv = blackPieces & wm & ~bm;
    
    if (nextMv != 0)
    {
        
        UINT8 oldPos = getPiecesFromBitArray(nextMv);
        UINT8 newPos =0;
        UINT64 auxPos = blackReach[board[oldPos]->id];
        if (auxPos & ~wm)
        {
            if (auxPos & whitePieces & ~wm & ~blackPieces)
            {
                if (auxPos & whitePieces & ~wm & bm & ~blackPieces)
                {
                    printf("1.1\n");
                    nextMv = auxPos & whitePieces & ~wm & bm & ~blackPieces;
                    while (!(nextMv & 1))
                    {
                        newPos++;
                        nextMv >>=1;
                    }
                    
                    whitePieces &= ~bitPos[newPos];
                    board[newPos]->type = OUT;
                }
                else
                {
                    printf("1.2\n");
                    nextMv = auxPos & whitePieces & ~wm & ~blackPieces;
                    while (!(nextMv & 1))
                    {
                        newPos++;
                        nextMv >>=1;
                    }
                    whitePieces &= ~bitPos[newPos];
                    board[newPos]->type = OUT;
                }
            }
            else if (auxPos & ~wm & bm & ~blackPieces)
            {
                printf("1.3\n");
                nextMv = auxPos & ~wm & bm & ~blackPieces;
                while (!(nextMv & 1))
                {
                    newPos++;
                    nextMv >>=1;
                }
            }
            else {
                printf("1.3.1 No aplica \n");
            }
        }
        else
        {
            if(auxPos & bm & ~blackPieces)
            {
                if (auxPos & bm & whitePieces & ~blackPieces)
                {
                    printf("1.4\n");
                    nextMv = auxPos & bm & whitePieces & ~blackPieces;
                    while (!(nextMv & 1))
                    {
                        newPos++;
                        nextMv >>=1;
                    }
                    whitePieces &= ~bitPos[newPos];
                    board[newPos]->type = OUT;
                }
                else
                {
                    printf("1.5\n");
                    nextMv = auxPos & bm & ~blackPieces;
                    while (!(nextMv & 1))
                    {
                        newPos++;
                        nextMv >>=1;
                    }
                }
            }
            else if (auxPos & whitePieces & ~blackPieces)
            {
                printf("1.6\n");
                nextMv = auxPos & whitePieces & ~blackPieces;
                while (!(nextMv & 1))
                {
                    newPos++;
                    nextMv >>=1;
                }
            }
            else
             {
                 printf("1.7 No aplica\n");
                ///- Buscar si hay otra pieza amenazada
                //- Revisar que otras piezas puedan moverse para resguardarla
             }
             
            
        }
        if (newPos >= 0)
        {
            moveBlackPiece(oldPos, newPos);
            return true;
        }
    }
    nextMv = whitePieces & bm & ~wm;
    if (nextMv != 0)
    {
        printf("2\n");
        UINT8 newPos =0;
        while (!(nextMv & 1))
        {
            newPos++;
            nextMv >>=1;
        }
        for (INT8 oldPos = 0; oldPos < BSIZE*2; oldPos++)
        {
            if (blackReach[oldPos] & bitPos[newPos])
            {
                oldPos = bpArray[oldPos].y*8 + bpArray[oldPos].x;
                printf("(%d,%d) => (%d,%d)\n",oldPos%8,oldPos/8,newPos%8,newPos/8);
                if (whitePieces & bitPos[newPos])
                {
                    whitePieces &= ~bitPos[newPos];
                    board[newPos]->type = OUT;
                }
                moveBlackPiece(oldPos, newPos);
                return true;
            }
        }
        return true;
    }
    nextMv = bm & ~wm & ~blackPieces;
    if (nextMv != 0)
    {
        printf("3\n");
        INT8 newPos=0;
        
        while (!(nextMv & 1))
        {
            newPos++;
            nextMv >>=1;
        }
        
        for (INT8 oldPos = 0; oldPos < BSIZE*2; oldPos++)
        {
            if (blackReach[oldPos] & bitPos[newPos])
            {
                oldPos = bpArray[oldPos].y*8 + bpArray[oldPos].x;
                printf("(%d,%d) => (%d,%d)\n",oldPos%8,oldPos/8,newPos%8,newPos/8);
                blackPieces &= ~bitPos[oldPos];
                blackPieces |= bitPos[newPos];
                if (whitePieces & bitPos[newPos])
                {
                    board[newPos]->type = OUT;
                    whitePieces &= ~bitPos[newPos];
                }
                moveBlackPiece(oldPos, newPos);
                return true;
            }
        }
        return true;
    }
    printf("No entro a ningun lado!");
    return true;
}