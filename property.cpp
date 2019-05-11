#include "property.hpp"
#include "player.hpp"

#define MAX_IMPROVEMENTS    6

using namespace std;


Property::Property(const string name, const pair<int,int> location, const int cost, const int totalMonoBlocks, const string monopolyBlock, const int upgradeCost, int upgradeLevel, initializer_list<int> tuitions) : Collectible(name, location, cost, totalMonoBlocks),
                                        monopolyBlock(monopolyBlock),
                                        upgradeCost(upgradeCost),
                                        upgradeLevel(upgradeLevel)

{
    for(auto it: tuitions){
        tuitionCosts.push_back(it);
    }
}


Property::~Property(){}

string Property::getMonopolyBlock() const{
    return this->monopolyBlock;
}

int Property::getUpgradeCost() const{
    return this->upgradeCost;
}

int Property::getUpgradeLevel() const{
    return this->upgradeLevel;
}

void Property::setUpgradeLevel(int level){
    if(level >= 0 && level < MAX_IMPROVEMENTS)
     this->upgradeLevel = level;
}

int Property::getRentalCost(const Player* p) const{
    if(this->getOwner()->hasMonopoly(this) && upgradeLevel == 0){
        return 2*tuitionCosts[upgradeLevel];
    }
    return tuitionCosts[upgradeLevel];
}
