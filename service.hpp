#ifndef service_hpp
#define service_hpp

#include <iostream>
#include <string>
#include "collectible.hpp"

class Service: public Collectible {

public:
	Service(const std::string name, const std::pair<int,int> location, const int cost, const int totalMonoBlocks);
    ~Service();

    std::string getMonopolyBlock() const;
    int getRentalCost(const Player* p) const;
};


#endif /* service_hpp */
