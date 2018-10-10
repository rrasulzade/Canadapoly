//
//  academic.cpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#include "academic.hpp"

Academic:: Academic(const string name, int status, const int cost, const int location, Player* player, const int monopoly_block, const int upgrade_cost, int upgrade_level, const int tuitions[]):
                                Ownable(const string name, int status, const int cost, const int location, Player* player), monopoly_block(monopoly_block), upgrade_cost(upgrade_cost), upgrade_level(upgrade_level){

                                    for(unsigned int i = 0; i < 6; i++){
                                        tuition_costs[i] = tuitions[i];
                                    }
                                }
Academic:: ~Academic();
