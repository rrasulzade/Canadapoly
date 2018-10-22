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
#include <map>

// #include "textDisplay.hpp"

class GameBoard;
class TextDisplay;

class Controller {
    GameBoard *board;
    TextDisplay *td;
    std::map <char, std::string> symbols;


    void printSymbols();
    bool checkAndUpdateSymbols(const char &symbol);

public:
    Controller(GameBoard *board, TextDisplay *td);
    ~Controller();

    void initialize();
    void play();

};

#endif /* controller_hpp */
