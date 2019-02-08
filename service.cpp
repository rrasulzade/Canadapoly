#include "service.hpp"
#include "player.hpp"

using namespace std;


Service::Service(const string name, const pair<int,int> location, const int cost, const int totalMonoBlocks): Collectible(name, location, cost, totalMonoBlocks){}
Service:: ~Service(){}

string Service::getMonopolyBlock() const{
    return "Service";
}

int Service::getRentalCost(const Player* p) const{
    if(this->getOwner()->hasMonopoly(this))
        return 10;
    return 4;
}
