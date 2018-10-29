//
//  ownable.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "ownable.hpp"

using namespace std;

Ownable::Ownable(const string name, const pair<int,int> location, int status, const int cost): Slot(name, location), status(status), cost(cost){}

Ownable::~Ownable(){}

int Ownable::getStatus() const{
    return this->status;
}

int Ownable::getCost() const{
    return this->cost;
}

Player* Ownable::getOwner() const{
    return this->owner;
}

void Ownable::setOwner(Player* owner){
    this->owner = owner;
    this->status = Ownable::OWNED;
}
