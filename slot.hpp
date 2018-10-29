//
//  slot.hpp  Abstract class
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
protected:
    const std::string name;
    const std::pair<int,int> location;

public:
    Slot(const std::string name, const std::pair<int,int> location);
    virtual ~Slot();
    virtual int getStatus() const;
    std::pair<int,int> getLocation();
};

#endif /* slot_hpp */
