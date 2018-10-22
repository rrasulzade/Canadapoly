//
//  residence.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "residence.hpp"

using namespace std;

Residence::Residence(const std::string name, const pair<int,int> location, int status, const int cost): Ownable(name, location, status, cost ){}
Residence:: ~Residence(){}
