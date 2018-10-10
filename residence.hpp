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
#include "ownable.hpp"


class Residence: public Ownable {

public:
    Residence(const string name, int status, const int cost, const int location, Player* player);
    ~Residence();
};



#endif /* residence_hpp */
