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
    b.fillBoard();
    b.printboard();
    while (true) {

        b.command();
        b.mvpiece();
        b.printboard();

    }
    return 0;
}
