#ifndef vicinity_hpp
#define vicinity_hpp

#include <iostream>
#include <string>
#include <vector>

#include "collectible.hpp"


class Vicinity: public Collectible {
    std::string monopolyBlock;
    const int upgradeCost;
    int upgradeLevel;
    std::vector<int> tuitionCosts;
public:
	Vicinity(const std::string name, const std::pair<int,int> location, const int cost, const int totalMonoBlocks, const std::string monopolyBlock, const int upgradeCost, int upgradeLevel, std::initializer_list<int> tuitions);
    ~Vicinity();

    std::string getMonopolyBlock() const;
    int getUpgradeCost() const;
    int getUpgradeLevel() const;
    int getRentalCost(const Player* p) const;

    void setUpgradeLevel(int level);

};

#endif /* vicinity_hpp */
