//
//  main.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/12/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "board.h"

int SDL_main (int argc, char **argv)
{
    board b = board();
    board b1 = board();
    b.fillBoard();
    b.fillTS();
    b.printboard();
    while (true)
    {
        do
        {
            while(!b.command());
            if (b.ccmd[0]=='x') return 0;
        }while(b.mvpiece() == -1);
        b.fillTS();
        b.printboard();
        b.fcpmv();
        printf("A:%d, x=%d, Y=%d, nx=%d, ny=%d\n",b.pl,b.ccmd[0],b.ccmd[1],b.ccmd[2],b.ccmd[3]);
        b.mvpiece();
        b.fillTS();
        b.printboard();
        b.pl = !b.pl;
    }
    return 0;
}
