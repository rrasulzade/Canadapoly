//
//  academic.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef academic_hpp
#define academic_hpp

#include <iostream>
#include <string>
#include <vector>

#include "ownable.hpp"


class Academic: public Ownable{
    std::string monopolyBlock;
    const int upgradeCost;
    int upgradeLevel;
    std::vector<int> tuitionCosts;
public:
    Academic(const std::string name, const std::pair<int,int> location, int status, const int cost, const int totalMonoBlocks, const std::string monopolyBlock, const int upgradeCost, int upgradeLevel, std::initializer_list<int> tuitions);
    ~Academic();

    std::string getMonopolyBlock() const;
    int getUpgradeCost() const;
    int getUpgradeLevel() const;
    int getRentalCost(const Player* p) const;

    void setUpgradeLevel(int level);

};

#endif /* academic_hpp */
