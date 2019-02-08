#ifndef railroad_hpp
#define railroad_hpp

#include <iostream>
#include <string>
#include "collectible.hpp"


class Railroad : public Collectible {

public:
	Railroad(const std::string name, const std::pair<int,int> location, const int cost, const int totalMonoBlocks);
    ~Railroad();

    std::string getMonopolyBlock() const;
    int getRezFee(int totalRez);
    int getRentalCost(const Player* p) const;
};



#endif /* railroad_hpp */
