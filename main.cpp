//
//  main.cpp
//  Chess
//
//  Created by Carlos Spaggiari on 12/12/14.
//  Copyright (c) 2014 ARSC. All rights reserved.
//

#include "board.h"

int main()
{
    board b = board();
    board b1 = board();
    
    b.fillBoard();
    b.fillTS();
    b.printboard();
    while (true)
    {
        b.command();
        if (b.ccmd[0]=='x') return 0;
        b.mvpiece();
        b.fillTS();
        b.printboard();
    }
    return 0;
}
