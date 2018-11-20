//
//  ownable.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "ownable.hpp"
#include "player.hpp"

using namespace std;

Ownable::Ownable(const string name, const pair<int,int> location, int status, const int cost, const int totalMonoBlocks): Slot(name, location), status(status), cost(cost), totalMonoBlocks(totalMonoBlocks){
    this->owner = nullptr;
    this->asset = cost;
}

Ownable::~Ownable(){}

int Ownable::getStatus() const{
    return this->status;
}

int Ownable::getCost() const{
    return this->cost;
}

// int Ownable::getRentalCost(const Player* p) const{
//     return 0;
// }

int Ownable::getTotalBlocks() const{
    return this->totalMonoBlocks;
}

// int Ownable::getUpgradeCost() const{
//     return 0;
// }
//
// int Ownable::getUpgradeLevel() const{
//     return -1;
// }

int Ownable::getAsset() const{
    return this->asset;
}

string Ownable::getMonopolyBlock() const{
    return "Ownable";
}

Player* Ownable::getOwner() const{
    return this->owner;
}

void Ownable::setOwner(Player* owner){
    this->owner = owner;
    this->status = Ownable::OWNED;
}

void Ownable::setAsset(const int& value){
    this->asset += value;
}

void Ownable::mortgage(){
    this->status = Ownable::MORTGAGED;
    this->owner->updateBalance(cost/2);
}

void Ownable::unmortgage(){
    this->status = Ownable::OWNED;
    this->owner->updateBalance(-1*cost/2*1.10);
}
