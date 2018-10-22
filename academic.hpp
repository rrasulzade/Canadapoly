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
    std::string monopoly_block;
    int upgrade_cost;
    int upgrade_level;
    std::initializer_list<int> tuition_costs;
public:
    Academic(const std::string name, const std::pair<int,int> location, int status, const int cost, const std::string monopoly_block, const int upgrade_cost, int upgrade_level, std::initializer_list<int> tuitions);
    ~Academic();


};

#endif /* academic_hpp */
