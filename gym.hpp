//
//  gym.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef gym_hpp
#define gym_hpp

#include <iostream>
#include <string>
#include "ownable.hpp"

class Gym: public Ownable{

public:
    Gym(const std::string name, const std::pair<int,int> location, int status, const int cost, const int totalMonoBlocks);
    ~Gym();

    std::string getMonopolyBlock() const;
    int getRentalCost(const Player* p) const;
};


#endif /* gym_hpp */
