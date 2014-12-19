//
//  chessPiece.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessPiece.h"

vector<UINT8*> vectorInit()
{
    std::vector<UINT8*> aux;
    aux.push_back(NULL);
    aux.push_back((UINT8*)pawnMvWhite);
    aux.push_back((UINT8*)pawnMvBlack);
    aux.push_back((UINT8*)knightMv);
    aux.push_back((UINT8*)bishopMv);
    aux.push_back((UINT8*)rookMv);
    aux.push_back((UINT8*)queenMv);
    aux.push_back((UINT8*)kingMv);
    
    return aux;
}


void imprimir(char mvList[56], UINT8  x, UINT8  y)
{
    char c[8][8];
    for (UINT8  i = 0; i < 8; i++) {
        for (UINT8  j =0; j < 8; j++) {
            c[i][j] = '.';
        }
    }
    UINT8  i = 0;
    while (mvList[i] >= 0) {
        c[mvList[i]][mvList[i+1]] = 'x';
        i+=2;
    }
    c[x][y] = 'O';
    for (UINT8  i = 0; i < 8; i++) {
        for (UINT8  j =0; j < 8; j++) {
            printf("%c ", c[j][i]);
        }
        printf("\n");
    }
}

PieceGraph::PieceGraph()
{
    for (UINT8 i=0 ; i < BSIZE; i++)
        for (UINT8 j=0 ; j < BSIZE; j++)
            this->reach[i][j] = (unsigned long int*) malloc(4);

}

void PieceGraph::initGraph(UINT8 type)
{

    
    UINT8 *mv = mvArray[type];
    UINT8 n = lenghtMv[type];
    for (UINT8 i = 0 ; i < BSIZE ; i++)
        for (UINT8 j=0 ; j < BSIZE; j++)
    {
        if ((j == 1 && WPAWN) || (j == 6 && BPAWN)) n+=2;
        for (UINT8 k = 0; k < n; k=k+2)
        {
            UINT8 x = i + mv[k];
            UINT8 y = j + mv[k+1];
            //if ( i == 1 && j == 1) printf(" %lu, (%d,%d) (%d,%d)\n",*reach[i][j],mv[k],mv[k+1],x,y);
            while (0 <= x && x < BSIZE && 0 <= y && y < BSIZE) {
                UINT64 sh = 1;
                *reach[i][j] |= (sh << (y*BSIZE+x));
                if (type == BPAWN || type == WPAWN || type == KING || type == KNIGHT) break;
                else {
                    x += mv[k];
                    y += mv[k+1];
                }
            }
        }
        if ((j == 1 && WPAWN) || (j == 6 && BPAWN)) n-=2;
    }
}

void PieceGraph::getReach(UINT8 x,  UINT8 y, UINT8 mvList[MAXMV], UINT64 board)
{
    UINT8 j = 0;
    UINT64 bitBoard = *reach[x][y];
    UINT64 ring;
    UINT8 *mv;
    strcpy(mv, mvArray[QUEEN]);
    for (UINT8 i = 0; i < lenghtMv[QUEEN]; i=i+2) {
        UINT64 shift = 1;
        ring |= shift << (8*(y+mv[i+1])+x+mv[i]);
    }
    for (UINT8 i = 0; i < BSIZE*BSIZE; i++)
    {
        //printf("%lu, %lu\n",bitBoard,*reach[x][y]);
        if (bitBoard & 1)
        {
            mvList[j++] = i % BSIZE;
            mvList[j++] = i / BSIZE;
        }
        bitBoard >>= 1;
    }
    mvList[j] = -1;
    
}

