//
//  ownable.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "ownable.hpp"


Ownable:: Ownable(const string name, int status, const int cost, const int location, Player* player): name(name), status(status), cost(cost), location(location), player(player){}
Ownable:: ~Ownable(){}
