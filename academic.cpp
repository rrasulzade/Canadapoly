//
//  academic.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "academic.hpp"

#define MAX_IMPROVEMENTS    6

using namespace std;


Academic:: Academic(const string name, const pair<int,int> location, int status, const int cost, const string monopoly_block, const int upgrade_cost, int upgrade_level, initializer_list<int> tuitions) : Ownable(name, location, status, cost),
                                        monopoly_block(monopoly_block),
                                        upgrade_cost(upgrade_cost),
                                        upgrade_level(upgrade_level),
                                        tuition_costs(tuitions)
{

}


Academic:: ~Academic(){}
