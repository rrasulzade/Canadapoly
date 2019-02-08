#ifndef chance_hpp
#define chance_hpp

#include <iostream>
#include "slot.hpp"

class Chance : public Slot{

public:
	Chance(const std::string name, const std::pair<int,int> location);
    ~Chance();
};

#endif /* chance_hpp */
