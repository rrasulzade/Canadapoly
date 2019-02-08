#include "railroad.hpp"
#include "player.hpp"

using namespace std;

Railroad::Railroad(const std::string name, const pair<int,int> location, const int cost, const int totalMonoBlocks): Collectible(name, location, cost, totalMonoBlocks){}
Railroad:: ~Railroad(){}

string Residence::getMonopolyBlock() const {
    return "Railroad";
}

int Railroad::getRentalCost(const Player* p) const{
    int totalRez = this->getOwner()->countOwnedBlocks(this);
    int cost = 0;
    switch (totalRez) {
        case 1:
            cost = 25;
            break;
        case 2:
            cost = 50;
            break;
        case 3:
            cost = 100;
            break;
        case 4:
            cost = 200;
            break;
    }
    return cost;
}
