//
//  slot.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-17.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "slot.hpp"

#define NO_STATUS       -1


using namespace std;

Slot::Slot(const string name, const std::pair<int,int> location): name(name), location(location){}

Slot::~Slot(){}

pair<int,int> Slot::getLocation() const{
    return this->location;
}

int Slot::getStatus() const{
    return NO_STATUS;
}

string Slot::getName() const{
    return name;
}
