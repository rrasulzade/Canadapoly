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
class Player;
class Ownable;

class Controller {
    GameBoard *board;
    TextDisplay *td;
    std::map <char, std::string> symbols;
    int curPlayerID;
    int totalPlayers;

    void printSymbols();
    bool checkAndUpdateSymbols(const char &symbol);
    void finishTrade(Player* p1, Player* p2, Ownable *give, Ownable *receive);
    void finishTrade(Player* p1, Player* p2, int money, Ownable *property);

public:
    Controller(GameBoard *board, TextDisplay *td);
    ~Controller();

    void initialize();
    void play();
    bool mortgage(Player* p, const std::string& propertyName);
    bool unmortgage(Player* p, const std::string& propertyName);
    bool trade(Player* p, const std::string& in);
    bool improve(Player* p, const std::string& in);
    bool payDebt(Ownable* property, Player* p);
    // auction
    // go to tims / get out Tims


};

#endif /* controller_hpp */
