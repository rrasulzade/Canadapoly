//
//  gym.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "gym.hpp"
#include "player.hpp"

using namespace std;


Gym:: Gym(const string name, const pair<int,int> location, int status, const int cost, const int totalMonoBlocks): Ownable(name, location, status, cost, totalMonoBlocks){}
Gym:: ~Gym(){}

string Gym::getMonopolyBlock() const{
    return "Gym";
}

int Gym::getRentalCost(const Player* p) const{
    if(this->getOwner()->hasMonopoly(this))
        return 10;
    return 4;
}
