//
//  gameBoard.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef gameBoard_hpp
#define gameBoard_hpp

#include <iostream>
#include <string>

class Player;
class Slot;

class GameBoard{
    int totalPlayers;
    Player **players;
    Slot *slots[40];

public:
    GameBoard();
    ~GameBoard();

    void initializePlayers(const int playerNum);
    void addPlayer(const int id, const std::string name, const char symbol);
    std::pair<int,int> getLocationByID(const int slotID);

};

#endif /* gameBoard_hpp */
