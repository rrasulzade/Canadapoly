#ifndef redCross_hpp
#define redCross_hpp

#include <iostream>
#include "slot.hpp"

class RedCross: public Slot{

public:
	RedCross(const std::string name, const std::pair<int,int> location);
    ~RedCross();

};

#endif /* redCross_hpp */
