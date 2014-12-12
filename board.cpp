//
//  board.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 11/29/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "board.h"

ChessPiece newPiece(int type, int x, int y)
{
    ChessPiece newp = ChessPiece(type,x,y);
    return newp;
}
/*
 7  R Kn B Q K B Kn R
 6  p  p p p p p p  p
 5  .  . . . . . .  .
 4  .  . . . . . .  .
 3  .  . . . . . .  .
 2  .  . . . . . .  .
 1  p  p p p p p p  p
 0  R Kn B Q K B Kn R
 
 0  1 2 3 4 5 6  7
 */
board::board(){}

void board::fillBoard()
{
    pl = true;
    pWhite.push_back(newPiece(KING|INGAME|(VALUE*KINGV), 4, 0));
    pBlack.push_back(newPiece(KING|ISBLACK|INGAME|(VALUE*KINGV), 4, 7));
    
    pWhite.push_back(newPiece(QUEEN|INGAME|(VALUE*QUEENV), 3, 0));
    pBlack.push_back(newPiece(QUEEN|ISBLACK|INGAME|(VALUE*QUEENV), 3, 7));
    
    pWhite.push_back(newPiece(BISHOP|INGAME|(VALUE*BISHOPV), 2, 0));
    pWhite.push_back(newPiece(BISHOP|INGAME|(VALUE*BISHOPV), 5, 0));
    pBlack.push_back(newPiece(BISHOP|ISBLACK|INGAME|(VALUE*BISHOPV), 2, 7));
    pBlack.push_back(newPiece(BISHOP|ISBLACK|INGAME|(VALUE*BISHOPV), 5, 7));
    
    pWhite.push_back(newPiece(KNIGHT|INGAME|(VALUE*KNIGHTV), 1, 0));
    pWhite.push_back(newPiece(KNIGHT|INGAME|(VALUE*KNIGHTV), 6, 0));
    pBlack.push_back(newPiece(KNIGHT|ISBLACK|INGAME|(VALUE*KNIGHTV), 1, 7));
    pBlack.push_back(newPiece(KNIGHT|ISBLACK|INGAME|(VALUE*KNIGHTV), 6, 7));
    
    pWhite.push_back(newPiece(ROOK|INGAME|(VALUE*ROOKV), 0, 0));
    pWhite.push_back(newPiece(ROOK|INGAME|(VALUE*ROOKV), 7, 0));
    pBlack.push_back(newPiece(ROOK|ISBLACK|INGAME|(VALUE*ROOKV), 0, 7));
    pBlack.push_back(newPiece(ROOK|ISBLACK|INGAME|(VALUE*ROOKV), 7, 7));
    
    for (int i = 0 ; i < 8 ; i++) {
        pWhite.push_back(newPiece(PAWN|INGAME|(VALUE*PAWN), i, 1));
        pBlack.push_back(newPiece(PAWN|ISBLACK|INGAME|(VALUE*PAWN), i, 6));
    }
    
    for(int i = 0 ; i < BSIZE ; i++)
        for ( int j = 0 ; j < BSIZE ; j++)
            space[i][j] = NULL;
    for (int  i = 0 ; i < pWhite.size() ; i++)
    {
        space[pWhite[i].x][pWhite[i].y] = &pWhite[i];
        space[pBlack[i].x][pBlack[i].y] = &pBlack[i];
    }
    for (int i =0; i < BSIZE; i++)
    {
        for(int j=0 ; j < BSIZE; j++)
        {
            ts[i][j][THREAT] = 0;
            ts[i][j][SAVE]   = 0;
        }
    }
}

void board::printboard()
{
    printf("  +");
    for(int i = 0 ;i <BSIZE ; i++)
    {
        printf("--");
    }
    string c = "";
    printf("-+\n");
    for(int i = BSIZE -1 ; i >= 0 ; i--)
    { printf("%d | ",i+1);
        for(int j = 0 ; j < BSIZE ; j++)
        {
            if (space[j][i] != NULL && (space[j][i]->type & INGAME))
            {
                if(space[j][i]->type & PAWN)
                    printf("P ");
                else if(space[j][i]->type & KNIGHT)
                    printf("Kn");
                else if(space[j][i]->type & BISHOP)
                    printf("B ");
                else if(space[j][i]->type & ROOK)
                    printf("R ");
                else if(space[j][i]->type & QUEEN)
                    printf("Q ");
                else if(space[j][i]->type & KING)
                    printf("K ");
            }
            else
                printf(". ");
        }
        printf("|\n");
    }
    printf("  +");
    for(int i = 0 ;i <BSIZE ; i++)
    {
        printf("--");
    }
    
    printf("-+\n    ");
    for(int i = 0 ;i <BSIZE ; i++)
    {
        printf("%c ",65+i);
    }
    printf("\n");
    for(int i = 0 ; i < 8 ; i ++)
    {
    
            printf("%c%d %d,%d    ",pBlack[i].x+97,pBlack[i].y+1,
                   (ts[pBlack[i].x][pBlack[i].y][THREAT]),
                   (ts[pBlack[i].x][pBlack[i].y][SAVE]));
        

            printf("%c%d %d,%d    ",pBlack[8+i].x+97,pBlack[8+i].y+1,
                   (ts[pBlack[8+i].x][pBlack[8+i].y][THREAT]),
                   (ts[pBlack[8+i].x][pBlack[8+i].y][SAVE]));
        

            printf("%c%d %d,%d    ",pWhite[i].x+97,pWhite[i].y+1,
                   (ts[pWhite[i].x][pWhite[i].y][THREAT]),
                   (ts[pWhite[i].x][pWhite[i].y][SAVE]));
        

            printf("%c%d %d,%d\n",pWhite[8+i].x+97,pWhite[8+i].y+1,
                   (ts[pWhite[8+i].x][pWhite[8+i].y][THREAT]),
                   (ts[pWhite[8+i].x][pWhite[8+i].y][SAVE]));
        
    }
}

