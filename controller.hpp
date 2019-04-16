#ifndef controller_hpp
#define controller_hpp

#include <iostream>
#include <map>

// #include "textDisplay.hpp"

class GameBoard;
class TextDisplay;
class Player;
class Collectible;

class Controller {
    GameBoard *board;
    TextDisplay *td;
    std::map <char, std::string> symbols;
    int curPlayerID;
    int totalPlayers;

    void printSymbols();
    bool checkAndUpdateSymbols(const char &symbol);
    void finishTrade(Player* p1, Player* p2, Collectible *give, Collectible *receive);
    void finishTrade(Player* p1, Player* p2, int money, Collectible *property);
    void endTurn(Player** p);

public:
    Controller(GameBoard *board, TextDisplay *td);
    ~Controller();

    void initialize();
    void play();
    bool mortgage(Player* p, const std::string& propertyName);
    bool unmortgage(Player* p, const std::string& propertyName);
    bool trade(Player* p, const std::string& in);
    bool improve(Player* p, const std::string& in);
    bool payDebt(Collectible* property, Player* p);
    bool auction(int playerID, int propertyID);

    bool handleLowBalance(Player* player, int moneyNeeded, bool forced=false);
    bool payTimsLineFee(Player* p);

};

#endif /* controller_hpp */
