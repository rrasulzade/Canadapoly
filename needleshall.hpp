//
//  needleshall.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-19.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef needleshall_hpp
#define needleshall_hpp

#include <iostream>
#include "slot.hpp"

class Needleshall: public Slot{

public:
    Needleshall(const std::string name, const std::pair<int,int> location);
    ~Needleshall();
};

#endif /* needleshall_hpp */
