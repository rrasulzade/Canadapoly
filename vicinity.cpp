#include "vicinity.hpp"
#include "player.hpp"

#define MAX_IMPROVEMENTS    6

using namespace std;


Vicinity::Vicinity(const string name, const pair<int,int> location, const int cost, const int totalMonoBlocks, const string monopolyBlock, const int upgradeCost, int upgradeLevel, initializer_list<int> tuitions) : Collectible(name, location, cost, totalMonoBlocks),
                                        monopolyBlock(monopolyBlock),
                                        upgradeCost(upgradeCost),
                                        upgradeLevel(upgradeLevel)

{
    for(auto it: tuitions){
        tuitionCosts.push_back(it);
    }
}


Vicinity::~Vicinity(){}

string Vicinity::getMonopolyBlock() const{
    return this->monopolyBlock;
}

int Vicinity::getUpgradeCost() const{
    return this->upgradeCost;
}

int Vicinity::getUpgradeLevel() const{
    return this->upgradeLevel;
}

void Vicinity::setUpgradeLevel(int level){
    if(level >= 0 && level < MAX_IMPROVEMENTS)
     this->upgradeLevel = level;
}

int Vicinity::getRentalCost(const Player* p) const{
    if(this->getOwner()->hasMonopoly(this) && upgradeLevel == 0){
        return 2*tuitionCosts[upgradeLevel];
    }
    return tuitionCosts[upgradeLevel];
}
