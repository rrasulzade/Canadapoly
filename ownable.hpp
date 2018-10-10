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


class Ownable {
    const string name;
    int status;
    const int cost;
    const int location;
    Player *owner;

    // add enum for status sold free mortgaged
public:
    enum {FREE=0, OWNED=1, MORTGAGED=2};
    Ownable(const string name, int status, const int cost, const int location, Player* player);
    ~Ownable();


};

#endif /* ownable_hpp */
