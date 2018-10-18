//
//  academic.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef academic_hpp
#define academic_hpp

#include <iostream>
#include <string>

#include "ownable.hpp"


class Academic: public Ownable{
    int monopoly_block;
    int upgrade_cost;
    int upgrade_level;
    int tuition_costs[6];
public:
    Academic(const std::string name, int status, const int cost, const int location, const int monopoly_block, const int upgrade_cost, int upgrade_level, const int tuitions[]);
    ~Academic();

};

#endif /* academic_hpp */
