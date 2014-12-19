//
//  chessBoard.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/17/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessBoard.h"

vector<INT8*> vectorMvInit()
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

ChessPiece newChessPiece(INT8 type, INT8 color, INT8 x, INT8 y)
{
    ChessPiece ncp = ChessPiece();
    ncp.initChessPiece(type,color, x, y);
    return ncp;
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
        for (INT8  j = 0; j < 8; j++) {
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
    printf("  +-----------------+\n");
    for (INT8  i = 7; i >= 0; i--) {
        printf("%d | ", i+1);
        for (INT8  j =0; j < 8; j++) {
            printf("%c ",c[i][j]);
        }
        printf("|\n");
    }
    printf("  +-----------------+\n    ");
    for (INT8  i = 0; i < 8; i++)
        printf("%c ",i+0x41);
    printf("\n\n");
}

void ChessBoard::setWhitePieces(UINT64 pieces)
{
    whitePieces = pieces;
}
void ChessBoard::setBlackPieces(UINT64 pieces)
{
    blackPieces = pieces;
}
UINT64 ChessBoard::getWhitePieces()
{
    return whitePieces;
}
UINT64 ChessBoard::getBlackPieces()
{
    return blackPieces;
}

ChessBoard::ChessBoard()
{
    wpArray.push_back(newChessPiece(KING,WHITE, 4, 0));
    bpArray.push_back(newChessPiece(KING,BLACK, 4, 7));
    
    wpArray.push_back(newChessPiece(QUEEN,WHITE, 3, 0));
    bpArray.push_back(newChessPiece(QUEEN,BLACK, 3, 7));
    
    wpArray.push_back(newChessPiece(BISHOP,WHITE, 2, 0));
    wpArray.push_back(newChessPiece(BISHOP,WHITE, 5, 0));
    bpArray.push_back(newChessPiece(BISHOP,BLACK, 2, 7));
    bpArray.push_back(newChessPiece(BISHOP,BLACK, 5, 7));
    
    wpArray.push_back(newChessPiece(KNIGHT,WHITE, 1, 0));
    wpArray.push_back(newChessPiece(KNIGHT,WHITE, 6, 0));
    bpArray.push_back(newChessPiece(KNIGHT,BLACK, 1, 7));
    bpArray.push_back(newChessPiece(KNIGHT,BLACK, 6, 7));
    
    wpArray.push_back(newChessPiece(ROOK,WHITE, 0, 0));
    wpArray.push_back(newChessPiece(ROOK,WHITE, 7, 0));
    bpArray.push_back(newChessPiece(ROOK,BLACK, 0, 7));
    bpArray.push_back(newChessPiece(ROOK,BLACK, 7, 7));
    
    for (int i = 0 ; i < 8 ; i++) {
        wpArray.push_back(newChessPiece(WPAWN,WHITE, i, 1));
        bpArray.push_back(newChessPiece(BPAWN,BLACK, i, 6));
    }
    
    for(int i = 0 ; i < BSIZE*BSIZE ; i++)
            board[i] = NULL;
    
    for(int i = 0 ; i < BSIZE*2 ; i++)
    {
        board[wpArray[i].y*8+wpArray[i].x] = &wpArray[i];
        whitePieces |= bitPos[wpArray[i].y*8+wpArray[i].x];
        
        board[bpArray[i].y*8+bpArray[i].x] = &bpArray[i];
        blackPieces |= bitPos[bpArray[i].y*8+bpArray[i].x];
    }
}


UINT64 ChessBoard::getReach(ChessPiece cp)
{
    UINT64 bitBoard = 0;
    UINT64 bitArray = whitePieces | blackPieces;
    INT8 k = 1;
    INT8 n;
    INT8 nx;
    INT8 ny;
    INT8 ring[lenghtMv[cp.type]/2];
    INT8 bp = blockedPath[cp.type];
    
    if (cp.type == KNIGHT || cp.type == KING)
    {
        n = 0;
        for (INT8 i = 0; i < lenghtMv[cp.type]; i=i+2) {
            
            if (bp & bitPos[n] ){
                nx = cp.x + mvArray[cp.type][i];
                ny = cp.y + mvArray[cp.type][i+1];
                if (nx < 0 || nx > 7 || ny < 0 || ny > 7)
                {
                    bp &= ~bitPos[n++];
                }
                else
                {
                    ring[n] = 8*ny + nx;
                    bitBoard |= bitPos[ring[n]];
                    if (bitArray & bitPos[ring[n]])
                    {
                        bp &= ~bitPos[n];
                    }
                    mvList.push_back(ring[n]);
                    n++;
                }
            }
            else
            {
                n++;
            }
        }
    }
    else if (cp.type == BPAWN || cp.type == WPAWN)
    {
        n = 0;
        INT8 nmv = lenghtMv[cp.type];
        if ((cp.type == BPAWN && cp.y == 6) || (cp.type == WPAWN && cp.y == 1))
        {
            nmv+=2;
        }
        
        for (INT8 i = 0; i < nmv; i=i+2)
        {
            nx = cp.x + mvArray[cp.type][i];
            ny = cp.y + mvArray[cp.type][i+1];
            if (!(nx < 0 || nx > 7 || ny < 0 || ny > 7))
            {
                ring[n] = 8*ny + nx;
                if ((i > 1 && i < 6 &&   bitArray & bitPos[ring[n]]) ||
                    ((i < 2 || i > 5) && !(bitArray & bitPos[ring[n]]
                                           )))
                {
                    bitBoard |= bitPos[ring[n]];
                    mvList.push_back(ring[n]);
                }
                n++;
            }
        }
    }
    else
    {
        do
        {
            n = 0;
            for (INT8 i = 0; i < lenghtMv[cp.type]; i=i+2) {
                
                if (bp & bitPos[n] ){
                    nx = cp.x + (k*mvArray[cp.type][i]);
                    ny = cp.y + (k*mvArray[cp.type][i+1]);
                    if (nx < 0 || nx > 7 || ny < 0 || ny > 7)
                    {
                        bp &= ~bitPos[n++];
                    }
                    else
                    {
                        ring[n] = 8*ny + nx;
                        bitBoard |= bitPos[ring[n]];
                        if (bitArray & bitPos[ring[n]])
                        {
                            bp &= ~bitPos[n];
                        }
                        mvList.push_back(ring[n]);
                        n++;
                    }
                }
                else
                {
                    n++;
                }
            }
            k++;
        }while (bp != 0);
    }
    return bitBoard;
}