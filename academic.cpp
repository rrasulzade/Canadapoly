//
//  academic.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "academic.hpp"
#include "player.hpp"

#define MAX_IMPROVEMENTS    6

using namespace std;


Academic::Academic(const string name, const pair<int,int> location, int status, const int cost, const int totalMonoBlocks, const string monopolyBlock, const int upgradeCost, int upgradeLevel, initializer_list<int> tuitions) : Ownable(name, location, status, cost, totalMonoBlocks),
                                        monopolyBlock(monopolyBlock),
                                        upgradeCost(upgradeCost),
                                        upgradeLevel(upgradeLevel)

{
    for(auto it: tuitions){
        tuitionCosts.push_back(it);
    }
}


Academic::~Academic(){}

string Academic::getMonopolyBlock() const{
    return this->monopolyBlock;
}

int Academic::getUpgradeCost() const{
    return this->upgradeCost;
}

int Academic::getUpgradeLevel() const{
    return this->upgradeLevel;
}

void Academic::setUpgradeLevel(int level){
    if(level >= 0 && level < MAX_IMPROVEMENTS)
     this->upgradeLevel = level;
}

int Academic::getRentalCost(const Player* p) const{
    if(this->getOwner()->hasMonopoly(this) && upgradeLevel == 0){
        return 2*tuitionCosts[upgradeLevel];
    }
    return tuitionCosts[upgradeLevel];
}
