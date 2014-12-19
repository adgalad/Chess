//
//  chessPiece.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessPiece.h"

vector<INT8*> vectorInit()
{
    std::vector<INT8*> aux;
    aux.push_back(NULL);
    aux.push_back((INT8*)pawnMvWhite);
    aux.push_back((INT8*)pawnMvBlack);
    aux.push_back((INT8*)knightMv);
    aux.push_back((INT8*)bishopMv);
    aux.push_back((INT8*)rookMv);
    aux.push_back((INT8*)queenMv);
    aux.push_back((INT8*)kingMv);
    
    return aux;
}


void imprimir(UINT64 mv, UINT64 board, INT8 x, INT8  y)
{
    char c[8][8];
    for (INT8  i = 0; i < 8; i++) {
        for (INT8  j =0; j < 8; j++) {
            c[i][j] = '.';
        }
    }

    
    for (INT8  i = 0; i < 8; i++) {
        for (INT8  j =0; j < 8; j++) {
            if (board & 1 && mv & 1) {
                c[i][j] = 'V';
            }else {
            if(board & 1) c[i][j] = 'E';
            if(mv & 1) c[i][j] = 'x';
            }
            mv >>=1;
            board >>=1;
        }
    }
    c[y][x] = 'O';
    for (INT8  i = 0; i < 8; i++) {
        for (INT8  j =0; j < 8; j++) {
            printf("%c ",c[i][j]);
        }
        printf("\n");
    }
}

PieceGraph::PieceGraph()
{


}


UINT64 PieceGraph::getReach(INT8 type, INT8 x,  INT8 y, INT8 mvList[MAXMV], UINT64 board)
{
    UINT64 bitBoard = 0;
    INT8 k = 1;
    INT8 n;
    INT8 nx;
    INT8 ny;
    INT8 ring[lenghtMv[type]/8];
    INT8 bp = blockedPath[type];
    bool moreThanOnce;
    if (type == BPAWN || type == WPAWN || type == KNIGHT || type == KING)
        moreThanOnce = false;
    else
        moreThanOnce = true;
    
    do
    {
        n = 0;
        for (INT8 i = 0; i < lenghtMv[type]; i=i+2) {
            
            if (bp & bitPos[n] ){
                nx = x+(k*mvArray[type][i]);
                ny = (y + (k*mvArray[type][i+1]));
                if (nx < 0 || nx > 7 || ny < 0 || ny > 7)
                {
                    bp &= ~bitPos[n++];
                }
                else
                {
                    ring[n] = 8*ny + nx;
                    bitBoard |= bitPos[ring[n]];
                    if (board & bitPos[ring[n]])
                    {
                        bp &= ~bitPos[n];
                    }
                    mvList[n] = ring[n];
                    n++;
                }
            }
            else
            {
                n++;
            }
        }
        k++;
    }while (bp != 0 && moreThanOnce);

    
    mvList[n] = -1;
    return bitBoard;
}

