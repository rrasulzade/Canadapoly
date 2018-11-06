//
//  residence.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-09.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef residence_hpp
#define residence_hpp

#include <iostream>
#include <string>
#include "ownable.hpp"


class Residence: public Ownable {

public:
    Residence(const std::string name, const std::pair<int,int> location, int status, const int cost, const int totalMonoBlocks);
    ~Residence();

    std::string getMonopolyBlock() const;
    int getRezFee(int totalRez);
    int getRentalCost(const Player* p) const;
};



#endif /* residence_hpp */
