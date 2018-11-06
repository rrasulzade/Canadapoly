//
//  textDisplay.hpp
//  BB7K
//
//  Created by Rasul on 2018-10-08.
//  Copyright © 2018 ***Rasul Rasulzade***. All rights reserved.
//

#ifndef textDisplay_hpp
#define textDisplay_hpp


#include <iostream>
#include <sstream>
#include <vector>

// #include "player.hpp"
// #include "building.hpp"

class Player;
class Slot;

class TextDisplay{
    char **theDisplay;
    std::vector<std::pair<int,int>> playerCurPosition;

public:
    TextDisplay();
    ~TextDisplay();
    void print();
    void updatePlayer(const Player* player, const std::pair<int, int> location);
    void printAssets(const Player*);
    void addOwner(const Player*);
    void updateOwner(const std::pair<int, int> &loc1, const std::pair<int, int> &loc2);
    void updateOwner(const char& ownerSymbol, const std::pair<int, int> &loc);
    void updateMortgage(const std::pair<int, int> location);
    void updateImprovement(const std::pair<int, int>& location, const int& levelOffset) const;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif /* textDisplay_hpp */
