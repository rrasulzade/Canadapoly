#ifndef gameBoard_hpp
#define gameBoard_hpp

#include <iostream>
#include <string>

extern const int TUITION_FEE;
extern const int COOP_FEE;

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
    Player* getPlayerByName(const std::string& name);
    Slot* getSlotByID(const int& slotID);
    Slot* getSlotByName(const std::string& slotName);


    void movePlayer(int& curPlayerID, const int& diceSum);
    int rollDice();
    std::string diceResults();
    bool isPair();
    bool isSlotFree(const int& slotID);
    bool isSlotOwned(const int& slotID);
    bool isSlotMortgaged(const int& slotID);
    bool tryBuy(const int& playerID, const int& slotID);
    bool tryPayTuitionFee(int playerID);
    bool tryPayCoopFee(int playerID);
    void collectOSAP(int playerID);

    void setDice(int d1, int d2);
};

#endif /* gameBoard_hpp */
