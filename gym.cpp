//
//  gym.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "gym.hpp"

using namespace std;


Gym:: Gym(const string name, const pair<int,int> location, int status, const int cost): Ownable(name, location, status, cost){}
Gym:: ~Gym(){}