int board::command()
{
    string c;
    cin >> c;
    if(c.size() != 4) {
        printf("Error en el comando.\n");
        return 0;
    }
    if(97 <= c[0] && c[0] < 105)    ccmd[0] = c[0] - 97;
    else if (65 <= c[0] && c[0] < 73) ccmd[0] = c[0] - 65;
    else
    {
        printf("Error en el comando. Se sale del rango x = %c \n",c[0]);
        return 0;
    }
    
    if (48 < c[1] && c[1] < 57) ccmd[1] = c[1] - 49;
    else
    {
        printf("Error en el comando. Se sale del rango y = %c\n",c[1]);
        return 0;
    }
    
    
    if(97 <= c[2] && c[2] < 105)      ccmd[2] = c[2] - 97;
    else if (65 <= c[2] && c[2] < 73) ccmd[2] = c[2] - 65;
    else
    {
        printf("Error en el comando. Se sale del rango x = %c \n",c[2]);
        return 0;
    }
    
    if (48 < c[3] && c[3] < 57) ccmd[3] = c[3] - 49;
    else
    {
        printf("Error en el comando. Se sale del rango y = %c\n",c[3]);
        return 0;
    }
    return 1;
}

int board::mvpiece()
{
    if (space[ccmd[0]][ccmd[1]] == NULL) {
        printf("No hay pieza en esta casilla\n");
        return 0;
    }
    ChessPiece *to = space[ccmd[2]][ccmd[3]];
    bool eat = false;
    if (to != NULL)
    {
        if( (pl && (to->type & ISBLACK)) || !(pl || (to->type & ISBLACK)))
        {
            eat = true;
        }
        else
        {
            printf("Error, casilla no vacia.\n");
            return 0;
        }
    }
    
    if(space[ccmd[0]][ccmd[1]]->mvp(ccmd[2], ccmd[3],pl,eat))
    {
        // Asigno la pieza a su nueva casilla
        space[ccmd[2]][ccmd[3]] = space[ccmd[0]][ccmd[1]];
        
        //borro de la tabla la vieja posicion
        space[ccmd[0]][ccmd[1]] = NULL;
        if (eat)
        {
            if (pl) {
                to->type = to->type & ~INGAME;
            }
        }
        return 1;
    }
    else
    {
        printf("No se puede mover la pieza de esa forma.\n");
    }
    return 0;
}

