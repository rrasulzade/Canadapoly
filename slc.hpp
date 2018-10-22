//
//  slc.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-19.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef slc_hpp
#define slc_hpp

#include <iostream>
#include "slot.hpp"

class SLC: public Slot{

public:
    SLC(const std::string name, const std::pair<int,int> location);
    ~SLC();

};

#endif /* slc_hpp */
