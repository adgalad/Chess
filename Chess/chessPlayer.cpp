//
//  chessPlayer.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/19/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "chessBoard.h"

bool ChessBoard::playerMv()
{
    string str;
    cin >> str;
    if (str.size() != 4)
    {
        printf("Error, el comando debe tener el formato \"a1b2\"\n");
        return false;
    }
    if (str[0] >= 0x41 && str[0] < 0x49)      str[0] -= 0x41;
    else if (str[0] >= 0x61 && str[0] < 0x69) str[0] -= 0x61;
    else
    {
        printf("Error, se sale del rango1 %d\n",str[0]);
        return false;
    }
    
    if (str[2] >= 0x41 && str[2] < 0x49)       str[2] -= 0x41;
    else if (str[2] >= 0x61 && str[2] < 0x69)  str[2] -= 0x61;
    else
    {
        printf("Error, se sale del rango3 %d\n",str[2]);
        return false;
    }
    if(str[1] >= 0x31 && str[1] < 0x39) str[1] -= 0x31;
    else
    {
        printf("Error, se sale del rango2 %d\n",str[1]);
        return false;
    }
    if(str[3] >= 0x31 && str[3] < 0x39) str[3] -= 0x31;
    else
    {
        printf("Error, se sale del rango4 %d\n",str[3]);
        return false;
    }
    INT8 newPos = 8*str[3]+str[2];
    INT8 oldPos = 8*str[1]+str[0];
    
    if (board[oldPos]->color == BLACK) {
        printf("Error, no puedes mover una pieza del jugador contrario\n");
        return false;
    }
    UINT64 m = getReach(*board[oldPos]);
    if((m & bitPos[newPos])&& !(blackPieces & bitPos[newPos]))
    {
        printf("(%d,%d) (%d,%d)\n",str[0],str[1],str[2],str[3]);
        board[newPos] = board[oldPos];
        board[oldPos] =  NULL;
        board[newPos]->x = str[2];
        board[newPos]->y = str[3];
        whitePieces &= ~bitPos[oldPos];
        whitePieces |= bitPos[newPos];
    }
    
    for(INT8 i = 0;i < mvList.size() ; i++)
        printf("%d (%d,%d)\n",mvList[i],mvList[i]%8,mvList[i]/8);
    return true;
}