#ifndef collectible_hpp
#define collectible_hpp

#include <iostream>
#include <string>

#include "slot.hpp"


class Player;

class Collectible: public Slot {
    int status;
    const int cost;
    const int totalMonoBlocks;
    int asset;
    Player *owner;

    // add enum for status sold free mortgaged
public:
    enum {FREE=0, OWNED=1, MORTGAGED=2};
	Collectible(const std::string name, const std::pair<int,int> location, const int cost, const int totalMonoBlocks);
    ~Collectible();

    int getStatus() const;
    int getCost() const;
    virtual int getRentalCost(const Player* p) const = 0;
    int getTotalBlocks() const;
    // virtual int getUpgradeCost() const;
    // virtual int getUpgradeLevel() const;
    virtual std::string getMonopolyBlock() const;
    int getAsset() const;
    Player* getOwner() const;

    void setOwner(Player* owner);
    void setAsset(const int& value);

    void mortgage();
    void unmortgage();

};

#endif /* collectible_hpp */
