//
//  ownable.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef ownable_hpp
#define ownable_hpp

#include <iostream>
#include <string>

#include "slot.hpp"


class Player;

class Ownable: public Slot {
    int status;
    const int cost;
    Player *owner;

    // add enum for status sold free mortgaged
public:
    enum {FREE=0, OWNED=1, MORTGAGED=2};
    Ownable(const std::string name, const std::pair<int,int> location, int status, const int cost);
    ~Ownable();

    int getStatus() const;
    int getCost() const;
    Player* getOwner() const;

    void setOwner(Player* owner);

};

#endif /* ownable_hpp */
