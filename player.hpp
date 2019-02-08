#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <string>
#include <vector>

class Collectible;

class Player {
    const std::string name;
    const char piece;
    const int id;
    int doublesCounter;
    bool inJail;
    unsigned int money;
    int position;
    std::vector<Collectible* > properties;

    static int playerID;

public:
    Player(const std::string name, const char piece, int position);
    ~Player();

    bool hasMonopoly(const Collectible* property) const;
    int countOwnedBlocks(const Collectible* property) const;

    // ACCESSORS
    int getPosition() const;
    std::string getName() const;
    int getID() const;
    char getPiece() const;
    int getBalance() const;
    int getPropertyCount() const;
    int getDoublesCounter() const;
    bool isInJail() const;

    void increaseDoublesCounter(int val=1);
    void decreaseDoublesCounter(int val=1);
    void setDoublesCounter(int val);
    void setPosition(const int position);
    void setJail(bool value);
    void updateBalance(const int amount);
    void attachProperty(Collectible* property);
    void detachProperty(Collectible* property);
};

#endif /* player_hpp */
