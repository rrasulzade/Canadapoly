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
class Dice;

class GameBoard{
    int totalPlayers;
    Player **players;
    Slot *slots[40];
    Dice *dice;

    static int curPlayerID;

public:
    GameBoard();
    ~GameBoard();

    void initializePlayers(const int playerNum);
    Player* addPlayer(const int id, const std::string name, const char symbol, const int slotID);

    std::pair<int,int> getLocationBySlotID(const int slotID);
    Player* getPlayerByID(const int& playerID);
    Slot* getPropertyByID(const int& slotID);

    void updatePlayer(int& curPlayerID, const int& diceSum);
    int rollDice();
    std::string diceResults();
    bool isPair();
    bool isSlotFree(const int& slotID);
    bool isSlotOwned(const int& slotID);
    bool isSlotMortgaged(const int& slotID);
    bool tryBuy(const int& playerID, const int& slotID);

};

#endif /* gameBoard_hpp */
