//
//  gym.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef gym_hpp
#define gym_hpp

#include <stdio.h>
#include "ownable.hpp"

class Gym: public Ownable{

public:
    Gym(const string name, int status, const int cost, const int location, Player* player);
    ~Gym();

};


#endif /* gym_hpp */
