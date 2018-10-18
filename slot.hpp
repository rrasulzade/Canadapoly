//
//  slot.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-17.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef slot_hpp
#define slot_hpp

#include <iostream>
#include <string>

class Slot {
    const std::string name;
    const int location;

public:
    Slot(const std::string name, const int location);

};

#endif /* slot_hpp */
