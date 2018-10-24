//
//  main.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-03.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include <iostream>
#include <string>
#include "gameBoard.hpp"
#include "textDisplay.hpp"
#include "controller.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, Monopoly!\n";

    GameBoard *board = new GameBoard;
    TextDisplay *td = new TextDisplay;

    Controller *controller = new Controller(board, td);

    // initialize slots and players, and print the board
    controller->initialize();

    // start the game
    controller->play();

    return 0;
}