int board::threatTo(ChessPiece *piece)
{
    unsigned int max = 0;
    if(piece->type & PAWN)
    {
        int mv[4];
        mv[0] = 1;
        mv[2] = -1;
        if (piece->type & ISBLACK) mv[1] = mv[3] = -1;
        else                       mv[1] = mv[3] = 1;
        for (int i = 0 ; i < 4 ; i+=2)
        {
            int nx = piece->x + mv[i];
            int ny = piece->y + mv[i+1];
            if ( 0<= nx && nx < 8 && 0 <= ny && ny < 8)
            {
                if (space[nx][ny] != NULL)
                {
                    if((space[nx][ny]->type & ISBLACK)!=(piece->type & ISBLACK))
                    {
                        ts[nx][ny][1]++;
                        if ((space[nx][ny]->type & VALUE) > max )
                        {
                            max = (space[nx][ny]->type & VALUE);
                        }
                    }
                    else
                    {
                        ts[nx][ny][1]++;
                    }
                }
            }
        }
        

    }
    else if(piece->type & KNIGHT)
    {
        int mv[16] = {1,3,1,-3,-1,3,-1,-3,3,1,3,-1,-3,1,-3,-1};
        int nx,ny;
        for (int i = 0 ; i < 16 ; i+=2)
        {
            nx = piece->x + mv[i];
            ny = piece->y + mv[i+1];
            if ( 0<= nx && nx < 8 && 0 <= ny && ny < 8)
            {
                if((space[nx][ny]->type & ISBLACK)!=(piece->type & ISBLACK))
                {
                    ts[nx][ny][1]++;
                    if ((space[nx][ny]->type & VALUE) > max )
                    {
                        max = (space[nx][ny]->type & VALUE);
                    }
                }
                else
                {
                    ts[nx][ny][1]++;
                }
            }
        }
    }
    else if(piece->type & BISHOP)
    {
        int nx,ny;
        int mv[8] = {1,1,-1,1,-1,-1,1,-1};
        for (int i = 0 ; i < 8 ; i+=2)
        {
            nx = piece->x+mv[i];
            ny = piece->y+mv[i+1];
            while (0<= nx && nx < 8 && 0 <= ny && ny < 8) {

                if (space[nx][ny] != NULL)
                {
                    if((space[nx][ny]->type & ISBLACK)!=(piece->type & ISBLACK))
                    {
                        ts[nx][ny][1]++;
                        if ((space[nx][ny]->type & VALUE) > max )
                        {
                            max = (space[nx][ny]->type & VALUE);
                        }
                    }
                    else
                    {
                        ts[nx][ny][1]++;
                    }
                    break;
                }
                nx+=mv[i];
                ny+=mv[i+1];
            }
        }
    }
    else if(piece->type & ROOK)
    {
        int nx,ny;
        int mv[8] = {0,1,0,-1,-1,0,1,0};
        for (int i = 0 ; i < 8 ; i+=2)
        {
            nx = piece->x+mv[i];
            ny = piece->y+mv[i+1];
            while (0<= nx && nx < 8 && 0 <= ny && ny < 8) {
                if (space[nx][ny] != NULL)
                {
                    if((space[nx][ny]->type & ISBLACK)!=(piece->type & ISBLACK))
                    {
                        ts[nx][ny][1]++;
                        if ((space[nx][ny]->type & VALUE) > max )
                        {
                            max = (space[nx][ny]->type & VALUE);
                        }
                    }
                    else
                    {
                        ts[nx][ny][1]++;
                    }
                    break;
                }
                nx+=mv[i];
                ny+=mv[i+1];
            }
        }
    }
    else if(piece->type & QUEEN)
    {
        int nx,ny;
        int mv[16] = {1,1,-1,1,-1,-1,1,-1,0,1,0,-1,-1,0,1,0};
        for (int i = 0 ; i < 16 ; i+=2)
        {
            nx = piece->x+mv[i];
            ny = piece->y+mv[i+1];
            while (0<= nx && nx < 8 && 0 <= ny && ny < 8) {
                if (space[nx][ny] != NULL)
                {
                    if((space[nx][ny]->type & ISBLACK)!=(piece->type & ISBLACK))
                    {
                        ts[nx][ny][1]++;
                        if ((space[nx][ny]->type & VALUE) > max )
                        {
                            max = (space[nx][ny]->type & VALUE);
                        }
                    }
                    else
                    {
                        ts[nx][ny][1]++;
                    }
                    break;
                }
                nx+=mv[i];
                ny+=mv[i+1];
            }
        }
    }
    else if(piece->type & KING)
    {
        int mv[16] = {1,1,-1,1,-1,-1,1,-1,0,1,0,-1,-1,0,1,0};
        int nx,ny;
        for (int i = 0 ; i < 16 ; i+=2)
        {
            nx = piece->x + mv[i];
            ny = piece->y + mv[i+1];
            if ( 0<= nx && nx < 8 && 0 <= ny && ny < 8)
            {
                if((space[nx][ny]->type & ISBLACK)!=(piece->type & ISBLACK))
                {
                    ts[nx][ny][1]++;
                    if ((space[nx][ny]->type & VALUE) > max )
                    {
                        max = (space[nx][ny]->type & VALUE);
                    }
                }
                else
                {
                    ts[nx][ny][1]++;
                }
            }
        }
    }
    return 1;
}

int cpBoard(board *from, board *to)
{
    to->pBlack = from->pBlack;
    to->pWhite = from->pWhite;
    to->pl = !from->pl;
    for(int i = 0 ; i < BSIZE ; i++)
        for ( int j = 0 ; j < BSIZE ; j++)
            to->space[i][j] = NULL;
    for (int  i = 0 ; i < to->pWhite.size() ; i++)
    {
        to->space[to->pWhite[i].x][to->pWhite[i].y] = &to->pWhite[i];
        to->space[to->pBlack[i].x][to->pBlack[i].y] = &to->pBlack[i];
    }
    return 1;
}

