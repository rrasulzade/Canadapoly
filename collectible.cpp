#include "collectible.hpp"
#include "player.hpp"

using namespace std;

Collectible::Collectible(const string name, const pair<int,int> location, const int cost, const int totalMonoBlocks): Slot(name, location), status(Collectible::FREE), cost(cost), totalMonoBlocks(totalMonoBlocks){
    this->owner = nullptr;
    this->asset = cost;
}

Collectible::~Collectible(){}

int Collectible::getStatus() const{
    return this->status;
}

int Collectible::getCost() const{
    return this->cost;
}

// int Ownable::getRentalCost(const Player* p) const{
//     return 0;
// }

int Collectible::getTotalBlocks() const{
    return this->totalMonoBlocks;
}

// int Ownable::getUpgradeCost() const{
//     return 0;
// }
//
// int Ownable::getUpgradeLevel() const{
//     return -1;
// }

int Collectible::getAsset() const{
    return this->asset;
}

string Collectible::getMonopolyBlock() const{
    return "Collectible";
}

Player* Collectible::getOwner() const{
    return this->owner;
}

void Collectible::setOwner(Player* owner){
    this->owner = owner;
    this->status = Collectible::OWNED;
}

void Collectible::setAsset(const int& value){
    this->asset += value;
}

void Collectible::mortgage(){
    this->status = Collectible::MORTGAGED;
    this->owner->updateBalance(cost/2);
}

void Collectible::unmortgage(){
    this->status = Collectible::OWNED;
    this->owner->updateBalance(-1*cost/2*1.10);
}
