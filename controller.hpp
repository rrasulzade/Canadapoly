//
//  controller.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef controller_hpp
#define controller_hpp

#include <iostream>
// #include "gameBoard.hpp"
// #include "textDisplay.hpp"

class GameBoard;
class TextDisplay;

class Controller {
    GameBoard *board;
    TextDisplay *td;
public:
    Controller(GameBoard *board, TextDisplay *td);
    ~Controller();

    void play();
};

#endif /* controller_hpp */
