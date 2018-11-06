//
//  residence.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "residence.hpp"
#include "player.hpp"

using namespace std;

Residence::Residence(const std::string name, const pair<int,int> location, int status, const int cost, const int totalMonoBlocks): Ownable(name, location, status, cost, totalMonoBlocks){}
Residence:: ~Residence(){}

string Residence::getMonopolyBlock() const {
    return "Residence";
}

int Residence::getRentalCost(const Player* p) const{
    int totalRez = this->getOwner()->countOwnedBlocks(this);
    int cost = 0;
    switch (totalRez) {
        case 1:
            cost = 25;
            break;
        case 2:
            cost = 50;
            break;
        case 3:
            cost = 100;
            break;
        case 4:
            cost = 200;
            break;
    }
    return cost;
}
